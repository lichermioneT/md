#include <signal.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void hander(int signo)
{
  cout << "捕捉到信号:" << signo << endl;
}


int main()
{
  struct sigaction act, oact;
  act.sa_handler = hander;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);
  sigaddset(&act.sa_mask, 3); // 屏蔽3号信号的

  sigaction(SIGINT, &act, &oact);
  while(true)
  {
    std::cout<< "process runing...." << std::endl;
    sleep(1);
  }

  return 0;

}
