#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char c0 = 'H';
    char c1 = 'I';
    char c2 = '!';

    string s = "HI!";

    printf("%i %i %i\n", (int)c0, c1, c2);
    printf("%i %i %i %i %i\n", s[0], s[1], s[2], s[3], s[39]);
    return 0;
}
