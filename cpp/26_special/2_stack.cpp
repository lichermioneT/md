#include <iostream>
using namespace std;

class stackonly 
{
public:
  stackonly()
  {
    cout<< "构造函数" <<endl;
  }

  ~stackonly()
  {
    cout<< "析构函数" <<endl;
  }

  void print()
  {
    cout<< "i am stackonly object" <<endl;
  }

// 静止单个对象在堆上创建
  static void* operator new(size_t size) = delete;
  static void  operator delete(void* ptr) = delete;

// 静止数组对象在堆上创建
  static void* operator new[](size_t size) = delete;
  static void  operator delete[](void* ptr) = delete;
};

int main()
{
  stackonly s;
  s.print();

  // StackOnly* p = new StackOnly;
  // 错误：operator new 被 delete 了，不能在堆上创建

  // StackOnly* arr = new StackOnly[5];
  // 错误：operator new[] 被 delete 了，不能在堆上创建数组
  return 0;
}
