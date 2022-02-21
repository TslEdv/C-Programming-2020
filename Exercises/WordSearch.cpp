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
Write a function that counts occurences of a given word in a given string. Write also main to
test the function. Do not use the functions developed in the previous exercises.
Requirements:
• The prototype must be
int WordSearch (char *, const char *);
• The first argument points to the text to analyze, the second to the word to find.
• Use standard function strstr.
• Words in the input text are separated by one space.
• The function must not crash if one or the both of the input pointers are null or point to an
empty string. In those cases the output value must be 0.
Tips: do not forget to test the special cases when:
• The word is the first one.
• The word is the last one.
• There are words a part of which matches the given word. For example if we search and
then in sentence and the band started to play the return value is 1.
*/

int WordSearch(char* text, const char* word)
{
	if (!text || !*text)
		return -1;
	if (!word|| !*word)
		return -1;
	int counter = 0;
	char* pCopy = (char*)malloc(strlen(text) + 1);
	strcpy(pCopy, text);
	while (1)
	{
		char* p = strstr(pCopy, word);
		if (p)
		{
			if ((*(p - 1) == ' ') || (*(p - 1) == 0) || (*(p) == text[0]))
			{
				if (*(p) == word[0])
				{
					*p = 0;
					strcpy(pCopy, p + 2);
					counter++;
				}
				else if (*(p + 1) == ' ')
				{
					*(p + 1) == 0;
					*p = 0;
					strcpy(pCopy, p + 2);
					counter++;
				}
				else
				{
					*p = 0;
					strcpy(pCopy, p + 2);
					counter++;
				}
			}
			else
			{
				*p = 0;
				strcpy(pCopy, p + 2);
			}
		}
		else
		{
			break;
		}
	}
	return counter;
}
int main()
{
	char* pSentence = 0;
	char buffer[81];
	printf("Type the text:");
	pSentence = gets_s(buffer);
	char buffer2[81];
	printf("Type the name to be found:");
	char* pWord = gets_s(buffer2);
	int counter = WordSearch(pSentence, pWord);
	printf("%s\n", pSentence);
	printf("%s\n", pWord);
	printf("The word reoccured %d number of times", counter);
	return 0;
}