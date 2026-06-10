#include <string>
#include <iostream>
using namespace std;

int main()
{
  // 1.无参构造函数
  string s;

  // 2.用c_str来构造string对象的
  string s1("hello lichermionex");

  // 3.n个字符进行构造的
  string s2(10, 'x');

  // 4.拷贝构造，就是用旧的对象，构造一个一模一样的新对象。
  string s3(s2);

  // 5.迭代器构造
  string s4(s2.begin(), s2.end());
  
  cout << s << endl;
  cout << s1 << endl;
  cout << s2 << endl;
  cout << s3 << endl;
  cout << s4 << endl;

  return 0;
}
