## c++ lesson8 

# string

## 1构造函数

**string一般常用的也就是四个构造函数。**

**1.无参数。  2.c字符串进行构造。  3.n个字符进行构造。  4.拷贝构造的。**

**代码示例**

```c++
#include <string>
#include <iostream>
using namespace std;

int main()
{
  // 1.无参构造函数
  string s;

  // 2.用c_str来构造string对象的
  string s1("hello lichermionex");

  // 3.n个字符进行构造的
  string s2(10, 'x');

  // 4.拷贝构造，就是用旧的对象，构造一个一模一样的新对象。
  string s3(s2);
  
  // 5.迭代器构造

  cout << s << endl;
  cout << s1 << endl;
  cout << s2 << endl;
  cout << s3 << endl;

  return 0;
}
```



## 2容量相关的

**1.capcacity:目前已经开辟了多少的空间的。**

**2.length和size: 目前里面有多少个有效的字符**

```c++
#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s1("hello lichermionexxxxxxxxxxxx");

  //1.现在开辟了多少的空间容量
  cout<< "capacity:"<< s1.capacity() <<endl;

  //2.现在空间里面有效字符串的个数。length等价size的。
  cout<< "size:" <<s1.size() <<endl;
  cout<< "length:" <<s1.length() << endl;

  //3.检测字符串是否为空串。空返回true，非空返回false 
  cout<< "empty:" <<s1.empty() << endl;

  //4.clear。清空字符串。
  //1.不会修改capacity的
  //2.size和length变成零的
  s1.clear(); 

  cout<< "清理后的，容量" <<endl;
  cout<< "size:" <<s1.size() <<endl; // 0
  cout<< "length:" <<s1.length() << endl; // 0

  cout<< "capacity:"<< s1.capacity() <<endl; // 不变

  return 0;
}

```



## 3容量相关的

**reserver.**

**1.capacty。 预定的空间小于现在的空间则不变。**

​	**预定的空间大于现在的空间，则增加到新的空间。**

**resize:**

**1.size。size小于现在的的size, 就改变现在size的大小。**

​	**大于现在的size，这里有函数重载可以添加新的字符串，直到size等于新的size.**

```c++
#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s1("hello lichermionexxxxxxxxxxxx");

  //1.现在开辟了多少的空间容量
  cout<< "capacity:"<< s1.capacity() <<endl;

  //2.现在空间里面有效字符串的个数。length等价size的。
  cout<< "size:" <<s1.size() <<endl;
  cout<< "length:" <<s1.length() << endl;

  // 3.预定的capacity至少是64个
  // 1.如果比已经知道的capacity小于或者等于，则不变
  // 2.比已知的capacity大，则需要增容到 新的capacity去的。
  s1.reserve(64);
  cout<< "预定64过后的容量" <<endl;
  cout<< "capacity:"<< s1.capacity() <<endl;
  cout<< "size:" <<s1.size() <<endl;
  cout<< "length:" <<s1.length() << endl;

  // 4.resize是改变有的个数
  // 1.resize的小于现在的size，只需要改变size的大小
  // 2.resize的大于现在的size, 函数重载了，可以多的部分可以填充新的字符。
  cout<< s1 <<endl;
  s1.resize(48, 'a');
  cout<< s1 <<endl;

  s1.resize(2);
  cout << s1 << endl;
  return 0;
}

```



## 4遍历的方式

### 4.1

**1.string重载了[],可以进行随机访问的。**

```c++
#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s1("hello lichermionexxxxxxxxxxxx");
  size_t size = s1.size();
  
  // 本质上还是一个字符数组，可以进行遍历的[]
  for(size_t i = 0; i < size; ++i)
  {
    cout<< s1[i];
  }
    
  cout<<endl;
  return 0;
}

```

### 4.2

**迭代器遍历**

**1.正向遍历**

```c++
#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s1("hello lichermionexxxxxxxxxxxx");
  string::iterator it = s1.begin();
  
  // string的迭代器本本质也是值的。
  while(it != s1.end())
  {
    cout<< *it;
    ++it;
  }
  cout<<endl;

  return 0;
}
```

**2.反向遍历**

**如何理解反向迭代器：++却是往前面走的**

```c++
#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s1("hello lichermionexxxxxxxxxxxx");
  string::reverse_iterator it = s1.rbegin();

  while(it != s1.rend())
  {
    cout<< *it;
    ++it;
  }
  cout<<endl;

  return 0;
}

```

### 4.3



### 4.4



## 5修改函数

**推荐使用+=。方便的。**

**push_back。只能插入一个字符的。**

**append。 插入一个字符串的。**

