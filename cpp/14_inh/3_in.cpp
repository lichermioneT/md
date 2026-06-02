#include <iostream>
#include <string>
using namespace std;

class person
{
public:
  string _name = "lic";
  int _age = 18;
  int _class = 0;
};

class student : public person 
{
public:
  int _jobid = 1;
};

int main()
{
  student s;
  // 1.派生类给基类对象赋值
  person p1 = s;
  
  // 2.派生类给基类指针赋值
  person* p2 = &s;

  // 3.派生类给基类引用赋值
  person& p3 = s;
  return 0;
}
