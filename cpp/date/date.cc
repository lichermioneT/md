#include "date.cpp"

const int date::monthDay[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void date::print()
{
  std::cout<< "year:" << _year << " month:" << _month << " day:" << _day << std::endl;
}

int date::getMonthDay(int year, int month)
{
    if(year >=0 && month >= 1 && month <= 12)
    {
      // 1.闰年2月返回29天
       if(month == 2 && ((year % 4 == 0 && year % 100 !=0) || (year % 400 == 0))) 
       {
         return monthDay[month-1] + 1;
       }
       // 2.其它正常返回的
       else 
       {
         return monthDay[month-1];
       }
    }
    return -1;
}

date::date(int year, int month, int day)
  :_year(year)
  ,_month(month)
  ,_day(day)
{
  int monthDay = getMonthDay(_year, _month);

  if(monthDay > 0 && day >=  1 && day <= monthDay)
  {
    std::cout<< "初始化工作已经完成了,正确日期是" << std::endl;
    std::cout<< "year:" << _year << " month:" << _month << " day:" << _day << std::endl;
  }
  else 
  {
    std::cout<< "初始化工作已经失败了,错误日期是" << std::endl;
    std::cout<< "year:" << _year << " month:" << _month << " day:" << _day << std::endl;
  }
}

date::date(const date& d)
{
  _year = d._year;
  _month = d._month;
  _day = d._day;
  std::cout<< "初始化工作已经完成了" << std::endl;
}

date& date::operator=(const date &d)
{
  _year = d._year;
  _month = d._month;
  _day = d._day;

  return *this;
}

date::~date()
{
  std::cout<< "清理工作已经完成了" << std::endl; 
}

// 2年月日的获取
int date::year()const 
{
  return _year;
}

int date::month() const 
{
  return _month;
}

int date::day() const 
{
  return _day;
}

// 函数重载
bool date::operator<(const date& d)const 
{
  return (_year < d._year) || 
         (_year == d._year && _month < d._month) ||
         (_year == d._year && _month == d._month && _day < d._day);
}

bool date::operator==(const date& d)const 
{
  return _year == d._year && _month == d._month && _day == d._day;
}

bool date::operator>=(const date& d) const 
{
  return !(*this < d);
}

bool date::operator<=(const date& d) const 
{
  return (*this < d || *this == d);
}

bool date::operator>(const date& d) const 
{
  return !(*this <= d); 
}

bool date::operator!=(const date& d) const 
{
  return !(*this == d);
}

// 函数重载
date& date::operator+=(int day)
{
  _day += day;
  
  while(_day > getMonthDay(_year, _month))
  {
    _day  -= getMonthDay(_year, _month);
    _month += 1;
    if(_month > 12)
    {
      _month = 1;
      _year += 1;
    }
  }
  return *this;
}

date date::operator+(int day) const
{
    date temp(*this);

    temp += day;
    return temp;
}

date& date::operator-=(int day)
{
  _day -= day;
  
  while(_day <= 0)
  {

    _month -= 1;
    if(_month == 0)
    {
      _month = 12;
      _year -= 1;
    }

    _day += getMonthDay(_year, _month);
  }

  return *this;
}

date date::operator-(int day) const
{
  date temp(*this);
  
  temp -= day;
  return temp;
}

date& date::operator++()
{
    *this += 1;
    return *this;
}

date date::operator++(int)
{
    date temp(*this);
    *this += 1;
    return temp;
}

date& date::operator--()
{
  *this -= 1;
  return *this;
}

date date::operator--(int)
{
  date temp(*this);
  *this += 1;

  return temp;
}


































