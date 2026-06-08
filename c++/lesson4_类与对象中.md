# lesson3_类与对象中

## 1.类的6个默认成员函数

**如果一个类中什么成员都没有，简称为空类。空类中什么都没有吗？**

**并不是的，任何一个类在我们不写的情 况下，都会自动生成下面6个默认成员函数。**



## 2. 构造函数

**构造函数是一个特殊的成员函数，名字与类名相同,创建类类型对象时由编译器自动调用，保证每个数据成员 都有 一个合**

**适的初始值，并且在对象的生命周期内只调用一次。**

| 序号 | 特征描述                                   |
| :--: | :----------------------------------------- |
|  1   | 函数名与类名相同。                         |
|  2   | 无返回值。                                 |
|  3   | 对象实例化时编译器自动调用对应的构造函数。 |
|  4   | 构造函数可以重载。                         |

**注意无参的构造函数不要带括号。否则成了函数的声明了的。**

**默认构造函数：1.编译器自己生成的。 2.无参的。  3.全缺省的。只能存在一个的。**

```c#
#include <string>
#include <iostream>
using namespace std;

class date 
{
public:
  date(int year =  2000, int month = 2, int day = 10)
    :_year(year)
    ,_month(month)
    ,_day(day)
  {}
  
  void print()
  {
    cout<<"year:" << this->_year<< " month:" << this->_month << " day:" << this->_day <<endl;
  }

private:
  int _year;
  int _month;
  int _day;
};

int main()
{
  // 注意这里掉用的时候默认构造函数，全缺省的构造函数
  date d;
  d.print();
  return 0;
}
// 注意：默认构造函数都不要带括号的。
```



```c++
#include <string>
#include <iostream>
using namespace std;

class hour 
{
public:
  hour(int hour = 1, int min = 1, int second = 1)
    :_hour(hour)
    ,_min(min)
    ,_second(second)
  {
    cout<< "hour的构造函数" <<endl;
  }

private:
  int _hour;
  int _min;
  int _second;
};

class date 
{
private:
  int _year;
  int _month;
  int _day;
  hour _h;
};

int main()
{
  date d;
}

```

**解答：C++把类型分成内置类型(基本类型)和自定义类型。内置类型就是语法已经定义好的类型：如 int/char...，自定义类型就是我们使用class/struct/union自己定义的类型，看看下面的程序，就会发现 编译器生成默认的构造函数会对自定类型成员_t调用的它的默认成员函数**



## 3.析构函数

**析构函数：与构造函数功能相反，析构函数不是完成对象的销毁，局部对象销毁工作是由编译器完成的。而 对象在销毁时会自动调用析构函数，完成类的一些资源清理工作**

| 序号 | 特征描述                                                     |
| :--: | :----------------------------------------------------------- |
|  1   | 析构函数名是在类名前加上字符 `~`。                           |
|  2   | 无参数无返回值。                                             |
|  3   | 一个类有且只有一个析构函数。若未显式定义，系统会自动生成默认的析构函数。 |
|  4   | 对象生命周期结束时，C++ 编译系统自动调用析构函数。           |



**编译器生成的默认 析构函数，对会自定类型成员调用它的析构函数**

```c++
#include <string>
#include <iostream>
using namespace std;

class hour 
{
public:
  hour(int hour = 1, int min = 1, int second = 1)
    :_hour(hour)
    ,_min(min)
    ,_second(second)
  {
    cout<< "hour的构造函数" <<endl;
  }

  ~hour()
  {
    cout<< "hour的析构函数" <<endl;
  }

private:
  int _hour;
  int _min;
  int _second;
};

class date 
{
private:
  int _year;
  int _month;
  int _day;
  hour _h;
};

int main()
{
  date d;
}

```



## 4. 拷贝构造函数

**拷贝构造函数也是特殊的成员函数，其特征如下：**

**1. 拷贝构造函数是构造函数的一个重载形式。**

**2. 拷贝构造函数的参数只有一个且必须使用引用传参，使用传值方式会引发无穷递归调用。**



**若未显示定义，系统生成默认的拷贝构造函数。 **

**默认的拷贝构造函数对象按内存存储按字节序完成拷 贝，这种拷贝我们叫做浅拷贝，或者值拷贝。**

**按字节拷贝：就是浅拷贝**

```c++
class Date
{
public:
    int _year;
    int _month;
    int _day;
};

Date(const Date& d)
{
    _year = d._year;
    _month = d._month;
    _day = d._day;
}
```

**成员属性存在指针的话。**

```c++
class String
{
public:
    char* _str;
};
```

```
s1._str  ─┐
          ├──> 堆上的同一块空间
s2._str  ─┘
```

```
Date d1(2026, 6, 8);
Date d2(d1);
Date d2 = d1;
```

**这里是用已有对象初始化新对象，调用拷贝构造。**



## 5.赋值运算符重载

```
operator 运算符
operator+
operator-
operator==
operator<
operator=
operator[]
operator<<
operator++
```

**成员函数**

```c++
operator=
operator[]
operator()
operator->
    
operator++
operator--
operator+=
operator-=
operator*=
operator/=
```

**全局函数**

```c++
operator+
operator-
operator==
operator<

operator<<
operator>>
```

```
返回值 operator运算符(参数列表)
{
    // 运算逻辑
}
```

**那么编译器生成的默认赋值重载函数已经可以完成字节序的值拷贝了，我们还需要自己实现吗？当然像日期类没有必要的**



## 6日期类的实现





## 7.const成员

**将const修饰的类成员函数称之为const成员函数，const修饰类成员函数，实际修饰该成员函数隐含的this 指针，表明在该成员函数中不能对类的任何成员进行修改。**



## 8.取地址及const取地址操作符重载















