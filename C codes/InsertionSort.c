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
	for(i=1;i<dim;i++)
	{
		temp=num[i];
		j=i-1;
		while(temp<num[j]&&j>=0)
		{
			num[j+1]=num[j];
			j--;
		}
		num[j+1]=temp;
	}
	printf("After sorting-\n");
	for(i=0;i<dim;i++)
		printf("%d\t",num[i]);
}