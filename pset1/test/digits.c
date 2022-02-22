#include <limits.h>
#include <stdio.h>

void generateArray(long);

int arr[16] = {};
long score = 123456789012345;

int main (void)
{
    printf ("score digit by digit: ");

    generateArray(score);

    return 0;
}

void generateArray(long number)
{
    long div = 1;
    long digit_count = 1;

    while ( div <= number / 10 ) {
    digit_count++;
    div *= 10;
    }

    while ( digit_count > 0 ) {
    arr[digit_count - 1] = number / div;
    number %= div;
    div /= 10;
    digit_count--;
    }

    for(int i = 0; i < 16; i++)
    {
        printf ("%i, ", arr[i]);
    }
}