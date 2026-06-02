#include <string>
#include <iostream>
using namespace std;

void rever(string& str)
{
  int left = 0;
  int right =  str.size()-1;

  while(left < right)
  {
    swap(str[left], str[right]);
    left++;
    right--;
  }
}

int main()
{
  string s("lichermionxe");
  cout<< s <<endl;

  rever(s);
  cout<< s <<endl;

  return 0;
}
