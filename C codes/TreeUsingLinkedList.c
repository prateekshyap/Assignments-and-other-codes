#include "stdio.h"
#include "stdlib.h"

struct Tree
{
	struct Tree *left;
	int num;
	struct Tree *right;
};

void insert();
void preorder(struct Tree *);
void inorder(struct Tree *);
void postorder(struct Tree *);
void smallest();
void largest();
void delete();
int total_elements(struct Tree *);
void delete_tree(struct Tree *);

struct Tree *root=NULL, *temp, *node, *current, *parent;

void insert()
{
	temp=(struct Tree *)malloc(sizeof(struct Tree));
	printf("Enter the information-\n");
	scanf("%d",&temp->num);
	temp->right=NULL;
	temp->left=NULL;
	if(root==NULL)
	{
		root=temp;
		node=root;
	}
	else
	{
		node=root;
		while(node!=NULL)
		{
			parent=node;
			if(node->num<temp->num)
				node=node->right;
			else
				node=node->left;
		}
		if(temp->num<parent->num)
			parent->left=temp;
		else
			parent->right=temp;
	}
	inorder(root);
}

void preorder(struct Tree *ptr)
{
	if(ptr!=NULL)
	{		
		printf("%d\t",ptr->num);
		preorder(ptr->left);
		preorder(ptr->right);
	}
}

void inorder(struct Tree *ptr)
{
	if(ptr!=NULL)
	{
		inorder(ptr->left);
		printf("%d\t",ptr->num);
		inorder(ptr->right);
	}
}

void postorder(struct Tree *ptr)
{
	if(ptr!=NULL)
	{
		postorder(ptr->left);
		postorder(ptr->right);
		printf("%d\t",ptr->num);
	}
}

void smallest()
{
	node=root;
	while(node!=NULL)
	{
		parent=node;
		node=node->left;
	}
	printf("The smallest number is %d",parent->num);
}

void largest()
{
	node=root;
	while(node!=NULL)
	{
		parent=node;
		node=node->right;
	}
	printf("The largest number is %d",parent->num);
}

void delete()
{
	int del;
	printf("Which information do you want to delete?\n");
	scanf("%d",&del);
	node=root;
	while(node->num!=del)
	{
		parent=node;
		if(del<node->num)
			node=node->left;
		else
			node=node->right;
	}
	if(node->left==NULL&&node->right==NULL)
	{
		printf("%d is deleted\n",node->num);
		if(del<parent->num)
			parent->left=NULL;
		else
			parent->right=NULL;
		free(node);
	}
	else if(node->left==NULL||node->right==NULL)
	{
		printf("%d is deleted\n",node->num);
		temp=node;
		if(node->left==NULL)
			node=node->right;
		else
			node=node->left;
		if(parent->left==temp)
		{
			parent->left=node;
			free(temp);
		}
		else
		{
			parent->right=node;
			free(temp);
		}
	}
	else if(node->left!=NULL&&node->right!=NULL)
	{
		printf("%d is deleted\n",node->num);
		temp=node;
		temp=temp->right;
		while(temp!=NULL)
		{
			current=temp;
			temp=temp->left;
		}
		node->num=current->num;
		temp=node;
		temp=temp->right;
		while(temp->num!=current->num)
		{
			parent=temp;
			temp=temp->left;
		}
		if(parent->left==current)
			parent->left=NULL;
		else
			parent->right=NULL;
		free(current);
	}
	inorder(root);
}

int total_elements(struct Tree *ptr)
{
	if(ptr==NULL)
		return 0;
	else
		return (total_elements(ptr->left)+total_elements(ptr->right)+1);
}

void delete_tree(struct Tree *ptr)
{
	if(ptr!=NULL)
	{
		delete_tree(ptr->left);
		delete_tree(ptr->right);
		free(ptr);
	}
	root=NULL;
}

void main()
{
	printf("\t\t\tTREE\n");
	while(1)
	{
		int choice;
		printf("\n\t\t\tSEE THE OPTIONS\n\t\t\t1- Insert\n\t\t\t2- Preorder Traversal\n\t\t\t3- Inorder traversal\n\t\t\t4- Post order traversal\n\t\t\t5- Find the smallest element\n\t\t\t6- Find the largest element\n\t\t\t7- Delete an element\n\t\t\t8- Count the total number of nodes-\n\t\t\t9- Delete the tree\n\t\t\t10- Quit\n\t\t\tEnter your choice-\n");
		scanf("%d",&choice);
		switch (choice)
		{
			case 1:
				insert();
				break;
			case 2:
				if(root==NULL)
					printf("Tree is empty\n");
				else
					preorder(root);
				break;
			case 3:
				if(root==NULL)
					printf("Tree is empty\n");
				else
					inorder(root);
				break;
			case 4:
				if(root==NULL)
					printf("Tree is empty\n");
				else
					postorder(root);
				break;
			case 5:
				smallest();
				break;
			case 6:
				largest();
				break;
			case 7:
				delete();
				break;
			case 8:
				printf("%d",total_elements(root));
				break;
			case 9:
				if(root==NULL)
					printf("Tree is empty\n");
				else
					delete_tree(root);
				break;
			case 10:
				printf("THANKS FOR USING MY APPLICATION!\n");
				return;
				break;
			default:
				printf("INVALID INPUT");
				break;
		}
	}
}