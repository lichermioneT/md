#include <unistd.h>
#include <iostream>
#include <stdlib.h> 

using namespace std;

int main()
{
  cout<< getenv("USER") << endl;
  cout<< getenv("PWD") << endl;
  cout<< getenv("HOME") << endl;
  cout<< getenv("PAHT") << endl;

  return 0;
}
