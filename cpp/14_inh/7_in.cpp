#include <iostream>
#include <string>
using namespace std;

class person
{
public:
  int a = 10;
};

class student1 : public person 
{
public:
};


class student2 : public person 
{
public:
};


class student : public student1, public student2
{
public:
};

int main()
{
  student s;
  // s.a = 0 不能访问会出现问题的。
  s.student1::a = 10;
  s.student2::a = 33;

  return 0;
}
