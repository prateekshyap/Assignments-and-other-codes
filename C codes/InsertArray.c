#include"stdio.h"
void main()
{
	int num[50], dim, i, ins, pos;
	printf("How many numbers?");
	scanf("%d",&dim);
	printf("Enter the numbers- ");
	for(i=0;i<dim;i++)
		scanf("%d",&num[i]);
	printf("The array is-");
	for(i=0;i<dim;i++)
		printf("%d ",num[i]);
	printf("Enter the element and its position you want to insert- ");
	scanf("%d%d",&ins,&pos);
	--pos;
	++dim;
	for(i=dim-1;i>pos;i--)
		num[i]=num[i-1];
	num[pos]=ins;
	printf("The array is-");
	for(i=0;i<dim;i++)
		printf("%d ",num[i]);
}