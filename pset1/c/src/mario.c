#include <stdio.h>

void drawLine(int);
void drawColumn(int);
void drawSpace(int);
void drawBlock(int);
int sharpToSpace(int);

    int screen_width =162;
    int screen_heigh = 12;
    int block_width = 12;
    int block_heigh = 5;

int main(void)
{
    //Faz a linha 1
    for (int i = 0; i < block_heigh; i++)
    {
        drawLine(screen_width);
        printf("\n");
    }

    //Faz a linha 2
    for (int i = 0; i < block_heigh; i++)
    {
        drawSpace(block_width*10);
        drawLine(block_width);
        printf("\n");
    }

    //Faz a linha 3
    for (int i = 0; i < block_heigh; i++)
    {
        drawLine(block_width * 9);
        drawSpace(block_width);
        drawLine(block_width);
        printf("\n");
    }

    //Faz a linha 4
    for (int i = 0; i < block_heigh; i++)
    {
        drawLine(block_width * 9);
        printf("\n");
    }

    //Faz a linha 5
    for (int i = 0; i < block_heigh; i++)
    {
        drawLine(block_width * 9);
        drawSpace(block_width);
        drawLine(block_width);
        printf("\n");
    }

    //Faz a linha 6
    for (int i = 0; i < block_heigh; i++)
    {
        drawSpace(block_width*10);
        drawLine(block_width);
        printf("\n");
    }

    //Faz a linha 7
    for (int i = 0; i < block_heigh; i++)
    {
        drawLine(screen_width);
        printf("\n");
    }
 
    
    return 0;
}

void drawLine(int counter)
{
    for (int i = 0; i < counter; i++)
    {
        printf("#");
    }
}

void drawColumn(int counter)
{
    for (int i = 0; i < counter; i++)
    {
        printf("#");
        printf("\n");
    }
}

int sharpToSpace(int n_sharp)
{
    int n_space = 1.5 * n_sharp;
    return n_space;
}

void drawSpace(int counter)
{
    for (int i = 0; i < counter; i++)
    {
        printf(" ");
    }
}

void drawBlock(int counter)
{
    for (int i = 0; i < counter; i++)
    {
        drawLine(block_width);
    }
    
}