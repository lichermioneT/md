# c++ lesson11

## 1stack

```c++
#include <stack>
#include <iostream>
using namespace std;

int main()
{
  stack<int> st;

  for(int i = 0; i < 10; ++i)
  {
    st.push(i + 1);
  }

  while(!st.empty())
  {
    cout<< st.top() << " ";
    st.pop();
  }
  cout<<endl;

  return 0;
}

```

**总结：stack。先进后出。进出都是一个窗口的。**



## 2queue

```c++
#include <iostream>
#include <queue>
using namespace std;

int main()
{
  queue<int> q;
  for(int i = 0; i < 10; ++i)
  {
    q.push(i + 1);
  }

  while(!q.empty())
  {
    cout<< q.front() << " ";
    q.pop();
  }
  cout<<endl;

  return 0;
}

```

**总结： queue:先进先出**



