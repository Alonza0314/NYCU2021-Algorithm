#pragma GCC optimization("0fast")
#pragma GCC optimization("unroll-loops")

#include<iostream>
#include<fstream>

int t,n;
long long int countting;

struct tree_node
{
    long long int number;
    long long int large;
    tree_node*left;
    tree_node*right;
};

inline void find(tree_node*cur,long long int dest)
{
    if(dest>cur->number)
    {
        if(cur->right==nullptr)
        {
            return;
        }
        else
        {
            find(cur->right,dest);
        }
    }
    else
    {
        countting+=cur->large;
        countting++;
        if(cur->left==nullptr)
        {
            return;
        }
        else
        {
            find(cur->left,dest);
        }
    }
}

inline void insert(tree_node*&cur,long long int dest)
{
    if(cur==nullptr)
    {
        cur=new tree_node;
        cur->number=dest;
        cur->large=0;
        cur->left=nullptr;
        cur->right=nullptr;
    }
    else
    {
        if(dest>=cur->number)
        {
            cur->large++;
            insert(cur->right,dest);
        }
        else
        {
            insert(cur->left,dest);
        }
    }
}

void delete_tree(tree_node*&cur)
{
    if(cur!=nullptr)
    {
        delete_tree(cur->left);
        delete_tree(cur->right);
        delete cur;
    }
}

int main()
{
    std::ifstream input;
    input.open("input.txt");
    std::fstream output;
    output.open("output.txt",std::ios::app);
    input>>t;
    for(int time=0;time<t;time++)
    {
        input>>n;
        long long int *num=new long long int[n];
        for(int i=0;i<n;i++)
        {
            input>>num[i];
        }

        countting=0;
        tree_node*root=new tree_node;
        root->number=num[n-1];
        root->large=0;
        root->left=nullptr;
        root->right=nullptr;

        for(int i=n-2;i>=0;i--)
        {
            find(root,2*num[i]);
            insert(root,num[i]);
        }
        std::cout<<countting<<"\n";
        //output<<countting<<"\n";
        delete[] num;
        delete_tree(root);
    }
    input.close();
    output.close();
    return 0;
}