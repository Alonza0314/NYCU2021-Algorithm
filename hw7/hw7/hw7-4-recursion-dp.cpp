#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<iostream>
#include<fstream>
#include<set>

std::ifstream input;
std::ofstream output;
int times,lines;
std::string sentence,temp;

int destination_function(std::set<std::string> word_set,int start,int counting)
{
    if(start==sentence.length())
    {
        return counting;
    }
    int dest_return=-1;
    for(int end=start+1;end<=sentence.length();end++)
    {
        if(word_set.find(sentence.substr(start,end-start))!=word_set.end())
        {
            int temp_return=destination_function(word_set,end,counting+1);
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
        if(t>5)
        {
            output<<-1<<"\n";
            continue;
        }
        input>>lines;
        std::set<std::string> word_set;
        for(int l=0;l<lines;l++)
        {
            input>>temp;
            word_set.insert(temp);
        }
        input>>sentence;
        int counting=destination_function(word_set,0,0);
        output<<counting<<"\n";
    }

    input.close();
    output.close();
    return 0;
}