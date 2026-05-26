#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "server.h"

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    printf("./a.out port path\n");
    return -1;
  }
  
  unsigned short port = atoi(argv[1]);
  chdir(argv[2]);

// 初始化监听套接字
  int lfd  = initListenFd(port); // 不建议bind 5000一下的端口

// 启动服务器程序
  epollRun(lfd);


  return 0;
}
