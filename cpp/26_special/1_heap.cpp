#include <iostream>
using namespace std;

// 1特殊类只能在堆上创建
class heapOnly 
{
public:
  static heapOnly* create()
  {
    return new heapOnly;
  }

  static void destory(heapOnly* ptr)
  {
    delete ptr;
  }

  void print()
  {
    cout<< "i am heapOnly  object" <<endl;
  }
  
  heapOnly(const heapOnly&) = delete;
  heapOnly& operator=(const heapOnly&) = delete ;

private:
  heapOnly()
  {
    cout<< "heapOnly()" <<endl;
  }

  ~heapOnly()
  {
    cout<< "~heapOnly()" <<endl;
  }
};

int main()
{
  // 1.构造函数私有，不能进行内外访问的
  // heapOnly h;
  
  heapOnly* p = heapOnly::create();
  p->print();
  
  heapOnly::destory(p);
  return 0;
}
