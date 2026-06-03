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

























