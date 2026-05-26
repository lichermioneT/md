#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s1("hello lichermionexxxxxxxxxxxx");
  string::iterator it = s1.begin();

  while(it != s1.end())
  {
    cout<< *it;
    ++it;
  }
  cout<<endl;

  return 0;
}
