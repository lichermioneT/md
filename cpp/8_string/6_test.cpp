#include <string>
#include <iostream>
using namespace std;

string findfile(string& str)
{
  size_t pos = str.rfind('.');
  if(pos != string::npos)
  {
    return str.substr(pos + 1);
  }
  return "";
}


int main()
{

  string file("test.cpp");
  cout<< findfile(file) <<endl;

  return 0;
}
