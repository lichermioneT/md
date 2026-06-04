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
