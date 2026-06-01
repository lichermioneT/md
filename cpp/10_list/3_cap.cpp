#include <list>
#include <iostream>
using namespace std;

int main()
{
// 5.数组也是一种迭代器的
  int arr[] = {1, 3, 4, 5, 9};
  list<int> l5(arr, arr + sizeof(arr) / sizeof(arr[0]));
  
  cout<< "l5.empty:"<< l5.empty() <<endl;
  cout<< "l5.size:" << l5.size() <<endl;

  cout<< "flist element:" << l5.front() <<endl;
  cout<< "last  element:" << l5.back() <<endl;

  return 0;
}
