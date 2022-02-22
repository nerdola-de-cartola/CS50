#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //All variables in this code
    int population_size;
    int end_size;
    int borns;
    int deaths;
    int years = 0;

    //Print information to the user
    printf("The start size must be at lest 9 because llamas should not be alone \n");
    printf("and the end size must be greater or equal to the start size, because the number of llamas should always grow \n");

    //Prompt ask for the initial size
    do
    {
        population_size = get_int("Start size: ");
    }
    while (population_size < 9);


    //Prompt ask for the end size
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < population_size);

    //Calculate the number of years until we reach threshold

    while (population_size < end_size)
    {
        borns = population_size / 3;
        deaths = population_size / 4;
        population_size += borns - deaths;
        years++;
    }

    //Print number of years to reach threshold
    printf("Years: %i\n", years);
}