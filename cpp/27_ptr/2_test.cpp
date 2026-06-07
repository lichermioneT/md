#include <iostream>
#include <memory>
using namespace std;

class MyClass {
public:
    ~MyClass() { std::cout << "MyClass destructor" << std::endl; }
};

int main() 
{
    std::unique_ptr<MyClass> p(new MyClass());
    // p 析构时，自动 delete 内部指针 → 调用 MyClass 的析构函数
    return 0;  // 输出 "MyClass destructor"
}

