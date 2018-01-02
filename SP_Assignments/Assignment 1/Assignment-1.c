/*
Name: Harshit Srivastava
Class: TEIT
Assignment: Design Pass-1 and Pass-2 Assembler.
*/

#include<stdio.h>
#include<string.h>

int search(char key[10], char str[11][10])
{
	int i=0;
	printf("\nIN SEARCH FUNCTION\n");
	for(i=0; str[i][10]!='\0'; i++)
	{
		if(strcmp(key, str[i])==0)
		{
			return i;	
		}
	}
	return -1;
}

void main()
{
	int check, index=0;
	int n, i=0;
	char buffer[200], val1[20], val2[20], val3[20], val4[20], is_tab[11][10]={"STOP", "ADD", "SUB", "MULT", "MOVER", "MOVEM", "COMP", "BC", "DIV", "READ", "PRINT"}, ad_tab[5][10]={"START", "END", "ORIGIN", "EQU", "LTORG"}, ds_tab[2][10]={"DC", "DS"};
/*
	Here,
	is_tab is Imperative Statements table 
	ad_tab is Assembler Directives table
	ds_tab is Declarative Statement table
*/
	FILE *fptr;
	fptr=fopen("input_file.txt", "r");
	if(fptr!=NULL)
	{
		while(fgets(buffer, 200, fptr))
		{
			n=sscanf(buffer, "%s%s%s%s", val1, val2, val3, val4);	//Here, n is n
//			printf("\nNumber of strings present in line %d is %d.\n", i++, n);
			if(n==1)
			{
				printf("\nValue 1 --> %s\n", val1);
				check=search(val1, is_tab);
				if(check>=0)
					index=check;
				else
				{
					check=search(val1, ad_tab);
					if(check!=-1)
					{
						printf("\nPresent\n");
						index=check+1;
					}	
				}
			}	
			if(n==2)
			{
				printf("\nValue 1 --> %s\nValue 2 --> %s\n", val1, val2);
				check=search(val1, is_tab);
				if(check>=0)
					index=check;
				else
				{
					check=search(val2, ad_tab);
					if(check!=-1)
					{
						printf("\nPresent\n");
						index=check+1;
					}	
				}
			}
/*			if(n==3)
			if(n==4)
*/		}
	}
}
