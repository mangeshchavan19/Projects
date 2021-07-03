#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static int empId=1000;


typedef struct Employee
{
	struct Employee *previous;
	int empId;
	char empName[50];
	long int salary;
	char address[100];
	char job[100];
	struct Employee *next;
}node;

typedef struct Index
{
	int empId;
	int position;
}Index;

char fileName[]={"Employee.dat"};
char indexName[]={"Index.dat"};


node *getNode();

node *insert(node *start,node *newEmployee);

void displayAll(node *start);

node *search(node *start,int empId);

node *searchById(node *start, int empId);

node *update(node *start,int empId);

node *deleteAt(node *start,int empId);

node *getDetails(node *employee);

void saveFile(node *start);

node *loadFile();

int notNull(node *temp);

int startNotNull(node *start);

void showDetails(node *employee);

void traverseList(node *start);


int main()
{
	node *employee=NULL;

	int flag=0;
	node *current=NULL;

	node *start=NULL;
	start=loadFile();

	char empName[100];
	int empId;
	int choice=0;
	int exit=10;

	//system("clear");

	printf("\n		EMPLOYEE MANAGEMENT SYSTEM		\n");

	do
	{

		printf("\n\n\tMAIN MENU ");
		printf("\n1:Add new employee:");
		printf("\n2:Display all employee details:");
		printf("\n3:Search Employee with id:");
		printf("\n4:Search Employee with id(this fast search requires file to be saved first):");
		printf("\n5:Update employee details:");
		printf("\n6:Delete employee:");
		printf("\n7:Save file:");
		printf("\n10:EXIT\n");
		printf("\nEnter your choice:\n");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
			{
				employee=getNode();
				employee=getDetails(employee);
				start=insert(start,employee);
			}
			break;

			case 2:
				if(startNotNull(start))
					displayAll(start);
			break;

			case 3:
			{
				if(startNotNull(start))
				{
						printf("\nEnter employee's id:");
						scanf("%d",&empId);
						current=search(start,empId);
						if(notNull(current))
							showDetails(current);
				}
			}
			break;


			case 4:
			{
				if(startNotNull(start))
				{
					printf("\nEnter employee id:\n");
					scanf("%d",&empId);
					current=searchById(start,empId);
					if(notNull(current))
						showDetails(current);
                    else
                        printf("\nRecord not found\n");
				}
			}
			break;

			case 5:
			{
				if(startNotNull(start))
				{
					printf("\nEnter employee's id that you want to update:");
					scanf("%d",&empId);
					start=update(start,empId);
					displayAll(start);
				}
			}
			break;

			case 6:
			{
				if(startNotNull(start))
				{
					printf("\nEnter employee's id that you want to delete:");
					scanf("%d",&empId);
					start=deleteAt(start,empId);
				}
			}
			break;

			case 7:
				if(startNotNull(start))
					saveFile(start);
			break;


			case 10: printf("Thank You...\n");
			break;
		}

	}while(choice!=exit);

}

node *getNode()
{
	node *employee=NULL;
	employee=(node *)malloc(sizeof(node));
	employee->previous=NULL;
	employee->next=NULL;
	return employee;
}

node *getDetails(node *employee)
{

	empId=empId+1;
	employee->empId=empId;

	printf("\nEnter employee name:");
	scanf("%s",employee->empName);

	printf("\nEnter employee address:");
	scanf("%s",employee->address);

	printf("\nEnter employee's job:");
	scanf("%s",employee->job);

	printf("\nEnter salary:");
	scanf("%ld",&employee->salary);

	return employee;
}

node *insert(node *start,node *employee)
{
	node *current=NULL;

	if(start==NULL)
		start=employee;
	else
	{
		current=start;
		while(current->next!=NULL)
		{
			current=current->next;
		}

		current->next=employee;
		employee->previous=current;
	}

	return start;
}

void showDetails(node *employee)
{
	printf("\nEmployee Id:%d",employee->empId);
	printf("\nEmployee name:%s",employee->empName);
	printf("\nEmployee address:%s",employee->address);
	printf("\nEmployee job:%s",employee->job);
	printf("\nEmployee salary:%ld",employee->salary);
}

void displayAll(node *start)
{
	node *employee=NULL;
	employee=start;

	printf("Employee Details are as follows:\n");
	do
	{
		showDetails(employee);
		printf("\n");
		employee=employee->next;

	}while(employee!=NULL);

}

