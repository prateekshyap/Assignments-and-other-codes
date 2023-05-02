#include<stdio.h>
void main()
{
	int dim, i, j, swp;
	printf("How many numbers?\n");
	scanf("%d",&dim);
	int num[dim];
	printf("Enter the numbers-\n");
	for(i=0;i<dim;i++)
		scanf("%d",&num[i]);
	printf("The array before sorting-\n");
	for(i=0;i<dim;i++)
		printf("%d ",num[i]);
	for(i=0;i<dim;i++)
	{
		for(j=1;j<=dim-i;j++)
		{
			if(num[j-1]>num[j])
			{
				swp=num[j-1];
				num[j-1]=num[j];
				num[j]=swp;
			}
		}
	}
	printf("\nThe array after sorting-\n");
	for(i=0;i<dim;i++)
		printf("%d ",num[i]);
}