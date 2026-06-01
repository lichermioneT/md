Linux 文件操作，真正核心的是：

# POSIX 文件 IO 接口

这是：

- Linux 系统编程
- C/C++ 后端
- 网络服务器
- 数据库
- 中间件
- Redis/Nginx/MySQL

的基础。

你需要分阶段掌握。

------

# 一、初级阶段（必须熟练）

这是：

# Linux 文件IO核心接口

------

## 1. open

打开文件。

```c
#include <fcntl.h>

int open(const char *pathname, int flags);
```

带权限：

```c
int open(const char *pathname, int flags, mode_t mode);
```

例如：

```c
int fd = open("test.txt", O_RDONLY);
```

------

## 2. close

关闭文件。

```c
#include <unistd.h>

int close(int fd);
```

------

## 3. read

读取文件。

```c
ssize_t read(int fd, void *buf, size_t count);
```

------

## 4. write

写文件。

```c
ssize_t write(int fd, const void *buf, size_t count);
```

------

## 5. lseek

移动文件偏移量。

```c
off_t lseek(int fd, off_t offset, int whence);
```

非常重要。

用于：

- 获取文件大小
- 随机读写
- 日志系统

------

# 二、必须理解的概念

------

# 1. 文件描述符 fd

Linux：

# 一切皆文件

例如：

```txt
0 -> stdin
1 -> stdout
2 -> stderr
```

open 后：

```txt
3
4
5
```

都是 fd。

------

# 2. 文件偏移量

每个 fd 内部都有：

```txt
当前读取位置
```

read/write 后：

```txt
自动移动
```

------

# 3. 内核缓冲区

用户：

```txt
read/write
```

实际上：

```txt
用户区
↕
内核缓冲区
↕
磁盘
```

------

# 三、中级阶段（必须掌握）

这些是真正 Linux 开发常用接口。

------

## 6. stat

获取文件属性。

```c
#include <sys/stat.h>

int stat(const char *path, struct stat *buf);
```

获取：

- 文件大小
- inode
- 权限
- 修改时间

------

## 7. fstat

根据 fd 获取属性。

```c
int fstat(int fd, struct stat *buf);
```

------

## 8. access

检查权限。

```c
int access(const char *pathname, int mode);
```

例如：

```c
access("test.txt", F_OK);
```

检查文件是否存在。

------

## 9. dup / dup2

复制文件描述符。

```c
int dup(int oldfd);

int dup2(int oldfd, int newfd);
```

这是：

# 重定向核心

例如：

```txt
ls > log.txt
```

底层就靠：

```txt
dup2
```

------

## 10. fsync

强制刷新磁盘。

```c
int fsync(int fd);
```

数据库特别重要。

------

## 11. unlink

删除文件。

```c
int unlink(const char *pathname);
```

Linux 删除文件本质：

```txt
删除目录项
```

------

## 12. rename

重命名。

```c
int rename(const char *oldpath, const char *newpath);
```

------

# 四、高级阶段（系统级开发）

------

## 13. mmap

内存映射。

```c
void *mmap(...);
```

极其重要。

用于：

- 文件映射
- 零拷贝
- 共享内存
- 数据库
- 高性能IO

------

## 14. munmap

解除映射。

```c
int munmap(void *addr, size_t length);
```

------

## 15. ioctl

设备控制。

```c
int ioctl(int fd, unsigned long request, ...);
```

驱动开发核心。

------

## 16. fcntl

文件控制。

```c
int fcntl(int fd, int cmd, ...);
```

用于：

- 非阻塞IO
- fd复制
- 文件锁

------

## 17. sendfile

零拷贝。

```c
ssize_t sendfile(...);
```

Nginx 高频使用。

------

# 五、目录操作（必须会）

------

## 18. opendir

打开目录。

```c
DIR *opendir(const char *name);
```

------

## 19. readdir

读取目录项。

```c
struct dirent *readdir(DIR *dirp);
```

------

## 20. closedir

关闭目录。

```c
int closedir(DIR *dirp);
```

------

# 六、文件系统必须理解

你以后必须理解：

------

# 1. inode

文件真正的数据结构。

文件名不是文件。

文件名：

```txt
只是inode映射
```

------

# 2. 硬链接

```txt
多个文件名
指向同一个inode
```

------

# 3. 软链接

类似：

```txt
Windows快捷方式
```

------

# 4. 文件删除原理

unlink 后：

```txt
引用计数-1
```

只有：

```txt
=0
```

才真正删除。

------

# 七、后端开发真正重要的接口

如果你走：

# C++ Linux 后端

必须重点掌握：

------

## 第一梯队（绝对核心）

```txt
open
close
read
write
lseek
stat
dup2
fcntl
mmap
```

------

## 第二梯队（高性能）

```txt
epoll
sendfile
splice
io_uring
```

------

## 第三梯队（工程化）

```txt
fsync
flock
fcntl锁
aio
```

------

# 八、学习路线（非常重要）

建议：

------

# 第一阶段

先学：

```txt
open
read
write
close
lseek
```

并自己写：

- cp
- cat
- echo
- tee

------

# 第二阶段

学习：

```txt
dup2
pipe
fork
exec
```

写：

# shell

------

# 第三阶段

学习：

```txt
mmap
sendfile
epoll
```

写：

- HTTP服务器
- Reactor网络库

------

# 九、真正高级程序员的理解

真正高手不会把：

```txt
文件
socket
pipe
tty
eventfd
epoll
```

分开。

因为 Linux：

# 一切皆文件

最后：

```txt
都是fd
```

所以：

```txt
read/write
```

能统一很多对象。