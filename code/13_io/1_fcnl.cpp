#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main()
{
  int flag = fcntl(0, F_GETFL);
  if(flag < 0)
  {
    perror("fcntl");
    return -1;
  }

  if(fcntl(0, F_SETFL, flag | O_NONBLOCK) < 0)
  {
    perror("F_SETFL");
    return -1;
  }

  char buf[1024];
  while(true)
  {
    int n = read(0, buf, sizeof(buf) - 1);
    if(n > 0)
    {
      buf[n] = '\0';
      std::cout<< buf << std::endl;
    }
    else if(n == 0)
    {
      std::cout<< "stdio close" <<std::endl;
    }
    else 
    {
      if(errno == EAGAIN || errno == EWOULDBLOCK)
      {
        std::cout<< "no data try again" << std::endl;
        sleep(1);
        continue;
      }
      else if(errno == EINTR)
      {
        continue;
      }
      else 
      {
        perror("read");
        break;
      }
    }
  }

  return 0;
}
