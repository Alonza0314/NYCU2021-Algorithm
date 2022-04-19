#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<iostream>
#include<fstream>
#include<algorithm>

std::ifstream input;
std::ofstream output;
int times,lines;
std::string sentence,temp;

bool cmp(std::string a,std::string b)
{
    return a.length()>b.length();
}

int destination_function(std::string *dictionary,std::string rest,int erase_idx,int counting)
{
    rest.erase(0,erase_idx);
    if(rest.length()==0)
    {
        return counting;
    }
    int dest_return=-1;
    for(int i=0;i<lines;i++)
    {
        temp="";
        for(int j=0;j<dictionary[i].length();j++)
        {
            temp+=rest[j];
        }
        if(temp==dictionary[i])
        {
            int temp_return=destination_function(dictionary,rest,dictionary[i].length(),counting+1);
            if(temp_return!=-1&&dest_return==-1)
            {
                dest_return=temp_return;
            }
            else if(temp_return!=-1&&dest_return!=-1)
            {
                if(temp_return<dest_return)
                {
                    dest_return=temp_return;
                }
            }
        }
    }
    return dest_return;
}

int main()
{
    input.open("input.txt");
    output.open("output.txt");

    input>>times;
    for(int t=0;t<times;t++)
    {
        input>>lines;
        std::string *dictionary=new std::string[lines];
        for(int l=0;l<lines;l++)
        {
            input>>dictionary[l];
        }
        input>>sentence;
        sort(dictionary,dictionary+lines,cmp);
        output<<destination_function(dictionary,sentence,0,0)<<"\n";
        delete[] dictionary;
    }

    input.close();
    output.close();
    return 0;
}