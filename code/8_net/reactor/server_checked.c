#include "server.h"
#include <dirent.h>
#include <sys/sendfile.h>
#include <assert.h>
#include <sys/stat.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdlib.h>

/*
 * 修改说明：
 * 1. 用“// 修改：”标出本次调整的位置。
 * 2. 主要修复：HTTP 响应头发送长度、404 文件名错误、Content-Length 为 -1、
 *    strstr 空指针、非阻塞 recv/sendfile 的基本错误处理。
 * 3. 仍然保持你的原始结构：initListenFd -> epollRun -> acceptClient -> recvHttpRequestt -> parseRequestLine。
 */

// 修改：封装 send，避免 send(cfd, buffer, sizeof buffer, 0) 把整个 4096 字节都发出去。
static int sendAll(int cfd, const char* buf, size_t len)
{
  size_t sent = 0;
  while(sent < len)
  {
    ssize_t n = send(cfd, buf + sent, len - sent, 0);
    if(n > 0)
    {
      sent += n;
    }
    else if(n == -1 && errno == EINTR)
    {
      continue;
    }
    else if(n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
    {
      // 修改：非阻塞 socket 暂时不可写，简单版先停止发送，避免死循环。
      // 更完整的写法应该注册 EPOLLOUT，再继续发送剩余数据。
      return 0;
    }
    else
    {
      perror("send");
      return -1;
    }
  }

  return 0;
}

int initListenFd(unsigned short port)
{
  // 1.创建监听的套接字
  int lfd = socket(AF_INET, SOCK_STREAM, 0);  
  if(lfd == -1)
  {
    perror("socket");
    return -1;
  }

  // 2.端口复用
  int opt = 1;
  int ret = setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);
  if(ret == -1)
  {
    perror("setsockopt");
    close(lfd); // 修改：失败时关闭已经创建的套接字，避免 fd 泄漏。
    return -1;
  }

  // 3.bind
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));  // 修改：初始化结构体，避免未初始化字段影响 bind。
  addr.sin_family = AF_INET;       // 地址协议
  addr.sin_addr.s_addr = INADDR_ANY; // IP：任意网卡地址
  addr.sin_port = htons(port);       // 端口：主机序转网络序

  ret = bind(lfd, (struct sockaddr*)&addr, sizeof(addr)); 
  if(ret == -1)
  {
    perror("bind");
    close(lfd); // 修改：失败时关闭监听 fd。
    return -1;
  }

  // 4.设置监听
  // listen 的第二个参数表示已完成连接队列的参考长度，不是“最多只能连接 128 个客户端”。
  ret = listen(lfd, 128);
  if(ret == -1)
  {
    perror("listen");
    close(lfd); // 修改：失败时关闭监听 fd。
    return -1;
  }

  // 返回监听 fd
  return lfd;
}

int epollRun(int lfd)
{
  // 1.创建 epoll 实例
  int epfd = epoll_create1(0); // 修改：epoll_create1 比 epoll_create(1) 更推荐。
  if(epfd == -1)
  {
    perror("epoll_create1");
    return -1;
  }

  // 2.lfd 上树
  struct epoll_event ev;  
  memset(&ev, 0, sizeof(ev)); // 修改：初始化 epoll_event。
  ev.data.fd = lfd;           // 监听套接字
  ev.events = EPOLLIN;        // 读事件

  int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
  if(ret == -1)
  {
    perror("epoll_ctl");
    close(epfd); // 修改：失败时关闭 epoll fd。
    return -1;
  }

  // 3.循环检测事件
  struct epoll_event evs[1024];
  int size = sizeof(evs) / sizeof(struct epoll_event);

  while(1)
  {
    int num = epoll_wait(epfd, evs, size, -1);
    if(num == -1)
    {
      if(errno == EINTR)
      {
        continue; // 修改：被信号打断时继续等待。
      }

      perror("epoll_wait");
      break;
    }

    for(int i = 0; i < num; ++i)
    {
      int fd = evs[i].data.fd;
      if(fd == lfd)
      {
        // 建立新的连接
        int ret = acceptClient(lfd, epfd);
        if(ret != 0)
        {
          perror("acceptClient");
        }
      }
      else 
      {
        // 通信 fd：读取并处理 HTTP 请求
        recvHttpRequestt(fd, epfd);
      }
    }
  }

  close(epfd); // 修改：理论上死循环很少走到这里，但保留资源释放。
  return 0;
}

