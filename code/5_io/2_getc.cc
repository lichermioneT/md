#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
 FILE* fp = fopen("log.txt", "w+"); 
 if(fp == NULL)
 {
   perror("fopen");
   return -1;
 }
  
  fputc('z', fp);
  fputc('z', fp);
  fputc('z', fp);

// 这里读取不成功，因为文件指针到末尾了的。
  rewind(fp);
  int ch = 0;
  while((ch = fgetc(fp)) != EOF)
  {
    putchar(ch);

    /*
     *cout<< ch;
     */
  }
  
  
  fclose(fp);
  return 0;
}
