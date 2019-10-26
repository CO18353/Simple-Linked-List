#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
struct Record {
	char roll_no[8];
	char name[50];
	int sem;
	char branch[10];
	struct Record *next;
};
typedef struct Record list;

void check_empty(list *start);
void file_write(list *start);
list *file_read(list *start);
list *create(list *start);
list *insert(list *start);
void search(list *start);
void update(list *start);
void file_update(char *str,list *std);
void traverse(list *start);
list *del(list *start);
void report(list *start);


int main()
{
	list *start;
	start=(list*)malloc(sizeof(list));
	start=file_read(start);
	int option,s;
	if(start==NULL)
	{
			printf("Linked list creation not possible\n");
			exit(1);
	}	
	do {
		printf("---------------**Enter your option**-----------------\n");
		printf("1. Create a linked list\n2. Insert a node in the list\n3. Search a record in the list\n4. Update a record\n5. Traverse the list\n6. Delete a record\n7. Generate report\n8.Save data\n9.Exit\n\n\n");
		scanf("%d",&option);
		switch(option)
	  	{
	     case 1:	
				start=create(start);		
	     	break;

	     case 2:
				start=insert(start);
	        break;

			case 3:
				search(start);
				break;

			case 4:
				update(start);
				break;

			case 5:
				traverse(start);
					break;
			  
			case 6:
				start=del(start);
				break;

			case 7:
				report(start);
				break;
				
			case 8:
				printf("Do you want to save the data :\n Enter 1 for yes and 2 for no :");
				fflush(stdin);			
				scanf("%d",&s);
				if(s==1)
					file_write(start);
				else
					exit(1);
				break;
			
			case 9:
				exit(1);
			
			default:	 
			   exit(1);
		}
	
	}while(option!=9);

	return 0;
}

void check_empty(list *start)
{
	if(start==NULL)
	{
		printf("List is empty\n");
		exit(1);
	}
}

void file_write(list *start)
{
	check_empty(start);
	FILE *fp;
	fp=fopen("student.dat","wb");
	if(fp==NULL)
	{
		printf("File cannot be created");
		exit(0);
	}
	list *temp;
	temp=start;
	while(temp->next!=NULL)
	{
		fwrite(temp,sizeof(*temp),1,fp);
		temp=temp->next;
	}
	fclose(fp);
}

list *file_read(list *start)
{
	FILE *fp;
	fp=fopen("student.dat","rb");
	if(fp==NULL)
	{
		printf("File cannot be opened");
		exit(0);
	}
	
	list *node;
	node=(list *)malloc(sizeof(list));
	if(node==NULL)
	{
		printf("Linked list creation not possible");
		exit(1);
	}
	start=node;
	while(fread(node,sizeof(*node),1,fp)==1)
	{
		node->next=(list*)malloc(sizeof(list));
		node=node->next;
	}
	node->next='\0';
	fclose(fp);
	return start;
}

list *create(list *start)
{
	int i=0,num;
	list *node;
	node=(list *)malloc(sizeof(list));
	if(node==NULL)
	{
		printf("Linked list creation not possible");
		exit(1);
	}
	
	start=node;
	printf("Enter the number of students");
	scanf("%d",&num);
	while(i<num)
	{
		printf("Enter Roll number: ");
		scanf("%s",node->roll_no);
		printf("Enter Name : ");
		scanf("%s",node->name);
		printf("Enter Branch : ");
		scanf("%s",node->branch);
		printf("Enter Semester: ");
		scanf("%d",&node->sem);
		printf("\n\n");
		node->next=(list*)malloc(sizeof(list));
		node=node->next;
		i=i+1;	
	}

	node->next='\0';
	printf("\n");
	return start;
}

list* insert(list *start)
{
	int option;
	char roll[8];
	check_empty(start);
	list *new_node,*temp,*prev;
	new_node=(list*)malloc(sizeof(list));
	if(new_node==NULL)
	{
		printf("Not possible to insert a node");
		exit(1);
	}
	printf("\nInsert the node as -\n 1.As a first record\n2.Before a record\n3.After a record\n");
	scanf("%d",&option);
	switch(option)
	{
		case 1:
				printf("Enter Roll number: ");
				scanf("%s",new_node->roll_no);
				printf("Enter Name : ");
				scanf("%s", new_node->name);				
				printf("Enter Branch : ");
				scanf("%s",new_node->branch);
				printf("Enter Semester: ");
				scanf("%d",&new_node->sem);
				printf("\n\n");
				new_node->next=start;
				start=new_node;
				printf("Record inserted\n\n");
			break;
			
		case 2:
				printf("Enter the roll number before which data has to be inserted : ");
				scanf("%s",roll);				
				printf("Enter Roll number: ");
				scanf("%s",new_node->roll_no);
				printf("Enter Name : ");
				scanf("%s",new_node->name);
				printf("Enter Branch : ");
				scanf("%s",new_node->branch);
				printf("Enter Semester: ");
				scanf("%d",&new_node->sem);
				printf("\n\n");
				temp=start;
				while(strcmp(temp->roll_no,roll)!=0)
				{
					prev=temp;
					temp=temp->next;
				}
				prev->next=new_node;
				new_node->next=temp;
				printf("Record inserted\n\n");
			break;
		
		case 3:
				printf("Enter the roll number after which data has to be inserted : ");
				scanf("%s",roll);				
				printf("Enter Roll number: ");
				scanf("%s",new_node->roll_no);
				printf("Enter Name : ");
				scanf("%s",new_node->name);
				printf("Enter Branch : ");
				scanf("%s",new_node->branch);
				printf("Enter Semester: ");
				scanf("%d",&new_node->sem);
				printf("\n\n");
				temp=start;
				while(temp->next!=NULL)
				{
					if(strcmp(temp->roll_no,roll)==0)
					{
							new_node->next=temp->next;	//set pointer of new node to next node in the list
							temp->next=new_node;		//set the pointer to hold the address of new created node
							printf("Record inserted\n\n");
							break;
					}
					
						temp=temp->next;
				}
			break;
			
		default:
			printf("Choose right option\n");
			exit(1);
	}
	
	printf("\n\n");
	return start;
}

