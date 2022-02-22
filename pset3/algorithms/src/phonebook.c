#include <cs50.h>
#include <stdio.h>
#include <string.h>

//Custom data type
//Like a object
typedef struct
{
    //Define attributes
    string names;
    string numbers;
}
//Name of data struct
person;

int main(void)
{
    //Crate an array of persons
    person people[2];

    //The first person receive his name 
    people[0].names = "Brian";
    //The first person receive his phonenumber 
    people[0].numbers = "+1-617-495-1000";

    //The second person receive his name
    people[1].names = "David";
    //The second person receive his number 
    people[1].numbers = "+1-949-468-2750";
    
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].names, "David")  == 0)
        {
            printf("Found %s\n", people[0].numbers);
            return 0;
        }
    }
    printf("Not found \n");
    return 1;
}
