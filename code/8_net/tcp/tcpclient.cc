#include <iostream>
#include <unistd.h>
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
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
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
 // 2.1客户端需要知道服务端的信息，这里的connet就是为了和服务器建立三次握手 
 int n = connect(socketfd, (struct sockaddr*)&server, sizeof(server));
 if(n == -1)
 {
   perror("connect");
   exit(1);
 }

// 3.开始发送消息
  string message;
  while(true)
  {
    cout<<"enter:";
    getline(cin, message);
    if(strcmp(message.c_str(), "q") == 0)
    {
      cout<< "客户端退出" << endl;
      break;
    }
    write(socketfd, message.c_str(), message.size());
  }
  return 0;
}
