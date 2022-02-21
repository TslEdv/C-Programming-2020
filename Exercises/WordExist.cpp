#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "math.h"
#include "ctype.h"
#include "stdarg.h"
#include "memory.h"
#pragma warning ( disable : 4996 )
#include "string.h"


/*
Exercise:
Using the results of function SentenceSplit from the previous exercise write a function that
checks whether the given word is present in the table or not. Write also main to test the
function and to print the results.
Requirements:
• The prototype must be
int WordExist (char **, int, const char *);
(the parameters are the pointer to table, the number of words in table and the pointer to
word to search).
• Use standard function strcmp.
• The output value is 1 (TRUE, exists) or 0 (FALSE, not found).
• The function must not crash if one or the both of the input pointers are null or the second
pointer points to an empty string. In those cases the output value must be -1.
*/

char** SentenceSplit(char* pInput, int* pnWords)
{
	if (!pInput || !*pInput)
		return 0;
	int n = strlen(pInput);
	char* pCopy = (char*)malloc(n + 1);
	strcpy(pCopy, pInput);
	int nSpace = 0;
	for (int i = 0; *(pInput + i); i++)
	{
		if (*(pInput + i) == ' ')
			nSpace++;
	}
	*pnWords = nSpace + 1;
	char** ppOutput = (char**)malloc(*pnWords * sizeof(char*));
	for (int i = 0; i < *pnWords; i++)
	{
		char* pSpace = strchr(pCopy, ' ');
		if (i == *pnWords - 1)
		{
			*(ppOutput + i) = (char*)malloc(strlen(pCopy) + 1);
			strcpy(*(ppOutput + i), pCopy);
			*(*(ppOutput + i) + strlen(pCopy) + 1) = 0;
			break;
		}
		if (pSpace)
		{
			*pSpace = 0;
			*(ppOutput + i) = (char*)malloc(strlen(pCopy) + 1);
			strcpy(*(ppOutput + i), pCopy);
			strcpy(pCopy, pSpace + 1);
		}
	}
	return ppOutput;
}
int WordExist(char** table, int nWords, const char* wordtosearch)
{
	int returnvalue = 0;
	if (!table || !**table || !*table)
		return -1;
	if (!wordtosearch || !*wordtosearch)
		return -1;
	int n = strlen(*table);
	nWords = n;
	for (int i = 0; i < nWords; i++)
	{
		int value = strcmp(*(table + i), wordtosearch);
		if (value == 0)
		{
			returnvalue = 1;
		}
	}
	return returnvalue;
}
int main()
{
	char* pSentence = 0;
	char buffer[81];
	printf("Type the words to put into table:");
	pSentence = gets_s(buffer);
	int nw;
	char** ppTable = SentenceSplit(pSentence, &nw);
	for (int i = 0; ppTable && i < nw; i++)
	{
		printf("%s\n", *(ppTable + i));
	}
	if (pSentence)
	{
		printf("%s\n\n", pSentence);
	}
	char buffer2[81];
	printf("Type the name to be found:");
	char* pName = gets_s(buffer2);
	int o = WordExist(ppTable, nw, pName);
	switch (o)
	{
	case -1:
		printf("ERROR IN INPUT!");
		return 0;
	case 0:
		printf("Name was found!");
		return 0;
	case 1:
		printf("Name was not found!");
		return 0;
	}
}