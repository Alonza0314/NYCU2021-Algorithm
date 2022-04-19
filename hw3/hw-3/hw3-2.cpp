#pragma GCC optimization("0fast")
#pragma GCC optimization("unroll-loops")

#include<iostream>
#include<fstream>
#define max 100
using namespace std;
int t,n,queen_pre;
int x,y;
int count;
bool row[max];
bool col[max];
bool addition[max+max];
bool subtraction[max];
bool minus_subtraction[max];

bool check(int x,int y)
{
    if(row[x])
    {
        return false;
    }
    if(col[y])
    {
        return false;
    }
    int add=x+y;
    int sub=x-y;
    if(addition[add])
    {
        return false;
    }
    if(sub<0)
    {
        if(minus_subtraction[y-x])
        {
            return false;
        }
    }
    else
    {
        if(subtraction[sub])
        {
            return false;
        }
    }
    return true;
}

void solve(int x)
{
    for(int y=0;y<n;y++)
    {
        if(check(x,y))
        {
            if(x==n-1)
            {
                count++;
            }
            else
            {
                row[x]=true;
                col[y]=true;
                addition[x+y]=true;
                if((x-y)<0)
                {
                    minus_subtraction[y-x]=true;
                }
                else
                {
                    subtraction[x-y]=true;
                }
                int temp=x;
                while(temp<n)
                {
                    temp++;
                    if(row[temp]==false)
                    {
                        break;
                    }
                }
                solve(temp);
                row[x]=false;
                col[y]=false;
                addition[x+y]=false;
                if((x-y)<0)
                {
                    minus_subtraction[y-x]=false;
                }
                else
                {
                    subtraction[x-y]=false;
                }
            }
        }
    }
}
int main()
{
    system("cls");
    ifstream input;
    input.open("input.txt");
    fstream output;
    output.open("output.txt",ios::app);
    input>>t;
    for(int times=0;times<t;times++)
    {
        input>>n>>queen_pre;
        //initial array
        for(int i=0;i<n;i++)
        {
            
            row[i]=false;
            col[i]=false;
            subtraction[i]=false;
            minus_subtraction[i]=false;
        }
        for(int i=0;i<(2*n);i++)
        {
            addition[i]=false;
        }
        
        //place pre_queen
        for(int i=0;i<queen_pre;i++)
        {
            input>>x>>y;
            row[x]=true;
            col[y]=true;
            addition[x+y]=true;
            if((x-y)<0)
            {
                minus_subtraction[y-x]=true;
            }
            else
            {
                subtraction[x-y]=true;
            }
        }
        count=0;
        int temp=0;
        while(temp<n)
        {
            temp++;
            if(row[temp]==false)
            {
                break;
            }
        }
        solve(temp);
        output<<count<<"\n";
    }
    output.close();
    input.close();
    return 0;
}