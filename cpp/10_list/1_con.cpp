#include <list>
#include <iostream>
using namespace std;

int main()
{
// 1.无参数构造
  list<int> l1;

// 2.n个数据构造
  list<int> l2(10, 33);

// 3.迭代器构[begin, end) z这个区间里面的。
  list<int> l3(l2.begin(), l2.end());

// 4.拷贝构造,已知的对象拷贝一个新的对象的。
  list<int> l4(l3);

// 5.数组也是一种迭代器的
  int arr[] = {1, 3, 4, 5, 9};
  list<int> l5(arr, arr + sizeof(arr) / sizeof(arr[0]));

  for(auto e : l1)
  {
    cout<< e << " ";
  }
  cout<<endl;

  for(auto e : l2)
  {
    cout<< e << " ";
  }
  cout<<endl;

  for(auto e : l3)
  {
    cout<< e << " ";
  }
  cout<<endl;

  for(auto e : l4)
  {
    cout<< e << " ";
  }
  cout<<endl;

  for(auto e : l5)
  {
    cout<< e << " ";
  }
  cout<<endl;
  return 0;
}