int acceptClient(int lfd, int epfd)
{
  // 1.建立连接
  int cfd = accept(lfd, NULL, NULL);
  if(cfd == -1)
  {
    perror("accept");
    return -1;
  }

  // 2.设置为非阻塞模式
  int flag = fcntl(cfd, F_GETFL);
  if(flag == -1)
  {
    perror("fcntl F_GETFL");
    close(cfd);
    return -1;
  }

  flag |= O_NONBLOCK;
  if(fcntl(cfd, F_SETFL, flag) == -1)
  {
    perror("fcntl F_SETFL");
    close(cfd);
    return -1;
  }

  // 3.放到 epoll 树上
  struct epoll_event ev;  
  memset(&ev, 0, sizeof(ev)); // 修改：初始化 epoll_event。
  ev.data.fd = cfd;           // 客户端通信套接字
  ev.events = EPOLLIN | EPOLLET; // ET 模式：读事件必须一次性读到 EAGAIN。

  // 4.epoll_ctl 添加到树
  int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
  if(ret == -1)
  {
    perror("epoll_ctl");
    close(cfd); // 修改：添加失败时关闭客户端 fd。
    return -1;
  }

  return 0;
}

int recvHttpRequestt(int cfd, int epfd)
{
  char buffer[4096] = {0};
  char temp[1024] = {0};
  int total = 0;
  int overflow = 0;

  while(1)
  {
    ssize_t len = recv(cfd, temp, sizeof(temp), 0);
    if(len > 0)
    {
      // 修改：防止请求数据超过 buffer 导致越界。
      int remain = (int)sizeof(buffer) - 1 - total;
      if(remain > 0)
      {
        int copyLen = len < remain ? (int)len : remain;
        memcpy(buffer + total, temp, copyLen);
        total += copyLen;

        if(copyLen < len)
        {
          overflow = 1;
        }
      }
      else
      {
        overflow = 1;
      }
    }
    else if(len == 0)
    {
      // 客户端断开连接
      epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, NULL);
      close(cfd);
      return 0;
    }
    else
    {
      if(errno == EINTR)
      {
        continue;
      }

      if(errno == EAGAIN || errno == EWOULDBLOCK)
      {
        // ET 模式下读到 EAGAIN，说明本轮数据已经读完。
        break;
      }

      perror("recv");
      epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, NULL);
      close(cfd);
      return -1;
    }
  }

  if(total <= 0)
  {
    return 0;
  }

  buffer[total] = '\0';

  if(overflow)
  {
    // 修改：请求头太大时返回 413，避免继续解析被截断的数据。
    const char* body = "<html><body><h1>413 Payload Too Large</h1></body></html>";
    sendHeadMsg(cfd, 413, "Payload Too Large", getFileType(".html"), strlen(body));
    sendAll(cfd, body, strlen(body));

    epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, NULL);
    close(cfd);
    return -1;
  }

  // 修改：解析请求行前必须判断 strstr 是否找到 "\r\n"。
  char* pt = strstr(buffer, "\r\n");
  if(pt == NULL)
  {
    const char* body = "<html><body><h1>400 Bad Request</h1></body></html>";
    sendHeadMsg(cfd, 400, "Bad Request", getFileType(".html"), strlen(body));
    sendAll(cfd, body, strlen(body));

    epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, NULL);
    close(cfd);
    return -1;
  }

  *pt = '\0'; // 修改：把请求行单独截出来，传给 parseRequestLine。
  parseRequestLine(buffer, cfd);

  // 修改：当前代码没有实现 HTTP keep-alive，也没有保存写缓冲区，所以处理完一个请求后主动关闭连接。
  epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, NULL);
  close(cfd);

  return 0;
}

