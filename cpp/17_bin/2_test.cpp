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
