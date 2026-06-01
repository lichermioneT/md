#include <list>
#include <iostream>
using namespace std;

void print_list(const list<int>& l)
{
  list<int>::const_iterator it = l.cbegin();
  while(it != l.cend())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
}

void  print_list_re(const list<int> l)
{
  list<int>::const_reverse_iterator it = l.crbegin();
  while(it != l.crend())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;
}

int main()
{
// 5.数组也是一种迭代器的
  int arr[] = {1, 3, 4, 5, 9};
  list<int> l5(arr, arr + sizeof(arr) / sizeof(arr[0]));
  
  list<int>::iterator it = l5.begin();
  while(it != l5.end())
  {
    cout<< *it << " ";
    ++it;
  }
  cout<<endl;

  print_list(l5);

  list<int>::reverse_iterator it2 = l5.rbegin();
  while(it2 != l5.rend())
  {
    cout<< *it2 << " ";
    ++it2;
  }
  cout<<endl;

  print_list_re(l5);

  return 0;
}