int parseRequestLine(const char* line, int cfd)
{
  char method[12] = {0};
  char path[1024] = {0};

  // GET /index.html HTTP/1.1
  // 修改：给 sscanf 增加宽度限制，并判断解析结果。
  if(sscanf(line, "%11s %1023s", method, path) != 2)
  {
    const char* body = "<html><body><h1>400 Bad Request</h1></body></html>";
    sendHeadMsg(cfd, 400, "Bad Request", getFileType(".html"), strlen(body));
    sendAll(cfd, body, strlen(body));
    return -1;
  }

  printf("请求方法:%s, 请求路径:%s\n", method, path);

  if(strcasecmp(method, "GET") != 0)
  {
    // 修改：非 GET 请求返回 405，而不是直接 return 导致客户端无响应。
    const char* body = "<html><body><h1>405 Method Not Allowed</h1></body></html>";
    sendHeadMsg(cfd, 405, "Method Not Allowed", getFileType(".html"), strlen(body));
    sendAll(cfd, body, strlen(body));
    return -1;
  }

  // 修改：简单防御目录穿越，例如请求 /../../etc/passwd。
  if(strstr(path, "..") != NULL)
  {
    const char* body = "<html><body><h1>403 Forbidden</h1></body></html>";
    sendHeadMsg(cfd, 403, "Forbidden", getFileType(".html"), strlen(body));
    sendAll(cfd, body, strlen(body));
    return -1;
  }

  // 处理客户端请求的静态资源：目录或者普通文件
  const char* file = NULL; // 修改：使用 const char*，因为这里不修改字符串内容。
  if(strcmp(path, "/") == 0)
  {
    file = "./";
  }
  else 
  {
    file = path + 1;
  }

  struct stat st;
  int ret = stat(file, &st);
  if(ret == -1)
  {
    // 修改：原代码写成了 404.htl，且 Content-Length 为 -1。这里直接返回简单 404 页面。
    const char* body = "<html><body><h1>404 Not Found</h1></body></html>";
    sendHeadMsg(cfd, 404, "Not Found", getFileType(".html"), strlen(body));
    sendAll(cfd, body, strlen(body));
    return 0;
  }

  if(S_ISDIR(st.st_mode))
  {
    // 目录列表长度事先不好计算，sendHeadMsg 中 length < 0 时不发送 Content-Length。
    sendHeadMsg(cfd, 200, "OK", getFileType(".html"), -1);
    sendDir(file, cfd);
  }
  else 
  {
    // 普通文件可以直接用 stat 得到 Content-Length。
    sendHeadMsg(cfd, 200, "OK", getFileType(file), (int)st.st_size);
    sendFile(file, cfd);
  }

  return 0;
}

int sendFile(const char* fileName, int cfd)
{
  int fd = open(fileName, O_RDONLY);
  if(fd == -1)
  {
    // 修改：不要使用 assert(fd > 0)。open 失败属于运行时错误，应该正常处理。
    perror("open");
    return -1;
  }

#if 0
  while(1)
  {
    char buffer[1024];

    int len = read(fd, buffer, sizeof buffer);
    if(len > 0)
    {
      sendAll(cfd, buffer, len); // 修改：使用 sendAll，避免部分发送问题。
    }
    else if(len == 0)
    {
      break;
    }
    else 
    {
      if(errno == EINTR)
      {
        continue;
      }
      perror("read");
      break;
    }
  }
#else 
  // sendfile 是零拷贝发送文件的接口。
  off_t size = lseek(fd, 0, SEEK_END);
  if(size == -1)
  {
    perror("lseek");
    close(fd);
    return -1;
  }

  lseek(fd, 0, SEEK_SET);
  off_t offset = 0;

  while(offset < size)
  {
    // 修改：第三个参数 offset 会被 sendfile 自动更新；第四个参数应该是剩余字节数。
    ssize_t ret = sendfile(cfd, fd, &offset, size - offset);
    if(ret > 0)
    {
      continue;
    }
    else if(ret == 0)
    {
      break;
    }
    else 
    {
      if(errno == EINTR)
      {
        continue;
      }

      if(errno == EAGAIN || errno == EWOULDBLOCK)
      {
        // 修改：非阻塞 socket 可能暂时不可写。完整方案应结合 EPOLLOUT。
        break;
      }

      perror("sendfile");
      break;
    }
  }
#endif

  close(fd);
  return 0;
}

