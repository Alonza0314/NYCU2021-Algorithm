#pragma GCC optimize("Ofast","unroll-loops")
#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>

std::ifstream input;
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
                    return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    input.open("input.txt");
    output.open("output.txt");

    while(!input.eof())
    {
        input>>lines;
        vertex_next*array=new vertex_next[lines];
        for(int i=0;i<lines;i++)
        {
            input>>v1>>v2;
            array[v1].table.push_back(v2);
        }
        flag=destination_function(array);
        if(flag)
        {
            sort(vec.begin(),vec.end());
            for(int t=0;t<vec.size();t++)
            {
                if(t==vec.size()-1)
                {
                    output<<vec[t]<<"\n";
                }
                else
                {
                    output<<vec[t]<<",";
                }
            }
        }
        else
        {
            output<<-1<<"\n";
        }
        delete[] array;
        vec.clear();
    }

    input.close();
    output.close();
    return 0;
}