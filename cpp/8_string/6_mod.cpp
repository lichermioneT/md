#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s1("hello ");
  // 1.注意push_back只能放字符串
  s1.push_back('l');
  s1.push_back('i');
  s1.push_back('c');
  
  // 2.append是放字符串的
  s1.append("hermionex");
  s1.append("z");

  // 3.+=可以字符串，可以放字符。
  s1 += ' ';

  s1 += "xxxxxxxxxx";
  
  // 4.返回的c_str()是一个const修饰的，不然你乱改了，那还得得行。
  cout<< s1.c_str() <<endl;

  return 0;
}
