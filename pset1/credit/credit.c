#include <stdio.h>
#include <cs50.h>
#include <math.h>

//CUSTOM FUNCTIONS
int firstDigits(int, long);
void updateAnswer(long);
bool LuhnsAlgorithm(long);
void updateArr(long);

//GLOBAL VARIABLES
long user_number;
string answer = "INVALID";
int arr[16] = {};
int pair_sum = 0;
int cousin_sum = 0;

int main(void)
{
    user_number = get_long("Number: ");

    updateAnswer(user_number);
    printf("%s\n", answer);
}

void updateAnswer(long card_number)
{
    //13 digits
    if (card_number > pow(10, 12) && card_number < pow(10, 13) - 1)
    {
        //STARTS WITH 4
        if (firstDigits(13, card_number) >= 40 && firstDigits(13, card_number) < 50)
        {
            if (LuhnsAlgorithm(card_number))
            {
                answer = "VISA";
            }
        }
    }

    //15 digits
    if (card_number > pow(10, 14) && card_number < pow(10, 15) - 1)
    {
        //START WITH 34 OR 37
        if (firstDigits(15, card_number) == 34 || firstDigits(15, card_number) == 37)
        {
            if (LuhnsAlgorithm(card_number))
            {
                answer = "AMEX";
            }
        }
    }

    //16 digits
    if (card_number > pow(10, 15) && card_number < pow(10, 16) - 1)
    {
        //STARTS WITH 4
        if (firstDigits(16, card_number) >= 40 && firstDigits(16, card_number) < 50)
        {
            if (LuhnsAlgorithm(card_number))
            {
                answer = "VISA";
            }
        }

        //STARTS WITH 51, 52, 53, 54 OR 55
        if (firstDigits(16, card_number) >= 51 && firstDigits(16, card_number) <= 55)
        {
            if (LuhnsAlgorithm(card_number))
            {
                answer = "MASTERCARD";
            }
        }
    }
}

int firstDigits(int total_digits, long first_two_digits)
{
    long rest = first_two_digits % (long) pow(10, total_digits - 2);
    first_two_digits -= rest;
    first_two_digits /= pow(10, total_digits - 2);

    return first_two_digits;
}

bool LuhnsAlgorithm(long card_number)
{
    //SETUP ARRAYS
    int pair[16] = {};
    int cousin[16] = {};
    updateArr(card_number);

    //SUM THE COUSIN AND THE PAIR DIGITS;
    for (int i = 0; i < 16; i++)
    {
        //PAIR
        if (i % 2 == 0)
        {
            pair[i] = arr[i];
            pair_sum += pair[i];
        }
        //COUSIN
        if (i % 2 != 0)
        {
            cousin[i] = arr[i] * 2;
        }
    }
    //COUSINS THAN HAVE 2 DIGITS
    for (int i = 0; i < 16; i++)
    {
        int current_cousin = cousin[i];

        if (current_cousin < 10)
        {
            cousin_sum += current_cousin;
        }
        if (current_cousin >= 10 &&  current_cousin <= 18)
        {
            int first_digit = current_cousin;
            int second_digit = current_cousin;

            second_digit %= 10;
            cousin_sum += second_digit;

            first_digit -= second_digit;
            first_digit /= 10;
            cousin_sum += first_digit;
        }
    }

    //CHECK THE TOTAL SUM
    int total_sum = cousin_sum + pair_sum;
    if (total_sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void updateArr(long number)
{
    //SETUP
    long div = 1;
    long digit_count = 1;

    //LOOP
    while (div <= number / 10)
    {
        digit_count++;
        div *= 10;
    }

    //USE LOOP TO ADD AT THE ARRAY
    while (digit_count > 0)
    {
        arr[digit_count - 1] = number / div;
        number %= div;
        div /= 10;
        digit_count--;
    }
}