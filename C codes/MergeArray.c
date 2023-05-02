#include"stdio.h"
void main()
{
	int dim1, dim2, i;
	printf("How many numbers are there in 1st array?\n");
	scanf("%d",&dim1);
	printf("How many numbers are there in 2nd array?\n");
	scanf("%d",&dim2);
	int num1[dim1], num2[dim2];
	printf("Enter the numbers for the 1st array-\n");
	for(i=0;i<dim1;i++)
		scanf("%d",&num1[i]);
	printf("Enter the numbers for the 2nd array-\n");
	for(i=0;i<dim2;i++)
		scanf("%d",&num2[i]);
	int dim=dim1+dim2;
	int merge[dim];
	int j=0;
	for(i=0;i<dim1;i++)
	{
		merge[j]=num1[i];
		j++;
	}
	for(i=0;i<dim2;i++)
	{
		merge[j]=num2[i];
		j++;
	}
	printf("The 1st array is-\n");
	for(i=0;i<dim1;i++)
		printf("%d ",num1[i]);
	printf("\nThe 2nd array is-\n");
	for(i=0;i<dim2;i++)
		printf("%d ",num2[i]);
	printf("\nThe merged array is-\n");
	for(i=0;i<dim;i++)
		printf("%d ",merge[i]);
}