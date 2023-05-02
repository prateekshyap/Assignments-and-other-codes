#include <stdio.h>
#include <stdlib.h>

struct Queue
{
	int num;
	struct Queue *next;
};

void enqueue();
void dequeue();
void display();

struct Queue *front=NULL, *rear=NULL, *node, *temp;

void enqueue()
{
		temp=(struct Queue *)malloc(sizeof(struct Queue));
		printf("Enter the information-\n");
		scanf("%d",&temp->num);
		if(front==NULL&&rear==NULL)
		{
			temp->next=NULL;
			front=temp;
			rear=temp;
		}
		else
		{
			temp->next=NULL;
			rear->next=temp;
			rear=rear->next;
		}
		display();
}

void dequeue()
{
	if(front==NULL&&rear==NULL)
		printf("Queue underflow\n");
	else if(front==rear)
	{
		printf("%d is deleted\n",front->num);
		temp=front;
		front=NULL;
		rear=NULL;
		free(temp);
		display();
	}
	else
	{
		printf("%d is deleted\n",front->num);
		temp=front;
		front=front->next;
		temp->next=NULL;
		free(temp);
		display();
	}
}

void display()
{
	if(front==NULL&&rear==NULL)
		printf("Queue is empty\n");
	else
	{
		printf("The queue is-\n");
		node=front;
		while(node!=NULL)
		{
			printf("%d\t",node->num);
			node=node->next;
		}
	}
}

void main()
{
	printf("\t\t\tQUEUE\n");
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