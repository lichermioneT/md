#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
using namespace std; 

int main()
{
// 1.创建一个文件描述符，用来进行udp通信的
  // AF_INET:通信的协议
  int socketfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(socketfd < 0)
  {
    perror("socket");
    exit(1);
  }

  struct sockaddr_in local;
  memset(&local, 0, sizeof local);

// 2.服务器的信息需要设置内核里面的
  local.sin_family = AF_INET;
  local.sin_addr.s_addr = htonl(INADDR_ANY);
  local.sin_port = htons(8080);
  
  // 2.1bind进内核里面去的
  int n = bind(socketfd, (struct sockaddr*)&local, sizeof local);
  if(n == -1)
  {
    perror("bind");
    exit(1);
  }

// 3.开始通信
  
  char buffer[1024];
  char ip_str[INET_ADDRSTRLEN];
  while(true)
  {
    struct sockaddr_in client;
    socklen_t len = sizeof client;

    ssize_t s  = recvfrom(socketfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client, &len);
    if(s > 0)
    {
      buffer[s] = 0;
      // 客户端的端口和ip
      uint16_t port = ntohs(client.sin_port);
      inet_ntop(AF_INET, &client.sin_addr.s_addr, ip_str, sizeof(ip_str)); 
      cout<<"ip:" << ip_str << "-" << "port:" << port << " 发的信息:" << buffer << endl;

      string echo = "客户端您的信息已经收到了，祝您生活愉快，天天开心。";
      sendto(socketfd, echo.c_str(), echo.size(), 0, (struct sockaddr*)&client, sizeof(client));
    }
  }
  return 0;
}
