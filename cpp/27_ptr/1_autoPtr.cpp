#include <iostream>
using namespace std;

template<class T>
class autoptr 
{
private:
  T* _ptr;

public:
 // 1.构造函数，缺省的构造函数
  autoptr(T* ptr = nullptr)
    :_ptr(ptr)
  {}

// 2.析构函数，释放资源
  ~autoptr()
  {
    if(_ptr)
    {
      delete _ptr;
      _ptr = nullptr;
    }
  }

// 3.拷贝构造：移交管理权。把指针的管理权给一个新的对象
   autoptr(autoptr<T>& ap)
     :_ptr(ap._ptr)
   {
      ap._ptr = nullptr;
   }

// 4.赋值构造：移交管理权。
  autoptr<T>& operator=(autoptr<T>& ap)
  {
    if(&ap != this)
    {
      delete _ptr;
      
      // 移交管理权
      _ptr = ap._ptr;
      ap._ptr = nullptr;
    }

    return *this;
  }

// 使用方法了
  
  // 1.指针一样解引用
  T& operator*()
  {
    return *_ptr;
  }

  // 2.指针一样访问成员
  T* operator->()
  {
    return _ptr;
  }

  // 3.获取原始指针
  T* get()
  {
    return _ptr;
  }

};

class Date
{
public:
    Date(int year = 2026, int month = 6, int day = 6)
        : _year(year)
        , _month(month)
        , _day(day)
    {}

    void Print()
    {
        cout << _year << "-" << _month << "-" << _day << endl;
    }

private:
    int _year;
    int _month;
    int _day;
};

int main()
{
  autoptr<int> ap{new int{22}}; 
  cout<< *ap <<endl;
  
  // 1.构造一个新的ap2
  autoptr<Date> ap2(new Date);
  ap2->Print();
  
  // 2.现在ap3接管了ap2的资源了。
  autoptr<Date> ap3(ap2);
  // ap2->Print();  不行的
  ap3->Print();

  return 0;
}
