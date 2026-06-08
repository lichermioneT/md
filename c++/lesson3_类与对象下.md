# lesson3_类与对象中

## 1. 再谈构造函数

```c++
class Date
{
public:
 Date(int year, int month, int day)
 {
 _year = year;
 _month = month;
 _day = day;
 }

private:
 int _year;
 int _month;
 int _day;
};
```

**虽然上述构造函数调用之后，对象中已经有了一个初始值，但是不能将其称作为类对象成员的初始化，**

**构造函数体中的语句只能将其称作为赋初值，而不能称作初始化。**

**因为初始化只能初始化一次，而构造函数体内 可以多次赋值。**



**初始化列表进行初始化**

```c++
{
public:
 Date(int year, int month, int day)
 : _year(year)
 , _month(month)
 , _day(day)
 {}

private:
 int _year;
 int _month;
 int _day;
};

```

**1. 每个成员变量在初始化列表中只能出现一次(初始化只能初始化一次)**

**2. 类中包含以下成员，必须放在初始化列表位置进行初始化：**

​	**引用成员。 const成员变量。 自定义类型，没有默认构造函数的。**

**3. 尽量使用初始化列表初始化，因为不管你是否使用初始化列表，对于自定义类型成员变量，一定会先使 用初始化列表初始化。**

**4. 成员变量在类中声明次序就是其在初始化列表中的初始化顺序，与其在初始化列表中的先后次序无关**

**用explicit修饰构造函数，将会禁止单参构造函数的隐式转换。**



## 2. static成员

**声明为static的类成员称为类的静态成员，用static修饰的成员变量，称之为静态成员变量；**

**用static修饰的 成员函数，称之为静态成员函数。**

**静态的成员变量一定要在类外进行初始化**

**特点**

**1. 静态成员为所有类对象所共享，不属于某个具体的实例**

**2. 静态成员变量必须在类外定义，定义时不添加static关键字**

**3. 类静态成员即可用类名::静态成员或者对象.静态成员来访问**

**4. 静态成员函数没有隐藏的this指针，不能访问任何非静态成员**

**5. 静态成员和类的普通成员一样，也有public、protected、private3种访问级别，也可以具有返回值**



## 3.C++11 的成员初始化新玩法。

**C++11支持非静态成员变量在声明时进行初始化赋值，**

**但是要注意这里不是初始化，这里是给声明的成员变 量缺省值。**



## 4. 友元

**友元函数可以直接访问类的私有成员，它是定义在类外部的普通函数，不属于任何类，**

**但需要在类的内部声 明，声明时需要加friend关键字。**

```c++
class Date
{
friend ostream& operator<<(ostream& _cout, const Date& d);
friend istream& operator>>(istream& _cin, Date& d);
public:
 Date(int year, int month, int day)
 : _year(year)
 , _month(month)
 , _day(day)
 {}

private:
 int _year;
 int _month;
 int _day；
};
ostream& operator<<(ostream& _cout, const Date& d)
{
 _cout<<d._year<<"-"<<d._month<<"-"<<d._day;

 return _cout;
}
istream& operator>>(istream& _cin, Date& d)
{
 _cin>>d._year;
 _cin>>d._month;
 _cin>>d._day;

 return _cin;
}
int main()
{
 Date d;
 cin>>d;
 cout<<d<<endl;
 return 0;
}

```