node *search(node *start,int empId)
{
	node *current=NULL;
	current=start;
	while(current!=NULL)
	{
		if(empId==current->empId)
			break;

		current=current->next;
	}
	return current;
}

node *searchById(node *start, int empId)
{
	long int position=0;
	Index *index;
	node *current=NULL;

	FILE *ptrIndex=NULL;
	FILE *ptrFile=NULL;

	current=getNode();
	index=(Index *)malloc(sizeof(Index));

	ptrIndex=fopen(indexName,"r");
	ptrFile=fopen(fileName,"r");

	while( fread(index,sizeof(Index),1,ptrIndex) == 1)
	{
		position=(index->position-1)*sizeof(node);
		fseek(ptrFile,position,SEEK_SET);
		fread((node *)current,sizeof(node),1,ptrFile);

		if(empId==current->empId)
		{
			return current;
		}
	}

	fclose(ptrFile);
	fclose(ptrIndex);
	return NULL;
}

node *update(node *start,int empId)
{
	int choice=0;
	node *current=NULL;
	current=search(start,empId);

	if(current!=NULL)
	{
		do
		{
			printf("\n1:Update name");
			printf("\n2:Update address");
			printf("\n3:Update job");
			printf("\n4:Update Salary");
			printf("\n5:Go to main menu");
			printf("\nEnter your choice:\n");
			scanf("%d",&choice);

			switch(choice)
			{
				case 1:
					printf("\nEnter new name:");
					scanf("%s",current->empName);
				break;

				case 2:
					printf("\nEnter address:");
					scanf("%s",current->address);
				break;

				case 3:
					printf("\nEnter job:");
					scanf("%s",current->job);
				break;

				case 4:
					printf("\nEnter salary:");
					scanf("%ld",&current->salary);
				break;

				case 5: //exit from loop
				break;

				default: printf("\nINVALID CHOICE\n");
				break;
			}

		}while(choice!=5);
	}

	showDetails(current);
	return start;
}

node *deleteAt(node *start,int empId)
{
	node *current=NULL;

	current=search(start,empId);

	showDetails(current);

	if(current!=NULL)
	{
		if(current==start)
		{
			current=start;
			start=start->next;

			if(notNull(start))
				start->previous=NULL;
		}
		else
		{
			(current->previous)->next=current->next;

			if(current->next!=NULL)
				(current->next)->previous=current->previous;
		}
		free(current);
	}

	return start;
}

void saveFile(node *start)
{
	long int position=1;
	Index *index;
	FILE *ptrIndex=NULL;
	FILE *ptrFile=NULL;
	node *current=NULL;
	current=start;

	index=(Index *)malloc(sizeof(Index));
	ptrFile=fopen(fileName,"w");
	ptrIndex=fopen(indexName,"w");

	if(ptrFile!=NULL)
	{
		while(current!=NULL)
		{
			fwrite(current,sizeof(node),1,ptrFile);

			index->empId=current->empId;
			index->position=position;
			position++;

			fwrite(index,sizeof(Index),1,ptrIndex);

			current=current->next;
		}
	}

	printf("\nYour file has been successfully saved.\n");

	fclose(ptrIndex);
	fclose(ptrFile);
}

node *loadFile()
{
	long int position=1;
	Index *index=NULL;
	node *start=NULL;
	node *current=NULL;
	node *temp=NULL;
	FILE *ptrFile=NULL;
	FILE *ptrIndex=NULL;

	ptrFile=fopen(fileName,"r");
	ptrIndex=fopen(indexName,"r");

	if(ptrFile==NULL || ptrIndex==NULL)
	{
		ptrFile=fopen(fileName,"w+");
		ptrIndex=fopen(indexName,"w+");
	}

	index=(Index *)malloc(sizeof(Index));
	current=getNode();


	while( fread(index,sizeof(Index),1,ptrIndex) == 1)
	{
		position=(index->position-1)*sizeof(node);

		fseek(ptrFile,position,SEEK_SET);

		fread((node *)current,sizeof(node),1,ptrFile);

		current->previous=NULL;
		current->next=NULL;
		start=insert(start,current);

		empId=current->empId;

		current=getNode();
		index=(Index *)malloc(sizeof(Index));
	}

	fclose(ptrIndex);
	fclose(ptrFile);
	return start;
}

int startNotNull(node *start)
{
	if(notNull(start))
		return 1;

	printf("\nYou have to insert employee data first as list is empty.\n");
	return 0;
}

int notNull(node *temp)
{
	if(temp==NULL)
		return 0;
	else
		return 1;
}



