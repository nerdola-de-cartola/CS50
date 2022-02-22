#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

void draw(int height);

int main(int argc, char const *argv[])
{
    int height = get_int("Height: ");
    draw(height);

    return 0;
}

void draw(int height)
{
    if (height == 0)
    {
        return;
    }
    else
    {
        draw(height - 1);

        for (int i = 0; i < height; i++)
        {
            printf("#");
        }
        printf("\n");       
    }
}