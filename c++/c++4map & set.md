# c++ map & set

## 1set

### 1.1 set的构造函数

```c++
#include <set>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
  // 1.无参数的构造函数
  set<int> s;
  
  // 2.迭代器的构造函数
  vector<int> v = {1, 3, 5, 7, 9, 10};
  set<int> s1(v.begin(), v.end());

  // 3.拷贝构造的构造函数
  set<int> s2(s1);

  for(auto& e : s)
  {
    cout<< e << " ";
  }
  cout<<endl;
  
  for(auto& e : s1)
  {
    cout<< e << " ";
  }
  cout<<endl;

  for(auto& e : s2)
  {
    cout<< e << " ";
  }
  cout<<endl;

  return 0;
}
```

**总结**

**set的底层是一颗红黑树的。**

**set不能够插入一样的元素的。**



### 1.2set的迭代器

```c++
#include <set>
#include <vector>
#include <iostream>
using namespace std;

void print_set(const set<int>& s)
{
  set<int>::const_iterator cit = s.cbegin();
  while(cit != s.cend())
  {
    cout<< *cit << " ";
    ++cit;
  }
  cout<<endl;
}

void print_reverse_set(const set<int>& s)
{
  set<int>::const_reverse_iterator crit = s.crbegin();
  while(crit != s.crend())
  {
     cout<< *crit << " ";
     ++crit;
  }
  cout<<endl;
}

int main()
{
  // 1.无参数的构造函数
  set<int> s;
  
  // 2.迭代器的构造函数
  vector<int> v = {1, 3, 5, 7, 9, 10,  10, 10, 10};
  set<int> s1(v.begin(), v.end());

  // 3.拷贝构造的构造函数
  set<int> s2(s1);

  
  set<int>::iterator it = s2.begin();
  while(it != s2.end())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
  print_set(s2);

  set<int>::reverse_iterator rit = s2.rbegin();
  while(rit != s2.rend())
  {
    cout<< *rit << " ";
    ++rit;
  }
  cout<<endl;
  print_reverse_set(s2); 

  return 0;
}

```

### 1.3 set的容量

```c++
#include <set>
#include <vector>
#include <iostream>
using namespace std;


int main()
{
  // 1.无参数的构造函数
  set<int> s;
  
  // 2.迭代器的构造函数
  vector<int> v = {1, 3, 5, 7, 9, 10,  10, 10, 10};
  set<int> s1(v.begin(), v.end());

  // 3.拷贝构造的构造函数
  set<int> s2(s1);
  
  // 简单判断是否为空和元素个数
  cout<< s2.empty() <<endl;  
  cout<< s2.size() <<endl;

  return 0;
}

```

**容量就两个： 是否为空和元素的个数。**

### 1.4 set的修改操作

**insert 操作**

```c++
#include <set>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
  // 1.无参数的构造函数
  set<int> s;
  
  // 2.迭代器的构造函数
  vector<int> v = {1, 3, 5, 7, 9, 10,  10, 10, 10};
  set<int> s1(v.begin(), v.end());

  // 3.拷贝构造的构造函数
  set<int> s2(s1);

// 1.插入失败了的
  pair<set<int>::iterator, bool> ret;
  ret = s2.insert(10);
  cout<< *ret.first <<endl;
  cout<< ret.second <<endl;

// 2.插入成功了的 
  ret = s2.insert(11);
  cout<< *ret.first <<endl;
  cout<< ret.second <<endl;

  return 0;
}

```

**不管是否插入成功，返回pair的迭代都是元素的位置。  成功就是true，失败就是false。**

**补充知识**

```c++
template<class T1, class T2>
struct pair
{
    T1 first;
    T2 second;
};
```

```c++
pair<int, string> p = make_pair(1, "hello");
```



**erase操作**

