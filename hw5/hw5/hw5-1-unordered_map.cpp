#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include<iostream>
#include<fstream>
#include<unordered_map>
using namespace std;

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
long long int first_num,second_num;
bool flag;

std::unordered_map<long long int,index_times> mapping;
std::unordered_map<long long int,index_times>::iterator itt;

inline void insert_mapping(int index,long long int number)
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

long long int destination_function(two_data*&array,long long int start_num)
{
    if(I==0)
    {
        return start_num;
    }
    long long int temp_num=start_num;
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

int main()
{
    std::ifstream input;
    input.open("input.txt");
    std::fstream output;
    output.open("output.txt",std::ios::app);

    input>>T;
    for(int t=0;t<T;t++)
    {
        input>>N>>I;
        two_data*array=new two_data[N-1];
        for(int i=0;i<N-1;i++)
        {
            input>>temp_two_data.num1>>temp_two_data.num2;
            array[i]=temp_two_data;
            insert_mapping(i,array[i].num1);
            insert_mapping(i,array[i].num2);
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

    input.close();
    output.close();

    return 0;
}