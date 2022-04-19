#pragma GCC optimization("0fast")
#pragma GCC optimization("unroll-loops")

#include<iostream>
#include<fstream>
//using namespace std;

long long int t,n;
long long int count;

void merge_and_count(long long int*array,int first,int mid,int last)
{
    for(int i=mid;i>=first;i--)
    {
        for(int j=mid+1;j<=last;j++)
        {
            if(array[i]*2<=array[j])
            {
                count++;
            }
        }
    }
}

void divide_and_conquer(long long int*array,int first,int last)
{
    if(first<last)
    {
        int mid=(first+last)/2;
        divide_and_conquer(array,first,mid);
        divide_and_conquer(array,mid+1,last);
        merge_and_count(array,first,mid,last);
    }
}

int main()
{
    //system("cls");
    std::ifstream input;
    input.open("input.txt");
    std::fstream output;
    output.open("output.txt",std::ios::app);

    input>>t;
    for(int time=0;time<t;time++)
    {
        input>>n;
        long long int*array=new long long int[n];
        for(long long int i=0;i<n;i++)
        {
            input>>array[i];
        }

        count=0;

        divide_and_conquer(array,0,n-1);

        delete array;
        std::cout<<count<<"\n";
        output<<count<<"\n";
    }
    input.close();
    output.close();
    return 0;
}