#include <unistd.h>
#include <csignal>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <iostream>
using namespace std;

void sig(int sig)
{
  cout<< "信号被捕捉了"<< sig <<endl;
}

int main()
{
// 1.创建一个匿名管道的文件,注意没目的是让子进程继承下去的。
  int fds[2] = {0};
  int n = pipe(fds);
  if(n == -1)
  {
    perror("pipe");
    return -1;
  }

// 2.创建子进程，子进程会继承父进程的文件描述符的。
  pid_t id = fork();
  if(id == -1)
  {
    perror("fork");
    return -2;
  }

// 3.匿名管道是半双工，只能一个方向进行通信的。
  if(id == 0)
  {
    // 3.1子进程继承了读端和写端的，这里我们关闭0,就是关闭读端。
    close(fds[0]);
    close(fds[1]);
    sleep(222);
  }
  
  // 3.2父进程我能关闭的是写端
  
  close(fds[1]);
  signal(SIGPIPE, sig);

  char buf[1024];
  while(true)
  {
    snprintf(buf, sizeof(buf), "ddddd");
    write(fds[1], buf, strlen(buf));
  }
  


// 4.回收子进程，一般就是子进程的信号和退出码
  int status = 0;
  int ret =  waitpid(id, &status, 0);
  if(ret == -1)
  {
    perror("waitpid");
    return -1;
  }

  if(WIFEXITED(status))
  {
    cout<< "exit_code:" << WEXITSTATUS(status) << endl;
  }
  if(WIFSIGNALED(status))
  {
    cout<< "sig_number:" << WTERMSIG(status) << endl;
  }

  return 0;
}
