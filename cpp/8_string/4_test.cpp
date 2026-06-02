#include <string>
#include <iostream>
using namespace std;

bool findsubstr(const string& str, const char* substr)
{
  size_t pos = str.find(substr);
  if(pos != string::npos)
  {
    return true;
  }
  else 
  {
    return false;
  }
}

int main()
{
  string s("hello world");
  const char* str = "world";
  const char* str1 = "xxxworld";

  cout<< findsubstr(s, str) <<endl;
  cout<< findsubstr(s, str1) <<endl;
  return 0;
}
