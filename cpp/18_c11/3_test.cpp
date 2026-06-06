#include <iostream>
#include <string>
using namespace std;

#include <iostream>
using namespace std;

void func(int& x)
{
    cout << "左值版本" << endl;
}

void func(int&& x)
{
    cout << "右值版本" << endl;
}

template<class T>
void wrapper(T&& x)
{
    func(x);
}

int main()
{
    int a = 10;

    wrapper(a);
    wrapper(10);

    return 0;
}

