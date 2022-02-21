#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "math.h"
#include "ctype.h"
#include "stdarg.h"
#include "memory.h"
#pragma warning ( disable : 4996 )
#include "string.h"
typedef struct item
{
	char* pName;
	int quantity, write_off; //write_off: 0, if not expired yet, 1 if expired
} ITEM;
ITEM* Exam(char* pInput, char* pItemName);
ITEM *Exam(char* pInput, char* pItemName)
{
	if (!pInput || !*pInput || !pItemName || !*pItemName)
	{
		return 0;
	}
	int braccounter = 0;
	for (int i = 0; ; i++)
	{
		if (*(pInput + i) == '\0')
		{
			break;
		}
		if (*(pInput + i) == ']')
		{
			braccounter++;
		}
	}
	ITEM* item = (ITEM*)malloc(sizeof(ITEM));
	char* bracketfinder1 = strchr(pInput, '[');
	*bracketfinder1 = 0;
	char* bracketfinder2 = strchr(bracketfinder1 + 1, ']');
	*bracketfinder2 = 0;
	for (int i = 0; i<braccounter; i++)
	{
		char* namefinder = strstr(bracketfinder1 + 1, pItemName);
		if (namefinder)
		{
			item->pName = (char*)malloc(sizeof(char) * (strlen(pItemName) + 1));
			strcpy(item->pName, pItemName);
			char* quantityfinder = strstr(bracketfinder1 + 1, "Quantity");
			char* spacefinder = strchr(quantityfinder + 10, ' ');
			if (spacefinder)
			{
				*spacefinder = 0;
				char* quantity = (char*)malloc(sizeof(char) * (strlen(quantityfinder + 10) + 1));
				for (int i = 0; ; i++)
				{
					if (*(quantityfinder + 10 + i) == 0)
					{
						break;
					}
					else
					{
						*(quantity + i) = *(quantityfinder + 10 + i);
					}
				}
				int realquan = atoi(quantity);
				item->quantity = realquan;
				if (spacefinder)
				{
					*spacefinder = ' ';
				}
				char* expiryfinder = strstr(bracketfinder1 + 1, "Expires");
				char* spacefinder = strchr(expiryfinder + 9, ' ');
				if (spacefinder)
				{
					*spacefinder = 0;
					char* expiry = (char*)malloc(sizeof(char) * (strlen(expiryfinder + 9) + 1));
					int expmonth = 0;
					int expyear = 0;
					for (int i = 0, j= 0; ; i++, j++)
					{
						if (*(expiryfinder + 9 + i) == 0)
						{
							*(expiry + j) = '\0';
							break;
						}
						if (*(expiryfinder + 9 + i) == '–')
						{
							expmonth = atoi(expiry);
							j = 0;
						}
						else
						{
							*(expiry + j) = *(expiryfinder + 9 + i);
						}
					}
					expyear = atoi(expiry+1);
					if (expyear >= 2019)
					{
						if (expyear > 2019)
						{
							item->write_off = 1;
						}
						if (expyear = 2019)
						{
							if (expmonth > 1)
							{
								item->write_off = 1;
							}
						}
					}
					else
					{
						item->write_off = 0;
					}
					return item;
				}
			}
		}
		else
		{
			bracketfinder1 = strchr(bracketfinder2 + 1, '[');
			*bracketfinder1 = 0;
			bracketfinder2 = strchr(bracketfinder1 + 1, ']');
			*bracketfinder2 = 0;
		}
	}
}
int main()
{
	char list[] = "[ Name: Mackerel Quantity: 1000 Expires: 10–2018 ] [ Quantity: 500 Name: Sardine Expires: 12–2017 ] [ Expires: 1–2020 Quantity: 10000 Name: Tuna ]";
	char item[] = "Sardine";
	ITEM* searched = Exam(list, item);
	printf("Name: %s Quantity: %d Expired: %d", searched->pName, searched->quantity, searched->write_off);
	free(searched->pName);
	free(searched);
	return 0;
}