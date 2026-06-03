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
  s2.insert(0);  
  s2.insert(-1);  
  s2.insert(-3);  
  
  cout<< "s1:" <<endl;
  print_set(s1);
  cout<< "s2:" <<endl;
  print_set(s1);
  
  cout<< "after" <<endl;
  swap(s1, s2); 

  cout<< "s1:" <<endl;
  print_set(s1);
  cout<< "s2:" <<endl;
  print_set(s2);

  return 0;
}
