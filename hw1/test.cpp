#include<iostream>
using namespace std;

int main()
{
    int *arr=new int[10*5];
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<5;j++)
        {
            arr[i*j]=0;
        }
    }
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<5;j++)
        {
            cout<<arr[i*j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}