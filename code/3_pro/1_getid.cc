#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{

  cout<< "ppid:" << getppid() << endl;
  cout<< "pid:" << getpid() << endl;

  return 0;
}
