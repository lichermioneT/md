#pragma once
#include <iostream>

class date 
{
friend std::ostream& operator<<(std::ostream&, const date&);
public:
// 1.默认构造函数
  date(int year, int month,  int day);
  date(const date&);
  date& operator=(const date&);
  ~date();
  
  void print();

// 2.年月日获取
  int year() const;
  int month() const;
  int day() const;

// 3.函数重载，日期比较
  bool operator<(const date&) const;
  bool operator==(const date&) const;
  bool operator>=(const date&) const;
  bool operator<=(const date&) const;
  bool operator>(const date&) const;
  bool operator!=(const date&) const;

// 3.函数重载，日期加减 
  date& operator+=(int day);
  date operator+(int day) const;
  date operator-(int day) const;
  date& operator-=(int day);

// 后置的，返回的是一个新的对象。
// int a = 10;
// int b = a++;
  date operator++(int);
  date operator--(int);

  date& operator++();
  date& operator--();

private:
  int _year;
  int _month;
  int _day;
  static const int monthDay[12];
	static int getMonthDay(int year, int month);
};

std::ostream& operator<<(std::ostream&, const date&);
