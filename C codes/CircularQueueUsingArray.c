#include <stdio.h>
#include <stdlib.h>

int num[10];
int SIZE=10, front=-1, rear=-1;

void enqueue();
void dequeue();
void display();

void enqueue()
{
	if(rear==SIZE-1&&front==0)
		printf("Queue overflow\n");
	else if(front==-1&&rear==-1)
	{
		front=rear=0;
		printf("Enter the information-\n");
		scanf("%d",&num[rear]);a
		display();
	}
	else
	{
		if(rear==SIZE-1&&front!=0)
		{
			rear=0;
			printf("Enter the information-\n");
			scanf("%d",&num[rear]);
			display();
		}
		else
		{
			if(front==rear+1)
				printf("Queue overflow\n");
			else
			{
				++rear;
				printf("Enter the information-\n");
				scanf("%d",&num[rear]);
				display();
			}
		}
	}
}

void dequeue()
{
	if(front==-1&&rear==-1)
		printf("Queue underflow\n");
	else if(front==rear)
	{
		printf("%d is deleted\n",num[front]);
		front=rear=-1;
		display();
	}
	else
	{
		if(front==SIZE-1)
		{
			printf("%d is deleted\n",num[front]);
			front=0;
			display();
		}
		else
		{
			printf("%d is deleted\n",num[front]);
			front=front+1;
			display();
		}
	}
}

void display()
{
	int i;
	if(front==-1&&rear==-1)
		printf("Queue is empty\n");
	else
	{
		if(front<=rear)
		{
			printf("The queue is-\n");
			for(i=front;i<=rear;i++)
				printf("%d\t",num[i]);
		}
		else
		{
			printf("The queue is-\n");
			for(i=front;i<SIZE;i++)
				printf("%d\t",num[i]);
			for(i=0;i<=rear;i++)
				printf("%d\t",num[i]);
		}
	}
}

void main()
{
	printf("\t\t\tQUEUE\n");
	printf("Queue size is 10\n");
	while(1)
	{
		int choice;
		printf("\n\t\t\tSEE THE OPTIONS\n\t\t\t1- Enqueue\n\t\t\t2- Dequeue\n\t\t\t3- Display\n\t\t\t4- Quit\n\t\t\tEnter your choice-\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				enqueue();
				break;
			case 2:
				dequeue();
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