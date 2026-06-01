# c++ lesson10

## 1list

**list带头双向循环链表**



## 2list的构造函数

```c++
#include <list>
#include <iostream>
using namespace std;

int main()
{
// 1.无参数构造
  list<int> l1;

// 2.n个数据构造
  list<int> l2(10, 33);

// 3.迭代器构[begin, end) z这个区间里面的。
  list<int> l3(l2.begin(), l2.end());

// 4.拷贝构造,已知的对象拷贝一个新的对象的。
  list<int> l4(l3);

// 5.数组也是一种迭代器的
  int arr[] = {1, 3, 4, 5, 9};
  list<int> l5(arr, arr + sizeof(arr) / sizeof(arr[0]));

  for(auto e : l1)
  {
    cout<< e << " ";
  }
  cout<<endl;

  for(auto e : l2)
  {
    cout<< e << " ";
  }
  cout<<endl;

  for(auto e : l3)
  {
    cout<< e << " ";
  }
  cout<<endl;

  for(auto e : l4)
  {
    cout<< e << " ";
  }
  cout<<endl;

  for(auto e : l5)
  {
    cout<< e << " ";
  }
  cout<<endl;
  return 0;
}

```

**总结**

**1.无参数构造。2.n个数据构造。3.拷贝构造。4.迭代器构造的。**



## 3list的迭代器

```c++
#include <list>
#include <iostream>
using namespace std;

void print_list(const list<int>& l)
{
  list<int>::const_iterator it = l.cbegin();
  while(it != l.cend())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
}

void  print_list_re(const list<int> l)
{
  list<int>::const_reverse_iterator it = l.crbegin();
  while(it != l.crend())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
}

int main()
{
// 5.数组也是一种迭代器的
  int arr[] = {1, 3, 4, 5, 9};
  list<int> l5(arr, arr + sizeof(arr) / sizeof(arr[0]));
  
  list<int>::iterator it = l5.begin();
  while(it != l5.end())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;

  print_list(l5);

  list<int>::reverse_iterator it2 = l5.rbegin();
  while(it2 != l5.rend())
  {
    cout<< *it2 << " ";
    ++it2;
  }
  cout<<endl;

  print_list_re(l5);

  return 0;
}
```

**总结**

**1.正向可读可写**

**2.正向可读不可写**

**3.反向可读可写**

**4.反向可读不可写**



## 4容量相关

```c++
#include <list>
#include <iostream>
using namespace std;

int main()
{
// 5.数组也是一种迭代器的
  int arr[] = {1, 3, 4, 5, 9};
  list<int> l5(arr, arr + sizeof(arr) / sizeof(arr[0]));
  
  cout<< "l5.empty:"<< l5.empty() <<endl;
  cout<< "l5.size:" << l5.size() <<endl;

  cout<< "flist element:" << l5.front() <<endl;
  cout<< "last  element:" << l5.back() <<endl;

  return 0;
}

```

**总结**

**list只有判断元素个数和是否为空的成员结口**

**以及第一个和最后一个元素的接口。**



## 5元素修改

```c++
#include <list>
#include <iostream>
using namespace std;

void print_list(const list<int>& l)
{
  list<int>::const_iterator it = l.cbegin();
  while(it != l.cend())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
}

int main()
{
// 5.数组也是一种迭代器的
  int arr[] = {1, 3, 4, 5, 9};
  list<int> l5(arr, arr + sizeof(arr) / sizeof(arr[0]));

// 头插头删 + 尾插尾巴删 vector只有尾巴插入，头插需要insert的。
// list因为是双向带头的很方便的。
  /*
   *print_list(l5);
   *l5.push_back(444);
   *print_list(l5);
   *l5.pop_back();
   *print_list(l5);
   *l5.push_front(4);
   *print_list(l5);
   *l5.pop_front();
   *print_list(l5);
   */

// insert进行插入元素。
// 1.指定的位置进行插入，相当于指定位置开始全部往后面移动。
// 2.返回插入元素的的位置
  print_list(l5);
  list<int>::iterator it = l5.begin();
  ++it;
  ++it;
  
  it = l5.insert(it, 88);
  print_list(l5);
  cout<< "*it:" << *it << endl;


  it = l5.erase(l5.begin());
  print_list(l5);
  cout<< "*it:" << *it << endl;

  return 0;
}

```

**总结**

**insert(pos, x)：在 pos 前面插入 x，返回新插入节点的迭代器。**

**erase(pos)：删除 pos 指向的节点，返回被删节点的下一个迭代器。**



## 6模拟实现list

































































































