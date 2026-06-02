#include <string>
#include <iostream>
using namespace std;

int countChar(const string& str, char ch)
{
  int ret = 0;
  for(auto e : str)
  {
    if(e == ch)
    {
      ret++;
    }
  }
  return ret;
}

int main()
{
  string s = "hello world";
  cout<< countChar(s, 'l') <<endl;

  return 0;
}
