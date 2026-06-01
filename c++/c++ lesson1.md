# c++ lesson1

## 1c++关键字

**c++的关键字后面慢慢记忆，用的多了就知道了**



## 2命名空间

**命名空间让对象局域化**

### 2.1命名空间的定义

**1.普通的命名空间示例**

**namespace name {}**

**里面就是命名空间的成员，可以是对象，变量，函数。**

```c++
#include <iostream>
using namespace std;

namespace N1
{
  int a = 10;
  int b = 22;
  
  int add(int x, int y)
  {
    return x + y;
  }

  class stu 
  {
    private:
      int age;
  };
}

int main()
{

  return 0;
}

```

























