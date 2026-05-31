#include "string.h"
#include <iostream>

#include <cassert>
#include <cstring>
#include <utility>

// =========================
// 1. 构造、拷贝、析构
// =========================
string::string()
    : _size(0)
    , _capacity(0)
    , _str(new char[1])
{
    _str[0] = '\0';
}

string::string(const char* str)
{
    if (str)
    {
        _size = strlen(str);
        _capacity = _size;

        _str = new char[_capacity + 1];
        memcpy(_str, str, _size + 1);  // 连同 '\0' 一起拷贝
    }
    else
    {
        _size = 0;
        _capacity = 0;
        _str = new char[1];
        _str[0] = '\0';
    }
}

string::string(size_t n, char ch)
    : _size(n)
    , _capacity(n)
    , _str(new char[n + 1])
{
    for (size_t i = 0; i < n; ++i)
    {
        _str[i] = ch;
    }

    _str[_size] = '\0';
}

string::string(const string& s)
    : _size(s._size)
    , _capacity(s._capacity)
    , _str(new char[s._capacity + 1])
{
    memcpy(_str, s._str, _size + 1);  // 连同 '\0' 一起拷贝
}

string::~string()
{
    delete[] _str;
    _str = nullptr;
    _size = 0;
    _capacity = 0;
}

// =========================
// 2. 容量相关接口
// =========================
size_t string::size() const
{
    return _size;
}

size_t string::length() const
{
    return _size;
}

size_t string::capacity() const
{
    return _capacity;
}

bool string::empty() const
{
    return _size == 0;
}

void string::reserve(size_t n)
{
    if (n <= _capacity)
    {
        return;
    }

    char* tmp = new char[n + 1];
    memcpy(tmp, _str, _size + 1);  // 连同 '\0' 一起拷贝

    delete[] _str;
    _str = tmp;
    _capacity = n;
}

void string::resize(size_t n, char ch)
{
    if (n > _size)
    {
        reserve(n);

        for (size_t i = _size; i < n; ++i)
        {
            _str[i] = ch;
        }

        _size = n;
        _str[_size] = '\0';
    }
    else if (n < _size)
    {
        _size = n;
        _str[_size] = '\0';
    }
}

void string::clear()
{
    _size = 0;
    _str[0] = '\0';
}

// =========================
// 3. 元素访问
// =========================
char& string::operator[](size_t i)
{
    assert(i < _size);
    return _str[i];
}

const char& string::operator[](size_t i) const
{
    assert(i < _size);
    return _str[i];
}

const char* string::c_str() const
{
    return _str;
}

// =========================
// 4. 迭代器
// =========================
string::iterator string::begin()
{
    return _str;
}

string::iterator string::end()
{
    return _str + _size;
}

string::const_iterator string::begin() const
{
    return _str;
}

string::const_iterator string::end() const
{
    return _str + _size;
}

string::const_iterator string::cbegin() const
{
    return _str;
}

string::const_iterator string::cend() const
{
    return _str + _size;
}

// =========================
// 5. 修改操作
// =========================
void string::push_back(char ch)
{
    if (_size == _capacity)
    {
        size_t newCapacity = (_capacity == 0) ? 2 : _capacity * 2;
        reserve(newCapacity);
    }

    _str[_size++] = ch;
    _str[_size] = '\0';
}

void string::append(const char* str)
{
    assert(str != nullptr);

    size_t len = strlen(str);

    // 处理 s.append(s.c_str()) 这种自追加场景
    bool self_append = (str >= _str && str <= _str + _size);
    size_t offset = 0;

    if (self_append)
    {
        offset = str - _str;
    }

    if (_size + len > _capacity)
    {
        reserve(_size + len);
    }

    if (self_append)
    {
        str = _str + offset;
    }

    memmove(_str + _size, str, len);
    _size += len;
    _str[_size] = '\0';
}

// =========================
// 6. 查找操作
// =========================
size_t string::find(char ch, size_t pos) const
{
    assert(pos <= _size);

    for (size_t i = pos; i < _size; ++i)
    {
        if (_str[i] == ch)
        {
            return i;
        }
    }

    return npos;
}

size_t string::find(const char* str, size_t pos) const
{
    assert(str != nullptr);
    assert(pos <= _size);

    if (*str == '\0')
    {
        return pos;
    }

    if (pos == _size)
    {
        return npos;
    }

    const char* index = strstr(_str + pos, str);

    if (index)
    {
        return index - _str;
    }

    return npos;
}

// =========================
// 7. 运算符重载
// =========================
string& string::operator=(string s)
{
    Swap(s);
    return *this;
}

string& string::operator+=(char ch)
{
    push_back(ch);
    return *this;
}

string& string::operator+=(const char* str)
{
    append(str);
    return *this;
}

string& string::operator+=(const string& s)
{
    append(s.c_str());
    return *this;
}

// =========================
// 8. 私有工具函数
// =========================
void string::Swap(string& s)
{
    std::swap(_size, s._size);
    std::swap(_capacity, s._capacity);
    std::swap(_str, s._str);
}

// =========================
// 9. 非成员函数
// =========================
std::ostream& operator<<(std::ostream& out, const string& s)
{
    out << s.c_str();
    return out;
}

