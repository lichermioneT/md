#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

int main()
{
  umask(0);
  cout<< "stdin:" << stdin->_fileno << endl;
  cout<< "stdou:" << stdout->_fileno << endl;
  cout<< "stderr:" << stderr->_fileno << endl;
  
  close(0);

  int fd = open("licher", O_RDWR | O_CREAT, 0666);
  if(fd == -1)
  {
    perror("open");
  }
  cout<< "fd:" << fd <<endl;
  return 0;
}
