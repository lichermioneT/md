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

int main()
{
// 5.数组也是一种迭代器的
  int arr[] = {1, 3, 4, 5, 9};
  list<int> l5(arr, arr + sizeof(arr) / sizeof(arr[0]));

// 头插头删 + 尾插尾巴删 vector只有尾巴插入，头插需要insert的。
// list因为是双向带头的很方便的。
  /*
   *print_list(l5);
   *l5.push_back(444);
   *print_list(l5);
   *l5.pop_back();
   *print_list(l5);
   *l5.push_front(4);
   *print_list(l5);
   *l5.pop_front();
   *print_list(l5);
   */


// insert进行插入元素。
// 1.指定的位置进行插入，相当于指定位置开始全部往后面移动。
// 2.返回插入元素的的位置
  print_list(l5);
  list<int>::iterator it = l5.begin();
  ++it;
  ++it;
  
  it = l5.insert(it, 88);
  print_list(l5);
  cout<< "*it:" << *it << endl;


  it = l5.erase(l5.begin());
  print_list(l5);
  cout<< "*it:" << *it << endl;



  return 0;
}
