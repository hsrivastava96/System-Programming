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
	
int search_cond(char key[10], char str[4][10])	//Search Register Table
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

void main()
{
	node *h_smbtab=NULL, *h_littab=NULL, *newn, *tmpsmb, *tmplit, *tmpsrch;
	int srch_res, index=0, lc=0, indsmb=0, indlit=0, sflag=0;	//srch_res=Search Result, index is index of the searched key in that table if present
	int n, i=0;
	char buffer[200], val1[20], val2[20], val3[20], val4[20];
	char is_tab[11][10]={"STOP", "ADD", "SUB", "MULT", "MOVER", "MOVEM", "COMP", "BC", "DIV", "READ", "PRINT"};
	char ad_tab[5][10]={"START", "END", "ORIGIN", "EQU", "LTORG"};
	char ds_tab[2][10]={"DC", "DS"};
	char reg_tab[4][10]={"AREG", "BREG", "CREG", "DREG"};
	char cond_tab[6][10]={"LT", "LE", "GT", "GE", "EQ", "ANY"};
/*
	Here,
	is_tab is Imperative Statements table 
	ad_tab is Assembler Directives table
	ds_tab is Declarative Statement table
	reg_tab is Register table
*/
	FILE *in1, *out1;
	in1=fopen("input_file.txt", "r");
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
					lc++;
					index=srch_res;
					printf("%d\t(IS, %d)\n", lc, index);
					fprintf(out1, "%d\t(IS, %d)\n", lc, index);
				}
				else if((srch_res=search_ad(val1, ad_tab))!=-1)
				{
					lc++;
					index=srch_res+1;
					printf("%d\t(AD, %d)\n", lc, index);
					fprintf(out1, "%d\t(AD, %d)\n", lc, index);
				}
			}	
			if(n==2)
			{
				if((srch_res=search_is(val1, is_tab))!=-1)
				{
					lc++;
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
						if(val2[0]=='=')	//Move to Link List of Literal Table
						{
							if(h_littab==NULL)
							{
								indlit++;
								newn=(node *)malloc(sizeof(node));
								newn->loc=lc;
								newn->ind=indlit;
								strcpy(newn->str, val2);
								newn->next=NULL;
								h_littab=newn;
								tmplit=newn;
								printf("(%s, %d)\n", val2, indsmb);
								fprintf(out1, "(%s, %d)\n", val2, indsmb);
							}
							else
							{
								tmpsrch=h_littab;
								while((tmpsrch!=NULL)&&(sflag==0))
								{
									if(strcmp(tmpsrch->str, val2)==0)
										sflag=1;
									tmpsrch=tmpsrch->next;
								}	
								if(sflag==0)
								{
									indlit++;
									newn=(node *)malloc(sizeof(node));
									newn->loc=lc;
									newn->ind=indlit;
									strcpy(newn->str, val2);
									newn->next=NULL;
									tmplit->next=newn;
									tmplit=newn;
									printf("(%s, %d)\n", val2, indlit);
									fprintf(out1, "(%s, %d)\n", val2, indlit);
								}
								else
								{
									printf("(%s, %d)\n", val2, indsmb);
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
								newn->loc=lc;
								newn->ind=indsmb;
								strcpy(newn->str, val2);
								newn->next=NULL;
								h_smbtab=newn;
								tmpsmb=newn;
								printf("(%s, %d)\n", val2, indsmb);
								fprintf(out1, "(%s, %d)\n", val2, indsmb);
							}
							else
							{
								tmpsrch=h_smbtab;
								while((tmpsrch!=NULL)&&(sflag==0))
								{
									if(strcmp(tmpsrch->str, val2)==0)
										sflag=1;
									tmpsrch=tmpsrch->next;
								}	
								if(sflag==0)
								{
									indsmb++;
									newn=(node *)malloc(sizeof(node));
									newn->loc=lc;
									newn->ind=indsmb;
									strcpy(newn->str, val2);
									newn->next=NULL;
									tmpsmb->next=newn;
									tmpsmb=newn;
									printf("(%s, %d)\n", val2, indsmb);
									fprintf(out1, "(%s, %d)\n", val2, indsmb);
								}
								else
								{
									printf("(%s, %d)\n", val2, indsmb);
									sflag=0;
								}
							}
						}
					}
				}
				else							//This is to check AD table Right Now assuming it's only start
				{
					srch_res=search_ad(val1, ad_tab);
					lc=atoi(val2);
					index=srch_res+1;
					printf("%d\t(AD, %d)\t(C, %d)\n", lc, index, atoi(val2));
					fprintf(out1, "%d\t(AD, %d)\t(C, %d)\n", lc, index, atoi(val2));
				}
			}
			if(n==3)
			{
				if((srch_res=search_is(val1, is_tab))!=-1)
				{
					lc++;
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
							if(val3[0]=='=')	//Move to Link List of Literal Table
							{
								if(h_littab==NULL)
								{
									indlit++;
									newn=(node *)malloc(sizeof(node));
									newn->loc=lc;
									newn->ind=indlit;
									strcpy(newn->str, val3);
									newn->next=NULL;
									h_littab=newn;
									tmplit=newn;
									printf("(%s, %d)\n", val3, indsmb);
									fprintf(out1, "(%s, %d)\n", val3, indsmb);
								}
								else
								{
									tmpsrch=h_littab;
									while((tmpsrch!=NULL)&&(sflag==0))
									{
										if(strcmp(tmpsrch->str, val3)==0)
											sflag=1;
										tmpsrch=tmpsrch->next;
									}	
									if(sflag==0)
									{
										indlit++;
										newn=(node *)malloc(sizeof(node));
										newn->loc=lc;
										newn->ind=indlit;
										strcpy(newn->str, val3);
										newn->next=NULL;
										tmplit->next=newn;
										tmplit=newn;
										printf("(%s, %d)\n", val3, indlit);
										fprintf(out1, "(%s, %d)\n", val3, indlit);
									}
									else
									{
										printf("(%s, %d)\n", val3, indlit);
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
									newn->loc=lc;
									newn->ind=indsmb;
									strcpy(newn->str, val3);
									newn->next=NULL;
									h_smbtab=newn;
									tmpsmb=newn;
									printf("(%s, %d)\n", val3, indsmb);
									fprintf(out1, "(%s, %d)\n", val3, indsmb);
								}
								else
								{
									tmpsrch=h_smbtab;
									while((tmpsrch!=NULL)&&(sflag==0))
									{
										if(strcmp(tmpsrch->str, val3)==0)
											sflag=1;
										tmpsrch=tmpsrch->next;
									}	
									if(sflag==0)
									{
										indsmb++;
										newn=(node *)malloc(sizeof(node));
										newn->loc=lc;
										newn->ind=indsmb;
										strcpy(newn->str, val3);
										newn->next=NULL;
										tmpsmb->next=newn;
										tmpsmb=newn;
										printf("(%s, %d)\n", val3, indsmb);
										fprintf(out1, "(%s, %d)\n", val3, indsmb);
									}
									else
									{
										printf("(%s, %d)\n", val3, indsmb);
										sflag=0;
									}
								}
							}
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
							if(val3[0]=='=')	//Move to Link List of Literal Table
							{
								if(h_littab==NULL)
								{
									indlit++;
									newn=(node *)malloc(sizeof(node));
									newn->loc=lc;
									newn->ind=indlit;
									strcpy(newn->str, val3);
									newn->next=NULL;
									h_littab=newn;
									tmplit=newn;
									printf("(%s, %d)\n", val3, indsmb);
									fprintf(out1, "(%s, %d)\n", val3, indsmb);
								}
								else
								{
									tmpsrch=h_littab;
									while((tmpsrch!=NULL)&&(sflag==0))
									{
										if(strcmp(tmpsrch->str, val3)==0)
											sflag=1;
										tmpsrch=tmpsrch->next;
									}	
									if(sflag==0)
									{
										indlit++;
										newn=(node *)malloc(sizeof(node));
										newn->loc=lc;
										newn->ind=indlit;
										strcpy(newn->str, val3);
										newn->next=NULL;
										tmplit->next=newn;
										tmplit=newn;
										printf("(%s, %d)\n", val3, indlit);
										fprintf(out1, "(%s, %d)\n", val3, indlit);
									}
									else
									{
										printf("(%s, %d)\n", val3, indlit);
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
									newn->loc=lc;
									newn->ind=indsmb;
									strcpy(newn->str, val3);
									newn->next=NULL;
									h_smbtab=newn;
									tmpsmb=newn;
									printf("(%s, %d)\n", val3, indsmb);
									fprintf(out1, "(%s, %d)\n", val3, indsmb);
								}
								else
								{
									tmpsrch=h_smbtab;
									while((tmpsrch!=NULL)&&(sflag==0))
									{
										if(strcmp(tmpsrch->str, val3)==0)
											sflag=1;
										tmpsrch=tmpsrch->next;
									}	
									if(sflag==0)
									{
										indsmb++;
										newn=(node *)malloc(sizeof(node));
										newn->loc=lc;
										newn->ind=indsmb;
										strcpy(newn->str, val3);
										newn->next=NULL;
										tmpsmb->next=newn;
										tmpsmb=newn;
										printf("(%s, %d)\n", val3, indsmb);
										fprintf(out1, "(%s, %d)\n", val3, indsmb);
									}
									else
									{
										printf("(%s, %d)\n", val3, indsmb);
										sflag=0;
									}
								}
							}
						}												
					}
					else
					{
						if(val2[0]=='=')	//Move to Link List of Literal Table
						{
							if(h_littab==NULL)
							{
								indlit++;
								newn=(node *)malloc(sizeof(node));
								newn->loc=lc;
								newn->ind=indlit;
								strcpy(newn->str, val2);
								newn->next=NULL;
								h_littab=newn;
								tmplit=newn;
								printf("(%s, %d)\n", val2, indsmb);
								fprintf(out1, "(%s, %d)\n", val2, indsmb);
							}
							else
							{
								tmpsrch=h_littab;
								while((tmpsrch!=NULL)&&(sflag==0))
								{
									if(strcmp(tmpsrch->str, val2)==0)
										sflag=1;
									tmpsrch=tmpsrch->next;
								}	
								if(sflag==0)
								{
									indlit++;
									newn=(node *)malloc(sizeof(node));
									newn->loc=lc;
									newn->ind=indlit;
									strcpy(newn->str, val2);
									newn->next=NULL;
									tmplit->next=newn;
									tmplit=newn;
									printf("(%s, %d)\n", val2, indlit);
									fprintf(out1, "(%s, %d)\n", val2, indlit);
								}
								else
								{
									printf("(%s, %d)\n", val2, indlit);
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
								newn->loc=lc;
								newn->ind=indsmb;
								strcpy(newn->str, val2);
								newn->next=NULL;
								h_smbtab=newn;
								tmpsmb=newn;
								printf("(%s, %d)\n", val2, indsmb);
								fprintf(out1, "(%s, %d)\n", val2, indsmb);
							}
							else
							{
								tmpsrch=h_smbtab;
								while((tmpsrch!=NULL)&&(sflag==0))
								{
									if(strcmp(tmpsrch->str, val2)==0)
										sflag=1;
									tmpsrch=tmpsrch->next;
								}	
								if(sflag==0)
								{
									indsmb++;
									newn=(node *)malloc(sizeof(node));
									newn->loc=lc;
									newn->ind=indsmb;
									strcpy(newn->str, val2);
									newn->next=NULL;
									tmpsmb->next=newn;
									tmpsmb=newn;
									printf("(%s, %d)\n", val2, indsmb);
									fprintf(out1, "(%s, %d)\n", val2, indsmb);
								}
								else
								{
									printf("(%s, %d)\n", val2, indsmb);
									sflag=0;
								}
							}
						}
						if((srch_res=search_rg(val3, reg_tab))!=-1)
						{
							index=srch_res+1;
							printf("(REG, %d)\n", index);
							fprintf(out1, "(REG, %d)\n", index);
						}
						else
						{
							if(val3[0]=='=')	//Move to Link List of Literal Table
							{
								if(h_littab==NULL)
								{
									indlit++;
									newn=(node *)malloc(sizeof(node));
									newn->loc=lc;
									newn->ind=indlit;
									strcpy(newn->str, val3);
									newn->next=NULL;
									h_littab=newn;
									tmplit=newn;
									printf("(%s, %d)\n", val3, indsmb);
									fprintf(out1, "(%s, %d)\n", val3, indsmb);
								}
								else
								{
									tmpsrch=h_littab;
									while((tmpsrch!=NULL)&&(sflag==0))
									{
										if(strcmp(tmpsrch->str, val3)==0)
											sflag=1;
										tmpsrch=tmpsrch->next;
									}	
									if(sflag==0)
									{
										indlit++;
										newn=(node *)malloc(sizeof(node));
										newn->loc=lc;
										newn->ind=indlit;
										strcpy(newn->str, val3);
										newn->next=NULL;
										tmplit->next=newn;
										tmplit=newn;
										printf("(%s, %d)\n", val3, indlit);
										fprintf(out1, "(%s, %d)\n", val3, indlit);
									}
									else
									{
										printf("(%s, %d)\n", val3, indlit);
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
									newn->loc=lc;
									newn->ind=indsmb;
									strcpy(newn->str, val3);
									newn->next=NULL;
									h_smbtab=newn;
									tmpsmb=newn;
									printf("(%s, %d)\n", val3, indsmb);
									fprintf(out1, "(%s, %d)\n", val3, indsmb);
								}
								else
								{
									tmpsrch=h_smbtab;
									while((tmpsrch!=NULL)&&(sflag==0))
									{
										if(strcmp(tmpsrch->str, val3)==0)
											sflag=1;
										tmpsrch=tmpsrch->next;
									}	
									if(sflag==0)
									{
										indsmb++;
										newn=(node *)malloc(sizeof(node));
										newn->loc=lc;
										newn->ind=indsmb;
										strcpy(newn->str, val3);
										newn->next=NULL;
										tmpsmb->next=newn;
										tmpsmb=newn;
										printf("(%s, %d)\n", val3, indsmb);
										fprintf(out1, "(%s, %d)\n", val3, indsmb);
									}
									else
									{
										printf("(%s, %d)\n", val3, indsmb);
										sflag=0;
									}
								}
							}
						}
					}
				}
				else					//For time being assume it is a label
				{
					lc++;
					printf("%d\tSymb/LitTab\t", lc);
					fprintf(out1, "%d\tSymb/LitTab\t", lc);
					if((srch_res=search_ds(val2, ds_tab))!=-1)	//POINT
					{
						index=srch_res+1;
						printf("(DL, %d)\t", index);
						fprintf(out1, "(DL, %d)\t", index);
						if(index==2)
						{
							lc=lc+atoi(val3);
							printf("(C, %d)\n", atoi(val3));	
							fprintf(out1, "(C, %d)\n", atoi(val3));	
						}
						else
						{
							printf("\n");
							fprintf(out1, "\n");
						}
					}
				}
			}
			if(n==4)
			{
				lc++;
				printf("%d\tSymb/LitTab\t", lc);
				fprintf(out1, "%d\tSymb/LitTab\t", lc);				
				if((srch_res=search_is(val2, is_tab))!=-1)
				{
					lc++;
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
							printf("Symb/LitTab\n");
							fprintf(out1, "Symb/LitTab\n");
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
							printf("Symb/LitTab\n");
							fprintf(out1, "Symb/LitTab\n");
						}												
					}
					else
					{
						printf("Symb/LitTab\t");		
						fprintf(out1, "Symb/LitTab\t");		
						if((srch_res=search_rg(val4, reg_tab))!=-1)
						{
							index=srch_res+1;
							printf("(REG, %d)\n", index);
							fprintf(out1, "(REG, %d)\n", index);
						}
						else
						{
							printf("Symb/LitTab\n");
							fprintf(out1, "Symb/LitTab\n");
						}
					}
				}
				else					//For time being assume it is a label
				{
					lc++;
					printf("%d\tSymb/LitTab\t", lc);
					fprintf(out1, "%d\tSymb/LitTab\t", lc);
					if((srch_res=search_ds(val3, ds_tab))!=-1)
					{
						index=srch_res+1;
						printf("(DL, %d)\t", index);
						fprintf(out1, "(DL, %d)\t", index);
						if(index==2)
						{
							lc=lc+atoi(val4);
							printf("(C, %d)\n", atoi(val4));	
							fprintf(out1, "(C, %d)\n", atoi(val4));	
						}
						else
							printf("\n");
							fprintf(out1, "\n");
					}
				}
			}
		}
	}
}
