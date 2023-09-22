/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  : HYERI JANG
Student ID#: 115328221
Email      : hjang34@myseneca.ca
Section    : NAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "core.h"


//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//

// As demonstrated in the course notes: 
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer
// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

// 1. Get a valid integer from the keyboard
// test01
int inputInt(void)
{
    char newLine = 'X';
    int inputValue = 0;
    int valid = 0;

    do
    {
        scanf("%d%c", &inputValue, &newLine);

        if (newLine == '\n')
        {
            valid = 1;
        }
        else
        {
            valid = 0;
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }

    } while (!valid);

    return inputValue;
}

// 2. Validates the value entered is greater than 0
// test02
int inputIntPositive(void)
{
    int inputValue = 0;
    int valid = 0;

    do
    {
        inputValue = inputInt();

        if (inputValue > 0)
        {
            valid = 1;
        }
        else
        {
            valid = 0;
            printf("ERROR! Value must be > 0: ");
        }

    } while (!valid);

    return inputValue;
}

// 3. Validates the value entered is between upper and lower limits
// test03, test04
int inputIntRange(int lowerBoundRange, int upperBoundRange)
{
    int inputValue = 0;
    int valid = 0;

    do
    {
        inputValue = inputInt();

        if (lowerBoundRange > inputValue || inputValue > upperBoundRange)
        {
            valid = 0;
            printf("ERROR! Value must be between %d and %d inclusive: ",
                lowerBoundRange, upperBoundRange);
        }
        else
        {
            valid = 1;
        }

    } while (!valid);

    return inputValue;
}

// 4. Validate the entered character matches any of the characters in the received C string
// test05
char inputCharOption(char validChar[])
{
    char inputValue;
    char newLine = 'X';
    int valid = 0;
    int i;

    do
    {
        scanf(" %c%c", &inputValue, &newLine);

        if (newLine == '\n')
        {
            valid = 0;

            for (i = 0; !valid && validChar[i] != '\0'; i++)
            {
                if (inputValue == validChar[i])
                {
                    valid = 1;
                }
            }
        }
        else
        {
            valid = 0;
            clearInputBuffer();
        }

        if (!valid)
        {
            printf("ERROR: Character must be one of [%s]: ", validChar);
        }

    } while (!valid);

    return inputValue;
}

// 5. Obtain user input for a C string value with a length
// test06, test07, test08
void inputCString(char* validChar, int lowerBoundRange, int upperBoundRange)
{
    char inputValue[STR_MAX + 1] = { 0 };
    int length;
    int valid = 0;

    do
    {
        scanf("%1000[^\n]", inputValue);
        clearInputBuffer();

        length = strlen(inputValue);

        if ((lowerBoundRange == upperBoundRange) && (length != lowerBoundRange))
        {
            printf("ERROR: String length must be exactly %d chars: ",
                upperBoundRange);
        }
        else if (length > upperBoundRange)
        {
            printf("ERROR: String length must be no more than %d chars: ",
                upperBoundRange);
        }
        else if (length < lowerBoundRange)
        {
            printf("ERROR: String length must be between %d and %d chars: ",
                lowerBoundRange, upperBoundRange);
        }
        else
        {
            valid = 1;
            strcpy(validChar, inputValue);
        }
    } while (!valid);

}

// 6. display an array of 10-character digits as a formatted phone number
// test09
void displayFormattedPhone(const char* validChar)
{
    int i, length;
    int isDigit = 0;

    if (validChar == NULL)
    {
        printf("(___)___-____");
    }
    else
    {
        length = strlen(validChar);

        isDigit = 1;
        for (i = 0; validChar[i] != '\0'; i++)
        {
            if (validChar[i] < '0' || validChar[i] > '9')
            {
                isDigit = 0;
            }
        }

        if (length == 10 && isDigit == 1)
        {
            printf("(%3.3s)%3.3s-%4.4s", &validChar[0], &validChar[3], &validChar[6]);
        }
        else
        {
            printf("(___)___-____");
        }
    }
}