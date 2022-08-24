// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////


// 3. inputInt function 
    //this function prompts the user to input data until an integer is received, doesn't use arguments.

int inputInt(void);

// 4. inpputIntPositive
    //this function prompts the user to input data until a positive (>0) integer is received, doesn't use arguments.


int inputIntPositive(void);

// 5. inputIntRanged
    //this function prompts the user to input data until an integer that lies within the minCap and maxCap is received. Requires 2 ARGUMENTS.


int inputIntRange(int minCap, int maxCap);

// 6. inputCharOption
    //this function prompts the user to input a SINGLE CHARACTER. Requires an argument that is a CHAR ARRAY or STRING


char inputCharOption(const char charArray[]);

// 7. inputCString
    //this function prompts the user to input data until an string which length lies within the minCap and maxCap is received. Requires a string of a determined length
    // and min and max.


void inputCString(char outString[], int minLen, int maxLen);

// 8. displayFormattedPhone
    //This function DOESN'T prompt the user for info, it receives a STRING and only works if it is composed of 10 digits.

void displayFormattedPhone(const char telephone[]);



// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H