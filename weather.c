#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "weather.h"
#include "core.h"

//menuMain function

void menuMain(struct WeatherRecord* data)
{
    int selection;
    do {
        printf("=======================================================\n"
            "         Ontario Weather Analysis Service\n"
            "                  Year: 2021\n"
            "=======================================================\n"
            "1. View all data\n"
            "2. View by region (sorted DESCENDING by precip.)\n"
            "3. View by month (sorted ASCENDING by precip.)\n"
            "4. View by location name (sorted DESCENDING by precip.)\n"
            "-------------------------------------------------------\n"
            "0. Exit\n"
            "-------------------------------------------------------\n"
            "Selection: ");


        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Application Terminated!");
            break;
        case 1:
            viewAllData(data, MAXRECORDS);
            break;
        case 2:
            viewByRegion(data, MAXRECORDS);
            break;
        case 3:
            viewByMonth(data, MAXRECORDS);
            break;
        case 4:
            viewByCity(data, MAXRECORDS);
            break;
        }
        putchar('\n');
    } while (selection);
    ;
}



// Import weather data

int importWeatherDataFile(FILE* fp, struct WeatherRecord* data, int max)

{
    int recs = 0;
    if (fp != NULL)
    {
        while (recs < max &&
            fscanf(fp, "%d,%d,%lf,%c,%d,%15[^\n]\n",
                &data[recs].date.year, &data[recs].date.month,
                &data[recs].precipAmt, &data[recs].unit,
                &data[recs].location.regionCode,
                data[recs].location.name) == 6)
        {
            recs++;
        }
    }
    return recs;
}


// View All Data

void viewAllData(struct WeatherRecord* data, int max)
{
    int i = 0, looping = 1;
    printf("Year Month Precip.Amt Unit Region Name\n"
        "---- ----- ---------- ---- ------ ---------------\n");
    while (looping)
    {
        if (data[i].date.year != 0)
        {
            printf("%d    %02d%11.1lf    %c%7d %s\n", data[i].date.year,
                data[i].date.month,
                data[i].precipAmt,
                data[i].unit,
                data[i].location.regionCode,
                data[i].location.name);
            i++;
            if (((i) % PAGELENGHT) == 0)
            {
                putchar('\n');
                suspend();
            }
        }
        else
        {
            looping = 0;
        }

    }
}

void viewByRegion(struct WeatherRecord* data, int max)
{
    int i = 0, k = 0;
    double average = 0;
    int total = 0;
    int FMT = FMTDES;
    int flag;
    printf("Region Name     Precip(mm)\n");
    printf("------ -------- ----------\n");

    struct TempArrays tempArrays = { {0}, {""}, {0} , {0}, {""} };

    for (i = 0; i < max; i++)
    {
        tempArrays.arrayByNum[i] = data[i].location.regionCode;
    }
    findUniqueAdd(data, &tempArrays, max);

    sortWeatherRecords(&tempArrays, MAXUNIQUE, FMT);

    k = 0;
    while (tempArrays.uniqueIntArray[k] != 0)
    {
        switch (tempArrays.uniqueIntArray[k]) {
        case 10:
            strcpy(tempArrays.uniqueCharArray[k], "Western");
            break;
        case 20:
            strcpy(tempArrays.uniqueCharArray[k], "Northern");
            break;
        case 30:
            strcpy(tempArrays.uniqueCharArray[k], "Eastern");
            break;
        case 40:
            strcpy(tempArrays.uniqueCharArray[k], "Central");
            break;

        }

        printf("    %d %-10s %8.0lf\n", tempArrays.uniqueIntArray[k], tempArrays.uniqueCharArray[k], tempArrays.precipAdd[k]);
        total += tempArrays.precipAdd[k];
        k++;

    }
    average = total / 4.00;
    printf("------ -------- ----------\n");
    printf("         Total: %10d\n", total);
    printf("       Average: %10.2lf\n", average);

}

