#include <iostream>
#include <string>
using namespace std;

void func(int& x)
{
  cout<< "左值引用" <<endl;
}

void func(int&& x)
{
  cout<< "右值引用" <<endl;
}


int main()
{
// 1.创建一个右值变量，让它绑定道临时对象10上面
  int&& r = 10;
  cout<< r <<endl;
  
// 现在绑定的22上面了
  r = 22;

// r 不是“记住”临时变量，而是成为这个临时对象的一个引用，也就是这个对象的别名。
// r 本身是一个右值，可以绑定不同的右值。
  

  return 0;
}
