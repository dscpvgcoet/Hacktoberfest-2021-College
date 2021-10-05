/*

Maitreya Kanitkat
TE-IT 8084

DAA Assignment 4 (Travelling Salesman Problem)

*/


#include<iostream>
using namespace std;

class tsp
{
    public:
    int arr[10][10], completed_node[10], n, cost=0;
 
    void input()
    {
	    cout<<"Enter the number of nodes : ";
	    cin>>n;
 
	    cout<<"\n\nEnter the cost matrix-\n";
 
	    for(int i=0; i<n; i++)
	    {
		    cout<<"\nEnter the elements of row "<<i+1<<" :\n";
 
		    for(int j=0; j<n; j++)
		    cin>>arr[i][j];
 
		    completed_node[i]=0;
	    }
 
	    cout<<"\n\nThe cost matrix is :\n";
 
	    for(int i=0; i<n; i++)
	    {
		    for(int j=0; j<n; j++)
		    cout<<arr[i][j]<<" ";

            cout<<endl;
	    }
    }
 
    int least(int node)
    {
	    int i,n_node=999,min=999,min1;
 
	    for(int i=0; i<n; i++)
        if(arr[node][i]!=0 && completed_node[i]==0)
	    if(arr[node][i]+arr[i][node]<min)
	    {
		    min=arr[i][0]+arr[node][i];
		    min1=arr[node][i];
		    n_node=i;
	    }
 
	    if(min!=999)
	    cost+=min1;
 
	    return n_node;
    }
 
    void costMin(int node)
    {
	    int n_node;
 
	    completed_node[node]=1;
 
	    cout<<node+1<<"-->";
	    n_node=least(node);

        if(n_node==999)
	    {
		    n_node=0;
		    cout<<n_node+1;
		    cost+=arr[node][n_node];
 
		    return;
	    }
 
	    costMin(n_node);
    }
};

int main()
{
    tsp obj;
	
    obj.input();
 
	cout<<"\n\nThe shortest path is :";
	obj.costMin(0);
 
	cout<<"\n\nMinimum cost of the Travelling Salesman Problem is "<<obj.cost;
 
	return 0;
}


/*

OUTPUT:-

Enter the number of nodes : 4


Enter the cost matrix-      

Enter the elements of row 1 :
0 4 1 3

Enter the elements of row 2 :
4 0 2 1

Enter the elements of row 3 :
1 2 0 5

Enter the elements of row 4 :
3 1 5 0


The cost matrix is :
0 4 1 3
4 0 2 1
1 2 0 5
3 1 5 0


The shortest path is :1-->3-->2-->4-->1

Minimum cost of the Travelling Salesman Problem is 7

*/