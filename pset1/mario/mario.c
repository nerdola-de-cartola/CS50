#include <stdio.h>
#include <cs50.h>

//Declare functions
void printPyramids(int n);
void printLine(int line_position, int total_lines);

int main(void)
{
    int pyramids_height;

    //Prompt for the size of de pyramid
    do
    {
        pyramids_height = get_int("Height: ");
    }
    while (pyramids_height <= 0 || pyramids_height > 8);

    printPyramids(pyramids_height);
}

void printPyramids(int max)
{
    //Recursively prints each line
    for (int i = 1; i <= max; i++)
    {
        printLine(i, max);
    }
}

void printLine(int line_position, int total_lines)
{

    int hashes_number = line_position;
    int spaces_number = total_lines - hashes_number;

    //Prints the initial space
    for (int i = 0; i < spaces_number; i++)
    {
        printf(" ");
    }

    //Prints the first triangle
    for (int i = 0; i < hashes_number; i++)
    {
        printf("#");
    }

    printf("  ");

    //Prints the second triangle
    for (int i = 0; i < hashes_number; i++)
    {
        printf("#");
    }

    printf("\n");
}