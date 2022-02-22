#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {   
        for (int i = 0, length = strlen(argv[i]); i < length; i++)
        {
            printf("%c\n", argv[1][i]);
        }
    }
    

    return 0;
}