#include <unistd.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[], char* env[])
{
  (void)argc;
  (void)argv;
  for(int i = 0; env[i]; ++i)
  {
    cout<< env[i] << endl;
  }

  return 0;
}
