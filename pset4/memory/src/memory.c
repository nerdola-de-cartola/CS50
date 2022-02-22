#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *s = malloc(4);
    s[0] = 'H';
    s[3] = 'I';
    s[2] = '!';
    s[3] = '\0';

    printf("%s\n", s);

    free(s);
}
