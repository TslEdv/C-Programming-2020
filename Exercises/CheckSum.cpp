#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "math.h"
#include "ctype.h"
#define NEGATIVEINTEGER 1
#define ZERO 2
#define TOOLARGE 3
#define POINTERZERO 4
#define EMPTYARRAY 5

/*
Exercise:
Write a function that checks the input integer array and computes the sum of its
members. Write also main to test the code. The prototype is
int CheckSum(int *, int, int *);
where the first parameter is the pointer to array, the second parameter is the number of
elements in array and the third (actually output) parameter is the pointer to integer for
storing the error code.
The array is incorrect, if some of its members are negative (error code 1), zero (error
code 2), greater that 1000 (error code 3). The array is also incorrect if the pointer to it
is zero (error code 4) or the array is empty (i.e. zero elements, error code 5). In that
case instead of sum the function must return 0. If the input array was correct, error
code is 0.
Mark the errors with #define preprocessor constants (see slide Informing about errors
(1) from chapter Deeper into C).
The main function must include the switch statement (see slides Multiple choice from
chapter Deeper into C) for analyzing the errors and print detailed messages.
To test use function CreateRandomArray (see the next slide). With it you can generate
arrays containing negative elements or too large elements (but not zero elements).


int *CreateRandomArray(int n, int lower, int upper)
{ // n is the length of array to be generated
// The random numbers will be in range lower….upper
// lower and upper may be negative
if (n <= 0 || lower >= upper)
{
return 0;
}
int *pResult = (int *)malloc(n * sizeof(int));
for (int i = 0; i < n; i++)
{
*(pResult + i) = lower + rand() % (upper - lower + 1);
}
return pResult;
}
*/

int errorcode;
int* CreateRandomArray(int n, int lower, int upper)
{ // n is the length of array to be generated
// The random numbers will be in range lower….upper
// lower and upper may be negative
	if (n <= 0 || lower >= upper)
	{
		return 0;
	}
	int* pResult = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		*(pResult + i) = lower + rand() % (upper - lower + 1);
	}
	return pResult;
}
int CheckSum(int* pArray, int numberofelements, int* errorcode)
{
	int sum = 0;
	if (numberofelements == 0)
	{
		*errorcode = EMPTYARRAY;
		return 0;
	}
	if (pArray == 0)
	{
		*errorcode = POINTERZERO;
		return 0;
	}
	for (int i = 0; i < numberofelements; i++)
	{
		if (*(pArray + i) == 0)
		{
			*errorcode = ZERO;
			return 0;
		}
		else if (*(pArray + i) < 0)
		{
			*errorcode = NEGATIVEINTEGER;
			return 0;
		}
		else if (*(pArray + i) > 1000)
		{
			*errorcode = TOOLARGE;
			return 0;
		}
		else
		{
			sum += *(pArray + i);
		}
	}
	return sum;
}
int main()
{
	int x, y, z;
	char Lenght[21], RangeLower[21], RangeUpper[21];
	printf("Welcome to SumCheck!\n");
	printf("Type how long you woud like the array to be:");
	gets_s(Lenght);
	x = atoi(Lenght);
	printf("Type the LOWEST number in the range to be:");
	gets_s(RangeLower);
	y = atoi(RangeLower);
	printf("Type the HIGHEST number in the range to be:");
	gets_s(RangeUpper);
	z = atoi(RangeUpper);
	int *pc;
	pc = CreateRandomArray(x, y, z);
	for (int i = 0; i < x; i++)
	{
		printf("The generated array is %d\n", *(pc + i));
	}
	int sum;
	sum = CheckSum(pc, x, &errorcode);
	switch (errorcode)
	{
	case 0: break;
	case NEGATIVEINTEGER: { printf("There cannot be negative integers in the array!");
		return 0; }
	case ZERO: { printf("There cannot be  0 in the array!");
		return 0; }
	case TOOLARGE: { printf("The member of an array cannot be larger than 1000!");
		return 0; }
	case POINTERZERO: { printf("The pointer to the array cannot be 0!");
		return 0; }
	case EMPTYARRAY: { printf("The array cannot be empty!");
		return 0; }
	}
	printf("the sum of integers is %d", sum);
	free(pc);
	return 0;
}