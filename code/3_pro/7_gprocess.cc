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
    while(true)
    {
      sleep(1);
    }
  }
  else 
  {
    while(true)
    {
      sleep(1); // 父进程一直不退出
      exit(1);
    } 
  }

  return 0;
}
