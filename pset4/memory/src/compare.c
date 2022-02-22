#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    char *s = get_string("i: ");
    char *t = get_string("j: ");

    if (!strcmp(s, t))
    {
        printf("Same\n");
    }
    else
    {
        printf("Different\n");
    }
    
    printf("%p\n", s);
    printf("%p\n", t);

    return 0;
}
