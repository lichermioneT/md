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
