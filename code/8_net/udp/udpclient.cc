#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
using namespace std; 


int main(int argc, char* argv[])
{

// ip和端口
  string serverip = argv[1];
  uint16_t serverport = atoi(argv[2]);

  if(argc != 3)
  {
    cout<< "usage: ./a.out ip port" <<endl;
  }
// 1.创建一个文件描述符，用来进行udp通信的
  // AF_INET:通信的协议
  int socketfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(socketfd < 0)
  {
    perror("socket");
    exit(1);
  }

  struct sockaddr_in server;
  memset(&server, 0, sizeof(server));
  
// 2.服务端的信息, 
  server.sin_family = AF_INET;
  server.sin_port = htons(serverport);
  inet_pton(AF_INET, serverip.c_str(), &server.sin_addr);
  

// 3.开始发送消息
  string message;
  char buffer[1024];
  while(true)
  {
    cout<<"enter:";
    cin>>message;
    sendto(socketfd, message.c_str(), message.size(), 0, (struct sockaddr*)&server,  sizeof(server));
    
    recvfrom(socketfd, buffer, sizeof(buffer), 0, nullptr, 0);
    cout<< buffer << endl;
  }
  return 0;
}
