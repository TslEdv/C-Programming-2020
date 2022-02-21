#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "math.h"
#include "ctype.h"
#include "stdarg.h"
#include "memory.h"
#pragma warning ( disable : 4996 )
#include "string.h"
typedef struct
{
	int day;
	char month[4];
	int year;
} DATE;
typedef struct
{
	const char* pFirstName, * pLastName, * pNationality;
	DATE Birthdate;
} STUDENT;
int Exam(STUDENT* pStudents, int nStudents, const char* pPattern);
int main()
{
	STUDENT students[] = { {"John","Smith","Britain",{1,"Feb",2000}},
					{"Mary","Weaver","USA",{2,"Mar",2001}},
					{"James","Carpenter","Canada",{11,"Oct",2002}},
					{"Elizabeth","Clerk","Ireland",{21,"Dec",2001}} };
	const char* ptoSearch = ("Carpenter, James born 11 October 2002 from Canada");
	printf("%d\n", Exam(students, 4, ptoSearch));
	return 0;
}
int Exam(STUDENT* pStudents, int nStudents, const char* pPattern)
{
	if (!pStudents || !nStudents || !nStudents || !pPattern || !*pPattern)
	{
		return 0;
	}
	int counter = 0;
	char* pattern = (char*)malloc(sizeof(char) * (strlen(pPattern) + 1));
	strcpy(pattern, pPattern);
	char* comma1 = strchr(pattern, ',');
	if (comma1)
	{
		*comma1 = 0;
	}
	for (int i = 0; i < nStudents; i++, pStudents++)
	{
		if (strcmp(pattern, pStudents->pLastName) == 0)
		{
			printf("Lastname found - %s\n", pStudents->pLastName);
			counter++;
			break;
		}
	}
	char* space = strchr(comma1 + 2, ' ');
	if (space)
	{
		*space = 0;
	}
	for (int i = 0; i < nStudents; i++)
	{
		if (strcmp(pStudents->pFirstName, comma1 + 2) == 0)
		{
			printf("Firstname found - %s\n", pStudents->pFirstName);
			counter++;
			break;
		}
	}
	char* space2 = strchr(space + 6, ' ');
	if (space2)
	{
		*space2 = 0;
	}
	for (int i = 0; i < nStudents; i++)
	{
		if (pStudents->Birthdate.day == atoi(space + 6))
		{
			printf("Day found - %d\n", pStudents->Birthdate.day);
			counter++;
			break;
		}
	}
	space = space2 + 4;
	if (space)
	{
		*space = 0;
	}
	for (int i = 0; i < nStudents; i++)
	{
		if (strcmp(pStudents->Birthdate.month, space2 + 1) == 0)
		{
			printf("Month found - %s\n", pStudents->Birthdate.month);
			counter++;
			break;
		}
	}
	space2 = strchr(space+1, ' ');
	if (space2)
	{
		*space2 = 0;
	}
	space = strchr(space2 + 1, ' ');
	if (space)
	{
		*space = 0;
	}
	for (int i = 0; i < nStudents; i++)
	{
		if (pStudents->Birthdate.year == atoi(space2 + 1))
		{
			printf("Year found - %d\n", pStudents->Birthdate.year);
			counter++;
			break;
		}
	}
	space2 = strchr(space + 1, ' ');
	if (space2)
	{
		*space2 = 0;
	}
	for (int i = 0; i < nStudents; i++)
	{
		if (strcmp(pStudents->pNationality, space2 + 1) == 0)
		{
			printf("Country found - %s\n", pStudents->pNationality);
			counter++;
			break;
		}
	}
	if (counter == 6)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}