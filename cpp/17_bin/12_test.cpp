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
