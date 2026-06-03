#include <iostream>
using namespace std;

class car
{
public:
  virtual void drive() = 0;
};

class modely : public car 
{
public:
  virtual void drive()
  {
    cout<< "modely:suv" <<endl;
  }
};

class model3 : public car 
{
public:
  virtual void drive()
  {
    cout<< "model3: super car" <<endl;
  }
};

int main()
{
  car* p1 = new modely;
  p1->drive();

  car* p2 = new model3;
  p2->drive();

  return 0;
}
