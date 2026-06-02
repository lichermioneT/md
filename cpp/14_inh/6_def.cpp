#include <iostream>
#include <string>
using namespace std;

class person
{
public:
  person()
  {
    cout<< "person的构造函数" <<endl;
  }

  person(const person& p)
  {
    cout<< "person的拷贝构造" <<endl;
  }
  
  ~person()
  {
    cout<< "person的析构函数" <<endl;
  }
};

class student : public person 
{
public:
  student()
  {
    cout<< "student的构造函数" <<endl;
  }
  
  student(const student& s)
  {
    cout<< "student的拷贝构造函数" <<endl;
  }

  ~student()
  {
    cout<< "student的析构函数" <<endl;
  }
};

int main()
{
  student s;
  student s2(s);

  return 0;
}
