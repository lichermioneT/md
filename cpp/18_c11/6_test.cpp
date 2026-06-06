#include <iostream>
#include <string>
using namespace std;

int main()
{
  int x = 10;

  auto f = [x]() mutable ->void 
  {
    x = 77777;
    cout<< "x:" << x <<endl;
  };
  
  f();


  cout<< "x:" << x <<endl;
  return 0;
}

