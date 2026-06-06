#include <iostream>
using namespace std;

template<class T>
class uniquePtr 
{
private:
  T* _ptr;

public:
// 1.构造函数
  explicit uniquePtr(T* ptr = nullptr)
    :_ptr(ptr)
  {}

// 2.析构函数
  ~uniquePtr()
  {
    delete _ptr;
    _ptr = nullptr;
  }

// 3.进制拷贝构造
  uniquePtr(const uniquePtr<T>&) = delete;

// 4.禁止赋值拷贝
  uniquePtr& operator=(const uniquePtr<T>&) = delete;

// 5.移动构造：转义资源
  uniquePtr(uniquePtr<T>&& up)
    :_ptr(up._ptr)
  {
    up._ptr = nullptr;
  }

// 6.移动赋值：转义资源 
  uniquePtr<T>& operator=(uniquePtr<T>&& up)
  {
    if(&up != this)
    {
      delete _ptr; // 释放自己的资源
      
      _ptr = up._ptr; // 接管对方的资源
      up._ptr = nullptr; // 对方置空
    }

    return *this;
  }

// 使用资源
  // 1.解引用
  T& operator*()
  {
    return * _ptr;
  }

  // 2.指针访问成员
  T* operator->()
  {
    return _ptr;
  }

  // 3.获取原始指针
  T* get() const 
  {
    return _ptr;
  }

  // 4.释放所有权，不delete
  T* release()
  {
    T* tmp = _ptr;
    _ptr = nullptr;
    return tmp;
  }

  // 5.重置资源的管理
  
  void reset(T* ptr = nullptr)
  {
    if(_ptr != nullptr)
    {
      delete _ptr;
      _ptr = ptr;
    }
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

  uniquePtr<Date> p1(new Date(1, 2, 3));
  p1->Print();

  // 禁止拷贝的和赋值的
  //uniquePtr<Date> p2(p1);
  
  uniquePtr<Date> p2(move(p1));
  p2->Print();

  uniquePtr<Date> p3;
 
  // 移动赋值给新的管理
  p3 = move(p2);

  p3->Print();

// 2. 
  
  // 释放管理权限了，现在由新的指针进行管理
  uniquePtr<int> p(new int{2});
  int* raw = p.release();
  *raw = 999;
  cout<< *raw <<endl;
 // 需要自己管理资源
  
// 释放原来的资源，管理新的资源
  p.reset(raw);

  return 0;
}
