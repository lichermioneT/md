#include <iostream>
using namespace std;

namespace N1
{
  int a = 10;
  int b = 22;
  
  int add(int x, int y)
  {
    return x + y;
  }

  class stu 
  {
    private:
      int age;
  };
}

namespace N1 
{
  int mul(int x, int y)
  {
    return x * y;
  }
}

int main()
{
// 1.using引入。
  using N1::a;
  cout<< "N1::a " << a <<endl;

// 2.using namespace 
  using namespace N1;
  cout<< "using namespace N1: b " <<endl;

// 3.自己突破类
  cout<< N1::add(22, 33) <<endl;

  return 0;
}
