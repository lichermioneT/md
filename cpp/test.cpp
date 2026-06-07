#include <iostream>
#include <string>
using namespace std;

class person
{
public:
  int a = 10;
  int ab = 10;
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
  cout<< sizeof(student) <<endl;
  
  return 0;
}
