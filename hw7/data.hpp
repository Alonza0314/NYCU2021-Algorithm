#include<iostream>

struct singleTestCase
{
    int M;
    char word[1024][128];
    char sentence[32768];
};

struct tTestData
{
    int N;
    singleTestCase data[128];
};