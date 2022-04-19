#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<iostream>
#include<fstream>
#include<unordered_set>
#include<algorithm>
#include<vector>

std::ifstream input;
std::ofstream output;
int times,lines,longest_size;
std::string sentence,temp;
std::unordered_set<std::string> dictionary;

int destination_function()
{
    if(dictionary.empty())
    {
        return -1;
    }
    std::vector<int> dp(sentence.length()+1,-1);
    dp[0]=0;

    for(int i=1;i<=sentence.length();i++)
    {
        for(int j=i-1;j>=std::max(i-longest_size,0);j--)
        {
            if(dp[j]!=-1&&dictionary.find(sentence.substr(j,i-j))!=dictionary.end())
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
    return dp[sentence.size()];
}


int main()
{
    input.open("input.txt");
    output.open("output.txt");

    input>>times;
    for(int t=0;t<times;t++)
    {
        input>>lines;
        longest_size=0;
        for(int l=0;l<lines;l++)
        {
            input>>temp;
            if(temp.length()>longest_size)
            {
                longest_size=temp.length();
            }
            dictionary.insert(temp);
        }
        input>>sentence;
        output<<destination_function()<<"\n";
        dictionary.clear();
    }

    input.close();
    output.close();
    return 0;
}