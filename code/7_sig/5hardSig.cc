#include <signal.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void hander(int signo)
{
  cout << "捕捉到信号:" << signo << endl;
  exit(12);
}

int main()
{
  // 标志位溢出是8号信号的
  signal(SIGFPE, hander);
  while(true)
  {
    sleep(1); 
    cout << "i a runing, pid:" << getpid() << endl;
    
    int a = 10;
    a /= 0;
  }
  
  return 0;
}
