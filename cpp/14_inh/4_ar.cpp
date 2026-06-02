#include <iostream>
#include <string>
using namespace std;

class person
{
public:
  string _name = "lic";
  int _age = 18;
  int _class = 0;

  void  print()
  {
    cout<< "_name:" << _name <<endl;
  }
};

class student : public person 
{
public:
  int _class = 111111;

  void print(int a = 10)
  {
    cout<< "_class" << _class <<endl;
    cout<< "a:" << a <<endl;
  }
};

int main()
{
  person p;
  student s;
// 1.成员属性出现重定义的方法。
  cout<< p._class << endl;
  //基类的优先，也可以突破类域进行访问的
  cout<< s._class <<endl;
  cout<< s.person::_class <<endl;

// 2.成员方法出现重定义的方法
  p.print();
  //基类的优先，也可以突破类域进行访问的
  s.print(2222);
  s.person::print();

  return 0;
}
