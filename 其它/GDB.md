# GDB

可以，我给你一份**面向 C/C++ 初学者、7 天内掌握 GDB 调试流程**的学习方案。目标不是把 GDB 所有命令背完，而是让你做到：

**一周后，你能独立完成：**

1. 编译带调试信息的程序
2. 用 GDB 启动程序并设置参数
3. 打断点、单步调试、查看变量
4. 看调用栈，定位崩溃位置
5. 调试循环、函数、指针、数组、线程的基础问题
6. 遇到段错误时知道怎么查

------

# 一、先明确：GDB 到底是干什么的？

GDB 本质上就是一个**让程序“暂停”下来给你检查现场**的工具。

你可以把程序执行过程理解成：

- 程序正常跑：太快了，看不清
- GDB 让它停住：你可以一行一行看
- 看当前执行到哪里
- 看变量现在是多少
- 看是谁调用了谁
- 看为什么崩溃

所以你学习 GDB，不是学命令本身，而是学会这套**调试思维流程**：

**编译 → 进入 gdb → 下断点 → 运行 → 单步观察 → 看变量 → 看调用栈 → 定位问题 → 修改代码 → 再验证**

------

# 二、先记住最核心的一套流程

你以后调试代码，基本都按这个流程走：

## 1）编译时加调试信息

```bash
g++ -g test.cpp -o test
```

如果想更利于调试，建议：

```bash
g++ -g -O0 test.cpp -o test
```

解释：

- `-g`：生成调试信息
- `-O0`：关闭优化，避免代码执行顺序和源码不一致

------

## 2）进入 gdb

```bash
gdb ./test
```

------

## 3）打断点

```bash
(gdb) b main
```

或者打在某一行：

```bash
(gdb) b 25
```

或者打在函数上：

```bash
(gdb) b func
```

------

## 4）运行程序

```bash
(gdb) r
```

如果 main 需要参数：

```bash
(gdb) r arg1 arg2
```

------

## 5）单步执行

```bash
(gdb) n
```

- `next`，单步执行，**遇到函数调用不进去**

```bash
(gdb) s
```

- `step`，单步执行，**遇到函数调用会进去**

```bash
(gdb) c
```

- `continue`，继续运行到下一个断点

------

## 6）看变量

```bash
(gdb) p x
(gdb) p arr[0]
(gdb) p *ptr
```

------

## 7）看代码

```bash
(gdb) l
```

------

## 8）看函数调用链

```bash
(gdb) bt
```

程序崩了最常用这个。

------

## 9）退出

```bash
(gdb) q
```

------

# 三、你一周内要掌握的命令，不要贪多

先只掌握这 15 个左右：

## 最基础

```bash
gdb ./a.out
b main
b 20
b func
r
r arg1 arg2
n
s
c
q
l
p x
bt
finish
info break
```

## 第二层

```bash
set args a b c
display x
watch x
info locals
info args
```

## 第三层

```bash
until
delete
disable
enable
```

------

# 四、7天学习安排

------

## 第1天：会启动 GDB，会打断点，会单步

### 目标

你今天只做一件事：
**让程序停下来，并能一行一行执行。**

### 学习内容

掌握：

- `g++ -g -O0`
- `gdb ./a.out`
- `b main`
- `b 行号`
- `r`
- `n`
- `s`
- `c`
- `l`
- `q`

### 练习代码

```cpp
#include <iostream>
using namespace std;

int add(int a, int b)
{
    int c = a + b;
    return c;
}

int main()
{
    int x = 10;
    int y = 20;
    int z = add(x, y);
    cout << z << endl;
    return 0;
}
```

### 你要练什么

1. 在 `main` 打断点
2. `run`
3. 用 `n` 一步一步走
4. 在 `add` 打断点
5. 用 `s` 进入函数
6. 用 `c` 继续执行

### 今天结束标准

你能说清楚：

- `n` 和 `s` 的区别

  `s` 钻进函数，`n` 跨过函数。

- 断点能打在 `main`、函数名、行号

- `run` 后程序为什么会停住

------

## 第2天：会看变量，会看函数参数

### 目标

今天你要学会：
**程序停住后，我怎么检查当前的数据状态。**

### 学习内容

掌握：

- `p 变量名`
- `info locals`
- `info args`
- `display 变量`
- `set args`

### 练习代码

```cpp
#include <iostream>
using namespace std;

int sum(int a, int b)
{
    int result = a + b;
    return result;
}

int main(int argc, char* argv[])
{
    int x = 3;
    int y = 5;
    int z = sum(x, y);
    cout << z << endl;
    return 0;
}
```

