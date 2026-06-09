#include "date.cpp"

int main()
{
// 1.传值的构造函数
  date d1(2000, 2 ,29); 
  /*
   *std::cout << (d1 < d2) << std::endl;
   *std::cout << (d1 > d2) << std::endl;
   *std::cout << (d1 <= d2) << std::endl;
   *std::cout << (d1 >= d2) << std::endl;
   *std::cout << (d1 == d2) << std::endl;
   *std::cout << (d1 != d2) << std::endl;
   */

  d1 += (1000);
  d1.print(); 

  d1 -= (1000);
  d1.print(); 
  return 0;
}
