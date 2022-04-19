#include<iostream>
#include<fstream>
#include<cstdlib>
#include"data.hpp"
#define max 20000
using namespace std;

void solve(tTestData*test_data)
{
    int times=test_data->cnt;
    fstream output;
    output.open("output.txt",ios::app);    
    for(int i=0;i<times;i++)
    {
        int arr[max]={0};
        for(int j=0;j<test_data->seq_size[i];j++)
        {
            arr[test_data->data[i][j]]++;
        }
        for(int j=0;j<max;j++)
        {
            while(arr[j]>0)
            {
               output<<j<<" ";
                arr[j]--;
            }
        }
        output<<endl;
    }
    output.close();
}