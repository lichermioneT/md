#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{
  while(true)
  {
    cout<< "pid:" << getpid() << endl;
    sleep(1);
  }

  // kill -19 发送19号信号让进程停止
  // kill -18 发送18号信号让进程恢复
  // 注意恢复了，就变成后台进程了，需要kill -9才能终止的
  return 0;
}
