#include <unistd.h>
#include <iostream>
#include <stdlib.h> 

using namespace std;
extern char** environ;

int main()
{
  for(int i = 0; environ[i]; ++i)
  {
    cout<< environ[i] << endl;
  }

  return 0;
}
