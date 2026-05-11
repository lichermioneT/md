#include <unistd.h>
#include <cstring>
#include <iostream>
#include <stdlib.h> 

using namespace std;

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    cout<< "uasge: ./a.out -a" << endl;
    exit(2);
  }
  
  if(strcmp("-a", argv[1]) ==0)
  {
    cout<< "方法a" <<endl;
  }
  else if (strcmp("-b", argv[1]) ==0)
  {
    cout<< "方法b" <<endl;
  }
  else if (strcmp("-ab", argv[1]) ==0)
  {
    cout<< "方法ab" <<endl;
  }
  else 
  {
    cout<< "方没有实现" <<endl;
  }
  return 0;
}
