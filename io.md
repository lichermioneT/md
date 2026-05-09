# io

下面给你系统总结一下 **C 语言中文件操作常用函数接口**。建议你重点掌握两类：

1. **C 标准库文件接口**：`fopen / fread / fwrite / fclose` 等，跨平台，基于 `FILE*`。
2. **Linux 系统调用接口**：`open / read / write / close` 等，Linux 下常用，基于文件描述符 `fd`。

------

# 一、C 标准库文件操作接口

需要头文件：

```c
#include <stdio.h>
```

核心特点：

```c
FILE* fp;
```

C 标准库通过 `FILE*` 操作文件。

------

## 1. 打开文件：`fopen`

```c
FILE* fopen(const char* pathname, const char* mode);
```

### 参数说明

```c
pathname：文件路径
mode：打开方式
```

### 常见 mode

| 模式   | 含义                                   |
| ------ | -------------------------------------- |
| `"r"`  | 只读打开，文件必须存在                 |
| `"w"`  | 只写打开，文件不存在则创建，存在则清空 |
| `"a"`  | 追加写，文件不存在则创建               |
| `"r+"` | 读写打开，文件必须存在                 |
| `"w+"` | 读写打开，文件不存在则创建，存在则清空 |
| `"a+"` | 读写追加，文件不存在则创建             |
| `"rb"` | 二进制只读                             |
| `"wb"` | 二进制只写                             |
| `"ab"` | 二进制追加                             |

### 返回值

```c
成功：返回 FILE* 文件指针
失败：返回 NULL
```

### 示例

```c
FILE* fp = fopen("test.txt", "w");
if (fp == NULL)
{
    perror("fopen");
    return 1;
}
```

------

## 2. 关闭文件：`fclose`

```c
int fclose(FILE* stream);
```

### 返回值

```c
成功：返回 0
失败：返回 EOF
```

### 示例

```c
fclose(fp);
```

文件使用完后必须关闭，否则可能导致：

```c
缓冲区数据没有刷新
文件描述符泄漏
资源浪费
```

------

# 二、字符级文件操作

## 1. 写一个字符：`fputc`

```c
int fputc(int c, FILE* stream);
```

### 示例

```c
fputc('A', fp);
```

------

## 2. 读一个字符：`fgetc`

```c
int fgetc(FILE* stream);
```

### 示例

```c
int ch = fgetc(fp);
if (ch != EOF)
{
    putchar(ch);
}
```

注意：`fgetc` 返回值是 `int`，不是 `char`，因为它需要表示 `EOF`。

------

# 三、字符串级文件操作

## 1. 写字符串：`fputs`

```c
int fputs(const char* s, FILE* stream);
```

### 示例

```c
fputs("hello world\n", fp);
```

------

## 2. 读一行字符串：`fgets`

```c
char* fgets(char* s, int size, FILE* stream);
```

### 参数

```c
s：存放读取内容的缓冲区
size：最多读取 size - 1 个字符
stream：文件指针
```

### 示例

```c
char buffer[1024];

while (fgets(buffer, sizeof(buffer), fp) != NULL)
{
    printf("%s", buffer);
}
```

### 重点

`fgets` 会读取换行符 `\n`，并自动在字符串末尾加 `\0`。

------

# 四、格式化文件操作

## 1. 格式化写入：`fprintf`

```c
int fprintf(FILE* stream, const char* format, ...);
```

### 示例

```c
int age = 20;
fprintf(fp, "age = %d\n", age);
```

类似于 `printf`，只是输出目标从屏幕变成文件。

------

## 2. 格式化读取：`fscanf`

```c
int fscanf(FILE* stream, const char* format, ...);
```

### 示例

```c
int age;
fscanf(fp, "%d", &age);
```

### 注意

`fscanf` 对格式要求比较严格，读取复杂文本时不如 `fgets + sscanf` 稳定。

------

# 五、二进制文件操作

## 1. 写二进制数据：`fwrite`

```c
size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);
```

### 参数

```c
ptr：要写入的数据地址
size：每个元素的大小
nmemb：元素个数
stream：文件指针
```

### 示例

```c
int arr[5] = {1, 2, 3, 4, 5};

fwrite(arr, sizeof(int), 5, fp);
```

------

## 2. 读二进制数据：`fread`

```c
size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
```

### 示例

```c
int arr[5];

size_t n = fread(arr, sizeof(int), 5, fp);
```

### 返回值

```c
返回成功读取的元素个数
```

------

# 六、文件位置操作

## 1. 移动文件指针：`fseek`

```c
int fseek(FILE* stream, long offset, int whence);
```

### whence 常见取值

| 参数       | 含义           |
| ---------- | -------------- |
| `SEEK_SET` | 从文件开头偏移 |
| `SEEK_CUR` | 从当前位置偏移 |
| `SEEK_END` | 从文件末尾偏移 |

### 示例

```c
fseek(fp, 0, SEEK_SET);   // 回到文件开头
fseek(fp, 0, SEEK_END);   // 跳到文件末尾
```

------

## 2. 获取当前位置：`ftell`

```c
long ftell(FILE* stream);
```

### 示例：获取文件大小

```c
fseek(fp, 0, SEEK_END);
long size = ftell(fp);
printf("file size = %ld\n", size);
```

------

## 3. 回到文件开头：`rewind`

```c
void rewind(FILE* stream);
```

等价于：

```c
fseek(fp, 0, SEEK_SET);
```

------

