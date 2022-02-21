Let us have

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

Write a function with prototype:
STUDENT** Exam(char* pNames, char* pResults, int* pnStudents);

where pnStudent points to the number of students (output value of our function, see slide Pointers(21) and pNameCodes
and pResults poiunt to strings like:
char NamesCodes[]= "John Smith 25156IVSB; Mary Weaver 253742ABB; James Carpenter 252422TAF; Elizabeth Clerk 251443MV";
char Results[]= "Elizabeth Clerk 4; Mary Weaver 5; John Smith 1; James Carpenter 3";

The components of strings are separated byt semicolon followed by one space. The names are everywhere the same but their
orders may be different. Turn attention that there is no semicolon after the last component.

The output vlaue is an array of pointers to structs (see slide Structs(19). The order of students in results may be any.

The value attributes in DATE must be read from the system clock.

The input values may not be zero or point to an empty array string. If those conditions are not satisfied, the function
must return zero. However, if those conditions are satisfied, we may be sure that the input data is 100% correct.

Write also main to test the code and print the results.