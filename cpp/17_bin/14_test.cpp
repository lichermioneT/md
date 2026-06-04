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
