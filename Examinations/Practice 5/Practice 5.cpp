#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "memory.h"
#include "ctype.h"
#pragma warning (disable : 4996)
typedef struct student {
	char* pName, * pCode;
	int mMathmatics, mPhysics, mChemistry;
	double Average;
}STUDENT;
STUDENT* Exam(char* pStudents, char* pMathmatics, char* pPhysics, char* pChemistry);
char Students[] = "John Smith 25156IVSB; Mary Weaver 253742ABB; James Carpenter 252422TAF; Elizabeth Clerk 251443MV"; //name and code
char Mathmatics[] = "John Smith 5; Mary Weaver 4; James Carpenter 4; Elizabeth Clerk 2"; //name and mark, order different
char Physics[] = "Mary Weaver 3; John Smith 5; Elizabeth Clerk 2; James Carpenter 2";
char Chemistry[] = "Elizabeth Clerk 4; Mary Weaver 5; John Smith 1; James Carpenter 3";
int main()
{
	STUDENT* best = Exam(Students, Mathmatics, Physics, Chemistry);
	printf("Name: %s | Code: %s | Avg Grade: %lg", best->pName, best->pCode, best->Average);
	free(best->pName);
	free(best->pCode);
	free(best);
	return 0;
}
STUDENT* Exam(char* pStudents, char* pMathmatics, char* pPhysics, char* pChemistry)
{
	if (!pStudents || !*pStudents || !pMathmatics || !*pMathmatics || !pPhysics || !*pPhysics || !pChemistry || !*pChemistry)
	{ // check if anything is zero or empty
		return 0;
	}
	int counter = 0;
	for (int i = 0; ; i++)//count students
	{
		if (pStudents[i] == '\0')
		{
			counter++;
			break;
		}
		if (pStudents[i] == ';')
		{
			counter++;
		}
	}
	STUDENT* students = (STUDENT*)malloc(sizeof(STUDENT) * counter);//give memory to students
	char* start = pStudents;
	char* spacefinder1 = strchr(pStudents, ' ');
	char* spacefinder2 = strchr(spacefinder1 + 1, ' ');
	char* semicolon = strchr(spacefinder2 + 1, ';');
	for (int i = 0; i < counter; i++, students++)
	{
		if (spacefinder2)
		{
			*spacefinder2 = 0;
			students->pName = (char*)malloc(sizeof(char) * (strlen(start) + 1));
			strcpy(students->pName, start);//name retrieved
			printf("%s - ", students->pName);
			semicolon = strchr(spacefinder2 + 1, ';');
			if (semicolon)
			{
				*semicolon = 0;
				students->pCode = (char*)malloc(sizeof(char) * (strlen(spacefinder2 + 1) + 1));
				strcpy(students->pCode, spacefinder2 + 1);//code retrieved
				printf("%s\n", students->pCode);
				start = semicolon + 2;
				spacefinder1 = strchr(semicolon + 3, ' ');
				spacefinder2 = strchr(spacefinder1 + 1, ' ');
			}
			else
			{
				students->pCode = (char*)malloc(sizeof(char) * (strlen(spacefinder2 + 1) + 1));
				strcpy(students->pCode, spacefinder2 + 1);//code retrieved
				printf("%s\n", students->pCode);
				break;
			}
		}
	}
	students -= (counter - 1);//roll it back
	for (int i = 0; i < counter; i++, students++)//get grades
	{
		char* mark = strstr(pMathmatics, students->pName);
		if (mark)
		{
			for (int j = 0; ; j++)
			{
				if (isdigit(*(mark + j)))
				{
					mark = mark + j;
					students->mMathmatics = atoi(mark);
					printf("%s - %d\n", students->pName, students->mMathmatics);
					break;
				}
			}
		}
	}
	students -= (counter);
	for (int i = 0; i < counter; i++, students++)
	{
		char* mark = strstr(pPhysics, students->pName);
		if (mark)
		{
			for (int j = 0; ; j++)
			{
				if (isdigit(*(mark + j)))
				{
					mark = mark + j;
					students->mPhysics = atoi(mark);
					printf("%s - %d\n", students->pName, students->mPhysics);
					break;
				}
			}
		}
	}
	students -= (counter);
	for (int i = 0; i < counter; i++, students++)
	{
		char* mark = strstr(pChemistry, students->pName);
		if (mark)
		{
			for (int j = 0; ; j++)
			{
				if (isdigit(*(mark + j)))
				{
					mark = mark + j;
					students->mChemistry = atoi(mark);
					printf("%s - %d\n", students->pName, students->mChemistry);
					break;
				}
			}
		}
	}
	students -= (counter);
	double max = 0;
	for (int i = 0; i < counter; i++, students++)
	{
		students->Average = ((double)(students->mChemistry) + (double)(students->mPhysics) + (double)(students->mMathmatics)) / (double)3;
		printf("%s - %lg\n", students->pName, students->Average);
		if (max <= students->Average)
		{
			max = students->Average;
		}
	}
	printf("%lg", max);
	students -= counter;
	STUDENT* bStudent = (STUDENT*)malloc(sizeof(STUDENT));

	for (int i = 0; i < counter; i++, students++)
	{
		if (max == students->Average)
		{
			bStudent->pName = (char*)malloc(strlen(students->pName) + 1);
			strcpy(bStudent->pName, students->pName);
			bStudent->pCode = (char*)malloc(strlen(students->pCode) + 1);
			strcpy(bStudent->pCode, students->pCode);
			bStudent->mChemistry = students->mChemistry;
			bStudent->mMathmatics = students->mMathmatics;
			bStudent->mPhysics = students->mPhysics;
			bStudent->Average = students->Average;
		}
	}
	students -= (counter);
	for (int i = 0; i < counter; i++, students++) { //frees memory for everything in struct
		free(students->pName);
		free(students->pCode);
	}
	students -= (counter);
	free(students);
	return bStudent;
}