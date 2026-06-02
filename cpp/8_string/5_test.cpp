#include <string>
#include <iostream>
using namespace std;

void findsubstr(string& str)
{
  /*
   *size_t i = 0;
   *for(size_t j = 0; j < str.size(); ++j)
   *{
   *  if(str[j] != ' ')
   *  {
   *    str[i++] = str[j];
   *  }
   *}
   */

  size_t pos = 0;
  while(pos != string::npos)
  {
    pos = str.find(' ');
    str.erase(pos);
  }
}

int main()
{
  string s("lic f f f f f f ff ");
  cout<< s <<endl;

  findsubstr(s);
  cout<< s <<endl;

  return 0;
}
