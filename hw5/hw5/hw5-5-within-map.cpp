#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<iostream>
#include<unordered_map>
#include<fstream>
using namespace std;

struct next_nodes_times
{
    int num1;
    int num2;
    int times=0;
};

unordered_map<int,next_nodes_times> mapping;
unordered_map<int,next_nodes_times>::iterator itt;

int T,N,I;
int first_num,second_num;
int temp_1,temp_2;
bool flag;
fstream input,output;

inline void insert_mapping(int num_one,int num_two)
{
    mapping[num_one].times++;
    mapping[num_two].times++;
    if(mapping[num_one].times==1)
    {
        mapping[num_one].num1=num_two;
    }
    else
    {
        mapping[num_one].num2=num_two;
    }
    if(mapping[num_two].times==1)
    {
        mapping[num_two].num1=num_one;
    }
    else
    {
        mapping[num_two].num2=num_one;
    }
}
int destination_function(int start_num)
{
    int temp_num=start_num;
    int next=mapping[temp_num].num1;
    int counting=0;
    while(counting<I)
    {
        if(mapping[next].num1==temp_num)
        {
            temp_num=next;
            next=mapping[temp_num].num2;
        }
        else
        {
            temp_num=next;
            next=mapping[temp_num].num1;
        }
        counting++;
    }
    return temp_num;
}

int main()
{
    input.open("input.txt",ios::in);
    output.open("output.txt",ios::app);
    input>>T;
    for(int t=0;t<T;t++)
    {
        input>>N>>I;
        for(int i=0;i<N-1;i++)
        {
            input>>temp_1>>temp_2;
            insert_mapping(temp_1,temp_2);
        }
        flag=true;
        for(itt=mapping.begin();itt!=mapping.end();itt++)
        {
            if(itt->second.times==1&&flag)
            {
                first_num=itt->first;
                flag=false;
            }
            else if(itt->second.times==1&&!flag)
            {
                second_num=itt->first;
                break;
            }
            else
            {
                continue;
            }
        }
        if(first_num>=second_num)
        {
            if(I==0)
            {
                output<<first_num<<"\n";
            }
            else
            {
                output<<destination_function(first_num)<<"\n";
            }
        }
        else
        {
            if(I==0)
            {
                output<<second_num<<"\n";
            }
            else
            {
                output<<destination_function(second_num)<<"\n";
            }
        }
        mapping.clear();
    }
    input.close();
    output.close();
    return 0;
}