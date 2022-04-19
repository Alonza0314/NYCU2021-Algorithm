#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    ifstream input;
    input.open("input.txt");
    string command;
    while(!input.eof())
    {
        input>>command;
        cout<<command<<"\n";
    }

    return 0;
}