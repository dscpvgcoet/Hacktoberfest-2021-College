/*
Name : Maitreya Kanitkar
TE-IT   8084
*/

#include<iostream>
using namespace std;

void maxmin(int arr[],int l,int h,int &min,int &max)
{
    if(l==h)
    {
        if(max<arr[l]) 
		max=arr[l];

	    if(min>arr[h])   		
		min=arr[h];

        return;
    } 
     
    if(l==h-1)
    {
        if(arr[l]<arr[h])
        { 
            if(min>arr[l])
            min=arr[l];

            if(max<arr[h])
            max=arr[h];
        } 

        else
        {    
            if(min>arr[h])
			min=arr[h];
			
			if(max<arr[l])    	
			max=arr[l];
        }
        return;
    } 

    int mid=(l+h)/2;
    maxmin(arr,l,mid,min,max);
    maxmin(arr,mid+1,h,min,max);
}

int main()
{ 
    int n,max=0,min=99999;

    cout<<"Enter size of the array :v";
    cin>>n;

    int arr[n], h=n-1, l=0;
     
    cout<<"\nEnter elements of the array :\n";
    for(int i=0;i<n;i++)
    cin>>arr[i];

    maxmin(arr,l,h,min,max);
    cout<<"Maximum value in array : "<<max<<"\nMinimum value in array : "<<min;
    return 0;
}

/*

OUTPUT :

Enter size of the array : 10

Enter elements of the array :
99
34
12
56
78
9
45
67
23
88
Maximum value in array : 99
Minimum value in array : 9

*/
