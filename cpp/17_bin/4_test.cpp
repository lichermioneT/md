#include <set>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
  // 1.无参数的构造函数
  set<int> s;
  
  // 2.迭代器的构造函数
  vector<int> v = {1, 3, 5, 7, 9, 10,  10, 10, 10};
  set<int> s1(v.begin(), v.end());

  // 3.拷贝构造的构造函数
  set<int> s2(s1);

// 1.插入失败了的
  pair<set<int>::iterator, bool> ret;
  ret = s2.insert(10);
  cout<< *ret.first <<endl;
  cout<< ret.second <<endl;

// 2.插入成功了的 
  ret = s2.insert(11);
  cout<< *ret.first <<endl;
  cout<< ret.second <<endl;

  return 0;
}
