/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 1
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
#define STR_MAX 1000

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

// 1. Get a valid integer from the keyboard
int inputInt(void);

// 2. Validates the value entered is greater than 0
int inputIntPositive(void);

// 3. Validates the value entered is between upper and lower limits
int inputIntRange(int lowerBoundRange, int upperBoundRange);

// 4. Validate the entered character matches any of the characters in the received C string
char inputCharOption(char validChar[]);

// 5. Obtain user input for a C string value with a length
void inputCString(char* validChar, int lowerBoundRange, int upperBoundRange);

// 6. display an array of 10-character digits as a formatted phone number
void displayFormattedPhone(const char* validChar);