#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s1("hello lichermionexxxxxxxxxxxx");
  string::reverse_iterator it = s1.rbegin();

  while(it != s1.rend())
  {
    cout<< *it;
    ++it;
  }
  cout<<endl;

  return 0;
}