int sendHeadMsg(int cfd, int status, const char* descr, const char* type, int length)
{
  char buffer[4096] = {0};
  int offset = 0;

  // 修改：http/1.1 改成标准写法 HTTP/1.1。
  offset += snprintf(buffer + offset, sizeof(buffer) - offset,
                     "HTTP/1.1 %d %s\r\n", status, descr);

  // 响应头
  offset += snprintf(buffer + offset, sizeof(buffer) - offset,
                     "Content-Type: %s\r\n", type);

  // 修改：length < 0 时不发送 Content-Length，避免出现 Content-Length: -1。
  if(length >= 0)
  {
    offset += snprintf(buffer + offset, sizeof(buffer) - offset,
                       "Content-Length: %d\r\n", length);
  }

  // 修改：当前服务器处理完请求会关闭连接，所以明确告诉浏览器 Connection: close。
  offset += snprintf(buffer + offset, sizeof(buffer) - offset,
                     "Connection: close\r\n\r\n");

  // 修改：只发送实际响应头长度，不能发送 sizeof(buffer)。
  sendAll(cfd, buffer, strlen(buffer));
  return 0;
}

const char* getFileType(const char* name)
{
    // a.jpg a.mp4 a.html
    // 自右向左查找 '.' 字符，如不存在返回 NULL。
    const char* dot = strrchr(name, '.');
    if (dot == NULL)
      return "text/plain; charset=utf-8"; // 纯文本
    if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
      return "text/html; charset=utf-8";
    if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
      return "image/jpeg";
    if (strcmp(dot, ".gif") == 0)
      return "image/gif";
    if (strcmp(dot, ".png") == 0)
      return "image/png";
    if (strcmp(dot, ".css") == 0)
      return "text/css";
    if (strcmp(dot, ".au") == 0)
      return "audio/basic";
    if (strcmp(dot, ".wav") == 0)
      return "audio/wav";
    if (strcmp(dot, ".avi") == 0)
      return "video/x-msvideo";
    if (strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt") == 0)
      return "video/quicktime";
    if (strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe") == 0)
      return "video/mpeg";
    if (strcmp(dot, ".vrml") == 0 || strcmp(dot, ".wrl") == 0)
      return "model/vrml";
    if (strcmp(dot, ".midi") == 0 || strcmp(dot, ".mid") == 0)
      return "audio/midi";
    if (strcmp(dot, ".mp3") == 0)
      return "audio/mpeg";
    if (strcmp(dot, ".ogg") == 0)
      return "application/ogg";
    if (strcmp(dot, ".pac") == 0)
      return "application/x-ns-proxy-autoconfig";

    return "text/plain; charset=utf-8";
}

int sendDir(const char* dirName, int cfd)
{
  char buf[4096] = {0};

  // 修改：使用 snprintf，降低缓冲区溢出的风险。
  snprintf(buf, sizeof(buf),
           "<html><head><meta charset=\"utf-8\"><title>%s</title></head>"
           "<body><h1>Index of %s</h1><table>",
           dirName, dirName);
  sendAll(cfd, buf, strlen(buf));

  struct dirent** namelist = NULL;
  int n = scandir(dirName, &namelist, NULL, alphasort);
  if(n == -1)
  {
    perror("scandir");
    return -1;
  }

  for(int i = 0; i < n; ++i)
  {
    // 1.取出名字
    char* name = namelist[i]->d_name;

    // 2.判断是目录还是普通文件
    char subPath[1024] = {0};
    snprintf(subPath, sizeof(subPath), "%s/%s", dirName, name);

    struct stat st;
    if(stat(subPath, &st) == -1)
    {
      perror("stat");
      free(namelist[i]);
      continue;
    }

    memset(buf, 0, sizeof(buf));

    if(S_ISDIR(st.st_mode))
    {
      // 修改：补全 </a> 和 </tr> 标签。
      snprintf(buf, sizeof(buf),
               "<tr><td><a href=\"%s/\">%s/</a></td><td>%ld</td></tr>",
               name, name, (long)st.st_size);
    }
    else 
    {
      snprintf(buf, sizeof(buf),
               "<tr><td><a href=\"%s\">%s</a></td><td>%ld</td></tr>",
               name, name, (long)st.st_size);
    }

    sendAll(cfd, buf, strlen(buf));
    free(namelist[i]);
  }

  snprintf(buf, sizeof(buf), "</table></body></html>");
  sendAll(cfd, buf, strlen(buf));

  free(namelist);

  return 0;
}
