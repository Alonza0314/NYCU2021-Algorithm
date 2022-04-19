#include<fstream>
#include<queue>
#include<vector>
#include<algorithm>
#include"data.hpp"
#define ll 10

std::ofstream output;
int lines,v1,v2,temp_index;
std::queue<int> que;
std::vector<int> vec;
bool flag;

struct vertex_next
{
    int color=-1;
    std::vector<int> table;
};

bool destination_function(vertex_next*array)
{
    array[0].color=0;
    que.push(0);
    while(!que.empty())
    {
        temp_index=que.front();
        que.pop();
        if(array[temp_index].color==0)
        {
            vec.push_back(temp_index);
            for(int t:array[temp_index].table)
            {
                if(array[t].color==-1)
                {
                    array[t].color=1;
                    que.push(t);
                }
                else if(array[t].color==0)
                {
                    while(!que.empty())
                    {
                        que.pop();
                    }
                    return false;
                }
                else
                {
                    continue;
                }
            }
        }
        else//array[temp_index].color==1
        {
            for(int t:array[temp_index].table)
            {
                if(array[t].color==-1)
                {
                    array[t].color=0;
                    que.push(t);
                }
                else if(array[t].color==0)
                {
                    continue;
                }
                else
                {
                    while(!que.empty())
                    {
                        que.pop();
                    }
                    output<<-1<<"\n";
                    return false;
                }
            }
        }
    }
    return true;
}

void solve(tTestData*test)
{
    output.open("output.txt");
    for(int times=0;times<2;times++)
    {
        vertex_next*array=new vertex_next[ll];
        for(int i=0;i<ll;i++)
        {
            array[test->data[times].edge[i][0]].table.push_back(test->data[times].edge[i][1]);
        }
        flag=destination_function(array);
        if(flag)
        {
            sort(vec.begin(),vec.end());
            for(int i=0;i<vec.size();i++)
            {
                if(i==vec.size()-1)
                {
                    output<<vec[i];
                }
                else
                {
                    output<<vec[i]<<",";
                }
            }
            output<<"\n";
        }
        else
        {
            output<<-1<<"\n";
        }
        delete[] array;
        vec.clear();
    }
    output.close();
}