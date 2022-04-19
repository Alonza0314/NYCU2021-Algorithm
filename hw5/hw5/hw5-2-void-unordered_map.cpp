#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include<iostream>
#include<fstream>
#include<unordered_map>
#include"data.hpp"

struct two_data
{
    long long int num1;
    long long int num2;
}temp_two_data,*data_ptr;
struct index_times
{
    int index1;
    int index2;
    int times;
}temp_index_times;

int T,N,I;
int first_num,second_num;
bool flag;

std::unordered_map<int,index_times> mapping;
std::unordered_map<int,index_times>::iterator itt;

inline void insert_mapping(int index,int number)
{
    itt=mapping.find(number);
    if(itt==mapping.end())
    {
        temp_index_times.index1=index;
        temp_index_times.times=1;
        mapping[number]=temp_index_times;
    }
    else
    {
        mapping[number].index2=index;
        mapping[number].times++;
    }
}

int destination_function(two_data*&array,int start_num)
{
    if(I==0)
    {
        return start_num;
    }
    int temp_num=start_num;
    int index=mapping[temp_num].index1;
    data_ptr=&array[index];

    int counting=0;
    while(counting<I)
    {
        if(data_ptr->num1==temp_num)
        {
            temp_num=data_ptr->num2;
            if(mapping[temp_num].index1==index)//find index2
            {
                index=mapping[temp_num].index2;
                data_ptr=&array[index];
            }
            else
            {
                index=mapping[temp_num].index1;
                data_ptr=&array[index];
            }
        }
        else
        {
            temp_num=data_ptr->num1;
            if(mapping[temp_num].index1==index)//find index2
            {
                index=mapping[temp_num].index2;
                data_ptr=&array[index];
            }
            else
            {
                index=mapping[temp_num].index1;
                data_ptr=&array[index];
            }
        }

        counting++;
    }

    return temp_num;
}

void solve(tTestData*test)
{
    std::fstream output;
    output.open("output.txt",std::ios::app);

    for(T=0;T<test->t;T++)
    {
        I=test->testcase[T].i;
        two_data*array=new two_data[test->testcase[T].n-1];
        for(int i=0;i<test->testcase[T].n-1;i++)
        {
            temp_two_data.num1=test->testcase[T].edges[i][0];
            temp_two_data.num2=test->testcase[T].edges[i][1];;
            array[i]=temp_two_data;
            insert_mapping(i,test->testcase[T].edges[i][0]);
            insert_mapping(i,test->testcase[T].edges[i][1]);
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
 
        if(first_num>second_num)
        {
            output<<destination_function(*&array,first_num)<<"\n";
        }
        else
        {
            output<<destination_function(*&array,second_num)<<"\n";
        }

        delete[] array;
        mapping.clear();
    }
    output.close();
}