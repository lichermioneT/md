#include <iostream>
#include <string>
using namespace std;

class person
{
public:
  void print()
  {
    cout<< "name:" << _name <<endl;
    cout<< "age:" << _age <<endl;
  }

protected:
  string _name = "lic";
  int _age = 18;
};

class student : public person 
{
protected:
  int _jobid;
};

int main()
{
  person p;
  student s;
  
  p.print();
  s.print();
  return 0;
}