# 七、刷新缓冲区：`fflush`

```c
int fflush(FILE* stream);
```

### 作用

把 C 库缓冲区中的数据刷新到文件中。

### 示例

```c
fprintf(fp, "hello\n");
fflush(fp);
```

### 注意

`fflush(stdout)` 常用于立即刷新屏幕输出。

------

# 八、错误判断相关函数

## 1. 判断是否到达文件结尾：`feof`

```c
int feof(FILE* stream);
```

### 注意

不要这样写：

```c
while (!feof(fp))
{
    fgets(buffer, sizeof(buffer), fp);
}
```

更推荐：

```c
while (fgets(buffer, sizeof(buffer), fp) != NULL)
{
    printf("%s", buffer);
}
```

原因：`feof` 只有在读取失败之后，才会判断到文件结尾。

------

## 2. 判断文件错误：`ferror`

```c
int ferror(FILE* stream);
```

------

## 3. 清除错误标记：`clearerr`

```c
void clearerr(FILE* stream);
```

------

# 九、文件删除和重命名

## 1. 删除文件：`remove`

```c
int remove(const char* pathname);
```

### 示例

```c
remove("test.txt");
```

------

## 2. 重命名文件：`rename`

```c
int rename(const char* oldname, const char* newname);
```

### 示例

```c
rename("old.txt", "new.txt");
```

------

# 十、Linux 系统级文件接口

如果你是在 Linux 下学习 C/C++，还需要掌握这一套。

需要头文件：

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
```

核心特点：

```c
int fd;
```

Linux 系统接口通过 **文件描述符 fd** 操作文件。

------

## 1. 打开文件：`open`

```c
int open(const char* pathname, int flags);
int open(const char* pathname, int flags, mode_t mode);
```

### 示例

```c
int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
if (fd < 0)
{
    perror("open");
    return 1;
}
```

### 常见 flags

| 标志       | 含义                           |
| ---------- | ------------------------------ |
| `O_RDONLY` | 只读                           |
| `O_WRONLY` | 只写                           |
| `O_RDWR`   | 读写                           |
| `O_CREAT`  | 文件不存在则创建               |
| `O_TRUNC`  | 打开时清空文件                 |
| `O_APPEND` | 追加写                         |
| `O_EXCL`   | 配合 `O_CREAT`，文件存在则失败 |

------

## 2. 关闭文件：`close`

```c
int close(int fd);
```

### 示例

```c
close(fd);
```

------

## 3. 写文件：`write`

```c
ssize_t write(int fd, const void* buf, size_t count);
```

### 示例

```c
const char* msg = "hello linux\n";
write(fd, msg, strlen(msg));
```

------

## 4. 读文件：`read`

```c
ssize_t read(int fd, void* buf, size_t count);
```

### 示例

```c
char buffer[1024];

ssize_t n = read(fd, buffer, sizeof(buffer) - 1);
if (n > 0)
{
    buffer[n] = '\0';
    printf("%s", buffer);
}
```

### 返回值

```c
> 0：实际读取的字节数
= 0：读到文件结尾
< 0：读取失败
```

------

## 5. 改变文件偏移量：`lseek`

```c
off_t lseek(int fd, off_t offset, int whence);
```

### 示例

```c
lseek(fd, 0, SEEK_SET);   // 回到文件开头
lseek(fd, 0, SEEK_END);   // 移动到文件末尾
```

------

# 十一、C 标准库接口和 Linux 系统接口的区别

| 对比项       | C 标准库                 | Linux 系统调用                 |
| ------------ | ------------------------ | ------------------------------ |
| 打开函数     | `fopen`                  | `open`                         |
| 关闭函数     | `fclose`                 | `close`                        |
| 读函数       | `fread / fgets / fgetc`  | `read`                         |
| 写函数       | `fwrite / fputs / fputc` | `write`                        |
| 操作对象     | `FILE*`                  | `int fd`                       |
| 是否带缓冲区 | 有 C 库缓冲区            | 无 C 库缓冲区                  |
| 可移植性     | 更好                     | 偏 Linux/Unix                  |
| 适合场景     | 普通文件读写             | 系统编程、网络、管道、设备文件 |

------

# 十二、最重要的几个函数

如果你是初学阶段，优先掌握这些：

```c
fopen
fclose
fgets
fputs
fprintf
fscanf
fread
fwrite
fseek
ftell
```

Linux 下还要掌握：

```c
open
close
read
write
lseek
```

------

# 十三、一个完整示例：文本文件写入和读取

```c
#include <stdio.h>

int main()
{
    FILE* fp = fopen("test.txt", "w");
    if (fp == NULL)
    {
        perror("fopen");
        return 1;
    }

    fprintf(fp, "hello file\n");
    fprintf(fp, "C language\n");

    fclose(fp);

    fp = fopen("test.txt", "r");
    if (fp == NULL)
    {
        perror("fopen");
        return 1;
    }

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        printf("%s", buffer);
    }

    fclose(fp);

    return 0;
}
```

------

# 十四、你需要形成的理解

文件操作本质上就是：

```c
打开文件 -> 读/写文件 -> 关闭文件
```

C 标准库版本：

```c
fopen -> fread/fwrite/fgets/fputs/fprintf -> fclose
```

Linux 系统调用版本：

```c
open -> read/write -> close
```

初学时建议你先掌握 `FILE*` 这一套，因为更简单；后面学习 Linux 系统编程时，再重点掌握 `fd` 文件描述符这一套。