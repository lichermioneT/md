# 5基础io

## 1文件操作的本质

**重新认识文件**

**1.空文件也要占磁盘空间的**

**2.文件 = 内容 + 属性**

**3.文件操作 == 属性操作 + 文件操作 + （文件内容 + 文件属性）**

**4.标定一个文件 必须使用 文件名+路径  唯一性**

**5.如果没有指定文件的路径，默认是当前路径访问文件。进程当前路径的。**

**6.OS接口，代码编译完成之后，形成的可以执行文件，但是没有运行，文件对应的操作没有被执行的。**

**7.一个文件没有被打开，可以直接访问吗？不可以的，一个文件要被访问，必须被进程打开的。**

**总结：**

**文件操作：进程和被打开文件的关系。**



## 2从谈文件操作

**1.c语言，c++，java, python, php, go , shell? 操作接口都不一样的**

 	**文件在哪里呢>>>>磁盘--》硬件---》os---》所有人想访问磁盘，都不能绕过os---》》使用os提供的接口--》可以，操	作    系统只有一个**

​	**---》上层语言无论如何变化，**

​	**a库函数必须 调用 系统调用接口**

​	**b库函数可以千变万化，但是底层不变--- 如何降低学习成本呢？**

**2.操作**

**c语言**

**r:只读打开，文件必须存在的。 r+:读写打开，文件必须存在的。**

**w:写文件打开，文件不存在就创建，存在则清理的。w+读写打开，每次都是新的写入。**

**a:向文本追加写入，文件不存在则创建，存在则不管，a+追加文件，每次都是新的追加**

![image-20260513102117877](picture/image-20260513102117877.png)

### 1.标记位传参



### 2.fopen接口

**fopen: r只是读，文件必须存在的。w写文件，文件不存在就创建的，新的写入。a追加文件，文件不存在就创建的，都是一次追加的。**

**fopen: r+读写，文件必须存在的。w+读写，文件不存在就创建的，新的写入。a+读写，文件不存在就创建的，都是一次追加的。**



**3.fgetc接口**

**代码示例**

```c
#include <stdio.h>

int main()
{
    FILE* fp = fopen("test.txt", "r");

    if(fp == NULL)
    {
        perror("fopen");
        return 1;
    }

    int ch;

    while((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }

    fclose(fp);

    return 0;
}
```

**注意读取文件的时候，注意文件指针的位置的。**



### 4.fgets接口

```c
#include <stdio.h>

int main()
{
    FILE* fp = fopen("test.txt", "r");

    if(fp == NULL)
    {
        perror("fopen");
        return 1;
    }

    char buf[1024];

    while(fgets(buf, sizeof(buf), fp) != NULL)
    {
        printf("%s", buf);
    }

    fclose(fp);

    return 0;
}
```

**1.读到 \n  **

**2.会自动填充零的。**



## 3系统接口



## 4系统文件I/O

**umask函数：当前进程的文件掩码。虽然他们是按位取反什么的。怎么感觉直接个减法就行了的。**

**open函数常用的宏**

**O_RDONLY:  只读打开**

**O_WRONLY:只写打开**

**O_RDWR:读写打开**

**O_CREAT:文件不存在，则创建，需要使用modet选项知名文件的权限。**

**O_APPEND:追加文件。**

**O_TRUNC:清除文件的内容，重新写的。**



**系统函数和语言函数的区别**

**c语言函数，本质上是对系统函数的封装。**

![image-20260513112938901](picture/image-20260513112938901.png)



## 5文件描述符fd

**linux文件描述的本质就是数组的下标。**

**最小原则：从零开始最小没有被分配的，就是新打开的。一个进程默认打开 0标准输入，1标准输出，2错误输出。**

**files_struct，里面有数组。file* fd_array[] 。**

![image-20260513135557649](picture/image-20260513135557649.png)

```c++
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

int main()
{
  umask(0);
  cout<< "stdin:" << stdin->_fileno << endl;
  cout<< "stdou:" << stdout->_fileno << endl;
  cout<< "stderr:" << stderr->_fileno << endl;
  
  close(0);

  int fd = open("licher", O_RDWR | O_CREAT, 0666);
  if(fd == -1)
  {
    perror("open");
  }
  cout<< "fd:" << fd <<endl;
  return 0;
}

```



## 6dup2接口

**`dup2(oldfd, newfd)` 会让 `newfd` 指向与 `oldfd` 完全相同的文件，相当于给一个打开的文件起了个“别名”。**

**如果 `newfd` 之前已经打开，它会先被自动关闭，然后再进行复制。**

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define METHON 2
#define OPT 2


int main()
{
  if(METHON == 1)
  {
#if OPT == 0
    close(0);

#elif OPT == 1
    close(1);

#elif OPT == 2
    close(2);

#endif
    umask(022);
    int fd = open("log.txt1", O_RDWR | O_APPEND | O_CREAT, 0666);
    if(fd == -1)
    {
      perror("open");
      return 1;
    }

    printf("fd:%d\n", fd);
  }
  else 
  {
    umask(022);
    int fd = open("log.txt1", O_RDWR | O_APPEND | O_CREAT, 0666);
    if(fd == -1)
    {
      perror("open");
      return 1;
    }

#if OPT == 0
    dup2(fd, 0);
    char buffer[1024] = {0};
    ssize_t n = read(fd, buffer, sizeof(buffer) - 1);
    if(n > 0)
    {
      buffer[n] = 0;
    }
    printf("%s\n", buffer);

#elif OPT == 1
    dup2(fd, 1);
    const char* name = "lichermionexTTTTTTTTTTTTT\n";
    write(fd, name, strlen(name));

#elif OPT == 2
    dup2(fd, 2);
    const char* name = "lichermionex---erron\n";
    write(fd, name, strlen(name));
      
#endif
    close(fd);
  }

  return 0;
}
```



## 7动静态库

























