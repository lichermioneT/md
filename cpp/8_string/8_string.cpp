#include <iostream>
#include <cassert>
#include <cstring>

class string 
{
private:
  size_t _size;
  size_t _capacity;
  char* _str;

static const size_t npos = -1;
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
    :_size(s._size)
    ,_capacity(s._capacity)
  {
    // 开辟新空间
    _str = new char[_capacity + 1];
    
    // 拷贝数据 (增加非空判断，防御 memcpy 的未定义行为)
    if (s._str != nullptr) 
    {
        memcpy(_str, s._str, _size);
    }
    
    // 确保以 \0 结尾
    _str[_size] = '\0';
  }

  ~string()
  {
    delete[] _str;
    _str = nullptr;

    _size = _capacity = 0;
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
    if(n <= _capacity)
    {
      return;
    }

    char* tmp = new char[n + 1];
    
    if(_str != nullptr)
    {
      memcpy(tmp, _str, _size);
      delete[]  _str;
    }
    _str = tmp;
    _str[_size] = '\0';
    _capacity = n;
  }
  
// 2.2 resize()
  void resize(size_t n, char ch = '\0')
  {
    if(n > _size)
    {
      reserve(n);
      
      for(size_t i = _size; i < n; ++i)
      {
        _str[i] =  ch;
      }
      
      _size = n;
      _str[n] = '\0';
    }
    else if (n < _size)
    {
      _size = n;
      _str[_size] = '\0';
    }
  }

  bool empty() const
  {
     return _size == 0;

  }



// operator[]
  char& operator[](size_t i)
  {
    assert(i < _size);
    return _str[i];
  }

  const char& operator[](size_t i) const
  {
    assert(i < _size);
    return _str[i];
  }

// iterator   
// 1. 提供标准的类型别名，方便与标准库算法兼容
  using iterator = char*;
  using const_iterator = const char*;

  iterator begin()
  {
    return _str;
  }

  iterator end()
  {
    return _str + _size;
  }

  const_iterator begin() const
  {
    return _str;
  }

  const_iterator end() const
  {
    return _str + _size;
  }

  const_iterator cbegin() const
  {
    return _str;
  }

  const_iterator cend() const 
  {
    return _str + _size;
  }

// 1.操作对象
  void push_back(char ch)
  {
    if(_size == _capacity)
    {
      size_t newCapacity = _capacity == 0 ? 2 : _capacity * 2;
      reserve(newCapacity);
    }

    _str[_size] = ch;
    _size++;
    _str[_size] = '\0';
  }

  void append(const char* str)
  {
    assert(str != nullptr);
    size_t len = strlen(str);
    
    bool self_append = (str >=  _str && str <= _str + _size);
    
    size_t offset = 0;
    if(self_append)
    {
      offset = str - _str;
    }

    
    if(_size + len > _capacity)
    {
      reserve(len + _size);
    }
    
    if(self_append)
    {
      str = _str + offset;
    }

    memmove(_str + _size, str, len); 

    _size += len;
    _str[_size] = '\0';
  }

// operator+= 
  string& operator+=(char ch)
  {
    push_back(ch);

    return *this;
  }

  string& operator+=(const char* str)
  {
    append(str);

    return *this;
  }

  string& operator+=(const string& s)
  {
    append(s.c_str());
    return *this;
  }

  size_t find(char ch, size_t pos = 0) const
  {
    assert(pos <= _size);
    for(size_t i = pos; i < _size; ++i)
    {
        if(_str[i] == ch)
        {
          return i;
        }
    }
    return npos;
  }

  size_t find(const char* str, size_t pos = 0) const
  {
    assert(pos <= _size);
    assert(str != nullptr);

    if(*str == '\0')
    {
      return pos;
    }

    if(pos == _size)
    {
      return npos;
    }

    const char* index = strstr(_str + pos, str);
    
    if(index)
    {
      return index - _str; 
    }
    return npos;
  }

// 
  string& operator=(string s)
  {
    Swap(s);
    return *this;
  }

friend std::ostream& operator<<(std::ostream& out, const string& s);

private:
  void Swap(string& s)
  {
    std::swap(_size, s._size);
    std::swap(_capacity, s._capacity);
    std::swap(_str, s._str);
  }
};

std::ostream& operator<<(std::ostream& out, const string& s)
{
    out << s._str;
    return out;
}

int main()
{

}

