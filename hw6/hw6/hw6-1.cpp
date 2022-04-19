#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<iostream>
#include<fstream>

struct node
{
    std::string key;
    std::string value;
    node*parent;
    node*left;
    node*right;
};
node*root=nullptr;
int counting=0;
std::string command;
std::string insert_key,insert_value,find_key,erase_key,enum_key1,enum_key2;
bool flag,szlow_flag,szhigh_flag;
std::ifstream input;
std::fstream output;

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
    else//CLEAR
    {
        return 4;
    }
}

void right_rotate(node*cur)
{
    node*l=cur->left;
    cur->left=l->right;
    if(l->right!=nullptr)
    {
        l->right->parent=cur;
    }
    l->parent=cur->parent;
    if(cur->parent==nullptr)
    {
        root=l;
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
void left_rotate(node*cur)
{
    node*r=cur->right;
    cur->right=r->left;
    if(r->left!=nullptr)
    {
        r->left->parent=cur;
    }
    r->parent=cur->parent;
    if(cur->parent==nullptr)
    {
        root=r;
    }
    else if(cur->parent->right==cur)
    {
        cur->parent->right=r;
    }
    else
    {
        cur->parent->left=r;
    }
    r->left=cur;
    cur->parent=r;
}
void splay(node*cur)
{
    while(cur->parent!=nullptr)
    {
        if(cur->parent->parent==nullptr)
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
        else if(cur->parent->parent->right==cur->parent&&cur->parent->left==cur)
        {
            right_rotate(cur->parent);
            left_rotate(cur->parent);
        }
        else
        {
            std::cout<<"Something Wrong!!\n";
        }
    }
}

void insert(node*&cur)
{
    if(cur==nullptr)
    {
        node *temp=new node;
        temp->key=insert_key;
        temp->value=insert_value;
        temp->parent=nullptr;
        temp->left=nullptr;
        temp->right=nullptr;
        cur=temp;
        splay(cur);
        output<<"INSERT ";
        for(int i=4;i<insert_key.length();i++)
        {
            output<<insert_key[i];
        }
        output<<" SUCCESS!\n";
        counting++;
    }
    else
    {
        if(insert_key<cur->key)
        {
            insert(cur->left);
            cur->left->parent=cur;
        }
        else if(insert_key>cur->key)
        {
            insert(cur->right);
            cur->right->parent=cur;
        }
        else if(insert_key==cur->key)
        {
            output<<"INSERT ";
            for(int i=4;i<insert_key.length();i++)
            {
                output<<insert_key[i];
            }
            output<<" FAIL!\n";
        }
        else
        {
            std::cout<<"Something Wrong!!\n";
        }
    }
}
void find(node*cur)
{
    if(cur==nullptr)
    {
        return;
    }
    else
    {
        if(cur->key==find_key)
        {
            output<<"FIND ";
            for(int i=4;i<cur->key.length();i++)
            {
                output<<cur->key[i];
            }
            for(int i=5;i<cur->value.length();i++)
            {
                output<<cur->value[i];
            }output<<"!\n";
            flag=false;
            splay(cur);
            return;
        }
        else if(find_key<cur->key)
        {
            find(cur->left);
        }
        else if(find_key>cur->key)
        {
            find(cur->right);
        }
        else
        {
            std::cout<<"Something Wrong!!\n";
        }
    }
}
void erase()
{
    node*cur=root;
    while(cur!=nullptr)
    {
        if(erase_key==cur->key)
        {
            break;
        }
        else if(erase_key<cur->key)
        {
            cur=cur->left;
        }
        else if(erase_key>cur->key)
        {
            cur=cur->right;
        }
        else
        {
            std::cout<<"Something Wrong!!\n";
        }
    }
    if(cur==nullptr)
    {
        output<<"ERASE ";
        for(int i=4;i<erase_key.length();i++)
        {
            output<<erase_key[i];
        }
        output<<" FAIL!\n";
    }
    else
    {
        splay(cur);
        if(cur->left==nullptr)
        {
            root=cur->right;
            root->parent=nullptr;
            cur->right=nullptr;
            delete cur;
            output<<"ERASE ";
            for(int i=4;i<erase_key.length();i++)
            {
                output<<erase_key[i];
            }
            output<<" SUCCESS!\n";
            counting--;
        }
        else if(cur->right==nullptr)
        {
            root=cur->left;
            root->parent=nullptr;
            cur->left=nullptr;
            delete cur;
            output<<"ERASE ";
            for(int i=4;i<erase_key.length();i++)
            {
                output<<erase_key[i];
            }
            output<<" SUCCESS!\n";
            counting--;
        }
        else
        {
            node*root_t;
            root_t=*&root;
            node*l=root->left;
            node*r=root->right;
            if(r->left==nullptr)
            {
                r->parent=nullptr;
                r->left=l;
                root_t->left=nullptr;
                root_t->right=nullptr;
                delete root_t;
                output<<"ERASE ";
                for(int i=4;i<erase_key.length();i++)
                {
                    output<<erase_key[i];
                }
                output<<" SUCCESS!\n";
                root=r;
                counting--;
            }
            else
            {
                node*dest=r;
                while(dest->left!=nullptr)
                {
                    dest=dest->left;
                }
                if(dest->right!=nullptr)
                {
                    node*dest_pa=dest->parent;
                    node*dest_right=dest->right;
                    dest_pa->left=dest_right;
                    dest_right->parent=dest_pa;
                    dest->parent=nullptr;
                    dest->right=nullptr;
                }
                else
                {
                    node*dest_pa=dest->parent;
                    dest_pa->left=nullptr;
                    dest->parent=nullptr;
                }
                dest->left=l;
                dest->right=r;
                l->parent=dest;
                r->parent=dest;
                root_t->left=nullptr;
                root_t->right=nullptr;
                delete root_t;
                output<<"ERASE ";
                for(int i=4;i<erase_key.length();i++)
                {
                    output<<erase_key[i];
                }
                output<<" SUCCESS!\n";
                counting--;
                root=dest;
            }
        }
    }
}
void enum_(node*cur)
{
    if(cur==nullptr)
    {
        return;
    }
    else
    {
        enum_(cur->left);
        if(!szlow_flag)
        {
            if(cur->key==enum_key1)
            {
                output<<"ENUM ";
                for(int i=4;i<cur->key.length();i++)
                {
                    output<<cur->key[i];
                }
                for(int i=5;i<cur->value.length();i++)
                {
                    output<<cur->value[i];
                }output<<"\n";
                szlow_flag=true;
            }
        }
        else if(szlow_flag&&!szhigh_flag)
        {
            output<<"ENUM ";
            for(int i=4;i<cur->key.length();i++)
            {
                output<<cur->key[i];
            }
            for(int i=5;i<cur->value.length();i++)
            {
                output<<cur->value[i];
            }output<<"\n";
            if(cur->key==enum_key2)
            {
                szhigh_flag=true;
            }
        }
        else
        {
            return;
        }
        enum_(cur->right);
    }
}
void enum_1(node*cur)
{
    if(cur==nullptr)
    {
        return;
    }
    else
    {
        enum_1(cur->left);
        output<<"ENUM ";
        for(int i=4;i<cur->key.length();i++)
        {
            output<<cur->key[i];
        }
        for(int i=5;i<cur->value.length();i++)
        {
            output<<cur->value[i];
        }output<<"\n";
        if(cur->key==enum_key2)
        {
            return;
        }
        enum_1(cur->right);
    }
}
void clear(node*cur)
{
    if(cur==nullptr)
    {
        return ;
    }
    else
    {
        clear(cur->left);
        clear(cur->right);
        if(cur==root)
        {
            node*root_t=root;
            root_t->left=nullptr;
            root_t->right=nullptr;
            delete root_t;
            root=nullptr;
        }
        else
        {
            node*temp_pa=cur->parent;
            if(temp_pa->left==cur)
            {
                temp_pa->left=nullptr;
            }
            else
            {
                temp_pa->right=nullptr;
            }
            delete cur;
        }
    }
}

int main()
{
    //system("cls");
    input.open("input.txt");
    output.open("output.txt",std::ios::app);
    while(!input.eof())
    {
        input>>command;
        //std::cout<<command<<std::endl;;
        switch(simple_hash())
        {
            case 0://insert
                input>>insert_key>>insert_value;
                if(counting>300000)
                {
                    output<<"INSERT ";
                    for(int i=4;i<insert_key.length();i++)
                    {
                        output<<insert_key[i];
                    }
                    output<<" FAIL!\n";
                }
                else
                {
                    insert(root);
                }
                break;
            case 1://find
                input>>find_key;
                flag=true;
                find(root);
                if(flag)
                {
                    for(int i=4;i<find_key.length();i++)
                    {
                        output<<find_key[i];
                    }
                    output<<" NOT FOUND!\n";
                }
                break;
            case 2://erase
                input>>erase_key;
                erase();
                break;
            case 3://enum
                input>>enum_key1>>enum_key2;
                szlow_flag=false;
                szhigh_flag=false;
                enum_(root);
                if(!szlow_flag)
                {
                    enum_1(root);
                }
                break;
            case 4:
                clear(root);
                break;
            default:
                std::cout<<"Something Wrong!!"<<"\n";
                break;
        }
    }
    input.close();
    output.close();
    return 0;
}