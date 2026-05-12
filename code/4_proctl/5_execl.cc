#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
using namespace std;

int main()
{

  pid_t id = fork();
  if(id == -1)
  {
    perror("fork");
    return -1;
  }

  if(id == 0)
  {
    execl("/usr/bin/ls", "ls", "-a", "-l", "-h", "/", NULL);
  }

  int status = 0;
  int ret = waitpid(id, &status, 0);
  if(ret == -1)
  {
    perror("waitpid");
    return -1;
  }

  cout<<endl;
  if(WIFEXITED(status))
  {
    cout<< "wait success pid:" << ret << endl;
    cout<< "exie_code:" << WEXITSTATUS(status) <<endl;
  }
  else if(WIFSIGNALED(status))
  {
    cout<< "wait success pid:" << ret << endl;
    cout<< "sig_number:" << WTERMSIG(status) << endl;
  }

  return 0;
}
