#include "stdio.h"
#include "stdlib.h"

struct Stack
{
	int num;
	struct Stack *next;
};

void push();
void pop();
void display();

struct Stack *temp, *node, *top=NULL;

void push()
{
	temp=(struct Stack *)malloc(sizeof(struct Stack));
	printf("Enter the information-\n");
	scanf("%d",&temp->num);
	if(top==NULL)
	{
		temp->next=NULL;
		top=temp;
	}
	else
	{
		temp->next=top;
		top=temp;
	}
	display();
}

void pop()
{
	temp=top;
	if(top==NULL)
		printf("STACK UNDERFLOW\n");
	else if(top->next==NULL)
	{
		printf("%d is popped\n",temp->num);
		top=NULL;
		free(temp);
		display();
	}
	else
	{
		printf("%d is popped\n",temp->num);
		top=top->next;
		temp->next=NULL;
		free(temp);
		display();
	}
}

void display()
{
	if(top==NULL)
		printf("STACK IS EMPTY\n");
	else
	{
		printf("The stack is-\n");
		node=top;
		while(node!=NULL)
		{
			printf("\t\t\t|\t%d\t|\n",node->num);
			node=node->next;
		}
	}
}

void main()
{
	printf("\t\t\tSTACK\n");
	while(1)
	{
		int choice;
		printf("\n\t\t\tSEE THE OPTIONS\n\t\t\t1- Push\n\t\t\t2- Pop\n\t\t\t3- Display\n\t\t\t4- Quit\n\t\t\tEnter your choice-\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				push();
				break;
			case 2:
				pop();
				break;
			case 3:
				display();
				break;
			case 4:
				printf("\t\t\tTHANKS FOR USING MY APPLICATION!!!");
				return;
				break;
			default:
				printf("INVALID INPUT\n");
				break;
		}
	}
}