**+=最方便的。都能进行插入的。**

```c++
#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s1("hello ");
  // 1.注意push_back只能放字符串
  s1.push_back('l');
  s1.push_back('i');
  s1.push_back('c');
  
  // 2.append是放字符串的
  s1.append("hermionex");
  s1.append("z");

  // 3.+=可以字符串，可以放字符。
  s1 += ' ';

  s1 += "xxxxxxxxxx";
  
  // 4.返回的c_str()是一个const修饰的，不然你乱改了，那还得得行。
  cout<< s1.c_str() <<endl;

  return 0;
}

```



## 6查找函数

**find函数第一个参数是需要查找的：字符或者字符串的。 返回值是起始位置的下标。**

**你也可以定，从哪个位置开始进行寻找的。**

**substr。 起始位置开始，然后找到步长的字符串。 默认找到末尾的。**

```c++
#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s("lichermionxexx");

  // 1.find函数找的字符或者字符串返回，返回找到位置的起始下标。
  int pos = s.find('l');
  cout << pos << endl;

  pos = s.find("lic");
  cout << pos << endl;
  
  // 2.substr 
  // 1.第一个参数是：字符串的起始位置
  // 2.第二个参数树：字符串的步长，起始位置也算的，。
  // 从开始位置找几个字符的。
  string sub = s.substr(1, 3);
  cout << sub <<endl;

  return 0;
}

```



## 删除函数

```c++
#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s("lichermionxexx");
  
  size_t pos = s.find("c");
  s.erase(pos, 4);
  
  // limionxexx
  // 从开始位置齐，然后删除几个元素的。
  cout<< s << endl;

  return 0;
}
```

| 用法                   | 含义                               | 返回值                   |
| ---------------------- | ---------------------------------- | ------------------------ |
| `s.erase(pos, len)`    | 从下标 `pos` 开始删除 `len` 个字符 | `string&`                |
| `s.erase(pos)`         | 从下标 `pos` 删除到结尾            | `string&`                |
| `s.erase(it)`          | 删除迭代器 `it` 指向的字符         | 下一个位置的迭代器       |
| `s.erase(first, last)` | 删除 `[first, last)` 区间          | 删除后新区间位置的迭代器 |

```c++
#include <string>
#include <iostream>
using namespace std;

int main()
{
// 1.erase删除pos位置的数据，然后返回删除的字符。
  string s{"licherminonex"};
  cout<< s <<endl; 
  size_t pos = s.find('e');
  cout<< s.erase(pos) <<endl;

// 2.传入迭代器删除
  string s2x{"licherminonex"};
  cout<< s2x <<endl; 

  string::iterator it = s2x.begin() + 4;
  it = s2x.erase(it);

  cout<< s2x <<endl; 
  cout<< *it <<endl;


  return 0;
}

```

```c++
licherminonex
lich
licherminonex
lichrminonex
r
```

**传入迭代器：传入什么位置，就删除那个位置的元素。**

**传入区间：从起始位置删到结束位置前一个。**

**string` 传入下标 `pos`：默认从 `pos` 删除到末尾。**



**s.erase(pos, len);   // 按下标删除**

**it = s.erase(it);    // 遍历时删除**

```c++
#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s("lichermionxe");

  cout<< s <<endl;
  cout<< s.erase(0,1) <<endl;
  cout<< s.erase(0,1) <<endl;
  cout<< s.erase(0,1) <<endl;

  string::iterator it = s.begin(); 
  it = s.erase(it);
  cout<< s <<endl;
  cout<< *it <<endl;

  return 0;
}
```



## 7实现string

### 1.头文件

```c++
#ifndef __STRING_H__
#define __STRING_H__

#include <cstddef>
#include <iosfwd>

class string
{
public:
    // =========================
    // 1. 类型定义和常量
    // =========================
    using iterator = char*;
    using const_iterator = const char*;

    static constexpr size_t npos = static_cast<size_t>(-1);

public:
    // =========================
    // 2. 构造、拷贝、析构
    // =========================
    string();
    string(const char* str);
    string(size_t n, char ch = '\0');
    string(const string& s);
    ~string();

    // =========================
    // 3. 容量相关接口
    // =========================
    size_t size() const;
    size_t length() const;
    size_t capacity() const;
    bool empty() const;

    void reserve(size_t n);
    void resize(size_t n, char ch = '\0');
    void clear();

    // =========================
    // 4. 元素访问
    // =========================
    char& operator[](size_t i);
    const char& operator[](size_t i) const;

    const char* c_str() const;

