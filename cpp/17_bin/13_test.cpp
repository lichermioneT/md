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