```c++
#include <set>
#include <vector>
#include <iostream>
using namespace std;

void print_set(const set<int>& s)
{
  set<int>::const_iterator cit = s.cbegin();
  while(cit != s.cend())
  {
    cout<< *cit << " ";
    ++cit;
  }
  cout<<endl;
}

int main()
{
  // 1.无参数的构造函数
  set<int> s;
  
  // 2.迭代器的构造函数
  vector<int> v = {1, 3, 5, 7, 9, 10,  10, 10, 10};
  set<int> s1(v.begin(), v.end());

  // 3.拷贝构造的构造函数
  set<int> s2(s1);
  
  print_set(s2);
  auto it  = s2.erase(s2.begin()); 

  print_set(s2);
  cout<< *it <<endl;

  it = s2.erase(s2.begin());
  print_set(s2);
  cout<< *it <<endl;

  return 0;
}

```

**输出**

```
1 3 5 7 9 10 
3 5 7 9 10 
3
5 7 9 10 
5
```

**删除传入迭代器： 返回下一个位置的迭代器。**

```c++
#include <set>
#include <vector>
#include <iostream>
using namespace std;

void print_set(const set<int>& s)
{
  set<int>::const_iterator cit = s.cbegin();
  while(cit != s.cend())
  {
    cout<< *cit << " ";
    ++cit;
  }
  cout<<endl;
}

int main()
{
  // 1.无参数的构造函数
  set<int> s;
  
  // 2.迭代器的构造函数
  vector<int> v = {1, 3, 5, 7, 9, 10,  10, 10, 10};
  set<int> s1(v.begin(), v.end());

  // 3.拷贝构造的构造函数
  set<int> s2(s1);
  
  size_t i = s2.erase(10);
  cout<< i <<endl;

  i = s2.erase(10);
  cout<< i <<endl;

  return 0;
}

```

**传值删除的话；返回的删除元素个个数的。**

**传入迭代器区间的话：删除区间的元素的。**



**swap:交换set**

```c++
#include <set>
#include <vector>
#include <iostream>
using namespace std;

void print_set(const set<int>& s)
{
  set<int>::const_iterator cit = s.cbegin();
  while(cit != s.cend())
  {
    cout<< *cit << " ";
    ++cit;
  }
  cout<<endl;
}

int main()
{
  // 1.无参数的构造函数
  set<int> s;
  
  // 2.迭代器的构造函数
  vector<int> v = {1, 3, 5, 7, 9, 10,  10, 10, 10};
  set<int> s1(v.begin(), v.end());

  // 3.拷贝构造的构造函数
  set<int> s2(s1);
  s2.insert(0);  
  s2.insert(-1);  
  s2.insert(-3);  
  
  cout<< "s1:" <<endl;
  print_set(s1);
  cout<< "s2:" <<endl;
  print_set(s1);
  
  cout<< "after" <<endl;
  swap(s1, s2); 

  cout<< "s1:" <<endl;
  print_set(s1);
  cout<< "s2:" <<endl;
  print_set(s2);

  return 0;
}

```

**clear:情况set的元素。**



**find函数**

```c++
#include <set>
#include <vector>
#include <iostream>
using namespace std;

void print_set(const set<int>& s)
{
  set<int>::const_iterator cit = s.cbegin();
  while(cit != s.cend())
  {
    cout<< *cit << " ";
    ++cit;
  }
  cout<<endl;
}

int main()
{
  // 1.无参数的构造函数
  set<int> s;
  
  // 2.迭代器的构造函数
  vector<int> v = {1, 3, 5, 7, 9, 10,  10, 10, 10};
  set<int> s1(v.begin(), v.end());

  // 3.拷贝构造的构造函数
  set<int> s2(s1);
  set<int>::iterator it = s2.find(8);
  if(it != s2.end())
  {
    cout<< *it <<endl;
  }

  it = s2.find(10);
  if(it != s2.end())
  {
    cout<< *it <<endl;
  }

  return 0;
}
```



**count函数**

