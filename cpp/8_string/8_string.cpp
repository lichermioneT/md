#include <iostream>
#include <cstring>

class string 
{
private:
  size_t _size;
  size_t _capacity;
  char* _str;

public:

// 1.1默认无参数构造函数，记得多开一个存放\0就行的
  string()
    :_size(0)
    ,_capacity(0)
    ,_str(new char[1])
  {
    _str[0] = '\0';
  }

// 1.2注意空字符串指针，注意多开一个存放\0就行的。
  string(const char* str)
  {
    if(str)
    {
      _size = strlen(str);
      _capacity = _size;

      _str = new char[_capacity + 1]; // 记得多开一个存放\0;
      memcpy(_str, str, _size);
      _str[_size] = '\0';
    }
    else 
    {
      _size = _capacity  = 0;
      _str = new char[1];
      _str[_size] = 0;
    }
  }

// 1.3n个字符进行构造，注意这里缺省参数\0进行构造的。
  string(size_t n, char ch = '\0')
  {
    _size = _capacity = n;
    _str = new char[_size + 1];

    for(size_t i = 0; i < n; ++i)
    {
      _str[i] = ch;
    }
    
    _str[_size] = '\0';
  }

// 1.4拷贝构造函数，注意不能调用 string temp = s; 会出现递归的
  string(const string& s)
  {
    /*
     *拷贝构造不能再用 string temp = s，因为这本身就是在调用拷贝构造
     */
    _size = s._size;
    _capacity = s._capacity;

    _str = new char[_capacity + 1];
    memcpy(_str, s._str, _size);

    _str[_size] = '\0';
  }

// 2. 容量相关的，size,capacity 和_str。 
    
  size_t size() const 
  {
    return _size;
  }

  size_t length() const 
  {
    return _size;
  }

  size_t capacity() const 
  {
    return _capacity;
  }

  const char* c_str() const 
  {
    return _str;
  }

// 2.1 clear只是清除容器的数据，不改变capacity的。
  void clear()
  {
    _size = 0;
    _str[_size] = '\0';
  }

// 2.2reserve预先开辟空间的 
  void reserve(size_t n)
  {
    if(_capacity > n)
    {
      return;
    }
    else if(_capacity < n)
    {
      char* tmp = new char[n + 1];
      memcpy(tmp, _str, _size);

      delete[]  _str;
      _str = tmp;
      _str[_size] = '\0';
      _capacity = n;
    }
  }
  
// 2.2 resize()
  void resize(size_t n, char ch = '\0')
  {
    if(_size < n)
    {
       reserve(n);


    }
  }



};


int main()
{
  string s;
  string s1("fffffffffffffff");
  string s2(20, 'x');
  string s3(s2);

  std::cout<< s.c_str() << std::endl;
  std::cout<< s1.c_str() << std::endl;
  std::cout<< s2.c_str() << std::endl;
  std::cout<< s3.c_str() << std::endl;



  return 0;
}
