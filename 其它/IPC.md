# IPC



Linux 进程间通信叫 **IPC：Inter-Process Communication**。

你可以按这条主线学：

```txt
文件描述符基础
  ↓
匿名管道 pipe
  ↓
命名管道 FIFO
  ↓
信号 signal
  ↓
消息队列 message queue
  ↓
共享内存 shared memory
  ↓
信号量 semaphore / 互斥锁
  ↓
Unix 域套接字 socket
  ↓
网络 socket / epoll
```

------

# 一、Linux 进程间通信有哪些？

常见 IPC 方式主要有这些：

| IPC 方式                 | 作用                 | 难度 | 重点                       |
| ------------------------ | -------------------- | ---- | -------------------------- |
| 匿名管道 `pipe`          | 有亲缘关系进程通信   | 简单 | 父子进程通信               |
| 命名管道 `FIFO`          | 无亲缘关系进程通信   | 简单 | 通过文件名通信             |
| 信号 `signal`            | 通知某个进程发生事件 | 中等 | 异步通知，不适合传大量数据 |
| 消息队列 `message queue` | 按消息为单位传数据   | 中等 | 自带消息边界               |
| 共享内存 `shared memory` | 多进程共享一块内存   | 较难 | 速度最快，但要同步         |
| 信号量 `semaphore`       | 控制资源访问顺序     | 较难 | 常配合共享内存使用         |
| 内存映射 `mmap`          | 文件/内存映射共享    | 较难 | 可实现共享内存             |
| Unix 域套接字            | 本机进程通信         | 较难 | 功能强，类似网络 socket    |
| TCP/UDP socket           | 跨主机通信           | 较难 | 网络通信基础               |
| 文件锁 `flock/fcntl`     | 多进程互斥访问文件   | 中等 | 文件级同步                 |
| `eventfd`                | 进程/线程事件通知    | 进阶 | 常用于高性能事件通知       |

------

# 二、推荐你的学习顺序

你现在已经学过 `fork`、`pipe`、进程池，所以可以这样循序渐进：

------

## 第一阶段：先掌握文件描述符基础

这是 IPC 的根基。

你要先彻底理解：

```c
open
close
read
write
dup
dup2
pipe
fork
```

核心问题：

```txt
1. 文件描述符是什么？
2. fork 后子进程会继承哪些 fd？
3. 为什么父进程要关闭读端？
4. 为什么子进程要关闭写端？
5. 管道什么时候 read 阻塞？
6. 管道什么时候 read 返回 0？
7. 管道什么时候触发 SIGPIPE？
```

你之前的进程池代码，本质上就是：

```txt
父进程 write 管道
子进程 read 管道
```

所以这一步你已经在入门了。

------

## 第二阶段：匿名管道 pipe

这是最适合入门的 IPC。

匿名管道特点：

```txt
1. 只能用于有亲缘关系的进程
2. 比如父子进程、兄弟进程
3. 本质是内核维护的一段缓冲区
4. 一端读，一端写
5. 半双工通信
```

典型代码结构：

```c
int fds[2];
pipe(fds);

pid_t id = fork();

if (id == 0)
{
    // child
    close(fds[1]);
    read(fds[0], buffer, sizeof(buffer));
}
else
{
    // parent
    close(fds[0]);
    write(fds[1], msg, strlen(msg));
}
```

这一阶段你要重点练：

```txt
父进程给子进程发数据
子进程给父进程发数据
父进程创建多个子进程，每个子进程一条管道
用管道实现简单进程池
```

你现在的代码就属于这个阶段。

------

## 第三阶段：命名管道 FIFO

匿名管道要求进程之间有亲缘关系。

但是如果两个进程完全没有关系，比如：

```txt
进程 A
进程 B
```

它们不是父子进程，这时候匿名管道就不方便了。

所以需要命名管道：

```c
mkfifo("myfifo", 0666);
```

它会在文件系统中创建一个管道文件：

```txt
myfifo
```

然后一个进程写：

```c
int fd = open("myfifo", O_WRONLY);
write(fd, "hello", 5);
```

另一个进程读：

```c
int fd = open("myfifo", O_RDONLY);
read(fd, buffer, sizeof(buffer));
```

FIFO 的重点是：

```txt
1. 它不是普通文件
2. 数据不会真正写入磁盘
3. 本质还是内核缓冲区
4. 通过路径名让无亲缘关系进程找到同一个管道
```

------

## 第四阶段：信号 signal

信号不是用来传大量数据的，而是用来做通知。

