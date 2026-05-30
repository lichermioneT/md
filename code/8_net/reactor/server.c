#include "server.h"
#include <dirent.h>
#include <sys/sendfile.h>
#include <assert.h>
#include <sys/stat.h>
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
    return -1;
  }

  // 3.bind
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;  // 地址协议
  addr.sin_addr.s_addr = INADDR_ANY; // ip. 0就是任意的地址。任意的网卡信息。
  addr.sin_port = htons(port);     // port.  端口不建议设置死了

  // 设置今年内核里面
  ret = bind(lfd, (struct sockaddr*)&addr, sizeof(addr)); 
  if(ret == -1)
  {
    perror("bind");
    return -1;
  }
  
  // 4.设置监听
  // 一次性可以接受多少个三次握手的链接数目
  ret = listen(lfd, 128);
  if(ret == -1)
  {
    perror("listen");
    return -1;
  }

  // 返回fd
  return lfd;
}

int epollRun(int lfd)
{
  // 1.创建epoll示例
  int epfd = epoll_create(1); // 目前参数已经被弃用了的
  if(epfd == -1)
  {
    perror("epoll_create");
    return -1;
  }

  // 2.lfd上树
  struct epoll_event ev;  
  ev.data.fd = lfd;    // 监听套接字
  ev.events = EPOLLIN; // 读事件

  int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
  if(ret == -1)
  {
    perror("epoll_ctl");
    return -1;
  }

  // 3.检查。死循环
  struct epoll_event evs[1024];
  size_t size = sizeof(evs) / sizeof(struct epoll_event);

  while(1)
  {
    int num = epoll_wait(epfd, evs, size, -1); // -1阻塞等待。 有事件就绪才准备才返回的
    for(int i = 0; i < num; ++i)
    {
      int fd = evs[i].data.fd;
      if(fd == lfd)
      {
        // 建立新的链接。listen已经监听到客户端的链接来了的 
        int ret = acceptClient(lfd, epfd);
        if(ret != 0)
        {
          perror("acceptClient");
        }
      }
      else 
      {
        // 通信的链接的,如何读取数据的
        recvHttpRequestt(fd, epfd);
      }
    }
  }
}

int acceptClient(int lfd, int epfd)
{
  // 1.建立链接
  int cfd  = accept(lfd, NULL, NULL);
  if(cfd == -1)
  {
    perror("accept");
    return -1;
  }

  // 2.设置为非阻塞模式的
  int flag = fcntl(cfd, F_GETFL);
  flag |= O_NONBLOCK;
  fcntl(cfd, F_SETFL, flag);

  // 3.放到epoll树上
  struct epoll_event ev;  
  ev.data.fd = cfd;    // 监听套接字
  ev.events = EPOLLIN | EPOLLET; // 读事件

  // 4.epoll_ctl放到树上去的
  int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
  if(ret == -1)
  {
    perror("epoll_ctl");
    return -1;
  }
  
  return 0;
}

int recvHttpRequestt(int cfd, int epfd)
{
  char  buffer[4096] = {0};
  char  temp[1024] = {0};
  int len = 0;
  int total = 0;

  while((len = recv(cfd, temp, sizeof temp, 0)) > 0)
  {
    if(total + len < sizeof buffer)
    {
      memcpy(buffer + total, temp, len);
    }

    total += len;
  }
  
  // 判断是否接收完毕的
  if(len == -1 && errno == EAGAIN)
  {
    // 解析请求行
    char* pt = strstr(buffer, "\r\n");
    int reqLen = pt - buffer;

    buffer[reqLen] = '\0';

    parseRequestLine(buffer, cfd);
  }
  else if(len == 0)
  {
    // 客户端断开链接的
    // 下树
    epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, NULL);
    // 关闭
    close(cfd);
  }
  else 
  {
    perror("recv");
  }

  return 0;
}

