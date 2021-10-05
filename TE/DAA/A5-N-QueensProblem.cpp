/* Design and Analysis of Algorithms Lab
 * Yatish Kelkar TE IT 8001
 * Assignment 5 : N Queens Problem
 * 22/05/21
*/


#include <iostream>
using namespace std;

class NQueens
{
    public:

    int n, board[8][8];

    bool underAttack(int i,int j)
    {
        for(int k=0; k<n; k++)
            if(board[i][k]==1 || board[k][j]==1)
                return true;

        for(int k=0; k<n; k++)
            for(int l=0; l<n; l++)
                if((k+l)==(i+j) || (k-l)==(i-j))
                    if(board[k][l]==1)
                        return true;
        return false; 
    }

    bool queenPos(int n1)
    {
        if(n1==0)
        return true;

        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                if(!underAttack(i,j) && board[i][j]!=1)
                {
                    board[i][j]=1;
                    if(queenPos(n1-1))
                        return true;           
                    board[i][j]=0;
                }
       
        return false;
    }
};


int main()
{   
    NQueens object;

    cout<<"Enter the value of n for nxn chessboard : ";
    cin>>object.n;
    
    for(int i=0; i<object.n; i++)
        for(int j=0; j<object.n; j++)
            object.board[i][j]=0;
   
    object.queenPos(object.n);

    cout<<endl<<"Chessboard :"<<endl;
   
    for(int i=0; i<object.n; i++)
    {
        for(int j=0; j<object.n; j++)
        cout<<object.board[i][j]<<" ";   
        cout<<endl;
    }

    return 0;
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