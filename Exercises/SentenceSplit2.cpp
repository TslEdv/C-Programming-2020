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
Exercise: write a function that splits a sentence into a table of words. For example, from
input sentence "John is a very good boy" we should get a table like:
The prototype of the function must be:
char **SentenceSplit(char *, int *);
where the first parameter is the pointer to input sentence
(string) and the second parameter is the pointer to second
output value presenting the number of words. The function
must return the pointer to the table.
Write also the main function for testing and printing the
results. Use function CreateRandomSentence (see the next
slide) to generate test data. Usage example:
char *p = CreateRandomSentence(5, 3, 4, 6, 1, 2);
we get a sentence of 5 words; 3, 4, 6, 1, 2 are the lengths of
words.
Tips:
• The sentence may include any number of words. The words are separated by one (and
only one) space. The sentence does not contain punctuation marks like comma or point.
The only allowed characters are space and the uppercase and lowercase English letters.
• If the first character of input sentence is the terminating zero, the sentence is empty and
the return values are zeroes.
• The function must check the correctness of input parameters (no null pointers)!

char *CreateRandomSentence(int nWords, int n1, ...)
{ // this code is out of scope of this course.
// #include "stdarg.h" is needed
// nWords is the number of words, it is followed by sequence specifying the word lengths
// nWords may be any positive number
va_list indic;
va_start(indic, nWords);
int nChars = 0, j = 0;
for (int i = 0; i < nWords; i++, nChars += va_arg(indic, int) + 1);
const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
char *pResult = (char *)malloc(nChars);
va_start(indic, nWords);
for (int i = 0; i < nWords; i++)
{
int nWord = va_arg(indic, int);
for (int k = 0; k < nWord; k++, *(pResult + j++) = alphabet[rand() % 26]);
*(pResult + j++) = ' ';
}
*(pResult + nChars - 1) = 0;
return pResult;
}
*/

char* CreateRandomSentence(int nWords, int n1, ...)
{
	va_list indic;
	va_start(indic, nWords);
	int nChars = 0, j = 0;
	for (int i = 0; i < nWords; i++, nChars += va_arg(indic, int) + 1);
	const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	if (!nWords)
		nChars = 1;
	char* pResult = (char*)malloc(nChars);
	va_start(indic, nWords);
	for (int i = 0; i < nWords; i++)
	{
		int nWord = va_arg(indic, int);
		for (int k = 0; k < nWord; k++, *(pResult + j++) = alphabet[rand() % 26]);
		*(pResult + j++) = ' ';
	}
	*(pResult + nChars - 1) = 0;
	return pResult;
}
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
int main()
{
	char* pSentence = 0;
	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 0:
			pSentence = CreateRandomSentence(1, 10);
			break;
		case 1:
			pSentence = CreateRandomSentence(6, 4, 2, 1, 4, 4, 3);
			break;
		case 2:
			pSentence = CreateRandomSentence(3, 1, 10, 1);
			break;
		case 3:
			pSentence = CreateRandomSentence(3, 4, 4, 4);
			break;
		case 4:
			pSentence = CreateRandomSentence(0, 0);
			break;
		case 5:
			pSentence = 0;
			break;
		}
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
	}
	return 0;
}