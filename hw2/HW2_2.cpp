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

struct element
{
    int row;
    int col;
    int val;
    element(){}
    element(int r,int c,int v):row(r),col(c),val(v){}
};
class sparsematrix
{
    public:
    int row_num;
    int col_num;
    int val_num;
    vector<element> vec;
    sparsematrix()
    {
        val_num=0;
    }
    sparsematrix(int row,int col):row_num(row),col_num(col)
    {
        val_num=0;
    }
};
sparsematrix multiply(sparsematrix m1,sparsematrix m2)
{
    sparsematrix m3(m1.row_num,m2.col_num);
    map<pair<int,int>,int> table;
    for(int i=0;i<m1.val_num;i++)
    {
        for(int j=0;j<m2.val_num;j++)
        {
            if(m1.vec[i].col==m2.vec[j].row)
            {
                pair<int,int> ppair={m1.vec[i].row,m2.vec[j].col};
                table[ppair]+=m1.vec[i].val*m2.vec[j].val;
            }
        }
    }
    for(auto it=table.begin();it!=table.end();it++)
    {
        element element_(it->first.first,it->first.second,it->second);
        m3.vec.push_back(element_);
        m3.val_num++;
    }
    return m3;
}
sparsematrix addition(sparsematrix a1,sparsematrix a2)
{
    sparsematrix a3(a1.row_num,a2.col_num);
    map<pair<int,int>,int> table;
    for(int i=0;i<a1.val_num;i++)
    {
        pair<int,int> ppair={a1.vec[i].row,a1.vec[i].col};
        table[ppair]+=a1.vec[i].val;
    }
    for(int i=0;i<a2.val_num;i++)
    {
        pair<int,int> ppair={a2.vec[i].row,a2.vec[i].col};
        table[ppair]+=a2.vec[i].val;
    }
    for(auto it=table.begin();it!=table.end();it++)
    {
        element element_(it->first.first,it->first.second,it->second);
        a3.vec.push_back(element_);
        a3.val_num++;
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
            //cout<<command<<" "<<name<<endl;
            sparsematrix matrix_;
            table.insert(pair<string,sparsematrix>(name,matrix_));
        }
        else if(command==init_)
        {
            //cout<<command<<" "<<name<<endl;
            input>>table[name].row_num>>table[name].col_num;
        }
        else if(command==assign_)
        {
            //cout<<command<<" "<<name<<endl;
            int row,col,val;
            input>>row>>col>>val;
            element element_(row,col,val);
            table[name].vec.push_back(element_);
            table[name].val_num++;
        }
        else if(command==print_)
        {
            //cout<<command<<" "<<name<<endl;
            fstream output;
            output.open("output.txt",ios::app);
            for(int i=0;i<table[name].val_num;i++)
            {
                if(table[name].vec[i].val==0)
                {
                    continue;
                }
                output<<"("<<table[name].vec[i].row<<" "<<table[name].vec[i].col<<" "<<table[name].vec[i].val<<")"<<" ";
            }output<<endl;
            output.close();
        }
        else if(command==delete_)
        {
            //cout<<command<<" "<<name<<endl;
            table.erase(name);
        }
        else if(command==mult_)
        {
            //cout<<command<<" "<<name<<endl;
            string mul,equal;
            input>>mul>>equal;
            table[equal]=multiply(table[name],table[mul]);
        }
        else if(command==add_)
        {
            //cout<<command<<" "<<name<<endl;
            string add,equal;
            input>>add>>equal;
            table[equal]=addition(table[name],table[add]);
        }
        else
        {
            //cout<<"Can't recognized."<<endl;
        }
    }
    return 0;
}