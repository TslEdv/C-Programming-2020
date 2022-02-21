#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "math.h"
#include "ctype.h"
#include "stdarg.h"
#include "memory.h"
#pragma warning ( disable : 4996 )
#include "string.h"
typedef struct employee
{
	char* pFirstName, * pMiddleName, * pLastName;
	int Brutto, TaxCoefficient, Netto;
} EMPLOYEE;
EMPLOYEE* Exam(char* pInput);
int main()
{
	char input[] = "John Smith 15000;";
	EMPLOYEE* emp = Exam(input);
	if (emp->pMiddleName == 0)
	{
		printf("Name: %s | LastName: %s | Brutto: %d | TaxCoefficient: %d percent | Netto: %d", emp->pFirstName, emp->pLastName, emp->Brutto, emp->TaxCoefficient, emp->Netto);
	}
	else
	{
		printf("Name: %s | MiddleName: %s | LastName: %s | Brutto: %d | TaxCoefficient: %d percent | Netto: %d", emp->pFirstName, emp->pMiddleName, emp->pLastName, emp->Brutto, emp->TaxCoefficient, emp->Netto);
	}
	free(emp->pFirstName);
	free(emp->pMiddleName);
	free(emp->pLastName);
	free(emp);
	return 0;
}
EMPLOYEE* Exam(char* pInput)
{
	EMPLOYEE* emp = (EMPLOYEE*)malloc(sizeof(EMPLOYEE));
	int spacecounter = 0;
	for (int i = 0; ; i++)
	{
		if (pInput[i] == '\0')
		{
			break;
		}
		if (pInput[i] == ' ')
		{
			spacecounter++;
		}
	}
	char* spacefinder1 = strchr(pInput, ' ');
	if (spacefinder1)
	{
		*spacefinder1 = 0;
		emp->pFirstName = (char*)malloc(sizeof(char) * (strlen(pInput)) + 1);
		strcpy(emp->pFirstName, pInput);
	}
	if (spacecounter == 3)
	{
		char* spacefinder2 = strchr(spacefinder1+1, ' ');
		if (spacefinder2)
		{
			*spacefinder2 = 0;
			emp->pMiddleName = (char*)malloc(sizeof(char) * (strlen(spacefinder1+1)) + 1);
			strcpy(emp->pMiddleName, spacefinder1 + 1);
		}
		char* finalspace = strchr(spacefinder2 + 1, ' ');
		if (finalspace)
		{
			*finalspace = 0;
			emp->pLastName = (char*)malloc(sizeof(char) * (strlen(spacefinder2 + 1)) + 1);
			strcpy(emp->pLastName, spacefinder2 + 1);
		}
		char* semicolon = strchr(finalspace + 1, ';');
		if (semicolon)
		{
			*semicolon = 0;
			char* value = (char*)malloc(sizeof(char)* (strlen(finalspace + 1)) + 1);
			strcpy(value, finalspace + 1);
			emp->Brutto = atoi(value);
		}

	}
	if (spacecounter == 2)
	{
		emp->pMiddleName = 0;
		char* finalspace = strchr(spacefinder1 + 1, ' ');
		if (finalspace)
		{
			*finalspace = 0;
			emp->pLastName = (char*)malloc(sizeof(char) * (strlen(spacefinder1 + 1)) + 1);
			strcpy(emp->pLastName, spacefinder1 + 1);
		}
		char* semicolon = strchr(finalspace + 1, ';');
		if (semicolon)
		{
			*semicolon = 0;
			char* value = (char*)malloc(sizeof(char) * (strlen(finalspace + 1)) + 1);
			strcpy(value, finalspace + 1);
			emp->Brutto = atoi(value);
		}
	}
	if (emp->Brutto > 10000)
	{
		emp->TaxCoefficient = 25;
		emp->Netto = emp->Brutto * 0.75;
	}
	if ((emp->Brutto > 7500) && (emp->Brutto <= 10000))
	{
		emp->TaxCoefficient = 20;
		emp->Netto = emp->Brutto * 0.8;
	}
	if ((emp->Brutto > 5000) && (emp->Brutto <= 7500))
	{
		emp->TaxCoefficient = 15;
		emp->Netto = emp->Brutto * 0.85;
	}
	if (emp->Brutto <= 5000)
	{
		emp->TaxCoefficient = 0;
		emp->Netto = emp->Brutto;
	}
	return emp;
}