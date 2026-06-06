#include <iostream>
using namespace std;

class p
{
public:
  int _age;
  int _class;
};  


class stu : public p
{
public:
  int _id;
};

int main()
{
// 1.基本类型的数据转换
  double d = 3.123;
  int x = static_cast<int>(d);

// 2.父子类型指针转换
  stu student;
  p* person = static_cast<p*>(&student);


  return 0;
}
