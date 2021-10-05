/* Design and Analysis of Algorithms Lab
 * Yatish Kelkar TE IT 8001
 * Assignment 2 : Optimal Storage of Tapes problem with Greedy Approach
 * 18/04/21
*/


#include<iostream>
using namespace std;

class tapes
{
    public :

    void merge(int arr[],int l,int m,int r)
    {
        int i=0,j=0,k=l,n1=m-l+1,n2=r-m,L[n1],R[n2];
  
        for(int i=0;i<n1;i++)
        L[i]=arr[l+i];
    
        for(int j=0;j<n2;j++)
        R[j]=arr[m+1+j];
  
        while(i<n1 && j<n2)
        {
            if(L[i]<=R[j])
            { 
                arr[k]=L[i];
                i++;
            }
        
            else
            {
                arr[k]=R[j];
                j++;
            }
            
            k++;
        }
  
        while(i<n1)
        {
            arr[k]=L[i];
            i++;
            k++;
        }
   
        while(j<n2)
        {
            arr[k]=R[j];
            j++;
            k++;
        }  
    }

    void mergesort(int arr[],int l,int r)
    {
        int m;
  
        if(l>=r)
        return;
   
        m=(l+r)/2;
   
        mergesort(arr,l,m);
        mergesort(arr,m+1,r);
        merge(arr,l,m,r);
    } 

    void output(int programs[], int num_progs)
    {
        cout<<endl<<"Sorted array :-";
        for(int i=0; i<num_progs; i++)
        cout<<programs[i]<<" ";
        cout<<endl<<endl;
    }

    void mrt(int programs[], int num_tapes, int num_progs)
    {
        int tapes[num_tapes][(num_progs/num_tapes)+1],k=0,flg=0,sum[]={0,0};
        float mrt[num_tapes][1],total=0;

        for(int i=0; i<num_progs; i++)
        {
            for(int j=0; j<num_tapes; j++)
            {
                tapes[j][i]=programs[k];
                if(k==num_progs)
                {
                    flg=1;
                    break;
                }
                k++;
            }
            if(flg==1)
            break;
        }

        cout<<"Arrangement according to tapes : "<<endl;

        for(int i=0; i<num_tapes; i++)
        {
            mrt[i][0]=0;
            for(int j=0; j<(num_progs/num_tapes); j++)
            {
                sum[0]+=tapes[i][j];
                mrt[i][0]+=sum[0];

                sum[1]+=tapes[j][i];
                total+=sum[1];

                cout<<tapes[i][j]<<" ";
            }
            mrt[i][0]/=(num_progs/num_tapes);
            cout<<"     MRT="<<mrt[i][0];
            sum[0]=0;
            cout<<endl;
        }
        total/=num_progs;
        cout<<"Total MRT="<<total;
    }
};

int main()
{
    int num_progs,num_tapes;
    tapes obj;

    cout<<"Enter number of tapes : ";
    cin>>num_tapes;

    cout<<"Enter number of programs : ";
    cin>>num_progs;

    int programs[num_progs], mrt[num_tapes];

    cout<<endl<<"Enter lengths of the programs :- "<<endl;
    for(int i=0; i<num_progs; i++)
    {
        cout<<"Enter length of the program "<<(i+1)<<":- ";
        cin>>programs[i];

        if(programs[i]<=0)
        {
            cout<<"Enter length again, length cannot be less than or equal to zero";
            i--;
        }
    }

    cout<<endl<<"Unsorted array :-";
    for(int i=0; i<num_progs; i++)
    cout<<programs[i]<<" ";

    obj.mergesort(programs, 0, num_progs-1);
    obj.output(programs, num_progs);
    obj.mrt(programs, num_tapes, num_progs);

    return 0;
}

/*
OUTPUT:-
Enter number of tapes : 2
Enter number of programs : 6
Enter lengths of the programs :-
Enter length of the program 1:- 6
Enter length of the program 2:- 5
Enter length of the program 3:- 4
Enter length of the program 4:- 3
Enter length of the program 5:- 2
Enter length of the program 6:- 1
Unsorted array :-6 5 4 3 2 1
Sorted array :-1 2 3 4 5 6
Arrangement according to tapes :
1 3 5      MRT=4.66667
2 4 6      MRT=6.66667
Total MRT=5.5
*/