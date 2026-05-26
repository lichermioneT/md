#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s1("hello lichermionexxxxxxxxxxxx");

  //1.现在开辟了多少的空间容量
  cout<< "capacity:"<< s1.capacity() <<endl;

  //2.现在空间里面有效字符串的个数。length等价size的。
  cout<< "size:" <<s1.size() <<endl;
  cout<< "length:" <<s1.length() << endl;

  //3.检测字符串是否为空串。空返回true，非空返回false 
  cout<< "empty:" <<s1.empty() << endl;

  //4.clear。清空字符串。
  //1.不会修改capacity的
  //2.size和length变成零的
  s1.clear(); 

  cout<< "清理后的，容量" <<endl;
  cout<< "size:" <<s1.size() <<endl;
  cout<< "length:" <<s1.length() << endl;

  cout<< "capacity:"<< s1.capacity() <<endl;

  return 0;
}
