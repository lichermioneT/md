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
  }
}

int main()
{

  thread t(func, 666, "lichermixss");
  t.join(); 

  return 0;
}
