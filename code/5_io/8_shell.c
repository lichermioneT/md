#include <unistd.h>
#include <sys/types.h>
#include <cassert>
#include <cstring>
#include <iostream>
#include <sys/wait.h>
using namespace std;

#define NONE_REDIR   0
#define INPUT_REDIR  1
#define OUTPUT_REDIR 2
#define APPEND_REDIR 3
int redirType = NONE_REDIR;
char*  redirFile = NULL;

void trimSpace(char* start)
{
  while(isspace(*start))
  {
    start++;
  }
}

void linecommd(char* line)
{
  assert(line); 
  // 1.指向字符的起始位置
  char* start = line;
  // 2.指向数组的\0;
  char* end = start + strlen(line); 
  while(start < end)
  {
    // 1.可能是输出重定向和追加重定向
    if(*start == '>')
    {
      *start = '\0';
      start++;
      if(*start == '>')
      {
        redirType = APPEND_REDIR;
        start++;
      }
      else 
      {
        redirType = OUTPUT_REDIR;
      }

      trimSpace(start);
      redirFile = start;
      break;
    }
    // 2.输出重定向
    else if(*start == '<')
    {
      *start = '\0';
      start++;

      trimSpace(start);
      redirType = INPUT_REDIR;
      redirFile = start;
      break;
    }
    // 跳过前面的数据
    else 
    {
      start++;
    }
  }


}


int main()
{
  while(true)
  {
    redirType = NONE_REDIR;
    redirFile = NULL;

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

  linecommd(buf);

// 3.获取命令行的参数
   char* argv[64] = {0};
  
   argv[0] = strtok(buf, " ");
  
   int i = 1;
   while((argv[i] = strtok(NULL, " ")) != NULL)
   {
     i++;
   }

    
// 4.内建指令处理
  
  // 4.1cd指令
  if(argv[0] != NULL && strcmp(argv[0], "cd") == 0)
  {
    if(argv[1] != NULL)
    {
      chdir(argv[1]);
    }
    continue;
  }
  //4...后面补充需要处理的内建指令信息的。

// 5.创建子进程
  pid_t id = fork();
  if(id == -1)
  {
    perror("fork");
    return -1;
  }

  if(id == 0)
  {
    switch(redirType)
    {
      // 1.没有重定向
      case NONE_REDIR: break;
      // 2.输入重定向
      case INPUT_REDIR:
      {
        int fd = open(redirFile, 0_RDO)
      }
    }
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
  }

  return 0;
}
