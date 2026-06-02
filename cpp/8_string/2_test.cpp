#include <string>
#include <iostream>
using namespace std;

bool loopstr(const string& str)
{
  int left = 0;
  int right = str.size() - 1;
  
  while(left < right)
  {
    if(str[left] != str[right])
    {
      return false;
    }

    left++;
    right--;
  }

  return true;
}

int main()
{

  cout<< loopstr("level") <<endl;
  cout<< loopstr("hello") <<endl;

  return 0;
}
