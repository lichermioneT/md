#include <iostream>
#include <cerrno>
#include <cstring>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main()
{
// 1.用户层创建一个唯一的标识符
    key_t key = ftok("lic", 210);
    if(key < 0)
    {
      perror("ftok");
      return -1;
    }

// 2.把key设置进，内核里面去的，然后给用户返回一个 句柄
//   同时设置空间的大小和权限
  int shmid = shmget(key, 1024, IPC_CREAT);
  if(shmid < 0)
  {
    perror("shmget");
    return -2;
  }

// 3.共享内存空间的地址，连接到进程地址空间的
  char* mem = (char*)shmat(shmid, nullptr, 0);
  if((long long)mem == -1L)
  {
    perror("shmat");
    return -1;
  }
  
  int cnt = 0;
  while(true)
  {
    snprintf(mem, 1024, "message %d\n", cnt++);
    sleep(1);
  }

// 4.断开链接
   shmdt(mem);


  return 0;
}
