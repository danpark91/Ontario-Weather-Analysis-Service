#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

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
	printf("< Press [ENTER] key to continue >");
	clearInputBuffer();
	putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////


// 3. inputInt function

int inputInt(void)
{
	int testNum;
	char afterNum;
	scanf("%d%c", &testNum, &afterNum);
	while (afterNum != '\n')
	{
		printf("Error! Input a whole number: ");
		clearInputBuffer();
		scanf("%d%c", &testNum, &afterNum);
	}
	return (testNum);
}


// 4. inputIntPositive

int inputIntPositive(void)
{
	int intPositive = 0;
	while (intPositive < 1)
	{
		intPositive = inputInt();
		if (intPositive < 1)
		{
			printf("ERROR! Value must be > 0: ");
		}
	}
	return(intPositive);
}

// 5. inputIntRange

int inputIntRange(int minCap, int maxCap)
{
	int testNum;
	testNum = inputInt();
	while (testNum<minCap || testNum>maxCap)
	{
		printf("ERROR! Value must be between %d and %d inclusive: ", minCap, maxCap);
		testNum = inputInt();
	}
	return(testNum);
}

// 6. inputCharOption

char inputCharOption(const char charArray[])
{
	int i, flag = 0;
	char singleChar, extraChar;
	scanf("%c%c", &singleChar, &extraChar);
	while (extraChar != '\n' || flag == 0)
	{
		if (extraChar == '\n')
		{
			for (i = 0; charArray[i] != '\0'; i++)
			{
				if (singleChar == charArray[i])
				{
					flag = 1;
				}
			}
			if (flag == 0)
			{
				printf("ERROR: Character must be one of [");
				for (i = 0; charArray[i] != '\0'; i++)
				{
					printf("%c", charArray[i]);
				}
				printf("]: ");
				scanf("%c%c", &singleChar, &extraChar);
			}
		}
		else
		{
			printf("ERROR: Character must be one of [");
			for (i = 0; charArray[i] != '\0'; i++)
			{
				printf("%c", charArray[i]);
			}
			printf("]: ");
			clearInputBuffer();
			scanf("%c%c", &singleChar, &extraChar);
		}
	}
	return (singleChar);
}

// 7. inputCString

void inputCString(char outString[], int minLen, int maxLen)
{
	char testString[31] = { '\0' };
	int flag = 0;
	scanf("%[^\n]s", testString);
	while (flag == 0)
	{
		if (minLen == maxLen)
		{
			if (strlen(testString) != minLen)
			{
				printf("Invalid 10-digit number! Number: ");
				clearInputBuffer();
				scanf("%[^\n]s", testString);
			}
			else
			{
				flag = 1;
			}
		}
		else if (strlen(testString) > maxLen)
		{
			printf("ERROR: String length must be no more than %d chars: ", maxLen);
			clearInputBuffer();
			scanf("%[^\n]s", testString);
		}
		else if (strlen(testString) < minLen)
		{
			printf("ERROR: String length must be between %d and %d chars: ", minLen, maxLen);
			clearInputBuffer();
			scanf("%[^\n]s", testString);
		}
		else
		{
			flag = 1;
		}
	}
	*outString = '\n';
	strcpy(outString, testString);
	/*for (i = 0; testString[i] != '\0'; i++)
	{
		outString[i] = testString[i];
	}*/
	clearInputBuffer();
}




//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// 8. displayFormattedPhone

void displayFormattedPhone(const char telephone[])
{
	int i = 0, j;
	j = 0;
	if (telephone == NULL)
	{
		printf("(___)___-____");
	}
	else
	{
		for (i = 0; i < strlen(telephone); i++)
		{
			switch (telephone[i])
			{
			case '0':
				j++;
				break;
			case '1':
				j++;
				break;
			case '2':
				j++;
				break;
			case '3':
				j++;
				break;
			case '4':
				j++;
				break;
			case '5':
				j++;
				break;
			case '6':
				j++;
				break;
			case '7':
				j++;
				break;
			case '8':
				j++;
				break;
			case '9':
				j++;
				break;
			}
		}
		if (j == 10 && i == 10)
		{
			printf("(");
			for (i = 0; i < 3; i++)
			{
				printf("%c", telephone[i]);
			}
			printf(")");
			for (i = 3; i < 6; i++)
			{
				printf("%c", telephone[i]);
			}
			printf("-");
			for (i = 6; i < j; i++)
			{
				printf("%c", telephone[i]);
			}
		}
		else
		{
			printf("(___)___-____");
		}
	}
}