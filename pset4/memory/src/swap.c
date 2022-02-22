#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);

int main(int argc, char const *argv[])
{
    int x = 1;
    int y = 2;

    printf("x is: %i and y is: %i\n", x, y);
    swap(&x, &y);
    printf("And now\n");
    printf("x is: %i and y is: %i\n", x, y);
    return 0;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
