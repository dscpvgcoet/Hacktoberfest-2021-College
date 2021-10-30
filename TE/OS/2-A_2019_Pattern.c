//Rivji Kulkarni
//TE IT 9078
//ASSIGNMENT 2A-1
//Problem Statement : Implement the C program in which main program accepts the integers to be sorted. Main program
//uses the FORK system call to create a new process called a child process. Parent process sorts the
//integers using sorting algorithm and waits for child process using WAIT system call to sort the integers
//using any sorting algorithm. Also demonstrate zombie and orphan states.


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int split(int[],int,int);
void quickSort(int*,int,int);

void mergeSort(int arr[],int low, int mid, int high) {
	int i,j,k,l,b[20];
	l=low;
	i=low;
	j=mid+1;
	while((l<=mid)&&(j<=high)) {
		if(arr[l]<=arr[j]) {
			b[i]=arr[l];
			l++;
		}
		else{
			b[i]=arr[j];
			j++;
		}
		i++;
	}
	
	if(l>mid){
		for(k=j;k<=high;k++){
			b[i]=arr[k];
			i++;
		}
	}
	else{
		for(k=l;k<=mid;k++){
			b[i]=arr[k];
			i++;
		}
	}
	
	for(k=low;k<=high;k++){
		arr[k]=b[k];
	}
}

void partition(int arr[],int low, int high) {
	int mid;
	if(low<high){
		double temp;
		mid=(low+high)/2;
		partition(arr,low,mid);
		partition(arr,mid+1,high);
		mergeSort(arr,low,mid,high);
	}
}

void display(int a[],int size){
	int i;
	for(i=0;i<size;i++){
		printf("%d\t\t",a[i]);
	}
	printf("\n");
}

int main(){
	int pid,child_pid;
	int size,i,status;

	printf("No. of intergers to be sorted : ");
	scanf("%d",&size);
	
	int a[size];
	int pArr[size];
	int cArr[size];
	
	for(i=0;i<size;i++){
		printf("Input Value %d: ",(i+1));
		scanf("%d",&a[i]);
		pArr[i]=a[i];
		cArr[i]=a[i];
	}
	
	printf("Your integers are: ");
	display(a,size);
	

	pid=getpid();
	printf("The current process id is: %d",pid);
	

	printf("\n[Forking Child Process... ] \n");
	child_pid=fork();
	
	if (child_pid<0) {
		
		printf("\nChild Process Creation Failed");
			exit(-1);
	}
	else if (child_pid==0) {
		/* Child Process */
		printf("\nChild Process\n");
		printf("\nThe child process is %d",getpid());
		printf("Sorting...\n");
		quickSort(cArr,0,size-1);
		printf("The sorted list by child process is: \n");
		display(cArr,size);
		printf("Child process completed\n");
		sleep(10);
		printf("Parent of child process is %d",getppid());
	}
	else {
		
		printf("Parent process %d started\n",getpid());
		printf("Parent of parent is %d\n",getppid());
		sleep(30);
		printf("The parent process\n");
		printf("Parent %d is sorting the list of integers by merge sort\n",pid);
		partition(pArr,0,size-1);
		printf("The sorted list by parent: \n");
		display(pArr,size);
		sleep(20);
		printf("Parent Process completed...\n");
	}
	return 0;
}

int split( int a[], int lower, int upper ) {
	int i,p,q,t;
	p = lower+1;
	q=upper;
	i=a[lower];
	
	while(q>=p) {
		while(a[p]<i)
		p++;
		while(a[q]>i)
		q--;
		
		if( q>p ){
			t=a[p];
			a[p]=a[q];
			a[q]=t;
		}
	}
	 t=a[lower];
	 a[lower]=a[q];
	 a[q]=t;
	 return q;
}

void quickSort(int a[], int lower, int upper){
	int i;
	if(upper>lower){
		i=split(a,lower,upper);
		quickSort(a,lower,i-1);
		quickSort(a,i+1,upper);
	}
}





