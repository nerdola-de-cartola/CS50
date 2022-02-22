#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string user_name = get_string("What is your name?\n");
    printf("hello, %s\n", user_name);
}
