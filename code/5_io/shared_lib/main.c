#include <stdio.h>
#include "add.h"
#include "sub.h"

int main()
{
    int a = 10;
    int b = 20;

    printf("Add: %d\n", Add(a, b));
    printf("Sub: %d\n", Sub(a, b));

    return 0;
}
