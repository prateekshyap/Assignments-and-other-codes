#include"stdio.h"
void main()
{
	int dim, i, search, found;
	printf("How many numbers?\n");
	scanf("%d",&dim);
	int num[dim];
	printf("Enter the numbers-\n");
	for(i=0;i<dim;i++)
		scanf("%d",&num[i]);
	printf("The array is-\n");
	for(i=0;i<dim;i++)
		printf("%d ",num[i]);
	printf("\nEnter the number you want to search-\n");
	scanf("%d",&search);
	i=0;
	while(search!=num[i])
	{
		i++;
	}
	found=i+1;
	if(found<=dim+1)
		printf("Found at %d position",found);
	else
		printf("Not found");
}