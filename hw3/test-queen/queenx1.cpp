#pragma GCC optimization("0fast")
#pragma GCC optimization("unroll-loops")
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
#define n 8

class queen
{
    public:
    int x,y;
    int addition_xy;
    int subtract_xy;
    queen(int x,int y):x(x),y(y),addition_xy(x+y),subtract_xy(x-y){}
    void add_x()
    {
        this->x++;
        this->y=0;
        this->addition_xy=this->x+this->y;
        this->subtract_xy=this->x-this->y;
    }
    void add_y()
    {
        this->y++;
        this->addition_xy=this->x+this->y;
        this->subtract_xy=this->x-this->y;
    }
};
vector<queen> board;
bool check(queen sub_queen)
{
    for(auto itt:board)
    {
        if(sub_queen.x==itt.x||sub_queen.y==itt.y||sub_queen.addition_xy==itt.addition_xy||sub_queen.subtract_xy==itt.subtract_xy)
        {
            return true;//有出現過
        }
    }
    return false;//沒有出現過
}
int main()
{
    system("cls");
    queen queen_(0,0);
    board.push_back(queen_);
    int row=0;
    while(row<n)
    {
        while((queen_.y<n)&&check(queen_))
        {
            queen_.add_y();
        }
        if(queen_.y<n)
        {
            board.push_back(queen_);
            queen_.add_x();
            row++;
        }
        else
        {
            queen_=board.back();
            board.pop_back();
            row--;
            queen_.add_y();
        }
        if(row<0)
        {
            row=0;
        }
    }
    bool array[n][n]={0};
    for(auto itt:board)
    {
        array[itt.x][itt.y]=1;
        cout<<itt.x<<" "<<itt.y<<"\n";
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<(int)array[i][j];
        }
        cout<<"\n";
    }
    return 0;
}