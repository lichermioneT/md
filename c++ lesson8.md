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
  cout<< "size:" <<s1.size() <<endl;
  cout<< "length:" <<s1.length() << endl;

  cout<< "capacity:"<< s1.capacity() <<endl;

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
  string sub = s.substr(1, 3);
  cout << sub <<endl;

  return 0;
}

```



## 7实现string

