### 你要练什么

1. 在 `sum` 入口打断点
2. `run`
3. 查看参数

```bash
(gdb) info args
```

1. 查看局部变量

```bash
(gdb) info locals
```

1. 打印变量

```bash
(gdb) p a
(gdb) p b
(gdb) p result
```

1. 自动显示变量

```bash
(gdb) display result
```

### 今天结束标准

你能做到：

- 停在某一行时，知道当前变量值是多少
- 知道参数和局部变量怎么查看
- 知道 `display` 的作用

------

## 第3天：掌握函数调试流程

### 目标

今天重点是：
**看懂函数调用过程。**

### 学习内容

掌握：

- `s`
- `n`
- `finish`
- `bt`

### 练习代码

```cpp
#include <iostream>
using namespace std;

int mul(int a, int b)
{
    int ret = a * b;
    return ret;
}

int add(int x, int y)
{
    int t = mul(x, y);
    return t + 1;
}

int main()
{
    int a = 2;
    int b = 4;
    int c = add(a, b);
    cout << c << endl;
    return 0;
}
```

### 你要练什么

1. 在 `main` 断住
2. `s` 进入 `add`
3. 再 `s` 进入 `mul`
4. 用 `finish` 从当前函数直接执行到返回
5. 用 `bt` 看调用栈

### 你要理解

比如当前在 `mul` 中，`bt` 可能显示：

- `mul`
- `add`
- `main`

意思就是：
**main 调了 add，add 又调了 mul**

### 今天结束标准

你能理解：

- 程序不是平面的，是一层层函数调用进去的
- `bt` 是看“谁调用了我”
- `finish` 是“当前函数剩下的直接跑完”

------

## 第4天：调试循环、分支、数组

### 目标

今天你要解决最常见的问题：
**循环为什么不对，数组为什么越界，if 为什么没进。**

### 学习内容

掌握：

- 反复 `n`
- `p i`
- `p arr[i]`
- `until`
- `watch`

### 练习代码

```cpp
#include <iostream>
using namespace std;

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    int sum = 0;
    for(int i = 0; i < 5; ++i)
    {
        sum += arr[i];
    }
    cout << sum << endl;
    return 0;
}
```

### 你要练什么

1. 在循环处打断点
2. 每次 `n`
3. 每一步 `p i`
4. 每一步 `p sum`
5. 每一步 `p arr[i]`

然后再故意写错：

```cpp
for(int i = 0; i <= 5; ++i)
```

看会发生什么。

### watch 的作用

```bash
(gdb) watch sum
```

表示：**只要 sum 被改动，程序就停下来**

这个对找“谁改坏了变量”特别有用。

### 今天结束标准

你能做到：

- 调试 for 循环
- 看循环变量变化
- 会用 `watch`
- 能意识到数组越界是怎么一步步发生的

------

## 第5天：重点攻克段错误（Segmentation fault）

### 目标

这是最重要的一天。
你要学会：**程序崩了，怎么查。**

### 练习代码

```cpp
#include <iostream>
using namespace std;

int main()
{
    int* p = nullptr;
    *p = 10;
    return 0;
}
```

### 编译运行

```bash
g++ -g -O0 test.cpp -o test
gdb ./test
```

### 调试流程

```bash
(gdb) r
```

程序崩溃后，执行：

```bash
(gdb) bt
(gdb) l
(gdb) p p
```

### 你要理解

当程序段错误时，不要慌，固定流程就是：

1. `run`
2. 崩了
3. `bt` 看在哪个函数崩的
4. `l` 看崩溃附近代码
5. `p 变量` 看空指针、野指针、越界下标等

### 再练一个

```cpp
#include <iostream>
using namespace std;

void func(int* p)
{
    *p = 100;
}

int main()
{
    int* ptr = nullptr;
    func(ptr);
    return 0;
}
```

你用 `bt` 能看到：

- 当前在 `func`
- 是 `main` 调进去的

### 今天结束标准

你必须掌握：

- 段错误最常见是空指针/野指针/越界
- `bt` 是崩溃定位第一命令
- 不要一上来猜，先看现场

------

## 第6天：调试 main 参数、命令行参数、简单项目

### 目标

今天让你更贴近真实开发。

### 学习内容

掌握：

- `run 参数`
- `set args`
- 多文件调试
- 在函数入口、关键分支处打断点

