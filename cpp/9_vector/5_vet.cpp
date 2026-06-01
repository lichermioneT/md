#include <iostream>
using std::cout;
using std::endl;

template<class T>
class vector 
{
public:
  typedef T* iterator;
  typedef const T* const_iterator;
  
  iterator begin() {return  _start;}
  iterator end() {return  _finish;}
  const_iterator cbegin() const {return  _start;}
  const_iterator cend() const {return _finish;}

private:
  iterator _start;
  iterator _finish;
  iterator _endOfStorage;

public:
  // 1.无参数的构造函数。
  vector()
    :_start(nullptr)
    ,_finish(nullptr)
    ,_endOfStorage(nullptr)
  {}

  // 2.N个T的构造函数
  vector(size_t n, const T& value = T())
      :_start(nullptr)
      ,_finish(nullptr)
      ,_endOfStorage(nullptr)
  {
    _start = new T[n];
    for(size_t i = 0; i < n; ++i)
    {
      _start[i] = value;
    }
    
    _finish = _start + n;
    _endOfStorage = _start + n;
  }

  // 3.拷贝构造函数
  vector(const vector<T>& v)
  {
    _start = new T[v.capacity()];

    iterator it = begin();
    const_iterator cit = v.cbegin(); 
    
    while(it != v.cend())
    {
      it++ = cit++; 
    }

  }
public:
  size_t size() const 
  {
    return _finish - _start;
  }

  size_t capacity() const 
  {
    return _endOfStorage - _start;
  }

  bool empty() const 
  {
    return _finish == _start;
  }

public:
  T& operator[](size_t i)
  {
    return _start[i];
  }
  
  const T& operator[](size_t i) const
  {
    return _start[i];
  }

public:
  void reserve(size_t n)
  {
    if(capacity() <= n)
    {
      return;
    }

    T* tmp = new T[n];
    size_t oldSize = size();
// 注意这里只能用for循环的，不能用memcpy.自定义类型会出问题的
    for(size_t i = 0; i < oldSize; ++i)
    {
      tmp[i] = _start[i];
    }
    
    delete[] _start;

    _start = tmp;
    _finish = tmp + oldSize;
    _endOfStorage = n;
  }

  void resize(size_t n, const T& value = T())
  {
    if(n < size())
    {
      _finish = _start + n;
      return;
    }

    if(n > capacity())
    {
      reserve(n);
      for(size_t i = size(); i < n; ++i)
      {
        _start[i] = value;
      }

      _finish = _start + n;
    }
  }

// 插入删除
  void push_back(const T& value)
  {
    if(_finish == _endOfStorage)
    {
      reserve(2 * capacity());
    }

    _start[s]
  }


};



int main()
{
  return 0;
}
