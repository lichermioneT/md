#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s("lichermionxexx");

  // 1.find函数找的字符或者字符串返回，返回找到位置的起始下标。
  int pos = s.find('l');
  cout << pos << endl;

  pos = s.find("lic");
  cout << pos << endl;
  
  // 2.substr 
  // 1.第一个参数是：字符串的起始位置
  // 2.第二个参数树：字符串的步长，起始位置也算的，。
  string sub = s.substr(1, 3);
  cout << sub <<endl;

  return 0;
}
