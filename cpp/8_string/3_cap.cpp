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

  // 3.预定的capacity至少是64个
  // 1.如果比已经知道的capacity小于或者等于，则不变
  // 2.比已知的capacity大，则需要增容到 新的capacity去的。
  s1.reserve(64);
  cout<< "预定64过后的容量" <<endl;
  cout<< "capacity:"<< s1.capacity() <<endl;
  cout<< "size:" <<s1.size() <<endl;
  cout<< "length:" <<s1.length() << endl;

  // 4.resize是改变有的个数
  // 1.resize的小于现在的size，只需要改变size的大小
  // 2.resize的大于现在的size, 函数重载了，可以多的部分可以填充新的字符。
  cout<< s1 <<endl;
  s1.resize(48, 'a');
  cout<< s1 <<endl;

  s1.resize(2);
  cout << s1 << endl;




  return 0;
}