    // =========================
    // 5. 迭代器
    // =========================
    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    // =========================
    // 6. 修改操作
    // =========================
    void push_back(char ch);
    void append(const char* str);

    // =========================
    // 7. 查找操作
    // =========================
    size_t find(char ch, size_t pos = 0) const;
    size_t find(const char* str, size_t pos = 0) const;

    // =========================
    // 8. 运算符重载
    // =========================
    string& operator=(string s);

    string& operator+=(char ch);
    string& operator+=(const char* str);
    string& operator+=(const string& s);

    // =========================
    // 9. 友元函数
    // =========================
    friend std::ostream& operator<<(std::ostream& out, const string& s);

private:
    // =========================
    // 10. 私有工具函数
    // =========================
    void Swap(string& s);

private:
    // =========================
    // 11. 成员变量
    // =========================
    size_t _size;
    size_t _capacity;
    char* _str;
};

// =========================
// 12. 非成员函数声明
// =========================
std::ostream& operator<<(std::ostream& out, const string& s);

#endif

```

### 2.源文件

```c++
#include "string.h"
#include <iostream>

#include <cassert>
#include <cstring>
#include <utility>

// =========================
// 1. 构造、拷贝、析构
// =========================
string::string()
    : _size(0)
    , _capacity(0)
    , _str(new char[1])
{
    _str[0] = '\0';
}

string::string(const char* str)
{
    if (str)
    {
        _size = strlen(str);
        _capacity = _size;

        _str = new char[_capacity + 1];
        memcpy(_str, str, _size + 1);  // 连同 '\0' 一起拷贝
    }
    else
    {
        _size = 0;
        _capacity = 0;
        _str = new char[1];
        _str[0] = '\0';
    }
}

string::string(size_t n, char ch)
    : _size(n)
    , _capacity(n)
    , _str(new char[n + 1])
{
    for (size_t i = 0; i < n; ++i)
    {
        _str[i] = ch;
    }

    _str[_size] = '\0';
}

string::string(const string& s)
    : _size(s._size)
    , _capacity(s._capacity)
    , _str(new char[s._capacity + 1])
{
    memcpy(_str, s._str, _size + 1);  // 连同 '\0' 一起拷贝
}

string::~string()
{
    delete[] _str;
    _str = nullptr;
    _size = 0;
    _capacity = 0;
}

// =========================
// 2. 容量相关接口
// =========================
size_t string::size() const
{
    return _size;
}

size_t string::length() const
{
    return _size;
}

size_t string::capacity() const
{
    return _capacity;
}

bool string::empty() const
{
    return _size == 0;
}

void string::reserve(size_t n)
{
    if (n <= _capacity)
    {
        return;
    }

    char* tmp = new char[n + 1];
    memcpy(tmp, _str, _size + 1);  // 连同 '\0' 一起拷贝

    delete[] _str;
    _str = tmp;
    _capacity = n;
}

void string::resize(size_t n, char ch)
{
    if (n > _size)
    {
        reserve(n);

        for (size_t i = _size; i < n; ++i)
        {
            _str[i] = ch;
        }

        _size = n;
        _str[_size] = '\0';
    }
    else if (n < _size)
    {
        _size = n;
        _str[_size] = '\0';
    }
}

void string::clear()
{
    _size = 0;
    _str[0] = '\0';
}

// =========================
// 3. 元素访问
// =========================
char& string::operator[](size_t i)
{
    assert(i < _size);
    return _str[i];
}

const char& string::operator[](size_t i) const
{
    assert(i < _size);
    return _str[i];
}

const char* string::c_str() const
{
    return _str;
}

// =========================
// 4. 迭代器
// =========================
string::iterator string::begin()
{
    return _str;
}

string::iterator string::end()
{
    return _str + _size;
}

string::const_iterator string::begin() const
{
    return _str;
}

string::const_iterator string::end() const
{
    return _str + _size;
}

string::const_iterator string::cbegin() const
{
    return _str;
}

string::const_iterator string::cend() const
{
    return _str + _size;
}

// =========================
// 5. 修改操作
// =========================
void string::push_back(char ch)
{
    if (_size == _capacity)
    {
        size_t newCapacity = (_capacity == 0) ? 2 : _capacity * 2;
        reserve(newCapacity);
    }

    _str[_size++] = ch;
    _str[_size] = '\0';
}

void string::append(const char* str)
{
    assert(str != nullptr);

    size_t len = strlen(str);

    // 处理 s.append(s.c_str()) 这种自追加场景
    bool self_append = (str >= _str && str <= _str + _size);
    size_t offset = 0;

    if (self_append)
    {
        offset = str - _str;
    }

    if (_size + len > _capacity)
    {
        reserve(_size + len);
    }

    if (self_append)
    {
        str = _str + offset;
    }

    memmove(_str + _size, str, len);
    _size += len;
    _str[_size] = '\0';
}

