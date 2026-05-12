#include <iostream>
#include <unistd.h>
#include <cstdio>
using namespace std;

#define opt 3

int main()
{
#if opt == 1

  cout<< "a process" <<endl;
  exit(1);

#elif opt == 2

  printf("aaaaaaaaaaaaaa");
  sleep(3);
  exit(2);
  
#elif opt == 3

  printf("aaaaaaaaaaaaaa");
  sleep(3);
  _exit(1);

#endif 

  return 0;
}
