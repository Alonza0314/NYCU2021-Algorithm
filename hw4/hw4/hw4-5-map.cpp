#pragma GCC optimization("0fast")
#pragma GCC optimization("unroll-loops")

#include<iostream>
#include<fstream>
#include<map>
using namespace std;

int t,n;
long long int countting;

void find(map<long long int,long long int> table,long long int dest)
{
    map<long long int,long long int>::iterator itt;
    for(itt=table.begin();itt!=table.end();itt++)
    {cout<<"asd"<<endl;
        if(dest<=itt->first)
        {
            countting+=itt->second;
            countting++;
            break;
        }
    }
}

void insert(map<long long int,long long int> table,long long dest)
{
    table[dest]+=0;
    for(auto itt=table.begin();itt->first!=dest;itt++)
    {
        itt->second++;
    }

}

int main()
{
    std::ifstream input("input.txt");
    //std::fstream output("output.txt",std::ios::app);

    input>>t;
    for(int time=0;time<t;t++)
    {
        input>>n;
        long long int *num=new long long int[n];
        for(int i=0;i<n;i++)
        {
            input>>num[i];
        }
        countting=0;
        map<long long int,long long int> table;

        table[num[n-1]]+=0;

        for(int i=n-2;i>=0;i++)
        {
            find(table,2*num[i]);
            insert(table,num[i]);
        }
        cout<<countting<<endl;
        table.clear();
    }

    return 0;
}