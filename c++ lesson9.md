## c++ lesson9

## 1.构造函数

```c++
#include <vector>
#include <iostream>
using namespace std;

int main()
{
  vector<int> v1;
  vector<int> v2(10, -1);
  vector<int> v3(v2);
  vector<int> v4(v2.begin(), v2.begin() + 10);
  vector<int> v5 = {1, 3, 5, 7, 9, 11};

  for(auto e : v1)
  {
    cout << e;
  }
  cout<<endl;

  for(auto e : v2)
  {
    cout << e;
  }
  cout<<endl;

  for(auto e : v3)
  {
    cout << e;
  }
  cout<<endl;

  for(auto e : v4)
  {
    cout << e;
  }
  cout<<endl;

  for(auto e : v5)
  {
    cout << e;
  }
  cout<<endl;

  return 0;
}

```

