#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

std::ifstream input;
std::ofstream output;
int times,lines,longest_size;
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

    std::vector<int> dp(sentence.length()+1,-1);
    dp[0]=0;
    
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