比如：

```txt
Ctrl + C 发送 SIGINT
kill -9 pid 发送 SIGKILL
子进程退出发送 SIGCHLD 给父进程
管道写端关闭后继续写可能触发 SIGPIPE
```

常见信号：

| 信号      | 含义                     |
| --------- | ------------------------ |
| `SIGINT`  | 终端中断，Ctrl+C         |
| `SIGKILL` | 强制杀死进程             |
| `SIGTERM` | 请求进程退出             |
| `SIGCHLD` | 子进程退出通知父进程     |
| `SIGPIPE` | 管道读端关闭，写端继续写 |
| `SIGALRM` | 定时器信号               |
| `SIGSTOP` | 暂停进程                 |
| `SIGCONT` | 继续进程                 |

你要重点掌握：

```c
signal()
sigaction()
kill()
raise()
alarm()
pause()
```

尤其是：

```c
waitpid(-1, &status, WNOHANG);
```

配合 `SIGCHLD` 回收子进程。

------

# 三、前面四个是基础必学

到这里，你应该掌握：

```txt
pipe       —— 父子进程传数据
FIFO       —— 无亲缘关系进程传数据
signal     —— 进程之间发通知
waitpid    —— 父进程回收子进程
```

这几个学完之后，你对 Linux 进程通信就已经有基础框架了。

------

# 四、第五阶段：消息队列

消息队列和管道有点像，都是传数据。

但是区别是：

```txt
管道：字节流，没有明显消息边界
消息队列：一条一条消息，有消息边界
```

比如管道中写：

```txt
hello
world
```

读的时候可能一次读到：

```txt
helloworld
```

但是消息队列可以保证：

```txt
第一条消息：hello
第二条消息：world
```

消息队列有两套接口：

```txt
System V 消息队列
POSIX 消息队列
```

System V 风格：

```c
msgget
msgsnd
msgrcv
msgctl
```

POSIX 风格：

```c
mq_open
mq_send
mq_receive
mq_close
mq_unlink
```

刚开始建议先了解 System V，因为很多 Linux 教材会讲它。

------

# 五、第六阶段：共享内存

共享内存是 IPC 里面速度最快的一种。

原因是：

```txt
管道/消息队列：
进程 A -> 内核 -> 进程 B

共享内存：
进程 A 和进程 B 直接访问同一块内存
```

共享内存的优点：

```txt
速度快
适合传大量数据
```

缺点：

```txt
需要自己处理同步问题
```

比如两个进程同时写同一块内存，就可能出现数据混乱。

共享内存常见接口：

System V：

```c
shmget
shmat
shmdt
shmctl
```

POSIX：

```c
shm_open
ftruncate
mmap
munmap
shm_unlink
```

这一阶段一定要配合信号量学。

------

# 六、第七阶段：信号量 semaphore

信号量主要不是用来传数据，而是用来做同步和互斥。

比如共享内存中有一块区域：

```txt
进程 A 正在写
进程 B 不能读
```

或者：

```txt
进程 A 写完了
进程 B 才能读
```

这时候就需要信号量。

核心操作：

```txt
P 操作：申请资源，可能阻塞
V 操作：释放资源，唤醒别人
```

System V 信号量：

```c
semget
semop
semctl
```

POSIX 信号量：

```c
sem_open
sem_wait
sem_post
sem_close
sem_unlink
```

建议你这样理解：

```txt
共享内存负责传数据
信号量负责保证顺序
```

比如：

```txt
生产者进程：写共享内存
消费者进程：读共享内存
信号量：控制谁先谁后
```

------

# 七、第八阶段：mmap

`mmap` 可以把文件或者匿名内存映射到进程地址空间。

它可以用于：

```txt
1. 文件映射
2. 共享内存
3. 高效文件读写
4. 父子进程共享内存
```

典型用法：

```c
void* addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
```

重点参数：

```txt
PROT_READ       可读
PROT_WRITE      可写
MAP_SHARED      共享映射
MAP_PRIVATE     私有映射，写时拷贝
```

这部分和你之前学过的：

```txt
虚拟地址空间
写时拷贝
进程地址空间
页表
```

联系非常紧密。

------

# 八、第九阶段：Unix 域套接字

Unix 域套接字用于本机进程间通信。

它和网络 socket 很像，但是不经过网络协议栈。

适合：

```txt
同一台机器上的客户端/服务器模型
```

比如：

```txt
Docker
Redis 本地通信
MySQL 本地 socket
Nginx 和其他服务通信
```

