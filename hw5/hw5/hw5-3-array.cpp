#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<iostream>
#include<fstream>
using namespace std;

struct two_data
{
    int num1=-10000005;
    int num2=-10000005;
}*data_ptr;

int T,N,I;
int first_num,second_num;
bool flag;

void insert_array(two_data*&array,int num,int another)
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

int main()
{
    ifstream input;
    input.open("input.txt");
    fstream output;
    output.open("output.txt",ios::app);

    input>>T;
    for(int time=0;time<T;time++)
    {
        input>>N>>I;
        two_data*array=new two_data[20000001];
        for(int i=0;i<N-1;i++)
        {
            int num1,num2;
            input>>num1>>num2;
            insert_array(array,num1,num2);
            insert_array(array,num2,num1);
        } 
        flag=true;
        for(int i=0;i<20000001;i++)
        {
            if(array[i].num1!=-10000005&&array[i].num2==-10000005&&flag)
            {
                first_num=i;
                flag=false;
            }
            else if(array[i].num1!=-10000005&&array[i].num2==-10000005&&!flag)
            {
                second_num=i;
                break;
            }
            else
            {
                continue;
            }
        }
        if(first_num>=second_num)
        {
            output<<destination_function(array,first_num)<<endl;
        }
        else
        {
            output<<destination_function(array,second_num)<<endl;
        }
        delete[] array;
    }
    
    input.close();
    output.close();
    return 0;
}