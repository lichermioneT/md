#include <iostream>
using namespace std;

// 函数可以再指定一个默认的参数。
// 1.不传就使用默认的
// 2.传入就使用传入的
// 3.声明给了，实现就不给的
int add1(int x, int y, int z = 33)
{
  return  x + y + z;
}

int add2(int x, int y = 10, int z = 33)
{
  return  x + y + z;
}

int add3(int x = 2, int y = 10, int z = 33)
{
  return x + y + z;
}

int main()
{

  return 0;
}
