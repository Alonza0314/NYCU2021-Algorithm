#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<iostream>
#include<fstream>
#include<algorithm>
//using namespace std;

std::ifstream input;
std::ofstream output;
int times,lines,counting;
std::string sentence,temp;
bool flag;

bool cmp(std::string a,std::string b)
{
    return a.length()>b.length();
}

void destination_function(std::string *dictionary)
{
    flag=false;
    for(int i=0;i<lines;i++)
    {
        temp="";
        for(int j=0;j<dictionary[i].length();j++)
        {
            temp+=sentence[j];
        }
        /*cout<<dictionary[i]<<".length()="<<dictionary[i].length()<<"\n";
        cout<<temp<<"\n";
        system("pause");*/
        if(temp==dictionary[i])
        {
            counting++;
            flag=true;
            sentence.erase(0,dictionary[i].length());
            break;
        }
    }
    if(!flag)
    {
        counting=-1;
        return;
    }
    else
    {
        if(sentence.length()==0)
        {
            return;
        }
        destination_function(dictionary);
    }
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
        /*for(int i=0;i<lines;i++)
        {
            std::cout<<dictionary[i]<<"\n";
        }
        std::cout<<sentence<<"\n";*/
        counting=0;
        destination_function(dictionary);
        output<<counting<<"\n";

        delete[] dictionary;
    }

    input.close();
    output.close();
    return 0;
}