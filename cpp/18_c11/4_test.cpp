#include <iostream>
#include <string>
using namespace std;

int main()
{
  int x = 10;

  auto f = [x]()->void
  {
    cout<< "x:" << x <<endl;
  };

  f();

  x = 1000;
  f();

  return 0;
}

