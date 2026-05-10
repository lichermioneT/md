#include <signal.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    cout<< "usage: ./a.out pid signumber" << endl;
    exit(3);
  }

  pid_t id = atoi(argv[1]);
  pid_t sig = atoi(argv[2]);
 
// kill函数这里模拟实现的是，linux的值 kill指令的
  int n = kill(id, sig);
  if(n == -1)
  {
    perror("kill");
    exit(2);
  }

  return 0;
}
