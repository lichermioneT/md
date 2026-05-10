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
// 对2号信号进行捕捉，填充PCB:指向的信号处理方法的函数指针数组。
  signal(2, hander);
  while(true)
  {
    sleep(1); 
    cout << "i a runing, pid:" << getpid() << endl;
  }
  
  return 0;
}
