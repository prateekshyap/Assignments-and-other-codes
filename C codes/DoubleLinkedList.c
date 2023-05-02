#include "stdio.h"
#include "stdlib.h"

struct Double
{
	struct Double *prev;
	int num;
	struct Double *next;
};

void create();
void forward_traverse();
void backward_traverse();
void insert();
void delete();
void search();

struct Double *start, *last, *temp, *node, *left, *right;

void create()
{
	char ch='y', skip;
	start=(struct Double *)malloc(sizeof(struct Double));
	temp=start;
	last=start;
	node=start;
	start->prev=NULL;
	start->next=NULL;
	printf("\nEnter the information-\n");
	scanf("%d",&start->num);
	printf("\nDo you want to create more?\n");
	skip=getchar();
	ch=getchar();
	while(ch=='y')
	{
		last=(struct Double *)malloc(sizeof(struct Double));
		node->next=last;
		last->prev=node;
		node=node->next;
		printf("\nEnter the information-\n");
		scanf("%d",&last->num);
		last->next=NULL;
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
		while(node!=NULL)
		{
			printf("%d\t",node->num);
			node=node->next;
		}
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
		while(node!=NULL)
		{
			printf("%d\t",node->num);
			node=node->prev;
		}
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
		temp=(struct Double *)malloc(sizeof(struct Double));
		temp->prev=NULL;
		printf("\nEnter the information-\n");
		scanf("%d",&temp->num);
		temp->next=start;
		start->prev=temp;
		start=temp;
	}
	else if(choice==2)
	{
		temp=(struct Double *)malloc(sizeof(struct Double));
		temp->next=NULL;
		printf("\nEnter the information-\n");
		scanf("%d",&temp->num);
		temp->prev=last;
		last->next=temp;
		last=temp;
	}
	else if(choice==3)
	{
		int pos, info;
		printf("\nWhere do you want to insert? Enter 1 for before an information and 2 for after an information-\n");
		scanf("%d",&pos);
		if(pos==1)
		{
			temp=(struct Double *)malloc(sizeof(struct Double));
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
			temp=(struct Double *)malloc(sizeof(struct Double));
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
			start=start->next;
			start->prev=NULL;
			temp->next=NULL;
			free(temp);
		}
		else if(choice==2)
		{
			if(start->next==NULL)
			{
				temp=start;
				start=NULL;
				free(temp);
			}
			else
			{
				temp=last;
				last=last->prev;
				last->next=NULL;
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
		while(temp->next!=NULL)
		{
			temp=temp->next;
			count++;
		}
		while(node->next!=NULL)
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