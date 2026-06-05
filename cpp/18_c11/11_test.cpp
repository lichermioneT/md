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
  t.detach();
  
  if(t.joinable())
  {
    cout<< "线程可以等待" <<endl;
    t.join();

  }
  else 
  {
    cout<< "线程不可以等待" <<endl;
    sleep(10);
  }

  return 0;
}
