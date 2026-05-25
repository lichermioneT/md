#include <iostream>
#include <string>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <pthread.h>
using namespace std; 

struct Info 
{
  pthread_t tid;
  int sock;
};
void* handmessage(void* arg)
{
  struct Info* info = static_cast<struct Info*>(arg);   
  char buffer[1024];
  string message;
  while(true)
  {
    int n = read(info->sock, buffer, sizeof(buffer));

    if(n > 0)
    {
      message.append(buffer, n);
      
      while(true)
      {
        // 1.先判断请求头师傅完整的
        size_t pos = message.find("\r\n\r\n");
        if(pos == string::npos)
        {
          break;
        }

        // 2.处理请求头的完整部分信息
        string header = message.substr(0, pos);
        
         // body 的起始位置
        size_t bodyStart = pos + 4;
        
        // 3. 判断是否有 Content-Length
        size_t contpos = header.find("Content-Length:");

        // 4. 处理 POST / 带请求体的情况
        if(contpos != string::npos)
        {
          contpos += string("Content-Length:").size();

          size_t contposend = header.find("\r\n", contpos);

          string lenStr;
          if(contposend == string::npos)
          {
            lenStr = header.substr(contpos);
          }
          else
          {
            lenStr = header.substr(contpos, contposend - contpos);
          }

          int contentLength = atoi(lenStr.c_str());

          // 判断 body 是否已经接收完整
          if(message.size() < bodyStart + contentLength)
          {
            break;
          }

          string body = message.substr(bodyStart, contentLength);

          cout << "post请求的完整请求:" << endl;
          cout << header << endl;
          cout << "请求体:" << endl;
          cout << body << endl;

          // 删除已经处理完的完整 HTTP 请求
          message.erase(0, bodyStart + contentLength);
        }
        // 5. 处理 GET / 没有请求体的情况
        else
        {
          cout << "get请求的完整请求:" << endl;
          cout << header << endl;
          // 删除已经处理完的请求头，包括 \r\n\r\n
          message.erase(0, pos + 4);
        }
      }
    } 
  }

  close(info->sock);

  return nullptr;
}


int main()
{
// 1.创建一个文件描述符，用来进行udp通信的
  int listesock = socket(AF_INET, SOCK_STREAM, 0);
  if(listesock < 0)
  {
    perror("socket");
    exit(1);
  }

  int opt = 1;
  if(setsockopt(listesock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
  {
    perror("setsockopt");
    return -1;
  }

  struct sockaddr_in local;
  memset(&local, 0, sizeof local);

// 2.服务器的信息需要设置内核里面的
  local.sin_family = AF_INET;
  local.sin_addr.s_addr = htonl(INADDR_ANY);
  local.sin_port = htons(8080);
  
  // 2.1bind进内核里面去的
  // 设置进内核：方便客户端进行寻找的
  int n = bind(listesock, (struct sockaddr*)&local, sizeof local);
  if(n == -1)
  {
    perror("bind");
    exit(1);
  }

// 3.开始进行建听，客户端到来的链接
  // 3.1这里做的存储128个三次握手的链接。
  n = listen(listesock, 128); 

// 4.建听成功，我们就可以拿上来
    
  for(;;)
  {
    struct sockaddr_in peer;
    socklen_t len = sizeof peer;
    
    // 4.1我们通过监听套接字，拿取到客户端的链接了
    int sock = accept(listesock, (struct sockaddr*)&peer, &len);
    if(sock < 0)
    {
      perror("accept");
      exit(1);
    }
     
    struct Info* info = new struct Info;
    info->sock = sock;

    int n = pthread_create(&info->tid, nullptr, handmessage, info);
    if(n < 0)
    {
      perror("pthread_create");
      exit(1);
    }
    pthread_detach(info->tid);

  }
  return 0;
}
