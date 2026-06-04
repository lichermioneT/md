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