int parseRequestLine(const char* line, int cfd)
{
  char method[12];
  char path[1024];
  
  // GET /index.html HTTP/1.1
  sscanf(line,"%[^ ] %[^ ]", method, path);

  printf("请求的路径:%s\n", path);

  if(strcasecmp(method, "get") != 0)
  {
    return -1;
  }

  // 处理客户端的静态资源(目录或者静态资源)
  
  const char* file = NULL;
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
    // 文件不存在的，回复404
    sendHeadMsg(cfd, 404, "Not Found", getFileType(".html"), -1); // -1我不知道，自己去读
    sendFile("404.html", cfd);
    return 0;
  }

  if(S_ISDIR(st.st_mode))
  {
    // 把这个目录发送给客户端
    sendHeadMsg(cfd, 200, "OK", getFileType(".html"), -1); // -1我不知道，自己去读
    sendDir(file, cfd);
  }
  else 
  {
    // 把文件的内容发送客户端
    sendHeadMsg(cfd, 200, "OK", getFileType(file), st.st_size); // -1我不知道，自己去读
    sendFile(file, cfd);
  }

  close(cfd);
  return 0;
}


int sendFile(const char* fileName, int cfd)
{
  int fd = open(fileName, O_RDONLY);
  assert(fd > 0);

#if 0
  while(1)
  {
    char buffer[1024];

    int len = read(fd, buffer, sizeof buffer);
    if(len > 0)
    {
      send(cfd, buffer, len, 0); // 发送数据给客户端。可能服务器还在慢慢渲染。需要时间的。
      usleep(10);  // 休眠一下，这很重要的。 接收端喘口气。
    }
    else if(len == 0)
    {
      break;
    }
    else 
    {
      perror("read");
    }
  }
#else 
  // sendFile号称零拷贝函数的
  
  int size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);

  off_t offset = 0;

  while(offset < size)
  {
     int ret =  sendfile(cfd, fd, &offset, size - offset);
     printf("ret: value:%d\n", ret);

     if(ret == -1 && errno == EAGAIN)
     {
       printf("没有数据的...\n");
     }
  }

#endif
  close(fd);
  return 0;
}

int sendHeadMsg(int cfd, int status, const char* descr, const char* type, int length)
{
  char buffer[4096];
  // 状态行
  sprintf(buffer, "http/1.1 %d %s\r\n", status, descr);

  // 响应头
  sprintf(buffer + strlen(buffer), "content-type: %s\r\n", type);
  sprintf(buffer + strlen(buffer), "content-length: %d\r\n\r\n", length);

  send(cfd, buffer, strlen(buffer), 0);
  return 0;
}

const char* getFileType(const char* name)
{
    // a.jpg a.mp4 a.html
    // 自右向左查找‘.’字符，如不存在返回NULL
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
  char buf[4096];
  sprintf(buf, "<html><head><title>%s</title></head><body><table>", dirName);

  struct dirent** namelist;
  int n = scandir(dirName, &namelist, NULL, alphasort);
  for(int i = 0; i < n; ++i)
  {
    // 1.取出名字。
    char* name = namelist[i]->d_name;

    // 2.判断是不是文件
    char subPath[1024];
    sprintf(subPath, "%s/%s", dirName, name);
    struct stat st;
    stat(subPath, &st);

    if(S_ISDIR(st.st_mode))
    {
      sprintf(buf + strlen(buf), "<tr><td><a href = \"%s/\">%s</td><td>%ld</td><tr>", name,name, st.st_size);
    }
    else 
    {
      sprintf(buf + strlen(buf), "<tr><td><a href = \"%s\">%s</td><td>%ld</td><tr>", name,name, st.st_size);
    }

    send(cfd, buf, strlen(buf), 0);
    memset(buf,0, sizeof buf);
    free(namelist[i]);
  }

  sprintf(buf + strlen(buf), "</table></body></html>");
  send(cfd, buf, strlen(buf), 0);

  free(namelist);

  return 0;
}


