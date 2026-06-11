#include <iostream>
#include <vector>
using namespace std;

void print1(vector<int>& nums)
{
  vector<int>::iterator it = nums.begin();
  while(it != nums.end())
  {
      *it += 1;
      cout<< *it << " ";
      ++it;
  }
  cout<<endl;
}

void print2(const vector<int>& nums)
{
  vector<int>::const_iterator it = nums.cbegin();
  while(it != nums.cend())
  {
      cout<< *it << " ";
      ++it;
  }
  cout<<endl;
}

void print3(vector<int>& nums)
{
  vector<int>::reverse_iterator it = nums.rbegin();
  while(it != nums.rend())
  {
      *it -= 1;
      cout<< *it << " ";
      ++it;
  }
  cout<<endl;
}

void print4(const vector<int>& nums)
{
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
// 面向对象编程，学习第一步就是学习它的构造函数的。
// 1.vector的构造函数
  vector<int> v1;        // 无参数构造
  vector<int> v2(10);    // 有参数构造
  vector<int> v3(10, 22);// 10个22构造
  vector<int> v4(v2);    // 拷贝构造
  vector<int> v5(v4.begin(), v4.end()); // 迭代器构造
  vector<int> v6{1,2,3,4,5,6,7,8,9}; // c++的初始化列表。

// 2.vector底层是连续的空间。
// 容量相关的接口
  
  // size目前有多少个有效的元素
  cout<< v6.size() <<endl;
  v6.push_back(10);

  // capacity目前给你开辟的空间是多少。
  cout<< v6.capacity() <<endl;
  
  if(!v6.empty())
  {
    cout<< "v6 is not empty" <<endl;
  }
  else 
  {
    cout<< "v6 is empty" <<endl;
  }

  // resize 
  // 1.n=<size时，只需要改变一下size=n
  // 2.n>size时，只需要扩容到n，此时可以指定填充的数据的。
  v6.resize(17);
  v6.resize(18,2);
  for(auto e : v6)
  {
    cout<< e << " ";
  }
  cout<<endl;

  v6.reserve(10); // 小于和等于已经知道的空间，没有作用的。
  v6.reserve(24); // 只有大于才有效的。 


// 3.访问元素的接口
   // 四个迭代器需要掌握的和范围for
  // print1(v6);
  // print2(v6);
  // print3(v6);
  // print4(v6);
  
  // vector重载了operator[]的
  /*
   *for(size_t i = 0; i < v6.size();  ++i)
   *{
   *  cout<< v6[i] << " ";
   *}
   *cout<<endl;
   */
  //[]没有安全检查，at检查了范围的
  
  // 头部和尾部的元素
  // cout<< v6.front() <<endl;
  // cout<< v6.back() <<endl;
 
// 4.元素的插入
// 返回新插入元素的位置。
   vector<int> v7{1,2,3,4,5,6,7,8,9,10};
   v7.push_back(222);
   print2(v7);

   auto it = v7.insert(v7.begin(), 333);
   print2(v7);
   cout<< *it <<endl;

   v7.insert(v7.begin(), 2, 444);
   print2(v7);
   cout<< *it <<endl;

// 5.删除元素的接口
   v7.pop_back();
   it = v7.erase(v7.begin());
   it = v7.erase(v7.begin());
   cout<< *it <<endl;

// 7.迭代器失效的原理
  vector<int> v8{0,1,2,3,4,5,6,7,8,9};
  
  auto it1 = v8.begin() + 5;
  v8.insert(v8.begin(), 2222);
  cout<< *it1 <<endl;



  return 0;
}
