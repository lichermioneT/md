#include <iostream>
#include <string>
using namespace std;

inline int add(int x, int y)
{
  return  x + y;
}

int main()
{
  int ret = add(2, 4);
  cout<< ret <<endl;

  return 0;
}
