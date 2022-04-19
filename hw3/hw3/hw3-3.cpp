#pragma GCC optimization ("0fast")
#pragma GCC optimization ("unroll-loops")
	
#include<iostream>
#include<fstream>
#define max 100

bool row[max];
bool col[max];
bool addition[2*max-1];
bool subtraction[2*max-2];

int t,n,m,x,y;
int count_kinds;
int last_row;

void queen(int);
bool check(int,int);

int main()
{
    std::ifstream input;
    input.open("input.txt");
    std::fstream output;
    output.open("output.txt",std::ios::app);
    input>>t;
    for(int times=0;times<t;times++)
    {
        input>>n>>m;
        for(int i=0;i<n;i++)
        {
            row[i]=false;
            col[i]=false;
            addition[i]=false;
            addition[i+n]=false;
            subtraction[i]=false;
            subtraction[i+n]=false;
        }
        
       for(int i=0;i<m;i++)
       {
            input>>x>>y;
            row[x]=true;
            col[y]=true;
            addition[x+y]=true;
            subtraction[x-y+n]=true;
        }
        count_kinds=0;
	    last_row=n-1;
        while(last_row>=0)
        {
            if(!row[last_row])
            {
               break;
            }
            last_row--;
        }
        int temp=0;
        while(temp<=last_row)
        {
            if(!row[temp])
            {
                break;
            }
	            temp++;
        }
        queen(temp);
        output<<count_kinds<<"\n";
    }
    input.close();
    output.close();
    return 0;
}

void queen(int x)
{
    for(int y=0;y<n;y++)
    {
        if(col[y])
        {
            continue;
        }
        else
        {
            if(check(x,y))
	            {
                if(x==last_row)
                {
                    count_kinds++;
                }
                else
                {
                    row[x]=true;
                    col[y]=true;
                    addition[x+y]=true;
                    subtraction[x-y+n]=true;
                    int temp=x+1;
                    while(temp<=last_row)
                    {
                        if(!row[temp])
                        {
                            break;
                        }
                        temp++;
                   }
                   queen(temp);
                   row[x]=false;
                   col[y]=false;
                   addition[x+y]=false;
                   subtraction[x-y+n]=false;
               }
           }    
       }
   }
}
bool check(int x,int y)
{
    int add=x+y;
    if(addition[add])
    {
       return false;
    }
    int sub=x-y;
    if(subtraction[sub+n])
    {
        return false;
    }
    return true;
}