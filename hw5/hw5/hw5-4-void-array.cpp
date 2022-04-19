#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<iostream>
#include<fstream>
#include"data.hpp"

struct two_data
{
    int num1=-10000005;
    int num2=-10000005;
}*data_ptr;

int T,N,I;
int first_num,second_num;
bool flag;

inline void insert_array(two_data*&array,int num,int another)
{
    if(array[num+10000000].num1==-10000005&&array[num+10000000].num2==-10000005)
    {
        array[num+10000000].num1=another+10000000;
    }
    else
    {
        array[num+10000000].num2=another+10000000;
    }
}
int destination_function(two_data*&array,int start_num)
{
    if(I==0)
    {
        return start_num-10000000;
    }
    int temp_num=start_num;
    int index=array[temp_num].num1;
    data_ptr=&array[index];

    int counting=0;
    while(counting<I)
    {
        if(data_ptr->num1==temp_num)
        {
            temp_num=index;
            index=data_ptr->num2;
        }
        else
        {
            temp_num=index;
            index=data_ptr->num1;
        }
        data_ptr=&array[index];
        counting++;
    }

    return temp_num-10000000;
}

void solve(tTestData*test)
{
    std::fstream output;
    output.open("output.txt",std::ios::app);
    for(T=0;T<test->t;T++)
    {
        I=test->testcase[T].i;
        two_data*array=new two_data[20000001];
        for(int j=0;j<test->testcase[T].n-1;j++)
        {
            insert_array(array,test->testcase[T].edges[j][0],test->testcase[T].edges[j][1]);
            insert_array(array,test->testcase[T].edges[j][1],test->testcase[T].edges[j][0]);
        }
        flag=true;
        for(int j=0;j<20000001;j++)
        {
            if(array[j].num1!=-10000005&&array[j].num2==-10000005&&flag)
            {
                first_num=j;
                flag=false;
            }
            else if(array[j].num1!=-10000005&&array[j].num2==-10000005&&!flag)
            {
                second_num=j;
                break;
            }
            else
            {
                continue;
            }
        }
        if(first_num>=second_num)
        {
            output<<destination_function(array,first_num)<<"\n";
        }
        else
        {
            output<<destination_function(array,second_num)<<"\n";
        }
        delete[] array;
    }
    output.close();
}