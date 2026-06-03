#include <iostream>
using namespace std;

class person
{
public:
  virtual void buyticket()
  {
    cout<< "成年人，全价" <<endl;
  }
};

class student : public person
{
public:
  virtual void buyticket()
  {
    cout<< "学生，半价" <<endl;
  }
};

void fun1(person& p)
{
  p.buyticket();
}

void func2(person* p)
{
  p->buyticket();
}

int main()
{
  person p;
  student s;
  
  fun1(p);
  fun1(s);

  func2(&p);
  func2(&s);
  return 0;
}
