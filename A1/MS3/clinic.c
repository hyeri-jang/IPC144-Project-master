/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
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


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i, noRecord = 1;

    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber)
        {
            displayPatientData(&patient[i], fmt);
            noRecord = 0;
        }
    }

    if (noRecord)
    {
        printf("\n*** No records found ***\n");
    }
    putchar('\n');
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;

    do
    {
        printf("Search Options\n"
               "==========================\n"
               "1) By patient number\n"
               "2) By phone number\n"
               "..........................\n"
               "0) Previous menu\n"
               "..........................\n"
               "Selection: ");

        selection = inputIntRange(0, 2);
        putchar('\n');

        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int index;

    index = findPatientIndexByPatientNum(0, patient, max);

    if (index != -1)
    {
        patient[index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[index]);

        printf("*** New patient record added ***\n\n");
    }
    else
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patientNum;
    int indexNum;

    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    putchar('\n');

    indexNum = findPatientIndexByPatientNum(patientNum, patient, max);

    if (indexNum < 0)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        menuPatientEdit(&patient[indexNum]);
    }
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int patientNum, indexNum;
    char wantToRemove;
    struct Patient clear = { 0 };

    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    putchar('\n');

    indexNum = findPatientIndexByPatientNum(patientNum, patient, max);

    if (indexNum < 0)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        displayPatientData(&patient[indexNum], FMT_FORM);
        putchar('\n');

        printf("Are you sure you want to remove this patient record? (y/n): ");
        wantToRemove = inputCharOption("yn");

        if (wantToRemove == 'y')
        {
            patient[indexNum] = clear;
            printf("Patient record has been removed!\n");
        }
        else if (wantToRemove == 'n')
        {
            printf("Operation aborted.\n");
        }
    }
    putchar('\n');

}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData data[])
{
    int i, noRecord;
    int patientIndex = 0;

    bubbleSorting(data);

    displayScheduleTableHeader(NULL, 1);

    noRecord = 1;
    for (i = 0; i < data->maxAppointments; i++)
    {
        patientIndex = findPatientIndexByPatientNum (data->appointments[i].patientNumber,
                                                     data->patients, data->maxPatient);
        if (data->appointments[i].patientNumber > 0)
        {
            if (data->appointments[i].patientNumber ==
                data->patients[patientIndex].patientNumber)
            {
                displayScheduleData(&data->patients[patientIndex],
                                    &data->appointments[i], ALL_RECORD);
                noRecord = 0;
            }
        }
    }
    putchar('\n');

    if (noRecord)
    {
        printf("*** No records found ***\n\n");
    }
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData data[])
{
    int i;
    int noRecord;
    int patientIndex = 0;
    struct Date date = { 0 };

    bubbleSorting(data);

    inputYearMonthDay(&date);
    putchar('\n');

    displayScheduleTableHeader(&date, 0);

    noRecord = 1;
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (date.year == data->appointments[i].date.year &&
            date.month == data->appointments[i].date.month &&
            date.day == data->appointments[i].date.day)
        {
            patientIndex = findPatientIndexByPatientNum (data->appointments[i].patientNumber,
                                                         data->patients, data->maxPatient);
            if (data->appointments[i].patientNumber > 0)
            {
                if (data->appointments[i].patientNumber ==
                    data->patients[patientIndex].patientNumber)
                {
                    displayScheduleData(&data->patients[patientIndex],
                                        &data->appointments[i], TIME_RECORD);
                    noRecord = 0;
                }
            }
        }
    }
    putchar('\n');

    if (noRecord)
    {
        printf("*** No records found ***\n\n");
    }
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment appointments[], int maxAppointments,
    struct Patient patients[], int maxPatient)
{
    int i;
    int patientNum = 0;
    int index = 0;
    int validPatientNum = 0;
    int noTimeSlot, valid;
    struct Time time = { 0 };
    struct Date date = { 0 };

    index = findEmptyAppointmentsIndex(appointments, maxAppointments);

