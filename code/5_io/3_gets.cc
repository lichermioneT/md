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
    
 fputs("zzzzzzzzzzzzzzzzzzzz", fp);
  
// 这里读取不成功，因为文件指针到末尾了的。
  rewind(fp);
  char buf[1024] = {0}; 
  char* ret = fgets(buf, 1024, fp); 

  cout<< ret << endl;
  cout<< buf << endl;
  
  fclose(fp);
  return 0;
}
