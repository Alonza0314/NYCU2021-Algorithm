#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<iostream>
#include<unordered_map>
#include<fstream>
#include"data.hpp"
#define int int_fast32_t

struct next_nodes_times
{
    int num1;
    int num2;
    int times=0;
};
std::unordered_map<int,next_nodes_times> mapping;
std::unordered_map<int,next_nodes_times>::iterator itt;

int T,N,I;
int first_num,second_num;
bool flag;
std::ofstream output;

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

void solve(tTestData*test)
{
    output.open("output.txt");
    for(T=0;T<test->t;T++)
    {
        I=test->testcase[T].i;
        for(int j=0;j<test->testcase[T].n-1;j++)
        {
            insert_mapping(test->testcase[T].edges[j][0],test->testcase[T].edges[j][1]);
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
    output.close();
}