void search(list *start)
{
	char roll[8];
	int find=0;
	list *temp;
	printf("Enter roll number : ");
	scanf("%s",roll);
	temp=start;
	while(temp->next!=NULL)
	{
		if(strcmp(roll,temp->roll_no)==0)
		{
			printf("%10s	%10s	%10d	%10s\n",temp->roll_no,temp->name,temp->sem,temp->branch);
			find=1;		
			break;				
		}
		temp=temp->next;	
	}

	if(find==0)
		printf("Record not found\n");
	
	printf("\n\n");
}

void traverse(list *start)
{
	check_empty(start);
	list *temp;
	temp=start;
	printf("Roll number\t\tName\t\tSemester\t  Branch\n");
	while(temp->next!=NULL)
	{
		printf("%10s	%10s	%10d	%10s\n",temp->roll_no,temp->name,temp->sem,temp->branch);
		temp=temp->next;	
	}
	printf("\n\n");
}

void update(list *start)
{
		check_empty(start);
		char roll[7];  
		int find=1;
		list *temp;
		temp=start;
		printf("Enter roll number to be updated : ");
		scanf("%s",roll);
		while(temp->next!=NULL)
		{
			if(strcmp(roll,temp->roll_no)==0)
			{			
				printf("Enter new Roll number: ");
				scanf("%s",temp->roll_no);
				printf("Enter Name : ");
				scanf("%s",temp->name);
				printf("Enter Semester: ");
				scanf("%d",&temp->sem);
				printf("Enter Branch : ");
				scanf("%s",temp->branch);
				file_update(roll,temp);
				find=1;				
				break;
			}
					temp=temp->next;
					find=0;
			
		}
			
		if(find==0)
				printf("Record not found,please enter new reord\n");
}

void file_update(char *str,list *std)
{
			FILE *fp;
			int i;
			list temp;
			fp=fopen("student.dat","rb+");
			if(fp!=NULL)
			{
					while(fread(&temp,sizeof(temp),1,fp)==1)
					{
						if(strcmp(str,temp.roll_no)==0)
						{			
							fseek(fp,-sizeof(temp),SEEK_CUR);				
							fwrite(std,sizeof(*std),1,fp);
						}
					}
			}
				
		fclose(fp);
}

list *del(list *start)
{
	check_empty(start);
	int option;
	char roll[8];
	list *node1,*temp,*prev;
	node1=(list*)malloc(sizeof(list));
	printf("\nDelete the node -\n 1.First record\n2.Last record\n3. At any desired position\n");
	scanf("%d",&option);
	switch(option)
	{
		case 1:
				node1->next=start;
				start=start->next;
				free(node1);
				printf("Record deleted");
			break;
			
		case 2:
				temp=start;
				while(temp->next!=NULL)
				{	
					prev=temp;
					temp=temp->next;
				}
				prev->next='\0';
				free(temp);
				printf("Record deleted\n");
			break;
		
		case 3:
				printf("Enter roll number to be deleted : ");
				scanf("%s",roll);
				temp=start;
				while(strcmp(temp->roll_no,roll)!=0)
				{
					prev=temp;
					temp=temp->next;
				}
				prev->next=temp->next;
				free(temp);
				printf("Record deleted\n");
			break;
			
		default:
			printf("Choose right option\n");
			exit(1);
	}
	
	printf("\n\n");
	return start;
}

void report(list *start)
{
	check_empty(start);
	list *temp;
	temp=start;
	int count=0,option,sem,find=0;
	char branch[10];
	printf("\n1. Based on semester\n2. Based on branch\n");	
	scanf("%d",&option);	
	switch(option)
	{
		case 1:
			printf("Enter semester : ");
			scanf("%d",&sem);
			printf("Roll number\t\tName\t\t  Branch\n");
			while(temp->next!=NULL)
			{
				if(sem==temp->sem)
				{
					printf("%10s	%10s  %10s\n",temp->roll_no,temp->name,temp->branch);
					count++;
					find=1;		
				}
				temp=temp->next;	
			}
			printf("Total number of students enrolled for %d semester are %d\n\n",sem,count);
			break;
		
		case 2:
			printf("Enter branch : ");
			scanf("%s",branch);
			printf("Roll number\t\tName\t\tSemester\n");
			while(temp->next!=NULL)
			{
				if(strcmp(branch,temp->branch)==0)
				{
					printf("%10s	%10s	%10d\n",temp->roll_no,temp->name,temp->sem);
					count++;
					find=1;				
				}
				temp=temp->next;	
			}

			if(find==0)
				printf("Record not found\n");
			else
				printf("Total number of students in %s branch are %d\n\n",branch,count);
		break;
		
		default:
			printf("Choose right option\n");
			exit(1);
	}
}

