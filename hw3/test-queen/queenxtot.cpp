#pragma GCC optimization("0fast")
#pragma GCC optimization("unroll-loops")
#include<iostream>
using namespace std;
#define n 8

bool array[n][n]={0};
int num=0;
void print()
{
    num++;
    cout<<"num="<<num<<"\n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<(int)array[i][j]<<" ";
        }
        cout<<"\n";
    }cout<<"\n";
}
bool check(int row,int col)
{
    if(row==0)
    {
        return 1;
    }
    for(int i=0;i<row;i++)
    {
        if(array[i][col])
        {
            return 0;
        }
    }

    int i=row-1;
    int j=col-1;
    while(i>=0&&j>=0)
    {
        if(array[i][j])
        {
            return 0;
        }
        i--;
        j--;
    }
    i=row-1;
    j=col+1;
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
void solve(int row)
{
    for(int i=0;i<n;i++)
    {
        array[row][i]=true;
        if(check(row,i))
        {
            if(row==n-1)
            {
                print();
            }
            else
            {
                solve(row+1);
            }
        }
        array[row][i]=false;
    }
}
int main()
{
    system("cls");
    solve(0);
    cout<<"total num="<<num<<"\n";
    return 0;
}