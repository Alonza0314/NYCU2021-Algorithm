#pragma GCC optimization ("0fast")
#pragma GCC optimization ("unroll-loops")
	
#include<iostream>
#include<fstream>
#define max 75

bool row[max];
bool col[max];
bool addition[2*max-1];
bool subtraction[2*max-2];

int t,n,m,x,y;
int count_kinds;
int last_row;
int last_col;
int first_col;
bool flag_row;
bool flag_col;

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
        last_col=n-1;
        flag_row=true;
        flag_col=true;
        while(last_row>=0||last_col>=0)
        {
            if(flag_row)
            {
                if(!row[last_row])
                {
                    flag_row=false;
                }
                else
                {
                    last_row--;
                }
            }
            if(flag_col)
            {
                if(!col[last_col])
                {
                    flag_col=false;
                }
                else
                {
                    last_col--;
                }
            }
            if((!flag_row)&&(!flag_col))
            {
                break;
            }
        }
        int temp=0;
        flag_row=true;
        flag_col=true;
        first_col=0;
        while(temp<=last_row||first_col<=last_col)
        {
            if(flag_row)
            {
                if(!row[temp])
                {
                    flag_row=false;
                }
                else
                {
                    temp++;
                }
            }
            if(flag_col)
            {
                if(!col[first_col])
                {
                    flag_col=false;
                }
                else
                {
                    first_col++;
                }
            }
            if((!flag_row)&&(!flag_col))
            {
                break;
            }
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
    int y=first_col;
    while(y<=last_col)
    {
        if(!col[y])
        {
            break;
        }
        y++;
    }
    while(y<=last_col)
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
        y++;
        while(y<=last_col)
        {
            if(!col[y])
            {
                break;
            }
            y++;
        }
   }
}
bool check(int x,int y)
{
    if(addition[x+y])
    {
       return false;
    }
    if(subtraction[x-y+n])
    {
        return false;
    }
    return true;
}