    if (index >= 0)
    {
        valid = 0;
        do
        {
            printf("Patient Number: ");
            patientNum = inputIntPositive();

            validPatientNum = findPatientIndexByPatientNum(patientNum, patients, maxPatient);

            if (validPatientNum >= 0)
            {
                valid = 1;
            }
            else
            {
                printf("\nERROR: Patient record not found!\n\n");
            }

        } while (!valid);

        valid = 0;
        do
        {
            inputYearMonthDay(&date);

            inputHourMin(&time);

            noTimeSlot = 0;
            for (i = 0; i < maxAppointments && !noTimeSlot; i++)
            {
                if (date.year == appointments[i].date.year &&
                    date.month == appointments[i].date.month &&
                    date.day == appointments[i].date.day &&
                    time.hour == appointments[i].time.hour &&
                    time.min == appointments[i].time.min)
                {
                    printf("\nERROR: Appointment timeslot is not available!\n\n");
                    noTimeSlot = 1;
                }
            }

            if (!noTimeSlot)
            {
                appointments[index].patientNumber = patientNum;
                appointments[index].date.year = date.year;
                appointments[index].date.month = date.month;
                appointments[index].date.day = date.day;
                appointments[index].time.hour = time.hour;
                appointments[index].time.min = time.min;
                printf("\n*** Appointment scheduled! ***\n\n");

                valid = 1;
            }

        } while (!valid);
    }
    else
    {
        printf("ERROR: Appointment listing is FULL!\n\n");
    }
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment appointments[], int maxAppointments,
                       struct Patient patients[], int maxPatient)
{
    int i;
    int yesNo = 0;
    int patientNum = 0;
    int appointIndex = 0, patientIndex = 0;
    int validPatientNum = 0, recordFound = 0, matching = 0;
    struct Date date = { 0 };
    struct Appointment clear = { 0 };
    
    printf("Patient Number: ");
    patientNum = inputIntPositive();

    validPatientNum = findPatientIndexByPatientNum(patientNum, patients, maxPatient);

    if (validPatientNum >= 0)
    {
        recordFound = 1;
    }
    else
    {
        recordFound = 0;
        printf("ERROR: Patient record not found!\n\n");
    }

    if (recordFound)
    {
        inputYearMonthDay(&date);
        putchar('\n');

        for (i = 0; i < maxAppointments; i++)
        {
            if (date.year == appointments[i].date.year &&
                date.month == appointments[i].date.month &&
                date.day == appointments[i].date.day)
            {
                if (patientNum == appointments[i].patientNumber)
                {
                    matching = 1;
                    appointIndex = i;
                }
            }
        }

        if (matching)
        {
            patientIndex = findPatientIndexByPatientNum(patientNum, patients, maxPatient);
            displayPatientData(&patients[patientIndex], FMT_FORM);

            printf("Are you sure you want to remove this appointment (y,n): ");
            yesNo = inputCharOption("yn");

            if (yesNo == 'y')
            {
                appointments[appointIndex] = clear;
                printf("\nAppointment record has been removed!\n\n");
            }
            else if (yesNo == 'n')
            {
                printf("Operation aborted.\n\n");
            }
        }
        else
        {
            printf("*** No records found ***\n\n");
        } 
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int index;
    int patientNum = 0;

    printf("Search by patient number: ");
    patientNum = inputIntPositive();
    putchar('\n');

    index = findPatientIndexByPatientNum(patientNum, patient, max);

    if (index < 0)
    {
        printf("*** No records found ***\n");
    }
    else
    {
        displayPatientData(&patient[index], FMT_FORM);
    }
    putchar('\n');
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i;
    int matchFound = 0;
    char inputPhoneNum[PHONE_LEN + 1] = { 0 };

    printf("Search by phone number: ");
    inputCString(inputPhoneNum, PHONE_LEN, PHONE_LEN);
    putchar('\n');

    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {
        if (strcmp(patient[i].phone.number, inputPhoneNum) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            matchFound = 1;
        }
    }

    if (!matchFound)
    {
        printf("\n*** No records found ***\n");
    }
    putchar('\n');
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int highestNum = patient[0].patientNumber;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > highestNum)
        {
            highestNum = patient[i].patientNumber;
        }
    }

    return highestNum + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max)
{
    int i;
    int returnValue = -1;

    for (i = 0; i < max && returnValue == -1; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            // indicates index number
            returnValue = i;
        }
    }

    return returnValue;
}

// Find the empty appointments struct index
int findEmptyAppointmentsIndex(struct Appointment appointments[], int max)
{
    int i, index = 0;
    int hasSpace = 0;

    for (i = 0; i < max && !hasSpace; i++)
    {
        if (appointments[i].patientNumber == 0)
        {
            hasSpace = 1;
            index = i;
        }
    }

    return index;
}

// Determines whether a given year is a leap year or not
// and get the last day of the month accordingly and returns it
int calculateLeapYearDays(int year, int month)
{
    int leapYear = 0;
    int days = 0;

    if ((((year % 4) == 0) && ((year % 100) != 0)) || (year % 400) == 0)
    {
        leapYear = 1;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        days = 30;
    }
    else if (month == 2)
    {
        if (leapYear)
        {
            days = 29;
        }
        else
        {
            days = 28;
        }
    }
    else
    {
        days = 31;
    }

    return days;
}

