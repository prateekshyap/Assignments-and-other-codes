#include "stdio.h"
#include "stdlib.h"

int top=-1, SIZE=10;
int num[10];

void push();
void pop();
void display();

void push()
{
	if(top==SIZE-1)
		printf("STACK OVERFLOW\n");
	else
	{
		++top;
		printf("Enter the information-\n");
		scanf("%d",&num[top]);
		display();
	}
}

void pop()
{
	if(top==-1)
		printf("STACK UNDERFLOW\n");
	else
	{
		printf("%d is popped\n",num[top]);
		--top;
		display();
	}
}

void display()
{
	if(top==-1)
		printf("STACK IS EMPTY\n");
	else
	{
		int i;
		printf("The stack is-\n");
		for(i=9;i>=0;i--)
		{
			if(i<=top)
				printf("\t\t\t|\t%d\t|\n",num[i]);
			else
				printf("\t\t\t|\t\t|\n");
		}
	}
}

void main()
{
	printf("\t\t\tSTACK\n");
	printf("Stack size is 10\n");
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