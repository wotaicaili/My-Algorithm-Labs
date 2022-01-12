/*
 * @Author       : zongzi
 * @Date         : 2022-1-11 16:37:20
 * @LastEditors  : zongzi
 * @LastEditTime : 2021-1-11 18:00:34
 */
#include <iostream>
#include <fstream>
#include <ctime>
#include <climits>
#include <cstring>

using namespace std;
ifstream fin;
ofstream fresult, ftime;
char text[5000];   //需要匹配的文本
char pattern[200]; //匹配的模式
int pi[200];       // pi 数组
//数组从位置1开始使用
int count;         //匹配次数统计
int begin_pos[10]; //存储匹配的T中开始位置
clock_t start, end;

void KMPMatch();
void ComputePrefixFuction();

int main()
{
    clock_t start, end;

    fin.open("../input/4_1_input.txt", ios::in);
    fresult.open("../output/result.txt", ios::out);
    ftime.open("../output/time.txt", ios::out);

    while (fin >> pattern + 1)
    {
        fin >> text + 1;
        count = 0;
        start = clock();
        KMPMatch();
        end = clock();
        fresult << count << endl;
        int i;
        for (i = 1; i <= strlen(pattern + 1); i++)
        {
            if (i != strlen(pattern + 1))
                fresult << pi[i] << " ";
            else
                fresult << pi[i] << endl;
        }
        for (i = 1; i <= count; i++)
        {
            if (i != count)
                fresult << begin_pos[i] << " ";
            else
                fresult << begin_pos[i] << endl;
        }
        fresult << endl;
        ftime << long(end - start) / (CLOCKS_PER_SEC / 1000000) << "us" << endl;
    }
}

void KMPMatch()
{
    int n = strlen(text + 1);
    int m = strlen(pattern + 1);
    ComputePrefixFuction();
    int q = 0;
    for (int i = 1; i <= n; i++)
    {
        while (q > 0 && pattern[q + 1] != text[i])
            q = pi[q];
        if (pattern[q + 1] == text[i])
            q++;
        if (q == m)
        //匹配成功
        {
            count++;
            begin_pos[count] = i - m + 1;
            q = pi[q];
        }
    }
}

void ComputePrefixFuction()
{
    for (int i = 0; i < 200; i++)
        pi[i] = 0;
    pi[1] = 0;
    int m = strlen(pattern + 1);
    int k = 0;
    for (int q = 2; q < m + 1; q++)
    {
        while (k > 0 && pattern[k + 1] != pattern[q])
            k = pi[k];
        if (pattern[k + 1] == pattern[q])
            k++;
        pi[q] = k;
    }
}
