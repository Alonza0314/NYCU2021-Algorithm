#pragma GCC optimization("0fast")
#pragma GCC optimization("unroll-loops")

#include<iostream>
#include<fstream>

int times,n;
long long int count;
long long int temp;
long long int this_num;
long long int *num;

int main()
{
    //system("cls");
    std::ifstream input;
    std::fstream output;
    input.open("input.txt");
    output.open("output.txt",std::ios::app);
    input>>times;
    for(int t=0;t<times;t++)
    {
        input>>n;
        num=new long long int[n];
        for(int i=0;i<n;i++)
        {
            input>>temp;
            num[i]=temp;
        }
        count=0;
        for(int i=0;i<n-1;i++)
        {
            this_num=2*num[i];
            for(int j=i+1;j<n;j++)
            {
                if(num[j]>=this_num)
                {
                    count++;
                }
            }
        }
        std::cout<<count<<"\n";
        //output<<count<<"\n";
        delete num;
    }
    input.close();
    output.close();
    return 0;
}