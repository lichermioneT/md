#include <vector>
#include <iostream>
using namespace std;

void print_arr(const vector<int>& nums)
{
// 2.第二种迭代器：cbegin + cend。正向的，可以读不能够写的。
  vector<int>::const_iterator it = nums.cbegin();
  
  while(it != nums.cend())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
}

void print_arr_re(const vector<int>& nums)
{
// 4.第四种迭代器：crbegin+crend。反向的。只能读，不能写的。
  vector<int>::const_reverse_iterator it = nums.crbegin();
  
  while(it != nums.crend())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
}

int main()
{
// 1.第一种迭代器：begin+end。正向的，可读可写的。
  vector<int> v2 = {1, 3, 4, 5, 6, 7, 7, 8, 9, 10};
  vector<int>::iterator it = v2.begin(); 

  while(it != v2.end())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
  
  print_arr(v2);

// 3.第三种迭代器：rbegin+rend。反向的可读可写的。
  vector<int>::reverse_iterator it2 = v2.rbegin();
  while(it2 != v2.rend())
  {
    cout<< *it2 << " ";
    ++it2;
  }
  cout<<endl;

  print_arr_re(v2);

  return 0;
}
