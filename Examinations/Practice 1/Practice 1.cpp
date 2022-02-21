#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "memory.h"
#include "ctype.h"
#pragma warning (disable : 4996)
typedef struct student
{
	char* pName;
	int nMarks, * pMarks; //number of marks and pointer to array of marks
	double AverageMark;
} STUDENT;
STUDENT* Exam(char* pInput, char* pStudentName);
int main()
{
	char input[] = "John Smith, 4, 2, 5, 3; James Farmhand, 4;";
	char searchedname[] = "James Farmhand";
	STUDENT* searched = Exam(input, searchedname);
	printf("Name - %s marks-%d average mark - %lg", searched->pName, searched->nMarks, searched->AverageMark);
	free(searched->pName);
	free(searched->pMarks);
	free(searched);
	return 0;
}
STUDENT* Exam(char* pInput, char* pStudentName)
{
	int lenght = strlen(pStudentName) + 2;
	char* pName = strstr(pInput, pStudentName);
	int counter = 0;
	if (pName)
	{
		STUDENT* wanted = (STUDENT*)malloc(1 * sizeof(STUDENT));
		wanted->pName = (char*)malloc(strlen(pStudentName) + 1);
		strcpy(wanted->pName, pStudentName);
		char* p = strchr(pName + lenght, ';');
		if (p)
		{
			*p = 0;
			for (int i = 0; ; i++)
			{
				if (*(pName + lenght + i) == 0)
				{
					break;
				}
				if (isdigit(*(pName + lenght + i)))
				{
					counter++;
				}
			}
			wanted->nMarks = counter;
			wanted->pMarks = (int*)malloc((counter + 1)*sizeof(int));
			int j = 0;
			for (int i = 0; ; i++)
			{
				if (*(pName + lenght + i) == 0)
				{
					break;
				}
				if (isdigit(*(pName + lenght + i)))
				{
					char a = *(pName + lenght + i);
					int b = atoi(&a);
					memcpy(wanted->pMarks, &b, sizeof(int));
					wanted->pMarks++;
				}
			}
			wanted->pMarks -= wanted->nMarks;
			for (int i = 0; i < counter; i++)
			{
				printf("%d\n", *wanted->pMarks);
				wanted->pMarks++;
			}
			wanted->pMarks -= wanted->nMarks;
			wanted->AverageMark = 0;
			for (int i = 0;i<counter ; i++, wanted->pMarks++)
			{
				wanted->AverageMark += *wanted->pMarks;
			}
			wanted->pMarks -= wanted->nMarks;
			wanted->AverageMark = wanted->AverageMark / counter;
		
			return wanted;
		}
	}
	else
	{
		printf("no name was found");
		return 0;
	}
}