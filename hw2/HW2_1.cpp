#include<iostream>
#include<vector>
#include<cstring>
#include<fstream>
#include<map> 
using namespace std;

const string matrix_={"Matrix"};
const string init_={"Init"};
const string assign_={"Assign"};
const string print_={"Print"};
const string delete_={"Delete"};
const string mult_={"Mult"};
const string add_={"Add"};

class sparsematrix
{
    public:
    int row_num;
    int col_num;
    map<pair<int,int>,int> table;
    sparsematrix(){}
    sparsematrix(int row,int col):row_num(row),col_num(col){}
};
sparsematrix multiply(sparsematrix m1,sparsematrix m2)
{
    sparsematrix m3(m1.row_num,m2.col_num);
    for(auto it=m1.table.begin();it!=m1.table.end();it++)
    {
        for(auto itt=m2.table.begin();itt!=m2.table.end();itt++)
        {
            if(it->first.second==itt->first.first)
            {
                pair<int,int> ppair={it->first.first,itt->first.second};
                m3.table[ppair]+=it->second*itt->second;
            }
        }
    }
    return m3;
}
sparsematrix addition(sparsematrix a1,sparsematrix a2)
{
    sparsematrix a3(a1.row_num,a2.col_num);
    for(auto it=a1.table.begin();it!=a1.table.end();it++)
    {
        a3.table[it->first]+=it->second;
    }
    for(auto it=a2.table.begin();it!=a2.table.end();it++)
    {
        a3.table[it->first]+=it->second;
    }
    return a3;
}
int main()
{
    ifstream input;
    input.open("input.txt");
    map<string,sparsematrix> table;
    while(!input.eof())
    {
        string command;
        input>>command;
        string name;
        input>>name;
        if(command==matrix_)
        {
            sparsematrix matrix_;
            table.insert(pair<string,sparsematrix>(name,matrix_));
        }
        else if(command==init_)
        {
            input>>table[name].row_num>>table[name].col_num;
        }
        else if(command==assign_)
        {
            int row,col,val;
            input>>row>>col>>val;
            pair<int,int> ppair={row,col};
            table[name].table[ppair]+=val;
        }
        else if(command==print_)
        {
            fstream output;
            output.open("output.txt",ios::app);
            for(auto it=table[name].table.begin();it!=table[name].table.end();it++)
            {
                if(it->second==0)
                {
                    continue;
                }
                output<<"("<<it->first.first<<" "<<it->first.second<<" "<<it->second<<")"<<" ";
            }output<<endl;
            output.close();
        }
        else if(command==delete_)
        {
            table.erase(name);
        }
        else if(command==mult_)
        {
            string mul,equal;
            input>>mul>>equal;
            table[equal]=multiply(table[name],table[mul]);
        }
        else if(command==add_)
        {
            string add,equal;
            input>>add>>equal;
            table[equal]=addition(table[name],table[add]);
        }
        else
        {}
    }
    input.close();
    return 0;
}