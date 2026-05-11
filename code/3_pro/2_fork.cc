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
    cout<< "ppid:" << getppid() << ":" << "pid:" << getpid() <<endl;
  }
  else 
  {
    cout<< "ppid:" << getppid() << ":" << "pid:" << getpid() <<endl;
  }

  return 0;
}
