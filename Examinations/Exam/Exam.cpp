#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"
#include "time.h"
#pragma warning ( disable : 4996 )
time_t now;
struct tm timeinfo;
typedef struct date
{
	int day;
	char month[4];
	int year;
}DATE;
typedef struct student
{
	char* pName, * pCode; 
	DATE Date;
	int Mark;
}STUDENT;
STUDENT** Exam(char* pNames, char* pResults, int* pnStudents);
char NamesCodes[]= "John Smith 25156IVSB; Mary Weaver 253742ABB; James Carpenter 252422TAF; Elizabeth Clerk 251443MV";
char Results[]= "Elizabeth Clerk 4; Mary Weaver 5; John Smith 1; James Carpenter 3";
int main()
{
	int numberofstudents;
	STUDENT** students = Exam(NamesCodes, Results, &numberofstudents);
	for (int i = 0; i < numberofstudents; i++)
	{
		printf("Name: %s | Code: %s | Date: %d %s %d | Grade: %d\n", students[i]->pName, students[i]->pCode, students[i]->Date.day, students[i]->Date.month, students[i]->Date.year, students[i]->Mark);
	}
	for (int i = 0; i < numberofstudents; i++)//free the structs
	{
		free(students[i]->pName);
		free(students[i]->pCode);
		free(students[i]);
	}
	free(students);
	return 0;
}
STUDENT** Exam(char* pNames, char* pResults, int* pnStudents)
{
	if (!pNames || !*pNames || !pResults || !*pnStudents||!pnStudents)
	{ // check if anything is zero or empty
		return 0;
	}
	int counter = 0;
	for (int i = 0; ; i++)//count students
	{
		if (pNames[i] == '\0')
		{
			counter++;//accounts for the last student name
			break;
		}
		if (pNames[i] == ';')
		{
			counter++;
		}
	}
	*pnStudents = counter;
	STUDENT** students = (STUDENT**)malloc(counter * sizeof(STUDENT*));//allocate memory for the array of pointers to structs
	for (int i = 0; i < counter; i++)
	{
		students[i] = (STUDENT*)malloc(sizeof(STUDENT));//allocate memory for each struct
	}
	char* start = pNames;
	char* spacefinder1 = strchr(pNames, ' ');
	char* spacefinder2 = strchr(spacefinder1 + 1, ' ');
	char* semicolon = strchr(spacefinder2 + 1, ';');
	for (int i = 0; i < counter; i++)// get names and codes from the list
	{
		if (spacefinder2)
		{
			*spacefinder2 = 0;
			students[i]->pName = (char*)malloc(sizeof(char) * (strlen(start) + 1));//allocate memory
			strcpy(students[i]->pName, start);//name retrieved
			semicolon = strchr(spacefinder2 + 1, ';');
			if (semicolon)
			{
				*semicolon = 0;
				students[i]->pCode = (char*)malloc(sizeof(char) * (strlen(spacefinder2 + 1) + 1));//allocate memory
				strcpy(students[i]->pCode, spacefinder2 + 1);//code retrieved
				start = semicolon + 2;
				spacefinder1 = strchr(semicolon + 3, ' ');
				spacefinder2 = strchr(spacefinder1 + 1, ' ');
			}
			else//do this if its the last name in the list
			{
				students[i]->pCode = (char*)malloc(sizeof(char) * (strlen(spacefinder2 + 1) + 1));//allocate memory
				strcpy(students[i]->pCode, spacefinder2 + 1);//code retrieved
				break;
			}
		}
	}
	for (int i = 0; i < counter; i++)//get grades
	{
		char* mark = strstr(pResults, students[i]->pName);
		if (mark)
		{
			for (int j = 0; ; j++)
			{
				if (isdigit(*(mark + j)))
				{
					mark = mark + j;
					students[i]->Mark = atoi(mark);
					break;
				}
			}
		}
	}
	time(&now);
	localtime_s(&timeinfo, &now);
	for (int i = 0; i < counter; i++)//find the time
	{
		students[i]->Date.day = timeinfo.tm_mday;//day
		for (int j = 0; j < 12; j++)//fill in the month array
		{
			char months[][4] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
			if (timeinfo.tm_mon + 1 == j+1)
			{
				for (int o = 0; o < 3; o++)
				{
					students[i]->Date.month[o] = months[j][o];
				}
				students[i]->Date.month[3] = '\0';
			}
		}
		students[i]->Date.year = timeinfo.tm_year + 1900;//year
	}
	return students;
}