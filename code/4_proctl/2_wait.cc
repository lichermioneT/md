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
    }
    exit(0);
#endif
  }

  int status = 0;
  int ret = wait(&status);
  if(ret > 0)
  {
    cout<< "子进程回收成功pid:" << ret << endl;
  }

  cout<< "exit_code:" << ((status>>8)&0xFF) << endl;
  cout<< "sign_number:" << ((status)&0x7F) << endl;



  return 0;
}
