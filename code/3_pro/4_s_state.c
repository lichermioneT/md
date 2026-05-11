#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{
  int a = 0;
  while(true)
  {
    sleep(1);
    cout<< "a:" << a << endl;
  }
  return 0;
}
