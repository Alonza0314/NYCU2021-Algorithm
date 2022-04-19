#include<iostream>
#include<fstream>
#include"data.hpp"
#include<algorithm>
#include<cstdlib>
using namespace std;

void solve(tTestData*test_data)
{
    int times=test_data->cnt;
    fstream output;
    output.open("output.txt",ios::app);    
    for(int i=0;i<times;i++)
    {
        int size=test_data->seq_size[i];
        int *arr=new int[size];
        for(int j=0;j<size;j++)
        {
            arr[j]=test_data->data[i][j];
        }
        sort(arr,arr+size);

        for (int j=0;j<size;j++)
        {
            output<<arr[j]<<" ";
        }
        delete []arr;
        output<<"\n";
    }
    output.close();
}