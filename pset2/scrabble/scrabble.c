#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Custom functions
int wordScore(string word);
int letterScore(int ascii_code);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Set the score for both words
    int score1 = wordScore(word1);
    int score2 = wordScore(word2);

    // Prints the game result
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Return the point of a word
int wordScore(string word)
{
    //
    int score = 0;
    int letter;

    for (int i = 0, length = strlen(word); i < length; i++)
    {
        letter = toupper(word[i]);
        score += letterScore(letter);
    }

    return score;
}

// Return the points of a letter
int letterScore(int ascii_code)
{
    if (ascii_code >= 65 && ascii_code <= 90)
    {
        int score = ascii_code - 65;
        return POINTS[score];
    }
    else
    {
        return 0;
    }
}