### 练习代码

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << "please input a number" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    cout << n * 2 << endl;
    return 0;
}
```

### 你要练什么

```bash
(gdb) set args 15
(gdb) r
```

或者：

```bash
(gdb) r 15
```

### 今天重点理解

以后你调试有参数的程序，不是只能直接运行：

```bash
./a.out 15
```

而是在 gdb 里也能传参数。

### 今天结束标准

你能做到：

- 给 `main` 传参数
- 能调试有输入参数的代码
- 知道真实项目也是这个思路，只是代码更大

------

## 第7天：做一次完整实战

今天你不要再学新命令，而是把前 6 天串起来。

### 实战目标

你自己独立完成一次完整调试：

**题目：下面代码为什么结果不对？**

```cpp
#include <iostream>
using namespace std;

int divide(int a, int b)
{
    int c = a / b;
    return c;
}

int main()
{
    int x = 10;
    int y = 0;
    int z = divide(x, y);
    cout << z << endl;
    return 0;
}
```

### 你要独立走完整流程

1. 编译

```bash
g++ -g -O0 test.cpp -o test
```

1. 进入 gdb

```bash
gdb ./test
```

1. 打断点

```bash
b main
b divide
```

1. 运行

```bash
r
```

1. 单步进入函数

```bash
s
```

1. 查看参数

```bash
info args
p a
p b
```

1. 发现 `b = 0`
2. 推断除零错误

### 今天结束标准

你已经具备了最基本的调试能力。

------

# 五、每天学习时间安排

我建议你每天按这个节奏学：

## 每天 2~3 小时就够

### 第1阶段：20分钟

先回顾昨天命令

### 第2阶段：40分钟

学今天的新命令和新概念

### 第3阶段：60分钟

拿代码实际敲、实际调

### 第4阶段：20分钟

总结今天的调试流程

------

# 六、你一定要养成的 GDB 调试习惯

------

## 习惯1：编译必须带 `-g -O0`

```bash
g++ -g -O0 test.cpp -o test
```

------

## 习惯2：不要一上来乱猜

先做这几步：

1. 程序停住
2. 看当前行
3. 看变量
4. 看调用栈

------

## 习惯3：优先看“数据什么时候变错了”

程序错，很多时候不是这一行错，而是：

- 变量早就错了
- 指针早就坏了
- 数组 earlier 越界了

所以要经常用：

```bash
p x
display x
watch x
```

------

## 习惯4：崩溃就先 `bt`

不要慌，不要瞎改，先：

```bash
bt
```

------

## 习惯5：`n` 和 `s` 分清楚

- `n`：当前行执行完，不进函数内部
- `s`：进入函数内部看细节

------

# 七、你必须会的“调试模板”

以后你调任何代码，都按这个模板：

## 模板1：普通逻辑错误

```bash
g++ -g -O0 test.cpp -o test
gdb ./test
b main
r
n
n
p x
p y
s
bt
```

------

## 模板2：程序崩溃

```bash
gdb ./test
r
bt
l
p 变量名
```

------

## 模板3：main 有参数

```bash
gdb ./test
set args 10 abc
r
```

------

## 模板4：看谁改了变量

```bash
watch x
r
```

------

# 八、这一周结束后，你算掌握到什么程度？

如果你能做到下面这些，你就算真正入门了：

- 能自己用 gdb 启动程序
- 能打断点
- 能单步
- 能看变量
- 能看函数调用链
- 能给 main 传参数
- 能初步定位段错误
- 能调试简单 C/C++ 项目

这时你已经超过很多“只会写代码，不会查问题”的初学者了。

------

# 九、我给你的最终学习顺序总结

你就按这个顺序记：

**第一步：会启动**

- `gdb ./a.out`
- `r`

**第二步：会停住**

- `b main`
- `b 行号`
- `b 函数名`

**第三步：会往下走**

- `n`
- `s`
- `c`
- `finish`

**第四步：会看数据**

- `p`
- `info locals`
- `info args`
- `display`

**第五步：会查崩溃**

- `bt`
- `l`

**第六步：会查变量被谁改了**

- `watch`

------

# 十、给你一个适合背诵的超简版

你可以把这个当成口令：

```bash
g++ -g -O0 test.cpp -o test
gdb ./test
b main
r
n
s
p x
bt
c
q
```

这就是 GDB 最核心的一套。

------

# 十一、给你的建议

你现在不要追求：

- 一次记住所有命令
- 一上来调复杂项目
- 一开始就学 core dump、反汇编、thread apply all bt

你先把这 7 天的内容练熟。
**GDB 入门的关键不是“知道”，而是“自己真的敲过很多次”。**

------

如果你愿意，我下一条可以直接继续给你一份：

**“GDB 一周训练用的 7 个调试小案例 + 每天配套代码”**
这样你可以直接照着练。