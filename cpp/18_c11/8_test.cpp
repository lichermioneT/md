#include <thread>
#include <iostream>
#include <unistd.h>
using namespace std;

void func(int x, const string& s)
{
  int n = 10;
  while(n)
  {
    cout<< "this is cpp thread:" << x << s << n-- <<endl;
    sleep(1);
  }
}

int main()
{

  thread t(func, 666, "lichermixss");
  
  int x = 5;
  while(x)
  {
    cout<< "main:" << x-- <<endl;
    sleep(1);
  }

  t.join();

  return 0;
}
