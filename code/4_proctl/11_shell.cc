#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sys/wait.h>
using namespace std;

int main()
{
// 1.获取命令行的参数
  char buf[128] = {0};
  cout<< "输入指令:";
  char* s = fgets(buf, sizeof(buf), stdin);
  if(s == NULL)
  {
    perror("fgets");
  }
  
  /*
   *abcde\n 6-1=5;   
   */
// 2.清除\n
  buf[strlen(buf)-1] = '\0';

// 3.获取命令行的参数
   char* argv[64] = {0};
  
   argv[0] = strtok(buf, " ");
  
   int i = 1;
   while((argv[i] = strtok(NULL, " ")) != NULL)
   {
     i++;
   }

// 4.创建子进程
  pid_t id = fork();
  if(id == -1)
  {
    perror("fork");
    return -1;
  }

  if(id == 0)
  {
    execvp(argv[0], argv);
    perror("execvp");
    exit(1);
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
