#include <bits/stdc++.h>
#include <cstdlib>
#include <cmath>
#include <ctime>
#define size 8

using namespace std;

void simulated_annealing(int** current);
void neighbor_state(int** present, int** neighbor);
int attacking_pairs(int** board);
void assign_board(int **present, int **target);
double rand_ZeroToOne();
void print_board(int** board);

int main()
{
    int a,b;
    int** random_board= (int**)malloc((size+1)*sizeof(int*));
    for(int i=1; i<=size; ++i)
        random_board[i]= (int*)malloc((size+1)*sizeof(int));

    for(int i=1; i<=size; ++i)
        for(int j=1; j<=size; ++j)
            random_board[i][j]=0;

    for(int i=1; i<=size; ++i)
    {
        a= rand() %size +1;
        b= rand() %size +1;
        if(random_board[a][b]==1)
            i--;
        random_board[a][b]=1;
    }

    cout<<"The random board is: "<<endl;
    print_board(random_board);

    simulated_annealing(random_board);

    return 0;
}

void simulated_annealing(int** current)
{
    int T= 100, dE;
    double pro, ran;
    int currAttPairs;
    int nextAttPairs;
    int** next= (int**)malloc((size+1)*sizeof(int*));
    for(int i=1; i<=size; ++i)
        next[i]= (int*)malloc((size+1)*sizeof(int));

    while(true)
    {
        if(T==0)
            break;
        neighbor_state(current,next);
        currAttPairs= attacking_pairs(current);
        nextAttPairs= attacking_pairs(next);
        if(currAttPairs==0)
            break;
        dE= currAttPairs-nextAttPairs;
        if(dE>=0)
            assign_board(next,current);
        else
        {
            pro= exp(dE/T);
            ran= rand_ZeroToOne();
            if(ran<=pro && ran>=0)
                assign_board(next,current);
        }
        T--;
        cout<<"Curr:"<<currAttPairs;
        cout<<"Next: "<<nextAttPairs;
    }

    cout<<endl<<T<<"The corrected board: "<<endl<<endl;
    print_board(current);
}

int attacking_pairs(int** board)
{
    int count=0;
    for(int j=1; j<=size; ++j)
    {
        for(int i=1; i<=size; ++i)
        {
            if(board[i][j]==1)
            {
                for(int k=i+1; k<=size; ++k)
                {
                    if(board[k][j]==1)
                    {
                        count++;
                        break;
                    }
                }
                for(int k=j+1; k<=size; ++k)
                {
                    if(board[i][k]==1)
                    {
                        count++;
                        break;
                    }
                }
                for(int m=i+1,n=j+1; m<=size && n<=size; ++m,++n)
                {
                    if(board[m][n]==1)
                    {
                        count++;
                        break;
                    }
                }
                for(int m=i-1,n=j+1; m>=1 && n<=size; --m,++n)
                {
                    if(board[m][n]==1)
                    {
                        count++;
                        break;
                    }
                }
            }
        }
    }
    return count;
}

void neighbor_state(int** present, int** neighbor)
{
    assign_board(present,neighbor);
    int x= rand() %size +1;
    int y= rand() %size +1;
    if(neighbor[x][y]==0)
    {
        neighbor_state(present, neighbor);
        return;
    }
    else
    {
        int x1= (x%8) +1;
        int y1= (y%8) +1;
        if(neighbor[x1][y1]==1)
        {
            neighbor_state(present, neighbor);
            return;
        }
        else
        {
            neighbor[x1][y1]=1;
            neighbor[x][y]=0;
        }
    }
}

void assign_board(int** present,int** target)
{
    for(int i=1; i<=size; ++i)
        for(int j=1; j<=size; ++j)
            target[i][j]= present[i][j];
}

double rand_ZeroToOne()
{
    srand((unsigned)time(NULL));
    return ((double)rand()/RAND_MAX);
}

void print_board(int** board)
{
    for(int i=1;i<=size;++i)
    {
        cout<<"\t";
        for(int j=1;j<=size;++j)
            cout<<board[i][j]<<"   ";
        cout<<endl<<endl;
    }
}
