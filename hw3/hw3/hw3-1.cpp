#pragma GCC optimization("0fast")
#pragma GCC optimization("unroll-loops")

#include<iostream>
#include<fstream>
#define max 50
using namespace std;

int array[max][max];
int t;
int n;
int count=0;
bool check(int x,int y)
{
    if(array[x][y])
    {
        return 0;
    }
    for(int i=0;i<x;i++)
    {
        if(array[i][y])
        {
            return 0;
        }
    }
    int i,j;
    i=x-1;
    j=y-1;
    while(i>=0&&j>=0)
    {
        if(array[i][j])
        {
            return 0;
        }
        i--;
        j--;
    }
    i=x-1;
    j=y+1;
    while(i>=0&&j<n)
    {
        if(array[i][j])
        {
            return 0;
        }
        i--;
        j++;
    }
    return 1;
}
void solve(int x)
{
    for(int i=0;i<n;i++)
    {
        if(check(x,i))
        {
            array[x][i]=1;
            if(x==n-1)
            {
                for(int j=0;j<n;j++)
                {
                    for(int k=0;k<n;k++)
                    {
                        cout<<(int)array[j][k]<<" ";
                    }cout<<"\n";
                }cout<<"\n";
                count++;
                cout<<count<<"\n";
            }
            else
            {
                solve(x+1);
            }
            array[x][i]=0;
        }
    }
}
int main()
{
    system("cls");
    ifstream input;
    input.open("input.txt");
    fstream output;
    output.open("output.txt");
    input>>t;
    int queen_pre;
    int x_pre,y_pre;
    for(int i=0;i<t;i++)
    {
        input>>n>>queen_pre;
        for(int j=0;j<queen_pre;j++)
        {
            input>>x_pre>>y_pre;
            array[x_pre][y_pre]=2;
        }
        solve(0);
        output<<count<<"\n";
        count=0;
    }
    input.close();
    output.close();
    return 0;
}