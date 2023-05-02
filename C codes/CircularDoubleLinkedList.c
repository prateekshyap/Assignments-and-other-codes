#include "stdio.h"
#include "stdlib.h"

struct CircularD
{
	struct CircularD *prev;
	int num;
	struct CircularD *next;
};

void create();
void forward_traverse();
void backward_traverse();
void insert();
void delete();
void search();

struct CircularD *start, *last, *temp, *node, *left, *right;

void create()
{
	char ch='y', skip;
	start=(struct CircularD *)malloc(sizeof(struct CircularD));
	temp=start;
	last=start;
	node=start;
	start->prev=start;
	start->next=start;
	printf("\nEnter the information-\n");
	scanf("%d",&start->num);
	printf("\nDo you want to create more?\n");
	skip=getchar();
	ch=getchar();
	while(ch=='y')
	{
		last=(struct CircularD *)malloc(sizeof(struct CircularD));
		node->next=last;
		last->prev=node;
		last->next=start;
		start->prev=last;
		last->prev=node;
		node=node->next;
		printf("\nEnter the information-\n");
		scanf("%d",&last->num);
		printf("\nDo you want to create more?\n");
		skip=getchar();
		ch=getchar();
	}
}

void forward_traverse()
{
	temp=start;
	node=start;
	if(start==NULL)
		printf("No nodes are available");
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

void backward_traverse()
{
	temp=last;
	node=last;
	if(start==NULL)
		printf("No nodes re available");
	else
	{
		printf("\nSee the list\n");
		while(node->prev!=last)
		{
			printf("%d\t",node->num);
			node=node->prev;
		}
		temp=node;
		printf("%d",temp->num);
	}
}

void insert()
{
	left=start;
	right=start;
	printf("\nWhere do you want to insert a node?\n1- At the beginning\n2- At the end\n3- Other positions\nEnter your choice-\n");
	int choice;
	scanf("%d",&choice);
	if(choice==1)
	{
		temp=(struct CircularD *)malloc(sizeof(struct CircularD));
		temp->prev=last;
		last->next=temp;
		start->prev=temp;
		temp->next=start;
		printf("\nEnter the information-\n");
		scanf("%d",&temp->num);
		start=temp;
	}
	else if(choice==2)
	{
		temp=(struct CircularD *)malloc(sizeof(struct CircularD));
		temp->next=start;
		start->prev=temp;
		temp->prev=last;
		last->next=temp;
		printf("\nEnter the information-\n");
		scanf("%d",&temp->num);
		last=temp;
	}
	else if(choice==3)
	{
		int pos, info;
		printf("\nWhere do you want to insert? Enter 1 for before an information and 2 for after an information-\n");
		scanf("%d",&pos);
		if(pos==1)
		{
			temp=(struct CircularD *)malloc(sizeof(struct CircularD));
			printf("\nEnter the new information-\n");
			scanf("%d",&temp->num);
			printf("\nEnter the information before which you want to insert-\n");
			scanf("%d",&info);
			while(right->num!=info)
				right=right->next;
			left=right->prev;
			left->next=temp;
			temp->prev=left;
			temp->next=right;
			right->prev=temp;
		}
		else if(pos==2)
		{
			temp=(struct CircularD *)malloc(sizeof(struct CircularD));
			printf("\nEnter the new information-\n");
			scanf("%d",&temp->num);
			printf("\nEnter the information after which you want to insert-\n");
			scanf("%d",&info);
			while(left->num!=info)
				left=left->next;
			right=left->next;
			left->next=temp;
			temp->prev=left;
			temp->next=right;
			right->prev=temp;
		}
		else
			printf("Wrong input");
	}
	else
		printf("Wrong input");
	forward_traverse();
}

void delete()
{
	left=start;
	right=start;
	temp=start;
	if(start==NULL)
		printf("No nodes are available");
	else
	{
		printf("\nWhere do you want to delete a node from?\n1- From the beginning\n2- From the end\n3- Other positions\nEnter your choice-\n");
		int choice;
		scanf("%d",&choice);
		if(choice==1)
		{
			if(start->next==start&&start->prev==start)
			{
				start->next=NULL;
				start->prev=NULL;
				start=NULL;
				free(temp);
			}
			else
			{
				start=start->next;
				start->prev=last;
				last->next=start;
				temp->prev=NULL;
				temp->next=NULL;
				free(temp);
			}
		}
		else if(choice==2)
		{
			if(start->next==start&&start->prev==start)
			{
				start->next=NULL;
				start->prev=NULL;
				start=NULL;
				free(temp);
			}
			else
			{
				temp=last;
				last=last->prev;
				last->next=start;
				start->prev=last;
				temp->next=NULL;
				temp->prev=NULL;
				free(temp);
			}
		}
		else if(choice==3)
		{
			printf("\nWhich node do you want to delete? Enter the corresponding information-\n");
			int delete;
			scanf("%d",&delete);
			while(temp->num!=delete)
				temp=temp->next;
			left=temp->prev;
			right=temp->next;
			left->next=right;
			right->prev=left;
			temp->prev=NULL;
			temp->next=NULL;
			free(temp);
		}
		else
			printf("Wrong input");
		forward_traverse();
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
	printf("\t\t\tCREATE A DOUBLE LINKED LIST");
	create();
	forward_traverse();
	while(1)
	{
		printf("\n\t\t\tSEE THE OPTIONS\n\t\t\t1- Insert node\n\t\t\t2- Delete node\n\t\t\t3- Search\n\t\t\t4- See the list\n\t\t\t5- See the reverse list\n\t\t\t6- Quit\n\t\t\tChoose your option\n");
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
				forward_traverse();
				break;
			case 5:
				backward_traverse();
				break;
			case 6:
				printf("\t\t\tTHANKS FOR USING MY APPLICATION!");
				return;
				break;
			default:
				printf("INVALID INPUT");
				break;
		}
	}
}