#include <signal.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void hander(int signo)
{
  cout << "捕捉到信号:" << signo << endl;
}

// 0000 0000 ... 0000 0000 
// 后面的才是123信号的。
void print_pending(sigset_t& pending)
{
  for(int i = 31; i >= 1; i--)
  {
    if(sigismember(&pending, i))
    {
      cout<< 1;
    }
    else 
    {
      cout<< 0;
    }
  }
  cout<<endl;
}

int main()
{
// 1.自定义捕捉2号信号的处理。
  signal(2, hander); 
  
// 2.指定需要屏蔽的信号
  sigset_t block, oblock, pending;

// 3.清理
  sigemptyset(&block);
  sigemptyset(&oblock);
  sigemptyset(&pending);

// 4.添加屏蔽的信号
  sigaddset(&block, 2);


// 5.设置进内核里面
  
  // block里面已经对2号信号进行设置了的。
  // 如果2号信号来了，会在pending表里面的。
  // oblock里面全都是零的。
  sigprocmask(SIG_SETMASK, &block, &oblock);
  // SIG_SETMASK set =   block 
  // SIG_BLOCK   set |=  block 
  // SIG_UNBLOCK set &= ~block

// 看看我们的信号是否真的设置进内核了的
  int cnt = 0;
  while(true)
  {
    // 输出型参数，看看pending表是否有数据的,阻塞了的数据不会抵达的，就在pending里面的。
    sigpending(&pending); 
    // 打印pending表的，注意pending表示从后面才是1号信号的。
    print_pending(pending);   
    sleep(1);
    cnt++;

    // 5秒后解除阻塞的
    // 解除阻塞后马上抵达的。
    if(cnt == 5)
    {
      sigprocmask(SIG_SETMASK, &oblock, &block);
    }
  }
  
  return 0;
}
