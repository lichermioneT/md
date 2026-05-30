#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
using namespace std; 

int main()
{
// 1.创建一个文件描述符，用来进行tcp通信的
  int listesock = socket(AF_INET, SOCK_STREAM, 0);
  if(listesock < 0)
  {
    perror("socket");
    exit(1);
  }

  int opt = 1;
  setsockopt(listesock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);

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
    
    string message;
    while(true)
    {
      char buffer[1024];
      int n = read(sock, buffer, sizeof(buffer) - 1);
      if(n > 0)
      {
        buffer[n] = 0;
        message += buffer;

        size_t pos = message.find("\r\n\r\n");
        if(pos != string::npos)
        {
          cout<< "一个完整的请求" << endl;
          cout<<  message.substr(0, pos) << endl;
        }
        
        message.erase(0);
      }
      else if(n == 0)
      {
        cout<< "客户端已经退出了" << endl;
        close(sock);
        break;
      }
      else 
      {
        cout<< "出现错误了" << endl;
        close(sock);
        break;
      }
    }
  }
  return 0;
}
