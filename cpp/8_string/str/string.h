#ifndef __STRING_H__
#define __STRING_H__

#include <cstddef>
#include <iosfwd>

class string
{
public:
    // =========================
    // 1. 类型定义和常量
    // =========================
    using iterator = char*;
    using const_iterator = const char*;

    static constexpr size_t npos = static_cast<size_t>(-1);

public:
    // =========================
    // 2. 构造、拷贝、析构
    // =========================
    string();
    string(const char* str);
    string(size_t n, char ch = '\0');
    string(const string& s);
    ~string();

    // =========================
    // 3. 容量相关接口
    // =========================
    size_t size() const;
    size_t length() const;
    size_t capacity() const;
    bool empty() const;

    void reserve(size_t n);
    void resize(size_t n, char ch = '\0');
    void clear();

    // =========================
    // 4. 元素访问
    // =========================
    char& operator[](size_t i);
    const char& operator[](size_t i) const;

    const char* c_str() const;

    // =========================
    // 5. 迭代器
    // =========================
    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    // =========================
    // 6. 修改操作
    // =========================
    void push_back(char ch);
    void append(const char* str);

    // =========================
    // 7. 查找操作
    // =========================
    size_t find(char ch, size_t pos = 0) const;
    size_t find(const char* str, size_t pos = 0) const;

    // =========================
    // 8. 运算符重载
    // =========================
    string& operator=(string s);

    string& operator+=(char ch);
    string& operator+=(const char* str);
    string& operator+=(const string& s);

    // =========================
    // 9. 友元函数
    // =========================
    friend std::ostream& operator<<(std::ostream& out, const string& s);

private:
    // =========================
    // 10. 私有工具函数
    // =========================
    void Swap(string& s);

private:
    // =========================
    // 11. 成员变量
    // =========================
    size_t _size;
    size_t _capacity;
    char* _str;
};

// =========================
// 12. 非成员函数声明
// =========================
std::ostream& operator<<(std::ostream& out, const string& s);

#endif