```c++
#include <set>
#include <vector>
#include <iostream>
using namespace std;

void print_set(const set<int>& s)
{
  set<int>::const_iterator cit = s.cbegin();
  while(cit != s.cend())
  {
    cout<< *cit << " ";
    ++cit;
  }
  cout<<endl;
}

int main()
{
  // 1.无参数的构造函数
  set<int> s;
  
  // 2.迭代器的构造函数
  vector<int> v = {1, 3, 5, 7, 9, 10,  10, 10, 10};
  set<int> s1(v.begin(), v.end());

  // 3.拷贝构造的构造函数
  set<int> s2(s1);
  
  size_t i = s2.count(10);
  cout<< i <<endl;


  size_t j = s2.count(100);
  cout<< j <<endl;


  return 0;
}

```



## 2map

### 2.1 map的构造函数

```c++
#include <map>
#include <string>
#include <iostream>
using namespace std;

int main()
{
// 1.使用默认的无参构造函数
  map<string, int> m;
  m["apple"] = 3;
  m["banana"] = 5;

  for(auto e : m)
  {
    cout<< e.first << ":" << e.second <<endl;
  }

// 2.c++11的初始化列表进行构造的。
  map<std::string, int> m2
  {
    {"apple", 3},
    {"banana", 5},
    {"orange", 8}
  };

  for(auto e : m2)
  {
    cout<< e.first << ":" << e.second <<endl;
  }

// 3.拷贝构造
  map<std::string, int> m3 = 
  {
    {"apple", 3},
    {"banana", 5}
  };
  
  // map<string, int> m4 = m3;  两种拷贝构造的写法
  map<string, int> m4(m3);

  for(auto e : m3)
  {
    cout<< e.first << ":" << e.second <<endl;
  }
  return 0;
}

```

**1.无参的构造函数。2.初始化列表。3.拷贝构造的**



### 2.1 map的迭代器

```c++
#include <map>
#include <string>
#include <iostream>
using namespace std;

void print_map(const map<string, int> m)
{
  map<string, int>::const_iterator cit = m.cbegin();
  while(cit != m.cend())
  {
    cout<< cit->first << ":" << cit->second <<endl;
    ++cit;
  }
}

void print_cr_map(const map<string, int>& m)
{
  map<string, int>::const_reverse_iterator crit = m.crbegin();
  while(crit != m.crend())
  {
    cout<< crit->first << ":" << crit->second <<endl;
    ++crit;
  }
}

int main()
{
// 2.c++11的初始化列表进行构造的。
  map<std::string, int> m2
  {
    {"apple", 3},
    {"banana", 5},
    {"orange", 8}
  };

// 1.正向可读可写
  map<string, int>::iterator it = m2.begin();
  while(it != m2.end())
  {
    cout<< it->first << ":" << it->second <<endl;
    ++it;
  }
// 2.正向只读的
  print_map(m2);

// 3.反向可读可写的
  map<string, int>::reverse_iterator rit = m2.rbegin();
  while(rit != m2.rend())
  {
    cout<< rit->first << ":" << rit->second <<endl;
    ++rit;
  }
// 4.返回只读的 
  print_cr_map(m2);

  return 0;
}

```



### 2.3 map的容量与元素访问

```c++
#include <map>
#include <string>
#include <iostream>
using namespace std;


int main()
{
// 2.c++11的初始化列表进行构造的。
  map<std::string, int> m2
  {
    {"apple", 3},
    {"banana", 5},
    {"orange", 8}
  };

  cout<< "m2.empty:" << m2.empty() <<endl;
  cout<< "m2.size:" << m2.size() <<endl;

// 1.Alice不存在的情况下
  // 这是会插入 int的默认构造。
  m2["Alice"];
  for(auto e : m2)
  {
    cout<< e.first << ":" << e.second << " ";
  }
  cout<<endl;

// 2.Alice存在的情况下，会把Alice的value值修改成2
  m2["Alice"] = 2;

  for(auto e : m2)
  {
    cout<< e.first << ":" << e.second << " ";
  }
  cout<<endl;
  return 0;
}

```



