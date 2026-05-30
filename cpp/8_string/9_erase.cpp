#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s("lichermionxexx");
  
  size_t pos = s.find("c");
  s.erase(pos, 4);
  
  // limionxexx
  cout<< s << endl;

  return 0;
}
