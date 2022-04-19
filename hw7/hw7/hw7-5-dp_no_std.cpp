#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<iostream>
#include<fstream>
#include<algorithm>

std::ifstream input;
std::ofstream output;
int times,lines;
std::string sentence;

bool cmp(std::string a,std::string b)
{
    return a.length()>b.length();
}

inline bool search(std::string *dictionary,std::string dest)
{
    for(int i=0;i<lines;i++)
    {
        if(dest==dictionary[i])
        {
            return true;
        }
    }
    return false;
}

int destination_function(std::string *dictionary)
{
    int longest_size=0;
    for(int i=0;i<lines;i++)
    {
        longest_size=std::max(longest_size,(int)dictionary[i].length());
    }
    int *dp=new int[sentence.length()+1]{0};
    for(int i=1;i<sentence.length()+1;i++)
    {
        dp[i]=-1;
    }
    for(int i=1;i<=sentence.length();i++)
    {
        for(int j=i-1;j>=std::max(i-longest_size,0);j--)
        {
            if(dp[j]!=-1)
            {
                if(search(dictionary,sentence.substr(j,i-j)))
                {
                    if(dp[i]==-1)
                    {
                        dp[i]=dp[j]+1;
                    }
                    else
                    {
                        if(dp[j]+1<dp[i])
                        {
                            dp[i]=dp[j]+1;
                        }
                    }
                }
            }
        }
    }
    return dp[sentence.length()];
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
        output<<destination_function(dictionary)<<"\n";
        delete[] dictionary;
    }

    input.close();
    output.close();
    return 0;
}