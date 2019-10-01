#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct student
{
	char roll[8];
	char name[30];
	char branch[4];
	int sem;
	struct student *next;
};
typedef struct student list;
list *start;
FILE *fr,*fw;
void traverse();
void delete_node();
void insert_node();
void search_node();
void gen_report();
void update_node();
void readf();
void writef();
int main(void)
{
	list *node;
	node=(list*)malloc(sizeof(list));
	if(node==NULL)
	{
		printf("Memory not allocated to head");
		exit(0);
	}
	start=node;
	node->next='\0';
	
	while(1)
	{
		printf("\n1.TO INSERT\n2.TO DELETE\n3.TO TRAVERSE\n4.TO SAVE\n5.TO READ\n6.TO SEARCH\n7.TO GENERATE REPORT\n8.TO UPDATE\n");
		int ch;
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
					insert_node();
					break;
			case 2:
					delete_node();
					break;
			case 3:
					traverse();
					break;
			case 4:
					writef();
					break;
			case 5:
					readf();
					break;
			case 6:
					search_node();
					break;
			case 7:
					gen_report();
					break;
			case 8:
					update_node();
					break;
			default:
					exit(0);
		}
	}
	return 0;
}

void traverse()
{
	list *stemp;
	stemp=start;
	while(stemp->next)
	{
		printf("Roll Number is %s\n",stemp->roll);
		printf("Name is %s\n",stemp->name);
		printf("Branch is %s\n",stemp->branch);
		printf("Semester is %d\n\n",stemp->sem);
		stemp=stemp->next;
	}
}

void delete_node()
{
	if(start==NULL)
	{
		printf("Empty List");
		exit(0);
	}
	list *delstart;
	int del,i;
	printf("\nEnter the node to delete\n");
	scanf("%d",&del);
	if(del==1)
	{
		delstart=start;
		start=start->next;
		free(delstart);
	}
	else
	{
		i=1;
		list *temp;
		delstart=start;
		while(delstart)
		{	
			if(i==(del-1))
			{
				temp=delstart;
			}
			if(i==del)
			{
				temp->next=delstart->next;
				free(delstart);
			}
			delstart=delstart->next;
			i++;
		}
	}
}

void insert_node()
{
	list *temp,*instart,*t;
	instart=start;
	int ins,i=1;
	temp=(list*)malloc(sizeof(list));
	if(temp==NULL)
	{
		printf("Memory not Allocated");
		exit(1);
	}
	printf("Enter the data for the new node\n");
	printf("Enter the Roll Number: ");
	scanf("%s",temp->roll);
	printf("Enter the Name: ");
	scanf("%s",temp->name);
	printf("Enter the Branch: ");
	scanf("%s",temp->branch);
	printf("Enter the Semester: ");
	scanf("%d",&temp->sem);

	printf("Enter the position where the node is to be inserted\n");
	scanf("%d",&ins);
	if(ins==1)
	{
		temp->next=start;
		start=temp;
	}
	else
	{
		while(instart)
		{	
			if(i==(ins-1))
			{
				t=instart;
			}
			if(i==ins)
			{
				t->next=temp;
				temp->next=instart;
			}
			instart=instart->next;
			i++;
		}
	}
}
void search_node()
{
	char rolls[8];
	printf("Enter the roll number of the student: ");
	scanf("%s",rolls);
	list *ser;
	ser=start;
	while(ser)
	{
		if(strcmp(ser->roll,rolls)==0)
			break;
		ser=ser->next;
	}
	printf("Name is %s\n",ser->name);
	printf("Branch is %s\n",ser->branch);
	printf("Semester is %d\n\n",ser->sem);	
}
void gen_report()
{
	int ch;
	printf("Press: 1.To List According to Branch\n2.To List According to Semester\n");
	scanf("%d",&ch);
	list *ser;
	switch(ch)
	{
		case 1:
				char bran[4];
				printf("Enter the branch: ");
				scanf("%s",bran);
				ser=start;
				printf("\tRoll Number\t\tName\tSemester\n");
				while(ser)
				{
					if(strcmp(ser->branch,bran)==0)
					{
						printf("%15s %15s %15d\n",ser->roll,ser->name,ser->sem);
					}
					ser=ser->next;
				}
				break;
		case 2:
				int se;
				printf("Enter the semester: ");
				scanf("%d",&se);
				ser=start;
				printf("\tRoll Number\t\tName\t\tBranch\n");
				while(ser)
				{
					if(ser->sem==se)
					{
						printf("%15s %15s %15s\n",ser->roll,ser->name,ser->branch);
					}
					ser=ser->next;
				}
				break;
	}
}
void update_node()
{
	char rolls[8];
	printf("Enter the roll number of the student: ");
	scanf("%s",rolls);
	list *ser;
	ser=start;
	while(ser)
	{
		if(strcmp(ser->roll,rolls)==0)
		{
			printf("Enter the new Name: ");
			scanf("%s",ser->name);
			printf("Enter the new Branch: ");
			scanf("%s",ser->branch);
			printf("Enter the new Semester: ");
			scanf("%d",&ser->sem);
			break;
		}
		ser=ser->next;
	}
}
void readf()
{
	fr=fopen("link.txt","rb");
	if(fr==NULL)
	{
		printf("Unable to open file");
		exit(0);
	}
	list *nod;
	nod=(list*)malloc(sizeof(list));
	start=nod;
	while(fscanf(fr,"%s %s %s %d",nod->roll,nod->name,nod->branch,&nod->sem)!=EOF)
	{
		nod->next=(list*)malloc(sizeof(list));
		nod=nod->next;
	}
	nod->next='\0';
	fclose(fr);
}
void writef()
{
	fw=fopen("link.txt","wb");
	if(fw==NULL)
	{
		printf("Unable to open file");
		exit(0);
	}
	list *fstart;
	fstart=start;
	while(fstart->next)
	{
		fprintf(fw,"%s %s %s %d\r",fstart->roll,fstart->name,fstart->branch,fstart->sem);
		fstart=fstart->next;
	}
	fclose(fw);
}
