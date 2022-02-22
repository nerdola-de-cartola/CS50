#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//Custom functions
int countLetters(string text);
int countWords(string text);
int countSenteces(string text);
int calculateIndex(int letters, int words, int senteces);
string defineMessage(int index);

int main(void)
{
    string text = get_string("Text :");

    int letters = countLetters(text);
    int words = countWords(text);
    int senteces = countSenteces(text);

    int index = calculateIndex(letters, words, senteces);

    string reading_level = defineMessage(index);
    printf("%s\n", reading_level);
}

int countLetters(string text)
{
    int n = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        char c = text[i];
        if (isalpha(c))
        {
            n++;
        }
    }

    return n;
}

int countWords(string text)
{
    int n = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        char c = text[i];
        if (isspace(c))
        {
            n++;
        }
    }

    return n + 1;
}

int countSenteces(string text)
{
    int n = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        char c = text[i];
        if (c == 33 || c == 46 || c == 63)
        {
            n++;
        }
    }

    return n;
}

int calculateIndex(int letters, int words, int senteces)
{
    float index;
    float L;
    float S;

    L = (float) letters / words * 100;
    S = (float) senteces / words * 100;

    index = 0.0588 * L - 0.296 * S - 15.8;

    return round(index);
}

string defineMessage(int index)
{
    string message;

    if (index <= 1)
    {
        message = "Before Grade 1";
    }
    if (index >= 16)
    {
        message = "Grade 16+";
    }
    if (index > 1 && index < 16)
    {
        //Turns the reading level into a string
        char concatenation[13];
        sprintf(concatenation, "Grade %i", index);

        message = concatenation;
    }

    return message;
}

