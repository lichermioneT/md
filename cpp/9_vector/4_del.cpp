#include <vector>
#include <iostream>
using namespace std;


int main()
{
// push_back和pop_back，一个删除一个增减，简单
  vector<int> v2 = {1, 3, 4, 5, 6, 7, 7, 8, 9, 10};
  
// 1.insert插入只能是迭代器的，迭代器指向的位置插入数字，然后返回插入位置的迭代器
// 1.它返回的是已经插入的元素的位置，这样子不管是底层扩容不扩容都没有关系的。
  auto it = v2.insert(v2.begin() + 2, 88);
  for(auto e : v2)
  {
    cout<< e << " ";
  }
  cout<<endl;

  cout<< *it <<endl;
 
// 2.erase删除元素，传入迭代器的，返回的迭代器是删除元素后的位置的。
// 想象成一个一个往前面移动的样的。
  it =  v2.erase(v2.begin() + 2);
  cout<< *it <<endl;
  return 0;
}
