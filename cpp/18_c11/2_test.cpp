#include <iostream>
#include <string>
using namespace std;

int main()
{
// 1.创建一个右值引用的变量,现在记录的临时资源是10
    int&& r = 10;

// 1.2现在记录的临时资源是20了。
    r = 20;

// 2.移动构造了
  string s("lichermionexs");
  string s2(move(s));
// 识别“即将销毁的临时对象”，把它的资源转移给新对象，从而减少深拷贝。
  cout<< "s:" << s <<endl;
  cout<< "s2:" << s2 <<endl;
  

  return 0;
}
