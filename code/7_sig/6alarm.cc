#include <signal.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int cnt = 0;
void hander(int signo)
{
  cout << "捕捉到信号:" << signo << endl;
  cout << "cnt:" << cnt << endl; 
  exit(12);
}

int main()
{
  signal(SIGALRM, hander);
  alarm(1);
  while(true)
  {
    cnt++;
  }
  
  return 0;
}