Unix 域套接字特点：

```txt
1. 支持双向通信
2. 支持无亲缘关系进程
3. 功能比管道强
4. 可以传文件描述符
```

常见接口：

```c
socket
bind
listen
accept
connect
send
recv
```

区别是地址结构用：

```c
struct sockaddr_un
```

------

# 九、第十阶段：网络 socket

最后再学 TCP/UDP socket。

因为网络 socket 已经不只是本机 IPC，而是跨主机通信。

核心模型：

```txt
服务器：
socket
bind
listen
accept
read/write

客户端：
socket
connect
read/write
```

TCP 是可靠字节流：

```txt
面向连接
可靠传输
有序
无消息边界
```

UDP 是数据报：

```txt
无连接
不可靠
有消息边界
速度快
```

然后再继续学：

```txt
select
poll
epoll
多路转接
Reactor 模式
高并发服务器
```

------

# 十、最推荐你的学习路线

按照你现在的基础，我建议你这样走：

```txt
第一步：pipe 匿名管道
第二步：多进程 pipe 通信
第三步：用 pipe 实现进程池
第四步：FIFO 命名管道
第五步：signal 信号
第六步：消息队列
第七步：共享内存
第八步：信号量
第九步：mmap
第十步：Unix 域套接字
第十一步：TCP/UDP socket
第十二步：epoll 高并发
```

你现在已经在第三步附近了。

------

# 十一、不同 IPC 的核心区别

你可以这样记：

```txt
管道：
适合简单数据流通信。

FIFO：
适合无亲缘关系进程的简单通信。

信号：
适合通知，不适合传数据。

消息队列：
适合一条一条消息传输。

共享内存：
适合大量数据传输，速度最快。

信号量：
适合同步和互斥，不是主要用来传数据。

socket：
适合复杂通信，本机和网络都能用。

mmap：
适合文件映射和共享内存。
```

------

# 十二、从使用场景理解

## 1. 父子进程简单通信

用：

```txt
pipe
```

例如：

```txt
父进程给子进程发任务
```

------

## 2. 没有亲缘关系的两个进程通信

用：

```txt
FIFO
Unix 域套接字
消息队列
```

简单场景用 FIFO，复杂场景用 Unix 域套接字。

------

## 3. 只想通知另一个进程

用：

```txt
signal
```

例如：

```txt
通知子进程退出
通知父进程回收子进程
```

------

## 4. 大量数据传输

用：

```txt
shared memory
mmap
```

例如：

```txt
图像数据
传感器数据
机器人状态数据
大块日志数据
```

------

## 5. 需要控制访问顺序

用：

```txt
semaphore
mutex
condition variable
file lock
```

例如：

```txt
进程 A 写完后，进程 B 才能读
```

------

## 6. 本机客户端/服务器通信

用：

```txt
Unix 域套接字
```

------

## 7. 跨机器通信

用：

```txt
TCP socket
UDP socket
```

------

# 十三、你应该重点掌握的优先级

如果按重要程度排序：

```txt
必须掌握：
1. pipe
2. signal
3. shared memory
4. semaphore
5. socket

建议掌握：
6. FIFO
7. message queue
8. mmap
9. file lock

进阶掌握：
10. Unix domain socket
11. eventfd
12. epoll
13. futex
```

------

# 十四、建议你每个阶段写一个小程序

你可以按这个顺序练：

```txt
1. pipe：父进程写，子进程读
2. pipe：父子双向通信
3. pipe：父进程创建 5 个子进程，随机分配任务
4. FIFO：两个无关进程聊天
5. signal：父进程捕捉 SIGCHLD 回收子进程
6. message queue：两个进程发送结构体消息
7. shared memory：两个进程共享一段字符串
8. shared memory + semaphore：生产者消费者模型
9. mmap：父子进程共享内存
10. Unix socket：本机客户端服务器
11. TCP socket：网络客户端服务器
12. epoll：多客户端服务器
```

------

# 十五、最重要的一句话

你学习 Linux IPC 不要一上来就背所有接口，应该按照这个逻辑理解：

```txt
先学怎么传数据：
pipe → FIFO → message queue → shared memory → socket

再学怎么通知：
signal

再学怎么同步：
semaphore → mutex → condition variable → file lock

最后学高性能：
mmap → Unix domain socket → epoll → eventfd
```

你现在最应该继续深入的是：

```txt
pipe + fork + 文件描述符继承 + 进程池
```

这一块打牢之后，再进入：

```txt
FIFO 和 signal
```