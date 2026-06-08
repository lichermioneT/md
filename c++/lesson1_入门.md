# c++ lesson1

## 1c++关键字

**c++的关键字后面慢慢记忆，用的多了就知道了**



## 2命名空间

**命名空间让对象局域化**

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

namespace N1 
{
  int mul(int x, int y)
  {
    return x * y;
  }
}

int main()
{
// 1.using引入。
  using N1::a;
  cout<< "N1::a " << a <<endl;

// 2.using namespace 
  using namespace N1;
  cout<< "using namespace N1: b " <<endl;

// 3.自己突破类
  cout<< N1::add(22, 33) <<endl;

  return 0;
}
```



## 3. C++输入&输出

```c++
#include <iostream>
using namespace std;

int main()
{
  cout<< 22 << " " << 1.3 << "string" << 'c' <<endl;

  int a = 10;
  cin >> a;
  cout<< a <<endl;

  return 0;
}

```



## 4.缺省参数

```c++
#include <iostream>
using namespace std;

// 函数可以再指定一个默认的参数。
// 1.不传就使用默认的
// 2.传入就使用传入的
// 3.声明给了，实现就不给的
int add1(int x, int y, int z = 33)
{
  return  x + y + z;
}

int add2(int x, int y = 10, int z = 33)
{
  return  x + y + z;
}

int add3(int x = 2, int y = 10, int z = 33)
{
  return x + y + z;
}

int main()
{

  return 0;
}

```



## 5函数重载

**1.函数名一样。2.函数的参数不一样的。**

```c++
#include <iostream>
using namespace std;

// 函数可以再指定一个默认的参数。
// 1.不传就使用默认的
// 2.传入就使用传入的
// 3.声明给了，实现就不给的
int add1(int x, int y, int z = 33)
{
  return  x + y + z;
}

int add2(int x, int y = 10, int z = 33)
{
  return  x + y + z;
}

int add3(int x = 2, int y = 10, int z = 33)
{
  return x + y + z;
}

int main()
{

  return 0;
}

```

**给你函数的参数的类型，进行函数名修饰的规则。**

```c++
extern "C" int Add(int left, int right);
int main()
{
 Add(1,2);
 return 0;
}
```



## 6引用

```c++
#include <iostream>
#include <string>
using namespace std;

int main()
{
  string s("lichermionex");

// 1.引用的语法,类型& 别名 = 变量
//   1.引用必须初始化
  string& s2 = s;
  s2 += "hello";
  cout<< s2 <<endl;


  return 0;
}

```

1. **引用在定义时必须初始化 2. 一个变量可以有多个引用 3.引用一旦引用一个实体，再不能引用其他实体**

**引用的权限只能缩小，不能放大的。**

**引用做函数参数，做返回值的。**



##  7. 内联函数

```c++
#include <iostream>
#include <string>
using namespace std;

inline int add(int x, int y)
{
  return  x + y;
}

int main()
{
  int ret = add(2, 4);
  cout<< ret <<endl;

  return 0;
}

```

**空间换时间：直接掉用的地方展开。**

## 8auto关键字

```c++
int TestAuto()
{
 return 10;
}
int main()
{
 int a = 10;
 auto b = a;
 auto c = 'a';
 auto d = TestAuto();

 cout << typeid(b).name() << endl;
 cout << typeid(c).name() << endl;
 cout << typeid(d).name() << endl;

 //auto e; 无法通过编译，使用auto定义变量时必须对其进行初始化
 return 0;
}
```

**用auto声明指针类型时，用auto和auto*没有任何区别，但用auto声明引用类型时则必须加&**



## 9基于范围的for循环

```c++
void TestFor()
{
 int array[] = { 1, 2, 3, 4, 5 };
 for (int i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
 array[i] *= 2;

 for (int* p = array; p < array + sizeof(array)/ sizeof(array[0]); ++p)
 cout << *p << endl;
}

void TestFor()
{
 int array[] = { 1, 2, 3, 4, 5 };
 for(auto& e : array)
 e *= 2;

 for(auto e : array)
 cout << e << " ";

 return 0;
}
```





























