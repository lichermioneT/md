#include <iostream>
using namespace std;

template<class T>
class sharePtr
{
private:
  T* _ptr;     // 管理的资源
  int* _pcount; // 引用计数

public:
  // 1.构造函数，有资源就是1, 没有资源就是零的。
  explicit sharePtr(T* ptr = nullptr)
    :_ptr(ptr)
    ,_pcount(nullptr)
  {
    if(_ptr)
    {
      _pcount = new int{1};
    }

  }

  // 2.拷贝构造,新的对象管理同一块资源的。
  // 成功了则，引用计数++；
  sharePtr(const sharePtr<T>& sp)
    :_ptr(sp._ptr)
    ,_pcount(sp._pcount)
  {
    if(_pcount)
    {
      ++(*_pcount);
    }
  }

  // 3.赋值重载了
  sharePtr<T>& operator=(const sharePtr<T>& sp)
  {
    if(this != &sp)
    {
      
      release();

      _ptr = sp._ptr;
      _pcount = sp._pcount;

      if(_pcount)
      {
        ++(*_pcount);
      }
    }

    return *this;
  }

 // 析构函数
    ~sharePtr()
    {
        release();
    }

    // 解引用
    T& operator*()
    {
        return *_ptr;
    }

    // 成员访问
    T* operator->()
    {
        return _ptr;
    }

    // 获取原始指针
    T* get() const
    {
        return _ptr;
    }

    // 获取引用计数
    int use_count() const
    {
        return _pcount ? *_pcount : 0;
    }

private:
  void release()
  {
    if(_pcount)
    {
      // 等于1才会真正的释放资源信息的。
      --(*_pcount);

      if(*_pcount == 0)
      {
        delete _ptr;
        delete _pcount;
        _ptr =  nullptr;
        _pcount = nullptr;
      }
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
    {
        // cout << "Date()" << endl;
    }

    ~Date()
    {
        // cout << "~Date()" << endl;
    }

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
  sharePtr<Date> sp1(new Date(2026, 6, 7));
  cout<< "sp1 count:" << sp1.use_count() <<endl;

  {
    sharePtr<Date> sp2(sp1);
    cout<< "sp1 count:" << sp1.use_count() <<endl;
    cout<< "sp2 count:" << sp2.use_count() <<endl;

    sharePtr<Date> sp3;
    sp3 = sp2;

    cout<< "sp1 count:" << sp1.use_count() <<endl;
    cout<< "sp2 count:" << sp2.use_count() <<endl;
    cout<< "sp3 count:" << sp3.use_count() <<endl;

    sp3->Print();
  }

  cout<< "sp1 count:" << sp1.use_count() <<endl;
  sp1->Print();

  return 0;
}
