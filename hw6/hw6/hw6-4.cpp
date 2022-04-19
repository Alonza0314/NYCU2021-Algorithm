#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<iostream>
#include<fstream>
#include<stack>

std::ifstream input;
std::fstream output;

std::string command;
std::string insert_key,insert_value,find_key,erase_key,enum_key1,enum_key2;
bool low,high,szlow_flag,szhigh_flag;

inline int simple_hash()
{
    if(command=="INSERT")
    {
        return 0;
    }
    else if(command=="FIND")
    {
        return 1;
    }
    else if(command=="ERASE")
    {
        return 2;
    }
    else if(command=="ENUM")
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

struct node
{
    std::string key;
    std::string value;
    node*parent;
    node*left;
    node*right;
    node(std::string k,std::string v)
    {
        this->key=k;
        this->value=v;
        this->parent=nullptr;
        this->left=nullptr;
        this->right=nullptr;
    }
};

typedef node* nodeptr;

class splaytree
{
private: 
    void left_rotate(nodeptr);
    void right_rotate(nodeptr);
    void splay(nodeptr);
    nodeptr search(nodeptr);
public:
    nodeptr root;
    splaytree();
    void insert();
    void find();
    void erase();
    void enum_();
    void clear(nodeptr);
};

void splaytree::left_rotate(nodeptr cur)
{
    nodeptr r=cur->right;
    cur->right=r->left;
    if(r->left!=nullptr)
    {
        r->left->parent=cur;
    }
    r->parent=cur->parent;
    if(cur->parent==nullptr)
    {
        this->root=r;
    }
    else if(cur->parent->left==cur)
    {
        cur->parent->left=r;
    }
    else
    {
        cur->parent->right=r;
    }
    r->left=cur;
    cur->parent=r;
}
void splaytree::right_rotate(nodeptr cur)
{
    nodeptr l=cur->left;
    cur->left=l->right;
    if(l->right!=nullptr)
    {
        l->right->parent=cur;
    }
    l->parent=cur->parent;
    if(cur->parent==nullptr)
    {
        this->root=l;
    }
    else if(cur->parent->right==cur)
    {
        cur->parent->right=l;
    }
    else
    {
        cur->parent->left=l;
    }
    l->right=cur;
    cur->parent=l;
}
void splaytree::splay(nodeptr cur)
{
    while(cur->parent)
    {
        if(!cur->parent->parent)
        {
            if(cur->parent->left==cur)
            {
                right_rotate(cur->parent);
            }
            else
            {
                left_rotate(cur->parent);
            }
        }
        else if(cur->parent->parent->left==cur->parent&&cur->parent->left==cur)
        {
            right_rotate(cur->parent->parent);
            right_rotate(cur->parent);
        }
        else if(cur->parent->parent->right==cur->parent&&cur->parent->right==cur)
        {
            left_rotate(cur->parent->parent);
            left_rotate(cur->parent);
        }
        else if(cur->parent->parent->left==cur->parent&&cur->parent->right==cur)
        {
            left_rotate(cur->parent);
            right_rotate(cur->parent);
        }
        else
        {
            right_rotate(cur->parent);
            left_rotate(cur->parent);
        }
    }
}
nodeptr splaytree::search(nodeptr cur)
{
    if(cur==nullptr||find_key==cur->key)
    {
        return cur;
    }
    if(find_key<cur->key)
    {
        return search(cur->left);
    }
    else
    {
        return search(cur->right);
    }
}

splaytree::splaytree()
{
    this->root=nullptr;
}
void splaytree::insert()
{
    nodeptr temp=new node(insert_key,insert_value);
    nodeptr temp_=nullptr;
    nodeptr cur=this->root;

    while(cur!=nullptr)
    {
        temp_=cur;
        if(temp->key<cur->key)
        {
            cur=cur->left;
        }
        else if(temp->key>cur->key)
        {
            cur=cur->right;
        }
        else
        {
            output<<"INSERT "<<insert_key<<" FAIL!\n";
            return;
        }
    }
    temp->parent=temp_;
    if(temp_==nullptr)
    {
        root=temp;
    }
    else if(temp->key<temp_->key)
    {
        temp_->left=temp;
    }
    else
    {
        temp_->right=temp;
    }
    output<<"INSERT "<<insert_key<<" SUCCESS!\n";
    splay(temp);
}
void splaytree::find()
{
    nodeptr cur=search(this->root);
    if(cur)
    {
        splay(cur);
        output<<"FIND "<<cur->key<<":"<<cur->value<<"!\n";
    }
    else
    {
        output<<find_key<<" NOT FOUND!\n";
    }
}
void splaytree::erase()
{
    nodeptr cur=this->root;
    nodeptr dest=nullptr;
    while(cur!=nullptr)
    {
        if(erase_key==cur->key)
        {
            dest=cur;
            break;
        }
        else if(erase_key<cur->key)
        {
            cur=cur->left;
        }
        else
        {
            cur=cur->right;
        }
    }
    if(dest==nullptr)
    {
        output<<"ERASE "<<erase_key<<" FAIL!\n";
        return;
    }
    splay(dest);
    nodeptr l=dest->left;
    nodeptr r=dest->right;
    if(l!=nullptr)
    {
        l->parent=nullptr;
    }
    if(r!=nullptr)
    {
        r->parent=nullptr;
    }
    if(l==nullptr&&r!=nullptr)
    {
        root=r;
        delete dest;
    }
    else if(r==nullptr&&l!=nullptr)
    {
        root=l;
        delete dest;
    }
    else if(r!=nullptr&&l!=nullptr)
    {
        root=r;
        while(r->left!=nullptr)
        {
            r=r->left;
        }
        r->left=l;
        l->parent=r;
        delete dest;
    }
    else
    {
        delete dest;
        root=nullptr;
    }
    output<<"ERASE "<<erase_key<<" SUCCESS!\n";
}
void splaytree::enum_()
{
    nodeptr start=this->root;
    nodeptr end=this->root;
    while(start!=nullptr)
    {
        if(start->key==enum_key1)
        {
            break;
        }
        else if(enum_key1<start->key)
        {
            start=start->left;
        }
        else
        {
            start=start->right;
        }
    }
    while(end!=nullptr)
    {
        if(end->key==enum_key2)
        {
            break;
        }
        else if(enum_key2<end->key)
        {
            end=end->left;
        }
        else
        {
            end=end->right;
        }
    }
    if(start==nullptr)
    {
        std::cout<<"asd\n";
    }
    if(end==nullptr)
    {
        std::cout<<"qwe\n";
    }
    if(start==nullptr&&end==nullptr)
    {
        std::stack<nodeptr> s;
        nodeptr cur=this->root;
        while(cur!=nullptr||s.empty()==false)
        {
            while(cur!=nullptr)
            {
                s.push(cur);
                cur=cur->left;
            }
            cur=s.top();
            s.pop();
            output<<"ENUM "<<cur->key<<":"<<cur->value<<"\n";
            cur=cur->right;
        }
    }
    else if(start==nullptr&&end!=nullptr)
    {
        std::stack<nodeptr> s;
        nodeptr cur=this->root;
        while(cur!=nullptr||s.empty()==false)
        {
            while(cur!=nullptr)
            {
                s.push(cur);
                cur=cur->left;
            }
            cur=s.top();
            s.pop();
            output<<"ENUM "<<cur->key<<":"<<cur->value<<"\n";
            if(cur->key==enum_key2)
            {
                return;
            }
            cur=cur->right;
        }
    }
    else if(start!=nullptr&&end==nullptr)
    {
        szlow_flag=false;
        std::stack<nodeptr> s;
        nodeptr cur=this->root;
        while(cur!=nullptr||s.empty()==false)
        {
            while(cur!=nullptr)
            {
                s.push(cur);
                cur=cur->left;
            }
            cur=s.top();
            s.pop();
            if(cur->key==enum_key1)
            {
                szlow_flag=true;
            }
            if(szlow_flag)
            {
                output<<"ENUM "<<cur->key<<":"<<cur->value<<"\n";
            }
            cur=cur->right;
        }
    }
    else
    {
        szlow_flag=false;
        std::stack<nodeptr> s;
        nodeptr cur=this->root;
        while(cur!=nullptr||s.empty()==false)
        {
            while(cur!=nullptr)
            {
                s.push(cur);
                cur=cur->left;
            }
            cur=s.top();
            s.pop();
            if(cur->key==enum_key1)
            {
                szlow_flag=true;
            }
            if(szlow_flag)
            {
                output<<"ENUM "<<cur->key<<":"<<cur->value<<"\n";
            }
            if(cur->key==enum_key2)
            {
                return;
            }
            cur=cur->right;
        }
    }
}
void splaytree::clear(nodeptr cur)
{
    if(cur==nullptr)
    {
        return ;
    }
    else
    {
        clear(cur->left);
        clear(cur->right);
        delete cur;
    }
}

int main()
{
    input.open("input.txt");
    output.open("output.txt",std::ios::app);

    splaytree tree;
    while(!input.eof())
    {
        input>>command;
        switch(simple_hash())
        {
            case 0:
            {
                input>>insert_key>>insert_value;
                insert_key.erase(0,4);
                insert_value.erase(0,6);
                tree.insert();
                break;
            }
            case 1:
            {
                input>>find_key;
                find_key.erase(0,4);
                tree.find();
                break;
            }
            case 2:
            {
                input>>erase_key;
                erase_key.erase(0,4);
                tree.erase();
                break;
            }
            case 3:
            {
                input>>enum_key1>>enum_key2;
                enum_key1.erase(0,4);
                enum_key2.erase(0,4);
                tree.enum_();
                break;
            }
            case 4:
            {
                tree.clear(tree.root);
                tree.root=nullptr;
                break;
            }
            default:
            {
                std::cout<<"Something ERROR!\n";
            }
        }
    }

    input.close();
    output.close();

    return 0;
}