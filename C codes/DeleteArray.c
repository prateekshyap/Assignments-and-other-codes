#include"stdio.h"
void main()
{
	int num[50], dim, i, pos;
	printf("How many numbers?\n");
	scanf("%d",&dim);
	printf("Enter the numbers-\n");
	for(i=0;i<dim;i++)
		scanf("%d",&num[i]);
	printf("The array is-\n");
	for(i=0;i<dim;i++)
		printf("%d ",num[i]);
	printf("\nEnter the position you want to delete-\n");
	scanf("%d",&pos);
	--pos;
	--dim;
	for(i=pos;i<dim;i++)
		num[i]=num[i+1];
	printf("The array is-\n");
	for(i=0;i<dim;i++)
		printf("%d ",num[i]);
}