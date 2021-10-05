/*

Name : Maitreya Kanitkar
class :TE-IT
Roll no. : 8084

OS Assignment 2A

*/




#include <stdio.h>
#include <unistd.h>


//Value Swapping function
void swap(int *x,int *y)
{
 *x=*x+*y;
 *y=*x-*y;
 *x=*x-*y;
}



//Quicksort sub function
int qsort(int arr[],int f,int l)
{
 int pivot=arr[l],i=f-1,k;

 for(int j=f;j<=l;j++)
 {
  if(arr[j]<pivot)
  {
   i++;
   k=arr[i];
   arr[i]=arr[j];
   arr[j]=k;
  }
 }
 k=arr[i+1];
 arr[i+1]=arr[l];
 arr[l]=k;

 return (i+1);
}




//Quick sort main function
void quicksort(int arr[],int f,int l)
{
 if(f<l)
 {
  int p=qsort(arr,f,l);
  quicksort(arr,f,p-1);
  quicksort(arr,p+1,l);
 }
}



//Mergesort function
void mergesort(int list[],int low,int mid,int high)
{
 int i=low,mi=mid+1,lo=low,temp[50];

 while(lo<=mid && mi<=high)
 {
  if(list[lo]<=list[mi])
  {
   temp[i]=list[lo];
   lo++;
  }
		
  else
  {
   temp[i]=list[mi];
   mi++;
  }
  
  i++;
 }

 if(lo>mid)
 for(int k=mi;k<=high;k++)
 {
  temp[i]=list[k];
  i++;
 }

 else
 for(int k=lo;k<=mid;k++)
 {
  temp[i]=list[k];
  i++;
 }
	
 for(int k=low;k<=high;k++)
 list[k]=temp[k];
}



//Partition function(for mergesort)
void partition(int arr[],int l,int h)
{
 if(l<h)
 {
  int m=(l+h)/2;
  partition(arr,l,m);
  partition(arr,m+1,h);
  mergesort(arr,l,m,h);
 }
}



//Display function
void display(int arr[],int n)
{
 for(int i=0;i<n;i++)
 printf("%d\t",arr[i]);

 printf("\n");
}



//Main function
int main()
{
 pid_t pid;
 int num[20],count;
	
 printf("\nEnter no. of integers to be sorted: ");
 scanf("%d",&count);
	
 printf("\nEnter integers\n");
 
 for(int i=0;i<count;i++)
 scanf("%d",&num[i]);

 pid=fork();
	
 if(pid>0)
 {
  wait(NULL);
  printf("\n\nInside parent process");
  printf("\nProcess ID:%d",getpid());
  printf("\n\n");
		
  quicksort(num,0,count-1);
		
  printf("\nIntegers sorted using Quicksort\n");
  display(num,count);
  printf("\n");
 }
	
 else if(pid==0)
 {
  printf("\n\nInside child process");
  printf("\nProcess ID:%d",getpid());
  printf("\n\n");
		
  partition(num,0,count-1);
		
  printf("\nIntegers sorted using Mergesort\n");
  display(num,count);
  printf("\n");
 }
	
 else
 printf("\nChild process could not be created!\n");
		
 return 0;
}







/*Output:-

Enter no. of integers to be sorted: 7

Enter integers
7
6
5
4
3
2
1


Inside child process
Process ID:4259


Integers sorted using Mergesort
1	2	3	4	5	6	7	



Inside parent process
Process ID:4258


Integers sorted using Quicksort
1	2	3	4	5	6	7

*/





//Zombie process program

#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
 pid_t pid;
 
 pid=fork();
 
 if(pid>0)
 {
  sleep(10);
  printf("\nIn parent process\n");
 }
 
 else
 {
  printf("\nIn child process\n");
  exit(0);
 }
 
 return 0;
}


/*Output :

In child process

In parent process

*/





//Orphan process program

#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
 pid_t pid;
 
 pid=fork();
 
 if(pid>0)
 printf("\nIn parent process\n");
 
 else
 {
  sleep(10);
  printf("\nIn child process\n");
  exit(0);
 }
 
 return 0;
}



/*Output :

In parent process

*/



