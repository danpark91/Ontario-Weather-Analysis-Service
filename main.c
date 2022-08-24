#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "weather.h"

int main(void)
{
    struct Date date = { {0} };
    struct Location location = { {0} };
    struct WeatherRecord data[MAXRECORDS] = { '\n', '\n', date, location, MAXRECORDS };

    FILE* fp = NULL;
    fp = fopen("weatherdata.txt", "r");

    int recs = importWeatherDataFile(fp, data, MAXRECORDS);

    menuMain(&data);

    return 0;
}