#include<stdio.h>
#include<stdlib.h>

void heap_sort(int, int[]);
void heap_adjust(int, int, int[]);

int main()
{
	int i, size;
	printf("Enter the dimesion of the array-");
	scanf("%d",&size);
	int arr[size];
	printf("Enter the elements for the array-");
	for(i=0;i<size;i++)
		scanf("%d",&arr[i]);
	printf("The array before sorting-");
	for(i=0;i<size;i++)
		printf("%d\t",arr[i]);
	printf("\n");
	heap_sort(size,arr);
	printf("The array after sorting-");
	for(i=0;i<size;i++)
		printf("%d\t",arr[i]);
	printf("\n");
}

void heap_sort(int s, int a[])
{
	int i=0, t=0, j=0;
	for(i=s/2-1;i>=0;i--)
		heap_adjust(s,i,a);
	for(i=s-1;i>=0;i--)
	{
		t=a[i];
		a[i]=a[0];
		a[0]=t;
		heap_adjust(i,0,a);
		printf("Iteration %d-\n",i+1);
		for(j=0;j<s;j++)
			printf("%d\t",a[j]);
		printf("\n");
	}
}

void heap_adjust(int lim, int x, int b[])
{
	int large=x, left=2*x+1, right=2*x+2, t=0;
	if(left<lim && b[left]>b[large])
		large=left;
	if(right<lim && b[right]>b[large])
		large=right;
	if(large!=x)
	{
		t=b[large];
		b[large]=b[x];
		b[x]=t;
		heap_adjust(lim,large,b);
	}
}