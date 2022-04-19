#pragma GCC optimize("Ofast","unroll-loops")
#include<fstream>
#include<vector>
#include<cmath>
#include<algorithm>
#include"data.hpp"

std::ofstream output;
double w,w_2,w_22,length,temp_length,r_w;
int counting;
bool flag;

struct pair
{
    double start,end;
    pair(int position,int radius)
    {
        r_w=radius*radius-w_22;
        this->start=position-sqrt(r_w);
        this->end=position+sqrt(r_w);
    }
};

std::vector<pair> table;

bool cmp(pair a,pair b)
{
    return a.start<b.start;
}

void solve(tTestData *t)
{
    output.open("output.txt");
    for(int times=0;times<936;times++)
    {
        w=t->data[times].w;
        w_2=w/2;
        w_22=w_2*w_2;
        for(int i=0;i<t->data[times].n;i++)
        {
            if(t->data[times].r[i]>w_2)
            {
                table.push_back(pair(t->data[times].p[i],t->data[times].r[i]));
            }
        }
        if(table.empty())
        {
            output<<-1<<"\n";
            continue;
        }
        std::sort(table.begin(),table.end(),cmp);
        if(table[0].start>0)
        {
            output<<-1<<"\n";
            table.clear();
            continue;
        }
        counting=0;
        length=0;
        temp_length=0;
        for(int i=0;i<table.size();)
        {
            flag=false;
            for(int j=i;table[j].start<=length&&j<table.size();j++)
            {
                if(table[j].end>temp_length)
                {
                    flag=true;
                    temp_length=table[j].end;
                    i=j;
                }
            }
            if(flag)
            {
                counting++;
                length=temp_length;
                if(length>=t->data[times].l)
                {
                    output<<counting<<"\n";
                    break;
                }
            }
            else
            {
                output<<-1<<"\n";
                break;
            }
        }
        table.clear();
    }
    output.close();
}