// Bubble sort the values of a string in ascending order
void bubbleSorting(struct ClinicData* data)
{
    data->patients->phone.number;
    data->patients[1].phone.number;

    int i, j;
    char str1[STR_LEN + 1] = { 0 };
    char str2[STR_LEN + 1] = { 0 };
    struct Appointment tempAppoints = { 0 };

    for (i = 0; i < data->maxAppointments; i++)
    {
        for (j = 0; j < (data->maxAppointments - i - 1); j++)
        {
            sprintf(str1, "%04d%02d%02d%02d%02d",
                           data->appointments[j].date.year,
                           data->appointments[j].date.month,
                           data->appointments[j].date.day,
                           data->appointments[j].time.hour,
                           data->appointments[j].time.min);

            sprintf(str2, "%04d%02d%02d%02d%02d",
                           data->appointments[j + 1].date.year,
                           data->appointments[j + 1].date.month,
                           data->appointments[j + 1].date.day,
                           data->appointments[j + 1].time.hour,
                           data->appointments[j + 1].time.min);

            if (strcmp(str1, str2) > 0)
            {
                tempAppoints = data->appointments[j];
                data->appointments[j] = data->appointments[j + 1];
                data->appointments[j + 1] = tempAppoints;
            }
        }
    }
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    char inputName[NAME_LEN + 1] = { 0 };

    printf("Patient Data Input\n"
           "------------------\n"
           "Number: %05d\n"
           "Name  : ",
           patient->patientNumber);

    inputCString(inputName, NAME_MIN, NAME_LEN);
    putchar('\n');

    strcpy(patient->name, inputName);
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int selection;
    char inputPhoneNum[PHONE_LEN + 1] = { 0 };

    printf("Phone Information\n"
           "-----------------\n"
           "How will the patient like to be contacted?\n"
           "1. Cell\n"
           "2. Home\n"
           "3. Work\n"
           "4. TBD\n"
           "Selection: ");

    selection = inputIntRange(1, 4);
    putchar('\n');

    switch (selection)
    {
    case 1:
        strcpy(phone->description, "CELL");
        break;
    case 2:
        strcpy(phone->description, "HOME");
        break;
    case 3:
        strcpy(phone->description, "WORK");
        break;
    case 4:
        // reset phone number
        *phone->number = 0;
        strcpy(phone->description, "TBD");
        break;
    }

    if (selection != 4)
    {
        printf("Contact: %s\n"
               "Number : ",
               phone->description);

        inputCString(inputPhoneNum, PHONE_LEN, PHONE_LEN);
        strcpy(phone->number, inputPhoneNum);
        putchar('\n');
    }
}

// Get user input for year, month, day information
// Returns the last day of month
void inputYearMonthDay(struct Date date[])
{
    int days = 0;

    printf("Year        : ");
    date->year = inputIntPositive();

    printf("Month (%d-%d): ", JAN, DEC);
    date->month = inputIntRange(JAN, DEC);

    days = calculateLeapYearDays(date->year, date->month);

    printf("Day (1-%d)  : ", days);
    date->day = inputIntRange(1, days);
}

// Get user input for hour, minute information
void inputHourMin(struct Time time[])
{
    int hourMinValid = 0;

    do
    {
        printf("Hour (0-23)  : ");
        time->hour = inputIntRange(0, 23);

        printf("Minute (0-59): ");
        time->min = inputIntRange(0, 59);

        if (time->hour > CLOSE_TIME || time->hour < OPEN_TIME ||
            time->min != 0 || (time->min % INTERVAL != 0))
        {
            printf("ERROR: Time must be between %d:00 "
                   "and %d:00 in %d minute intervals.\n\n",
                   OPEN_TIME, CLOSE_TIME, INTERVAL);
        }
        else
        {
            hourMinValid = 1;
        }
    } while (!hourMinValid);
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0;

    FILE* fp;
    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (i < max && fscanf(fp, "%d|%15[^|]|%4[^|]|%10[^\n]",
                                      &patients[i].patientNumber,
                                      patients[i].name,
                                      patients[i].phone.description,
                                      patients[i].phone.number) != EOF)
        {
            i++;
        }

        fclose(fp);
        fp = NULL;
    }
    else
    {
        printf("ERROR: File could not be read\n");
    }

    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0;

    FILE* fp;
    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (i < max && fscanf(fp, "%d,%d,%d,%d,%d,%d",
                                     &appoints[i].patientNumber,
                                     &appoints[i].date.year,
                                     &appoints[i].date.month,
                                     &appoints[i].date.day,
                                     &appoints[i].time.hour,
                                     &appoints[i].time.min) != EOF)
        {
            i++;
        }

        fclose(fp);
        fp = NULL;
    }
    else
    {
        printf("ERROR: File could not be read\n");
    }

    return i;
}
