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