void viewByMonth(struct WeatherRecord* data, int max)
{
    int i = 0, k = 0;
    double average = 0;
    int total = 0;
    int FMT = FMTASC;
    printf("Month     Precip(mm)\n");
    printf("--------- ----------\n");

    struct TempArrays tempArrays = { {0}, {""}, {0} , {0}, {""} };

    for (i = 0; i < max; i++)
    {
        tempArrays.arrayByNum[i] = data[i].date.month;
    }


    findUniqueAdd(data, &tempArrays, max);

    sortWeatherRecords(&tempArrays, MAXUNIQUE, FMT);

    while (tempArrays.uniqueIntArray[k] != 0)
    {
        switch (tempArrays.uniqueIntArray[k])
        {
        case 1:
            strcpy(tempArrays.uniqueCharArray[k], "January");
            break;
        case 2:
            strcpy(tempArrays.uniqueCharArray[k], "February");
            break;
        case 3:
            strcpy(tempArrays.uniqueCharArray[k], "March");
            break;
        case 4:
            strcpy(tempArrays.uniqueCharArray[k], "April");
            break;
        case 5:
            strcpy(tempArrays.uniqueCharArray[k], "May");
            break;
        case 6:
            strcpy(tempArrays.uniqueCharArray[k], "June");
            break;
        case 7:
            strcpy(tempArrays.uniqueCharArray[k], "July");
            break;
        case 8:
            strcpy(tempArrays.uniqueCharArray[k], "August");
            break;
        case 9:
            strcpy(tempArrays.uniqueCharArray[k], "Septemper");
            break;
        case 10:
            strcpy(tempArrays.uniqueCharArray[k], "October");
            break;
        case 11:
            strcpy(tempArrays.uniqueCharArray[k], "November");
            break;
        case 12:
            strcpy(tempArrays.uniqueCharArray[k], "December");
            break;
        }
        printf("%-9s %10.0lf\n", tempArrays.uniqueCharArray[k], tempArrays.precipAdd[k]);
        total += tempArrays.precipAdd[k];
        k++;

    }
    average = total / 12.00;
    printf("--------- ----------\n");
    printf("   Total: %10d\n", total);
    printf(" Average: %10.2lf\n", average);

}


//View by City

void viewByCity(struct WeatherRecord* data, int max)
{
    int i = 0, k = 0;
    double average = 0;
    int total = 0;
    int FMT = FMTDES;
    printf("Location        Precip(mm)\n");
    printf("--------------- ----------\n");
    struct TempArrays tempArrays = { {0}, {""}, {0} , {0}, {""} };

    for (i = 0; i < max; i++)
    {
        strcpy(tempArrays.arrayByStr[i], data[i].location.name);
    }

    findUniqueAdd(data, &tempArrays, max);

    sortWeatherRecords(&tempArrays, MAXUNIQUE, FMT);

    k = 0;
    while (strlen(tempArrays.uniqueCharArray[k]) != 0)
    {
        printf("%15s %10.0lf\n", tempArrays.uniqueCharArray[k], tempArrays.precipAdd[k]);
        total += tempArrays.precipAdd[k];
        k++;
    }
    average = total / 8.00;
    printf("--------------- ----------\n");
    printf("         Total: %10d\n", total);
    printf("       Average: %10.2lf\n", average);
}


//Utility functions

//sort ascending