### 2.4  map中元素的修改

```c++
#include <map>
#include <string>
#include <iostream>
using namespace std;

int main()
{
// 2.c++11的初始化列表进行构造的。
  map<std::string, int> m2
  {
    {"apple", 3},
    {"banana", 5},
    {"orange", 8}
  };

  pair<string, int> value1("lic", 18);
  pair<string, int> value2("lic", 18);

 
// 1.insert的返回值是一个pair。pair的first是map的迭代器。第二个是bool值的。
  pair<map<string, int>::iterator, bool> ret =  m2.insert(value1);
 
// 2.插入成功，返回插入元素的位置的迭代器 bool变成true。
  if(ret.second)
  {
    cout<< ret.first->first <<endl;
    cout<< ret.first->second <<endl;
  }
  else 
  {
    cout<< "插入失败" <<endl;
    cout<< "现在key的value" << ret.first->second <<endl;
  }

// 3.插入失败，返回已经有key值的迭代器的位置，bool变成false
  ret =  m2.insert(value2);
  
  if(ret.second)
  {
    cout<< ret.first->first <<endl;
    cout<< ret.first->second <<endl;
  }
  else 
  {
    cout<< "插入失败" <<endl;
    cout<< "现在key的value" << ret.first->second <<endl;
  }
  return 0;
}

```



**删除元素**

```c++
#include <map>
#include <string>
#include <iostream>
using namespace std;

int main()
{
// 2.c++11的初始化列表进行构造的。
  map<std::string, int> m2
  {
    {"apple", 3},
    {"banana", 5},
    {"orange", 8}
  };

  map<string, int>::iterator it = m2.find("apple");
  if(it != m2.end())
  {
    cout<< it->first << ":" << it->second <<endl;
  }
  else 
  {
    cout<< "apple没有找到" <<endl; 
  }

// 1.erase传入迭代器，删除迭代所指向的元素。
//   返回值是下一个元素的迭代器。 注意可能下一个是end()的。
  it = m2.erase(it);
  if(it != m2.end())
  {
    cout<< "删除apple后的下一个元素的信息" <<endl;
    cout<< it->first << ":" << it->second <<endl;
  }

  size_t i = m2.erase("apple");
  if(i)
  {
    cout<< "apple 删除成功" <<endl;
  }
  else 
  {
    cout<< "不存在apple" <<endl;
  }

// 2.erase传入key删除，返回的是0和1.
  size_t j = m2.erase("banana");
  if(j)
  {
    cout<< "banana 删除成功" <<endl;
  }
  else 
  {
    cout<< "不存在banana" <<endl;
  }

// 3.erase还可以传入迭代器的区间，进行区间的删除。
  return 0;
}

```

**1.传入迭代器，存在则删除迭代器的数据，返回下一个位置的迭代器。 不存在则返回end。**

**2.传入key值， 存在则删除 返回1，不存在则返回0.**

**3.传入迭代器区间，删除区间的数据的。**



**find和count函数**

```c++
#include <map>
#include <string>
#include <iostream>
using namespace std;

int main()
{
// 2.c++11的初始化列表进行构造的。
  map<std::string, int> m2
  {
    {"apple", 3},
    {"banana", 5},
    {"orange", 8}
  };

  map<string, int>::iterator it = m2.find("apple");
  if(it != m2.end())
  {
    cout<< it->first << ":" << it->second <<endl;
  }
  else 
  {
    cout<< "没有找到apple" <<endl;
  }

  size_t i = m2.count("apple");
  if(i)
  {
    cout<< "apple 存在 " << i<< endl;
  }
  else 
  {
    cout<< "apple 不存在" << i<< endl;
  }


  return 0;
}

```



##  multiset



## multimap







## AVL







## 红黑树















































