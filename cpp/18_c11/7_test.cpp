#include <thread>
#include <iostream>
#include <unistd.h>
using namespace std;

void func()
{
  int n = 10;
  while(n)
  {
    cout<< "this is cpp thread:" << n-- <<endl;
    sleep(1);
  }
}

int main()
{

  thread t(func);
  
  int x = 5;
  while(x)
  {
    cout<< "main:" << x-- <<endl;
    sleep(1);
  }

  t.join();

  return 0;
}
