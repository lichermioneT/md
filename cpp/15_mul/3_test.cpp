#include <iostream>
using namespace std;

class car
{
public:
  virtual void func1()
  {

  }

  virtual void func2()
  {

  }

  void func3()
  {

  }

private:
  int a;
};


class model : public car 
{
public:
  virtual void func1()
  {

  }

  virtual void fun()
  {

  }

int b;
};


int main()
{

  cout<< (sizeof(car)) <<endl;
  cout<< sizeof(model) <<endl;

  return 0;
}