// =========================
// 6. 查找操作
// =========================
size_t string::find(char ch, size_t pos) const
{
    assert(pos <= _size);

    for (size_t i = pos; i < _size; ++i)
    {
        if (_str[i] == ch)
        {
            return i;
        }
    }

    return npos;
}

size_t string::find(const char* str, size_t pos) const
{
    assert(str != nullptr);
    assert(pos <= _size);

    if (*str == '\0')
    {
        return pos;
    }

    if (pos == _size)
    {
        return npos;
    }

    const char* index = strstr(_str + pos, str);

    if (index)
    {
        return index - _str;
    }

    return npos;
}

// =========================
// 7. 运算符重载
// =========================
string& string::operator=(string s)
{
    Swap(s);
    return *this;
}

string& string::operator+=(char ch)
{
    push_back(ch);
    return *this;
}

string& string::operator+=(const char* str)
{
    append(str);
    return *this;
}

string& string::operator+=(const string& s)
{
    append(s.c_str());
    return *this;
}

// =========================
// 8. 私有工具函数
// =========================
void string::Swap(string& s)
{
    std::swap(_size, s._size);
    std::swap(_capacity, s._capacity);
    std::swap(_str, s._str);
}

// =========================
// 9. 非成员函数
// =========================
std::ostream& operator<<(std::ostream& out, const string& s)
{
    out << s.c_str();
    return out;
}

```





## 题 1：统计字符出现次数

```c++
#include <string>
#include <iostream>
using namespace std;

int countChar(const string& str, char ch)
{
  int ret = 0;
  for(auto e : str)
  {
    if(e == ch)
    {
      ret++;
    }
  }
  return ret;
}

int main()
{
  string s = "hello world";
  cout<< countChar(s, 'l') <<endl;

  return 0;
}
```

## 题 2：反转字符串

```c++
#include <string>
#include <iostream>
using namespace std;

void rever(string& str)
{
  int left = 0;
  int right =  str.size()-1;

  while(left < right)
  {
    swap(str[left], str[right]);
    left++;
    right--;
  }
}

int main()
{
  string s("lichermionxe");
  cout<< s <<endl;

  rever(s);
  cout<< s <<endl;

  return 0;
}

```



## 题 3：判断回文串

```c++
#include <string>
#include <iostream>
using namespace std;

bool loopstr(const string& str)
{
  int left = 0;
  int right = str.size() - 1;
  
  while(left < right)
  {
    if(str[left] != str[right])
    {
      return false;
    }

    left++;
    right--;
  }

  return true;
}

int main()
{

  cout<< loopstr("level") <<endl;
  cout<< loopstr("hello") <<endl;

  return 0;
}

```



## 题 4：查找子串

```c++
#include <string>
#include <iostream>
using namespace std;

bool findsubstr(const string& str, const char* substr)
{
  size_t pos = str.find(substr);
  if(pos != string::npos)
  {
    return true;
  }
  else 
  {
    return false;
  }
}

int main()
{
  string s("hello world");
  const char* str = "world";
  const char* str1 = "xxxworld";

  cout<< findsubstr(s, str) <<endl;
  cout<< findsubstr(s, str1) <<endl;
  return 0;
}
```



## 题 5：删除所有空格

```c++
#include <string>
#include <iostream>
using namespace std;

void findsubstr(string& str)
{
  size_t i = 0;
  for(size_t j = 0; j < str.size(); ++j)
  {
    if(str[j] != ' ')
    {
      str[i++] = str[j];
    }
  }
  s.resize(i);
}

int main()
{
  string s("lic f f f f f f ff ");
  cout<< s <<endl;

  findsubstr(s);
  cout<< s <<endl;

  return 0;
}
```

```c++
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s = "a b c d";

    for (size_t i = 0; i < s.size(); )
    {
        if (s[i] == ' ')
        {
            s.erase(i, 1);
        }
        else
        {
            ++i;
        }
    }

    cout << s << endl;

    return 0;
}
```



## 题 6：截取文件后缀

```c++
#include <string>
#include <iostream>
using namespace std;

string findfile(string& str)
{
  size_t pos = str.rfind('.');
  if(pos != string::npos)
  {
    return str.substr(pos + 1);
  }
  return "";
}


int main()
{

  string file("test.cpp");
  cout<< findfile(file) <<endl;

  return 0;
}

```



## 题 7：简单分割字符串

```

```

