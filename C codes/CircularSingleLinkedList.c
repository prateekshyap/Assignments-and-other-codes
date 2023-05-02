#include"stdio.h"
#include"stdlib.h"

struct CircularS
{
	int num;
	struct CircularS *next;
};

void create();
void traverse();
void insert();
void delete();
void search();

struct CircularS *start, *last, *temp, *node, *left, *right;

void create()
{
	char ch='y', skip;
	start=(struct CircularS *)malloc(sizeof(struct CircularS));
	temp=start;
	node=start;
	start->next=start;
	printf("\nEnter the information-\n");
	scanf("%d",&start->num);
	printf("\nDo you want to create more?\n");
	skip=getchar();
	ch=getchar();
	while(ch=='y')
	{
		node->next=(struct CircularS *)malloc(sizeof(struct CircularS));
		node=node->next;
		last=node;
		printf("\nEnter the information-\n");
		scanf("%d",&node->num);
		node->next=start;
		printf("\nDo you want to create more?\n");
		skip=getchar();
		ch=getchar();
	}
}

void traverse()
{
	temp=start;
	node=start;
	if(start==NULL)
		printf("\nNo nodes are available\n");
	else
	{
		printf("\nSee the list\n");
		while(node->next!=start)
		{
			printf("%d\t",node->num);
			node=node->next;
		}
		temp=node;
		printf("%d",temp->num);
	}
}

void insert()
{
	temp=start;
	node=start;
	left=start;
	right=start;
	printf("\nWhere do you want to insert a node?\n1- At the beginning\n2- At the end\n3- Other positions\nEnter your choice-\n");
	int choice;
	scanf("%d",&choice);
	if(choice==1)
	{
		temp=(struct CircularS *)malloc(sizeof(struct CircularS));
		printf("\nEnter the information-\n");
		scanf("%d",&temp->num);
		temp->next=start;
		start=temp;
		last->next=temp;
	}
	else if(choice==2)
	{
		temp=(struct CircularS *)malloc(sizeof(struct CircularS));
		printf("\nEnter the information-\n");
		scanf("%d",&temp->num);
		temp->next=start;
		last->next=temp;
		last=temp;
	}
	else if(choice==3)
	{
		temp=(struct CircularS *)malloc(sizeof(struct CircularS));
		printf("\nEnter the information-\n");
		scanf("%d",&temp->num);
		printf("\nEnter the information after which you want to insert the new information-\n");
		int info;
		scanf("%d",&info);
		while(left->num!=info)
			left=left->next;
		right=left->next;
		temp->next=right;
		left->next=temp;
	}
	else
		printf("Wrong input");
	traverse();
}

void delete()
{
	temp=start;
	node=start;
	left=start;
	right=start;
	if(start==NULL)
		printf("No nodes are available");
	else
	{
		int choice;
		printf("\nWhere do you want to delete a node from?\n1- From the beginning\n2- From the end\n3- Other positions\nEnter your choice-\n");
		scanf("%d",&choice);
		if(choice==1)
		{
			if(start->next==start)
			{
				start=start->next;
				last->next=start;
				temp->next=NULL;
				start=NULL;
				free(temp);
			}
			else
			{
				start=start->next;
				last->next=start;
				temp->next=NULL;
				free(temp);
			}
		}
		else if(choice==2)
		{
			if(start->next==start)
			{
				start=start->next;
				last->next=start;
				temp->next=NULL;
				start=NULL;
				free(temp);
			}
			else
			{
				node=last;
				while(temp->next!=last)
					temp=temp->next;
				last=temp;
				temp=node;
				last->next=start;
				temp->next=NULL;
				free(temp);
			}
		}
		else if(choice==3)
		{
			printf("\nWhich node do you want to delete? Enter the corresponding information-\n");
			int delete;
			scanf("%d",&delete);
			while(left->next->num!=delete)
				left=left->next;
			temp=left->next;
			right=temp->next;
			left->next=right;
			temp->next=NULL;
			free(temp);
		}
		else
			printf("Wrong input");
		traverse();
	}
}

void search()
{
	node=start;
	temp=start;
	int search, count=1, found=1;
	if(start==NULL)
		printf("No nodes are available");
	else
	{
		printf("\nWhich information do you want to search?\n");
		scanf("%d",&search);
		while(temp->next!=start)
		{
			temp=temp->next;
			count++;
		}
		while(node->next!=start)
		{
			if(node->num!=search)
			{
				node=node->next;
				found++;
			}
		}
		if(count==found&&temp->num!=search)
			printf("\nNot found\n");
		else
			printf("\nFound at %d position\n",found);
	}
}

void main()
{
	printf("\t\t\tCREATE A CIRCULAR SINGLE LINKED LIST");
	create();
	traverse();
	while(1)
	{
		printf("\n\t\t\tSEE THE OPTIONS\n\t\t\t1- Insert node\n\t\t\t2- Delete node\n\t\t\t3- Search\n\t\t\t4- See the list\n\t\t\t5- Quit\n\t\t\tChoose your option\n");
		int choice;
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				insert();
				break;
			case 2:
				delete();
				break;
			case 3:
				search();
				break;
			case 4:
				traverse();
				break;
			case 5:
				printf("\t\t\tTHANKS FOR USING MY APPLICATION!");
				return;
				break;
			default:
				printf("INVALID INPUT");
				break;
		}
	}
}