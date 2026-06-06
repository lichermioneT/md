#include <iostream>
#include <errno.h>
using namespace std;

int Div(int x, int y)
{
  if(y == 0)
  {
    throw "Div by zero";
  }

  return x / y;
}

int main()
{
  try 
  {
    int ret = Div(10, 0);
    cout<< ret <<endl;
  }
  catch(const char* msg)
  {
    cout<< "捕获异常的信息：" << msg <<endl;
  }
  return 0;
}
