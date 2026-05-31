#include <vector>
#include <iostream>
using namespace std;


int main()
{
// 1.size:一共有多少个数据和下一个数据待尾插的地方
// 2.capacity: 一共给你开辟了多少空间的。
// 3.empty: 是否为空的
  vector<int> v2 = {1, 3, 4, 5, 6, 7, 7, 8, 9, 10};
  cout<< "v2 size:" << v2.size() <<endl;
  cout<< "v2 capacity:" << v2.capacity() <<endl;
  cout<< "v2 empty:" << v2.empty() <<endl;
  v2.push_back(12);
  v2.push_back(13);
  v2.push_back(14);
  v2.push_back(12);
  v2.push_back(13);
  v2.push_back(14);
  v2.push_back(12);
  v2.push_back(13);
  v2.push_back(14);
  v2.push_back(14);
  v2.push_back(14);
  
  cout<< "after push_back" <<endl;
  cout<< "v2 size:" << v2.size() <<endl;
  cout<< "v2 capacity:" << v2.capacity() <<endl;
  cout<< "v2 empty:" << v2.empty() <<endl;

// 4.resize:改变有效数据的个数
  v2.resize(31, 44);
  for(auto e : v2)
  {
    cout<< e << " ";
  }
  cout<<endl;
  cout<< "after resize" <<endl;
  cout<< "v2 size:" << v2.size() <<endl;
  cout<< "v2 capacity:" << v2.capacity() <<endl;
  cout<< "v2 empty:" << v2.empty() <<endl;

// 5.reserve 预定多少个空间
  vector<int> v;
  v.reserve(10);
  cout<< "v size:" << v.size() <<endl;
  cout<< "v capacity:" << v.capacity() <<endl;
  cout<< "v empty:" << v.empty() <<endl;


  return 0;
}
