#include <string>
#include <iostream>
using namespace std;


int main()
{
  string s("lichermionxe");

  cout<< s <<endl;
  cout<< s.erase(0,1) <<endl;
  cout<< s.erase(0,1) <<endl;
  cout<< s.erase(0,1) <<endl;

  string::iterator it = s.begin(); 
  it = s.erase(it);
  cout<< s <<endl;
  cout<< *it <<endl;


  return 0;
}
