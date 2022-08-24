//////////////////////////////////////
// Module macro's (usable by any file that includes this header)
//////////////////////////////////////

#define MaxRegionLen 50
#define MAXRECORDS 250
#define PAGELENGHT 15
#define MAXUNIQUE 20
#define FMTASC 1
#define FMTDES 2

//////////////////////////////////////
// Structures
//////////////////////////////////////

// Data type: date

struct Date
{
    int year;
    int month;
};

// Data type: location 

struct Location
{
    int regionCode;
    char name[MaxRegionLen];
};

struct WeatherRecord
{
    char unit;
    double precipAmt;
    struct Date date;
    struct Location location;
    int MaxRecords;
};


struct TempArrays
{
    int arrayByNum[MAXRECORDS];
    char arrayByStr[MAXRECORDS][MaxRegionLen];
    double precipAdd[20];
    int uniqueIntArray[20];
    char uniqueCharArray[20][MaxRegionLen];
};

// Import weather data

int importWeatherDataFile(FILE* fp, struct WeatherRecord* data, int max);

//View All Data Function 
void viewAllData(struct WeatherRecord* data, int max);

//view by region
void viewByRegion(struct WeatherRecord* data, int max);

//view by month
void viewByMonth(struct WeatherRecord* data, int max);

//view by city

void viewByCity(struct WeatherRecord* data, int max);






//Utility functions

//create int array

void createIntArray(const struct WeatherRecord* data, int* userArray[], int max);

//sort array

void sortWeatherRecords(struct TempArrays* temparrays, int max, int FMT);

//create arrays with unique values and add the precipitation

void findUniqueAdd(struct WeatherRecord* data, struct TempArrays* tempArrays, int max);