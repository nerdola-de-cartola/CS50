#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

//Custom functions
bool isValidKeyWords(void);
bool isValidKeyCharacters(void);
int createNewAlphabet(void);
int encryptText(void);

//Global Variables
int N_ARGUMENTS;
int KEY_LENGTH;
char ALPHABET[52];
string KEY;
string ENCHIPER_TEXT;
string PLAIN_TEXT;

int main(int argc, char *argv[])
{
    N_ARGUMENTS = argc;

    if (isValidKeyWords())
    {
        KEY_LENGTH = strlen(argv[1]);
        KEY = argv[1];

        if (isValidKeyCharacters())
        {
            //Get input from user
            PLAIN_TEXT = get_string("plaintext: ");

            //Generates encrypted text
            createNewAlphabet();
            encryptText();

            //Output for user
            printf("ciphertext: %s\n", ENCHIPER_TEXT);

            return 0;
        }
    }
    //Error
    return 1;
}

bool isValidKeyWords(void)
{
    if (N_ARGUMENTS != 2)
    {
        printf("Usage: ./substitution key\n");
        return false;
    }
    return true;
}

bool isValidKeyCharacters(void)
{
    if (KEY_LENGTH != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    for (int i = 0; i < KEY_LENGTH; i++)
    {
        char current_char = KEY[i];

        if (!isalpha(current_char))
        {
            printf("Key must only contain alphabetic characters.\n");
            return false;
        }

        for (int j = 0; j < i; j++)
        {
            if (current_char == KEY[j])
            {
                printf("Key must not contain repeated characters.\n");
                return false;
            }
        }
    }
    return true;
}

int createNewAlphabet(void)
{
    for (int i = 0; i < KEY_LENGTH ; i++)
    {
        char current_letter = KEY[i];

        if (isalpha(current_letter))
        {
            if (!islower(current_letter))
            {
                //Place the new character in the corresponding position
                ALPHABET[i] = current_letter;
                //Case insensitive
                ALPHABET[i + 26] = tolower(current_letter);
            }
            else if (islower(KEY[i]))
            {
                //Place the new character in the corresponding position
                ALPHABET[i] = toupper(current_letter);
                //Case insensitive
                ALPHABET[i + 26] = current_letter;
            }
            else
            {
                //Error
                return 1;
            }
        }
    }
    return 0;
}

int encryptText(void)
{
    ENCHIPER_TEXT = PLAIN_TEXT;

    for (int i = 0, length = strlen(PLAIN_TEXT); i < length ; i++)
    {
        char current_letter = ENCHIPER_TEXT[i];

        if (isalpha(current_letter))
        {
            //Alphabetical position
            int alpha_position;

            if (isupper(current_letter))
            {
                //Find the position of the corresponding letter in the new alphabet
                alpha_position = current_letter - 65;
                //Generate the new text
                ENCHIPER_TEXT[i] = ALPHABET[alpha_position];
            }
            else if (islower(current_letter))
            {
                //Find the position of the corresponding letter in the new alphabet
                alpha_position = current_letter - 71;
                //Generate the new text
                ENCHIPER_TEXT[i] = ALPHABET[alpha_position];
            }
            else
            {
                //Error
                return 1;
            }
        }
    }
    return 0;
}