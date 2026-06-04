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
