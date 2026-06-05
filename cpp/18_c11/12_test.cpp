#include <thread>
#include <iostream>
#include <unistd.h>
using namespace std;

void func(int& x, string& s)
{
  x += 1;
  s += ": lic";
}

int main()
{
  int a{10};
  string s{"hell"};
  cout<< "before:" <<endl;
  cout<< a <<endl;
  cout<< s <<endl;

  thread t(func, ref(a), ref(s));
  t.join();

  cout<< "after:" <<endl;
  cout<< a <<endl;
  cout<< s <<endl;
  return 0;
}
