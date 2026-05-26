#include <string>
#include <iostream>
using namespace std;

int main()
{
  string s1("hello lichermionexxxxxxxxxxxx");
  size_t size = s1.size();
  for(size_t i = 0; i < size; ++i)
  {
    cout<< s1[i];
  }

  cout<<endl;
  return 0;
}
