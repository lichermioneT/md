#include <iostream>
#include <string>
using namespace std;

class person
{
public:
  int a = 10;
};

class student1 : virtual public person 
{
public:
};


class student2 : virtual public person 
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
  s.a = 1111110;

  cout<< s.a <<endl;

  return 0;
}
