/*
Name: Harshit Srivastava
Class: TEIT
Assignment: Design Pass-1 and Pass-2 Assembler.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int search_is(char key[10], char str[11][10])	//Search Imperative Statements Table
{
	int i=0;
	for(i=0; i<11; i++)
	{
		if(strcmp(key, str[i])==0)
			return i;	
	}
	return -1;
}

int search_ad(char key[10], char str[5][10])	//Search Assembler Directives Table
{
	int i=0;
	for(i=0; i<11; i++)
	{
		if(strcmp(key, str[i])==0)
			return i;	
	}
	return -1;
}

int search_ds(char key[10], char str[2][10])	//Search Declarative Statements Table
{
	int i=0;
	for(i=0; i<11; i++)
	{
		if(strcmp(key, str[i])==0)
			return i;	
	}
	return -1;
}

int search_rg(char key[10], char str[4][10])	//Search Register Table
{
	int i=0;
	for(i=0; i<4; i++)
	{
		if(strcmp(key, str[i])==0)
			return i;	
	}
	return -1;
}
	
int search_cond(char key[10], char str[4][10])	//Search Condition Table
{
	int i=0;
	for(i=0; i<4; i++)
	{
		if(strcmp(key, str[i])==0)
			return i;	
	}
	return -1;
}

struct newtable	//Basically this can act as a node for both symbol and literal table 
{
	int loc, ind;
	char str[20];
	struct newtable *next;
};
typedef struct newtable node;

node *h_smbtab=NULL, *h_littab=NULL, *newn, *tmpsmb, *tmplit, *tmpsrch;
int indsmb=0, indlit=0, sflag=0;

void create(char val[20], int lc, int key)
{
	if(key==0)
	{
		FILE *out1;
		out1=fopen("output_fileP1.txt", "a+");
		if(val[0]=='=')	//Move to Link List of Literal Table
		{
			if(h_littab==NULL)
			{
				indlit++;
				newn=(node *)malloc(sizeof(node));
				newn->loc=0;
				newn->ind=indlit;
				strcpy(newn->str, val);
				newn->next=NULL;
				h_littab=newn;
				tmplit=newn;
				printf("(L, %d)", indlit);
				fprintf(out1, "(L, %d)", indlit);
			}
			else
			{
				tmpsrch=h_littab;
				while((tmpsrch!=NULL)&&(sflag==0))
				{
					if(strcmp(tmpsrch->str, val)==0)
					{
						sflag=1;
						indlit=tmpsrch->ind;
					}
					tmpsrch=tmpsrch->next;
				}	
				if(sflag==0)
				{
					indlit++;
					newn=(node *)malloc(sizeof(node));
					newn->loc=0;
					newn->ind=indlit;
					strcpy(newn->str, val);
					newn->next=NULL;
					tmplit->next=newn;
					tmplit=newn;
					printf("(L, %d)", indlit);
					fprintf(out1, "(L, %d)", indlit);
				}
				else
				{
					printf("(L, %d)", indlit);
					fprintf(out1, "(L, %d)", indlit);
					sflag=0;
				}
			}
		}
		else
		{
			if(h_smbtab==NULL)
			{
				indsmb++;
				newn=(node *)malloc(sizeof(node));
				newn->loc=0;
				newn->ind=indsmb;
				strcpy(newn->str, val);
				newn->next=NULL;
				h_smbtab=newn;
				tmpsmb=newn;
				printf("(S, %d)", indsmb);
				fprintf(out1, "(S, %d)", indsmb);
			}
			else
			{
				tmpsrch=h_smbtab;
				while((tmpsrch!=NULL)&&(sflag==0))
				{
					if(strcmp(tmpsrch->str, val)==0)
					{
						sflag=1;
						indsmb=tmpsrch->ind;
					}
					tmpsrch=tmpsrch->next;
				}	
				if(sflag==0)
				{
					indsmb++;
					newn=(node *)malloc(sizeof(node));
					newn->loc=0;
					newn->ind=indsmb;
					strcpy(newn->str, val);
					newn->next=NULL;
					tmpsmb->next=newn;
					tmpsmb=newn;
					printf("(S, %d)", indsmb);
					fprintf(out1, "(S, %d)", indsmb);
				}
				else
				{
					printf("(S, %d)", indsmb);
					fprintf(out1, "(S, %d)", indsmb);
					sflag=0;
				}
			}
		}
		fclose(out1);
	}
	else
	{
		FILE *out1;
		out1=fopen("output_fileP1.txt", "a+");
		if(val[0]=='=')	//Move to Link List of Literal Table
		{
			if(h_littab==NULL)
			{
				indlit++;
				newn=(node *)malloc(sizeof(node));
				newn->loc=lc;
				newn->ind=indlit;
				strcpy(newn->str, val);
				newn->next=NULL;
				h_littab=newn;
				tmplit=newn;
			}
			else
			{
				tmpsrch=h_littab;
				while((tmpsrch!=NULL)&&(sflag==0))
				{
					if(strcmp(tmpsrch->str, val)==0)
					{
						sflag=1;
						indlit=tmpsrch->ind;
						tmpsrch->loc=lc;
					}
					tmpsrch=tmpsrch->next;
				}	
				if(sflag==0)
				{
					indlit++;
					newn=(node *)malloc(sizeof(node));
					newn->loc=lc;
					newn->ind=indlit;
					strcpy(newn->str, val);
					newn->next=NULL;
					tmplit->next=newn;
					tmplit=newn;
				}
				else
					sflag=0;
			}
		}
		else
		{
			if(h_smbtab==NULL)
			{
				indsmb++;
				newn=(node *)malloc(sizeof(node));
				newn->loc=lc;
				newn->ind=indsmb;
				strcpy(newn->str, val);
				newn->next=NULL;
				h_smbtab=newn;
				tmpsmb=newn;
			}
			else
			{
				tmpsrch=h_smbtab;
				while((tmpsrch!=NULL)&&(sflag==0))
				{
					if(strcmp(tmpsrch->str, val)==0)
					{
						sflag=1;
						indlit=tmpsrch->ind;
						tmpsrch->loc=lc;
					}
					tmpsrch=tmpsrch->next;
				}	
				if(sflag==0)
				{
					indsmb++;
					newn=(node *)malloc(sizeof(node));
					newn->loc=lc;
					newn->ind=indsmb;
					strcpy(newn->str, val);
					newn->next=NULL;
					tmpsmb->next=newn;
					tmpsmb=newn;
				}
				else
					sflag=0;
			}
		}
		fclose(out1);
	}
}

void main()
{
	int srch_res, index=0, lc=0;	//srch_res=Search Result, index is index of the searched key in that table if present
	int n, i=0;
	char buffer[200], val1[20], val2[20], val3[20], val4[20];
	char is_tab[11][10]={"STOP", "ADD", "SUB", "MULT", "MOVER", "MOVEM", "COMP", "BC", "DIV", "READ", "PRINT"};
	char ad_tab[5][10]={"START", "END", "ORIGIN", "EQU", "LTORG"};
	char ds_tab[2][10]={"DC", "DS"};
	char reg_tab[4][10]={"AREG", "BREG", "CREG", "DREG"};
	char cond_tab[6][10]={"LT", "LE", "GT", "GE", "EQ", "ANY"};
	char fname[20];
/*
	Here,
	is_tab is Imperative Statements table 
	ad_tab is Assembler Directives table
	ds_tab is Declarative Statement table
	reg_tab is Register table
	cond_tab is Condition table
*/
	FILE *in1, *out1;
	printf("\nPlease enter file name --> ");
	scanf("%s", fname);
	in1=fopen(fname, "r");
	out1=fopen("output_fileP1.txt", "a+");
	if(in1!=NULL)
	{
		while(fgets(buffer, 200, in1))
		{
			n=sscanf(buffer, "%s%s%s%s", val1, val2, val3, val4);	//Here, n is number of strings in that line
			if(n==1)
			{
				if((srch_res=search_is(val1, is_tab))!=-1)
				{
					index=srch_res;
					printf("%d\t(IS, %d)\n", lc, index);
					fprintf(out1, "%d\t(IS, %d)\n", lc, index);
					lc++;
				}
				else if((srch_res=search_ad(val1, ad_tab))!=-1)
				{
					index=srch_res+1;
					printf("%d\t(AD, %d)\n", lc, index);
					fprintf(out1, "%d\t(AD, %d)\n", lc, index);
					lc++;
				}
			}	
			if(n==2)
			{
				if((srch_res=search_is(val1, is_tab))!=-1)
				{
					index=srch_res;
					printf("%d\t(IS, %d)\t", lc, index);
					fprintf(out1, "%d\t(IS, %d)\t", lc, index);
					if((srch_res=search_rg(val2, reg_tab))!=-1)
					{
						index=srch_res+1;
						printf("(REG, %d)\n", index);
						fprintf(out1, "(REG, %d)\n", index);
					}
					else			//For Lables and Literals
					{
						fclose(out1);
						create(val2, lc, 0);
						out1=fopen("output_fileP1.txt", "a+");
						printf("\n");
						fprintf(out1, "\n");
					}
					lc++;
				}
				else							//This is to check AD table Right Now assuming it's only start
				{
					srch_res=search_ad(val1, ad_tab);
					index=srch_res+1;
					printf("%d\t(AD, %d)\t(C, %d)\n", lc, index, atoi(val2));
					fprintf(out1, "%d\t(AD, %d)\t(C, %d)\n", lc, index, atoi(val2));
					lc=atoi(val2);
				}
			}
			if(n==3)
			{
				if((srch_res=search_is(val1, is_tab))!=-1)
				{
					index=srch_res;						
					printf("%d\t(IS, %d)\t", lc, index);
					fprintf(out1, "%d\t(IS, %d)\t", lc, index);
					if((srch_res=search_rg(val2, reg_tab))!=-1)
					{			
						index=srch_res+1;
						printf("(REG, %d)\t", index);
						fprintf(out1, "(REG, %d)\t", index);
						if((srch_res=search_rg(val3, reg_tab))!=-1)
						{
							index=srch_res+1;
							printf("(REG, %d)\n", index);
							fprintf(out1, "(REG, %d)\n", index);
						}
						else
						{
							fclose(out1);
							create(val3, lc, 0);
							out1=fopen("output_fileP1.txt", "a+");
							printf("\n");
							fprintf(out1, "\n");
						}
					}
					else if((srch_res=search_cond(val2, cond_tab))!=-1)
					{
						index=srch_res+1;
						printf("(Cond, %d)\t", index);
						fprintf(out1, "(Cond, %d)\t", index);
						if((srch_res=search_rg(val3, reg_tab))!=-1)
						{
							index=srch_res+1;
							printf("(REG, %d)\n", index);
							fprintf(out1, "(REG, %d)\n", index);
						}
						else
						{
							fclose(out1);
							create(val3, lc, 0);
							out1=fopen("output_fileP1.txt", "a+");
							printf("\n");
							fprintf(out1, "\n");
						}												
					}
					else	
					{
						fclose(out1);
						create(val2, lc, 0);
						out1=fopen("output_fileP1.txt", "a+");
						if((srch_res=search_rg(val3, reg_tab))!=-1)
						{
							index=srch_res+1;
							printf("\t(REG, %d)\n", index);
							fprintf(out1, "\t(REG, %d)\n", index);
						}
						else
						{
							fclose(out1);
							create(val3, lc, 0);
							out1=fopen("output_fileP1.txt", "a+");
							printf("\n");
							fprintf(out1, "\n");
						}
					}
					lc++;
				}
				else					//For time being assume it is a label
				{
					printf("%d\t", lc);
					fprintf(out1, "%d\t", lc);
					fclose(out1);
					create(val1, lc, 1);
					out1=fopen("output_fileP1.txt", "a+");
					if((srch_res=search_ds(val2, ds_tab))!=-1)	//POINT
					{
						index=srch_res+1;
						printf("\t(DL, %d)\t", index);
						fprintf(out1, "\t(DL, %d)\t", index);
						if(index==2)
						{
							printf("(C, %d)\n", atoi(val3));	
							fprintf(out1, "(C, %d)\n", atoi(val3));	
							lc=lc+atoi(val3);
						}
						else
						{
							printf("\n");
							fprintf(out1, "\n");
							lc++;
						}
					}
				}
			}
			if(n==4)
			{
				printf("%d\t", lc);
				fprintf(out1, "%d\t", lc);
				fclose(out1);
				create(val1, lc, 1);
				out1=fopen("output_fileP1.txt", "a+");
				if((srch_res=search_is(val2, is_tab))!=-1)
				{
					index=srch_res;						
					printf("\t(IS, %d)\t", index);
					fprintf(out1, "\t(IS, %d)\t", index);
					if((srch_res=search_rg(val3, reg_tab))!=-1)
					{			
						index=srch_res+1;
						printf("(REG, %d)\t", index);
						fprintf(out1, "(REG, %d)\t", index);
						if((srch_res=search_rg(val4, reg_tab))!=-1)
						{
							index=srch_res+1;
							printf("(REG, %d)\n", index);
							fprintf(out1, "(REG, %d)\n", index);
						}
						else
						{
							fclose(out1);
							create(val4, lc, 0);
							out1=fopen("output_fileP1.txt", "a+");
							printf("\n");
							fprintf(out1, "\n");
						}
					}
					else if((srch_res=search_cond(val3, cond_tab))!=-1)
					{
						index=srch_res+1;
						printf("(Cond, %d)\n", index);
						fprintf(out1, "(Cond, %d)\n", index);
						if((srch_res=search_rg(val4, reg_tab))!=-1)
						{
							index=srch_res+1;
							printf("(REG, %d)\n", index);
							fprintf(out1, "(REG, %d)\n", index);
						}
						else
						{
							fclose(out1);
							create(val4, lc, 0);
							out1=fopen("output_fileP1.txt", "a+");
							printf("\n");
							fprintf(out1, "\n");
						}
					}
					else
					{
						fclose(out1);
						create(val3, lc, 0);
						out1=fopen("output_fileP1.txt", "a+");
						if((srch_res=search_rg(val4, reg_tab))!=-1)
						{
							index=srch_res+1;
							printf("\t(REG, %d)\n", index);
							fprintf(out1, "\t(REG, %d)\n", index);
						}
						else
						{
							printf("\t");
							fprintf(out1, "\t");
							fclose(out1);
							create(val4, lc, 0);
							out1=fopen("output_fileP1.txt", "a+");
							printf("\n");
							fprintf(out1, "\n");
						}
					}
				}
				else					//For time being assume it is a label
				{
					printf("\t");
					fprintf(out1, "\t");
					fclose(out1);
					create(val2, lc, 0);
					out1=fopen("output_fileP1.txt", "a+");
					if((srch_res=search_is(val2, is_tab))!=-1)
					{
						index=srch_res;						
						printf("%d\t(IS, %d)\t", lc, index);
						fprintf(out1, "%d\t(IS, %d)\t", lc, index);
						if((srch_res=search_rg(val3, reg_tab))!=-1)
						{			
							index=srch_res+1;
							printf("(REG, %d)\t", index);
							fprintf(out1, "(REG, %d)\t", index);
							if((srch_res=search_rg(val4, reg_tab))!=-1)
							{
								index=srch_res+1;
								printf("(REG, %d)\n", index);
								fprintf(out1, "(REG, %d)\n", index);
							}
							else
							{
								fclose(out1);
								create(val4, lc, 0);
								out1=fopen("output_fileP1.txt", "a+");
								printf("\n");
								fprintf(out1, "\n");
							}
						}
						else if((srch_res=search_cond(val3, cond_tab))!=-1)
						{
							index=srch_res+1;
							printf("(Cond, %d)\t", index);
							fprintf(out1, "(Cond, %d)\t", index);
							if((srch_res=search_rg(val4, reg_tab))!=-1)
							{
								index=srch_res+1;
								printf("(REG, %d)\n", index);
								fprintf(out1, "(REG, %d)\n", index);
							}
							else
							{
								fclose(out1);
								create(val4, lc, 0);
								out1=fopen("output_fileP1.txt", "a+");
								printf("\n");
								fprintf(out1, "\n");
							}												
						}
						else	
						{
							fclose(out1);
							create(val3, lc, 0);
							out1=fopen("output_fileP1.txt", "a+");
							if((srch_res=search_rg(val4, reg_tab))!=-1)
							{
								index=srch_res+1;
								printf("\t(REG, %d)\n", index);
								fprintf(out1, "\t(REG, %d)\n", index);
							}
							else
							{
								fclose(out1);
								create(val4, lc, 0);
								out1=fopen("output_fileP1.txt", "a+");
								printf("\n");
								fprintf(out1, "\n");
							}
						}
					}
				}
					lc++;
			}
		}
	}
	fclose(out1);
	fclose(in1);
	printf("\n\n\t------------\n");
	printf("\tSymbol Table\n");
	printf("\t------------\n");
	node *t1, *t2;
	t1=h_smbtab;
	t2=h_littab;
	printf("Index\tLC\tValue\n");
	while(t1!=NULL)
	{
		printf("%d\t%d\t%s\n", t1->ind, t1->loc, t1->str);
		t1=t1->next;
	}
	printf("\n\n\t-------------\n");
	printf("\tLiteral Table\n");
	printf("\t-------------\n");
	printf("Index\tLC\tValue\n");
	while(t2!=NULL)
	{
		printf("%d\t%d\t%s\n", t2->ind, t2->loc, t2->str);
		t2=t2->next;
	}
}

