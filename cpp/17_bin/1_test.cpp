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

  for(auto& e : s)
  {
    cout<< e << " ";
  }
  cout<<endl;
  
  for(auto& e : s1)
  {
    cout<< e << " ";
  }
  cout<<endl;

  for(auto& e : s2)
  {
    cout<< e << " ";
  }
  cout<<endl;

  return 0;
}