void sortWeatherRecords(struct TempArrays* temparrays, int max, int FMT)
{
    int i = 0, k = 0;
    struct TempArrays temp = { {0}, {""}, {0} , {0}, {""} };
    if (FMT == FMTASC)
    {
        for (i = max - 1; i > 0; i--)
        {
            for (k = 0; k < i; k++)
            {
                if (temparrays->precipAdd[k + 1] == 0)
                {
                    ;
                }
                else
                {
                    if (temparrays->precipAdd[k] > temparrays->precipAdd[k + 1])
                    {
                        temp.precipAdd[0] = temparrays->precipAdd[k];
                        temp.uniqueIntArray[0] = temparrays->uniqueIntArray[k];
                        strcpy(temp.uniqueCharArray[0], temparrays->uniqueCharArray[k]);

                        temparrays->precipAdd[k] = temparrays->precipAdd[k + 1];
                        temparrays->uniqueIntArray[k] = temparrays->uniqueIntArray[k + 1];
                        strcpy(temparrays->uniqueCharArray[k], temparrays->uniqueCharArray[k + 1]);

                        temparrays->precipAdd[k + 1] = temp.precipAdd[0];
                        temparrays->uniqueIntArray[k + 1] = temp.uniqueIntArray[0];
                        strcpy(temparrays->uniqueCharArray[k + 1], temp.uniqueCharArray[0]);
                    }
                }
            }
        }
    }
    else
    {
        for (i = max - 1; i > 0; i--)
        {
            for (k = 0; k < i; k++)
            {
                if (temparrays->precipAdd[k + 1] == 0)
                {
                    ;
                }
                else
                {
                    if (temparrays->precipAdd[k] < temparrays->precipAdd[k + 1])
                    {
                        temp.precipAdd[0] = temparrays->precipAdd[k];
                        temp.uniqueIntArray[0] = temparrays->uniqueIntArray[k];
                        strcpy(temp.uniqueCharArray[0], temparrays->uniqueCharArray[k]);

                        temparrays->precipAdd[k] = temparrays->precipAdd[k + 1];
                        temparrays->uniqueIntArray[k] = temparrays->uniqueIntArray[k + 1];
                        strcpy(temparrays->uniqueCharArray[k], temparrays->uniqueCharArray[k + 1]);

                        temparrays->precipAdd[k + 1] = temp.precipAdd[0];
                        temparrays->uniqueIntArray[k + 1] = temp.uniqueIntArray[0];
                        strcpy(temparrays->uniqueCharArray[k + 1], temp.uniqueCharArray[0]);
                    }
                }
            }
        }
    }

}


//create arrays with unique values and add the precipitation

void findUniqueAdd(struct WeatherRecord* data, struct TempArrays* temparrays, int max)
{
    int i = 0, j = 0, k = 0, bigFlag = 0, flag = 0, counter = 0;

    while (i < max && bigFlag == 0)
    {
        if (temparrays->arrayByNum[i] == 0 && strlen(temparrays->arrayByStr[0]) == 0)
        {
            bigFlag = 1;
        }
        else
        {
            if (i == 0)
            {
                temparrays->uniqueIntArray[i] = temparrays->arrayByNum[i];
                strcpy(temparrays->uniqueCharArray[i], temparrays->arrayByStr[i]);
            }
            flag = 0;
            while (flag == 0 && j < max)
            {
                counter = 0;
                if (temparrays->uniqueIntArray[i] == temparrays->arrayByNum[j] && (strcmp(temparrays->uniqueCharArray[i], temparrays->arrayByStr[j])) == 0)
                {
                }
                else
                {
                    for (k = 0; k < (i + 1); k++)
                    {
                        if (temparrays->uniqueIntArray[k] == temparrays->arrayByNum[j] && (strcmp(temparrays->uniqueCharArray[k], temparrays->arrayByStr[j])) == 0)
                        {
                            counter--;
                        }
                    }
                    if (counter == 0)
                    {
                        temparrays->uniqueIntArray[i + 1] = temparrays->arrayByNum[j];
                        strcpy(temparrays->uniqueCharArray[i + 1], temparrays->arrayByStr[j]);
                        flag = 1;
                    }

                }
                j++;
            }

        }

        i++;
    }
    k = 0;
    while (temparrays->uniqueIntArray[k] != 0 || strlen(temparrays->uniqueCharArray[k]) != 0)
    {
        for (j = 0; j < max; j++)
        {
            if (temparrays->uniqueIntArray[k] == temparrays->arrayByNum[j] && strcmp(temparrays->uniqueCharArray[k], temparrays->arrayByStr[j]) == 0)
            {
                if (data[j].unit == 'c')
                {
                    temparrays->precipAdd[k] = temparrays->precipAdd[k] + data[j].precipAmt * 10;
                }
                else
                {
                    temparrays->precipAdd[k] = temparrays->precipAdd[k] + data[j].precipAmt;
                }
            }
        }
        k++;
    }
}