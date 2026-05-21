#pragma once 

#include <fcntl.h>
#include <unistd.h>
#include <cassert>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

int main()
{
  umask(0);
// 1.客户端创建一个命名管道文件，权限是600
  int n = mkfifo("name_pipe", 0600);
  if(n != -1)
  {
    perror("mkfifo");
    return -1;
  }

// 2.这打开文件，然后
  int rfd = open("name_pipe", O_RDONLY);
  if(rfd == -1)
  {
    perror("open");
  }

  



  return 0;
}
