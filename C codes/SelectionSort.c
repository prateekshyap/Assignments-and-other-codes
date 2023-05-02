#include <stdio.h>
#include <stdlib.h>

void main()
{
	int dim, temp, i, j;
	printf("How many numbers?\n");
	scanf("%d",&dim);
	int num[dim];
	printf("Enter the numbers-\n");
	for(i=0;i<dim;i++)
		scanf("%d",&num[i]);
	printf("Before sorting-\n");
	for(i=0;i<dim;i++)
		printf("%d\t",num[i]);
	printf("\n");
	for(i=0;i<dim;i++)
	{
		for(j=i+1;j<dim;j++)
		{
			if(num[i]>num[j])
			{
				temp=num[i];
				num[i]=num[j];
				num[j]=temp;
			}
		}
	}
	printf("After sorting-\n");
	for(i=0;i<dim;i++)
		printf("%d\t",num[i]);
}