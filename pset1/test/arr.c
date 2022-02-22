#include <stdio.h>

int pairLength(void);

int pair[] = {1, 2, 10};

int main(void)
{
    printf("%i\n", pairLength());

    pair[pairLength() - 1] = 99;

    for(int i =0; i < pairLength(); i++)
    {
        printf("%i\n", pair[i]);
    }
}

int pairLength(void)
{
    return sizeof(pair) / sizeof(pair[0]);
}