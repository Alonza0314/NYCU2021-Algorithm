#pragma GCC optimize("Ofast","unroll-loops")
#include<fstream>
#include<vector>
#include<cmath>
#include<algorithm>
#define oj 936

std::ifstream input;
std::ofstream output;

//936 cases in CodeSensor
//n=n lines
//l=long
//w=width
//p=position
//r=radius

double n,l,w,p,r,length,temp_length;
bool flag;
int counting,out;

struct pair
{
    double start,end;
    pair(double position,double radius)
    {
        this->start=position-sqrt(radius*radius-(w/2)*(w/2));
        this->end=position+sqrt(radius*radius-(w/2)*(w/2));
    }
};

std::vector<pair> table;

bool cmp(pair a,pair b)
{
    return a.start<b.start;
}

int destination_function()
{
    if(table[0].start>0)
    {
        return -1;
    }
    counting=0;
    length=0;
    temp_length=length;
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
            if(length>=l)
            {
                return counting;
            }
        }
        else
        {
            break;
        }
    }
    return -1;
}

int main()
{
    input.open("input.txt");
    output.open("output.txt");

    for(int t=0;t<oj;t++)
    {
        input>>n>>l>>w;
        for(int i=0;i<n;i++)
        {
            input>>p>>r;
            if(r>w/2)
            {
                table.push_back(pair(p,r));
            }
        }
        std::sort(table.begin(),table.end(),cmp);
        out=destination_function();
        output<<out<<"\n";
        table.clear();
    }

    input.close();
    output.close();
    return 0;
}