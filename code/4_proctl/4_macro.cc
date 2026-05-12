#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
using namespace std;

#define opt 2

int main()
{

  pid_t id = fork();
  if(id == -1)
  {
    perror("fork");
    exit(2);
  }
  
  if(id == 0)
  {
#if op1 == 1

    cout<< "子进程" << endl;
    exit(21);

#else 
    while(true)
    {
      cout<< "子进程pid:" << getpid() << endl;
      sleep(1);
      exit(22);
    }
    exit(0);
#endif
  }

  int status = 0;
  while(true)
  {
    int ret = waitpid(id, &status, WNOHANG);
    if(ret == 0)
    {
      cout<< "本次循环没有等到子进程" << endl;
      sleep(1);
    }
    else if(ret > 0)
    {
      cout<< "子进程回收成pid:" << ret << endl;
      
      if(WIFEXITED(status))
      {
        cout<< "exit_code:" << WEXITSTATUS(status) << endl;
      }
      else if(WIFSIGNALED(status))
      {
        cout<< "sig_num:" << WTERMSIG(status) << endl;
      }

      return 12;
    }
    else 
    {
      cout<< " 运行出错了" << endl;
      return 1;
    }
  }
  return 0;
}
