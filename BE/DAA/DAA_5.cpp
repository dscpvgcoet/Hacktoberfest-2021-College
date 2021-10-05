/*

Maitreya Kanitkar
TE-IT   8084

DAA Assignment 5 (N queens chessborad)

*/


#include <iostream>
using namespace std;

class n_queens
{
    public:

    int n, board[8][8];

    int underAttack(int i,int j)
    {
        for(int k=0; k<n; k++)
        if(board[i][k]==1 || board[k][j]==1)
        return 1;

        for(int k=0; k<n; k++)
        for(int l=0; l<n; l++)
        if((k+l)==(i+j) || (k-l)==(i-j))
        if(board[k][l]==1)
        return 1;
            
        return 0; 
    }

    int queenPos(int n1)
    {
        if(n1==0)
        return 1;

        for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        if(!underAttack(i,j) && board[i][j]!=1)
        {
            board[i][j]=1;
            if(queenPos(n1-1)==1)
            return 1;           
            board[i][j]=0;
        }
       
        return 0;
    }
};


int main()
{   
    n_queens obj;

    cout<<"Enter the value of n for nxn chessboard : ";
    cin>>obj.n;
    
    for(int i=0; i<obj.n; i++)
    for(int j=0; j<obj.n; j++)
    obj.board[i][j]=0;
   
    obj.queenPos(obj.n);

    cout<<endl<<"Chessboard :"<<endl;
   
    for(int i=0; i<obj.n; i++)
    {
        for(int j=0; j<obj.n; j++)
        cout<<obj.board[i][j]<<" ";
        
        cout<<endl;
    }

    cout<<endl<<"1 denotes the position of the queen on the chess board where they cannot attack each other.";
    cout<<endl<<"If you see no 1s then that means that there is no such position.";
}



/*

OUTPUT:-

Enter the value of n for nxn chessboard : 4

Chessboard :
0 1 0 0 
0 0 0 1 
1 0 0 0 
0 0 1 0 

1 denotes the position of the queen on the chess board where they cannot attack each other.
If you see no 1s then that means that there is no such position.

*/