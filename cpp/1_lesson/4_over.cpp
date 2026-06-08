#include <iostream>
#include <string>
using namespace std;

void print(int x)
{
  cout<< "x" << x <<endl;
}

void print(int x, char ch)
{
  cout<< "x:" << x << " " << "ch:" << ch <<endl;
}

void print(const string& s)
{
  cout<< s <<endl;
}


int main()
{
  string s("ssssssssssssssssssssss");
  print(10);
  print(s);
  print(22,'w');

  return 0;
}
