#include <memory>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
  // 1.用一个指针进行初始化p
  unique_ptr<int> p(new int{28});
  cout<< *p <<endl;
  
  // 2.现在p释放了对这个资源的管理权限了
  int* raw = p.release();
  cout<< *raw <<endl;

  *raw = 888;

  // 3.开始接管新的资源
  p.reset(raw);
  cout<< *p <<endl;

  // p2这个智能指针指向 string("licher")这个对象的。 
  unique_ptr<string> p2(new string("licher"));
  cout<< *p2 <<endl;
  cout<< p2->size() <<endl;

  *p2 += "mionex";
  cout<< *p2 <<endl;
  
  p2->append(" hello");
  cout<< *p2 <<endl;

  // p2变成空的，资源全部给p3了的。
  unique_ptr<string> p3(move(p2));
  cout<< "p3" <<endl;
  cout<< *p3 <<endl;
  
  // 现在住的让出p3的资源给s了。
  string* s= p3.release();
  
  // reset重新接管一个资源，释放原来的资源了。
  p3.reset(s);

  return 0;
}
