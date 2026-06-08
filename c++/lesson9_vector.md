## c++ lesson9

## 1.构造函数

**1.无参数构造**

**2.n个数据进行构造**

**3.拷贝狗构造**

**4.{}初始化列表**

**5.迭代器构造的。**

```c++
#include <vector>
#include <iostream>
using namespace std;

int main()
{
  vector<int> v1;
  vector<int> v2(10, -1);
  vector<int> v3(v2);
  vector<int> v4(v2.begin(), v2.begin() + 10);
  vector<int> v5 = {1, 3, 5, 7, 9, 11};

  for(auto e : v1)
  {
    cout << e;
  }
  cout<<endl;

  for(auto e : v2)
  {
    cout << e;
  }
  cout<<endl;

  for(auto e : v3)
  {
    cout << e;
  }
  cout<<endl;

  for(auto e : v4)
  {
    cout << e;
  }
  cout<<endl;

  for(auto e : v5)
  {
    cout << e;
  }
  cout<<endl;

  return 0;
}

```

**c++的迭代器都是[)的    左闭区间，右开区间。 [first, last)**

**C++ 中，只要是两个迭代器表示范围，基本都是左闭右开 `[first, last)`。**



## 2.迭代器

**1.正向和反向。**

**2.是否可以修改数据的。**

```c++
#include <vector>
#include <iostream>
using namespace std;

void print_arr(const vector<int>& nums)
{
// 2.第二种迭代器：cbegin + cend。正向的，可以读不能够写的。
  vector<int>::const_iterator it = nums.cbegin();
  
  while(it != nums.cend())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
}

void print_arr_re(const vector<int>& nums)
{
// 4.第四种迭代器：crbegin+crend。反向的。只能读，不能写的。
  vector<int>::const_reverse_iterator it = nums.crbegin();
  
  while(it != nums.crend())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
}

int main()
{
// 1.第一种迭代器：begin+end。正向的，可读可写的。
  vector<int> v2 = {1, 3, 4, 5, 6, 7, 7, 8, 9, 10};
  vector<int>::iterator it = v2.begin(); 

  while(it != v2.end())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
  
  print_arr(v2);

// 3.第三种迭代器：rbegin+rend。反向的可读可写的。
  vector<int>::reverse_iterator it2 = v2.rbegin();
  while(it2 != v2.rend())
  {
    cout<< *it2 << " ";
    ++it2;
  }
  cout<<endl;

  print_arr_re(v2);

  return 0;
}

```



## 3.空间的问题

**1.size: 里面有多少个有效数据 。最后一个尾插的数据的位置。**

**2.capacity; 目前给你开辟的空间是多少的。**

**3.empty： 空间是否是零的**

**4.resie:  1.如果新的n < size。则size直接变到n. 2等于则不变。 3.n > size. 需要填充到n去的。**

**5.reserve: 1.新的n <= capacity, 不变的。 >capacity。 开辟新的空间的n. **

```c++
#include <vector>
#include <iostream>
using namespace std;


int main()
{
// 1.size:一共有多少个数据和下一个数据待尾插的地方
// 2.capacity: 一共给你开辟了多少空间的。
// 3.empty: 是否为空的
  vector<int> v2 = {1, 3, 4, 5, 6, 7, 7, 8, 9, 10};
  cout<< "v2 size:" << v2.size() <<endl;
  cout<< "v2 capacity:" << v2.capacity() <<endl;
  cout<< "v2 empty:" << v2.empty() <<endl;
  v2.push_back(12);
  v2.push_back(13);
  v2.push_back(14);
  v2.push_back(12);
  v2.push_back(13);
  v2.push_back(14);
  v2.push_back(12);
  v2.push_back(13);
  v2.push_back(14);
  v2.push_back(14);
  v2.push_back(14);
  
  cout<< "after push_back" <<endl;
  cout<< "v2 size:" << v2.size() <<endl;
  cout<< "v2 capacity:" << v2.capacity() <<endl;
  cout<< "v2 empty:" << v2.empty() <<endl;

// 4.resize:改变有效数据的个数
  v2.resize(31, 44);
  for(auto e : v2)
  {
    cout<< e << " ";
  }
  cout<<endl;
  cout<< "after resize" <<endl;
  cout<< "v2 size:" << v2.size() <<endl;
  cout<< "v2 capacity:" << v2.capacity() <<endl;
  cout<< "v2 empty:" << v2.empty() <<endl;

// 5.reserve 预定多少个空间
  vector<int> v;
  v.reserve(10);
  cout<< "v size:" << v.size() <<endl;
  cout<< "v capacity:" << v.capacity() <<endl;
  cout<< "v empty:" << v.empty() <<endl;

  return 0;
}
```



## 4.增删查改

**插入/删除之后，原来的迭代器可能失效，所以函数必须返回一个“新的、还能继续用的位置”。**

**以 `vector/list/deque/string` 这类顺序容器为主：**

| 操作                 | 含义                      | 返回值                         |
| -------------------- | ------------------------- | ------------------------------ |
| `insert(pos, value)` | 在 `pos` 前插入元素       | 返回新插入元素的位置           |
| `erase(pos)`         | 删除 `pos` 位置元素       | 返回被删元素的下一个位置       |
| `erase(first, last)` | 删除 `[first, last)` 区间 | 返回 `last` 删除后对应的新位置 |

```c++
#include <vector>
#include <iostream>
using namespace std;


int main()
{
// push_back和pop_back，一个删除一个增减，简单
  vector<int> v2 = {1, 3, 4, 5, 6, 7, 7, 8, 9, 10};
  
// 1.insert插入只能是迭代器的，迭代器指向的位置插入数字，然后返回插入位置的迭代器
// 1.它返回的是已经插入的元素的位置，这样子不管是底层扩容不扩容都没有关系的。
  auto it = v2.insert(v2.begin() + 2, 88);
  for(auto e : v2)
  {
    cout<< e << " ";
  }
  cout<<endl;

  cout<< *it <<endl;
 
// 2.erase删除元素，传入迭代器的，返回的迭代器是删除元素后的位置的。
// 想象成一个一个往前面移动的样的。
  it =  v2.erase(v2.begin() + 2);
  cout<< *it <<endl;
  return 0;
}

```

## 5.模拟实现vector





























