#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{
  pid_t id = fork();
  if(id == -1)
  {
    exit(2);
  }

  if(id == 0)
  {
    sleep(3); // 3秒后变成僵尸进程
    exit(0);
  }
  else 
  {
    while(true)
    {
      sleep(1); // 父进程一直不退出
    } 
  }

  return 0;
}
