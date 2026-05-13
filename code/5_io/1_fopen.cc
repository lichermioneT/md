#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
 FILE* fp = fopen("log.txt", "w"); 
 if(fp == NULL)
 {
   perror("fopen");
   return -1;
 }

 const char* name  = "---------ffffffffffffff---------";
 fwrite(name, sizeof(char), strlen(name), fp);

  
  fclose(fp);
  return 0;
}
