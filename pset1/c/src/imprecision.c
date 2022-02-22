#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float x = get_float("x: ");
    float y = get_float("y: ");
    float w = x / y;

    printf("%.100f\n", w);
}