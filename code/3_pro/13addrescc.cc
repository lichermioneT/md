#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
  int value = 100;
  pid_t id = fork();
  if(id == -1)
  {
    exit(1);
  }
  
  if(id == 0)
  {
    while(value > 0)
    {
      cout<< "child process,value:" << value << "  &value:" << &value <<endl;
      value -= 2;
      sleep(1);
    }
  }
  else 
  {
    while(value > 0)
    {
      cout<< "paren process,value:" << value << "  &value:" << &value <<endl;
      value -= 3;
      sleep(1);
    }
  }



  return 0;
}
