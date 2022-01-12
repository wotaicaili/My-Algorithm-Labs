/*
 * @Author       : zongzi
 * @Date         : 2022-1-11 16:37:20
 * @LastEditors  : zongzi
 * @LastEditTime : 2021-1-11 18:00:34
 */
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstring>

using namespace std;
ifstream fin;
ofstream fresult, ftime;
char text[5000];   //需要匹配的文本
char pattern[200]; //匹配的模式
//数组从位置1开始使用
int count;         //匹配次数统计
int begin_pos[10]; //存储匹配的T中开始位置
int false_hit[4];  //伪命中次数统计
long time_dq[4][5];
clock_t start, end;

void RKMATCH(int, int, int);
int compare(int, int);

int main()
{
    clock_t start, end;

    fin.open("../input/4_2_input.txt", ios::in);
    fresult.open("../output/result.txt", ios::out);
    ftime.open("../output/time.txt", ios::out);
    int j = -1;

    while (fin >> pattern + 1)
    {
        j++;
        fin >> text + 1;
        count = 0;

        //(2,13)
        start = clock();
        RKMATCH(2, 13, 0);
        end = clock();
        time_dq[0][j] = long(end - start) / (CLOCKS_PER_SEC / 1000000);

        //(2,1009)
        start = clock();
        RKMATCH(2, 1009, 1);
        end = clock();
        time_dq[1][j] = long(end - start) / (CLOCKS_PER_SEC / 1000000);

        //(10, 13)
        start = clock();
        RKMATCH(10, 13, 2);
        end = clock();
        time_dq[2][j] = long(end - start) / (CLOCKS_PER_SEC / 1000000);

        //(10,1009)
        start = clock();
        RKMATCH(10, 1009, 3);
        end = clock();
        time_dq[3][j] = long(end - start) / (CLOCKS_PER_SEC / 1000000);

        fresult << count << endl;
        for (int i = 0; i < 4; i++)
        {
            if (i != 3)
                fresult << false_hit[i] << " ";
            else
                fresult << false_hit[i] << endl;
        }
        for (int i = 1; i <= count; i++)
        {
            if (i != count)
                fresult << begin_pos[i] << " ";
            else
                fresult << begin_pos[i] << endl;
        }
        fresult << endl;
    }

    ftime << "(2, 13)" << endl;
    for (int i = 0; i < 5; i++)
    {
        if (i != 4)
            ftime << time_dq[0][i] << " ";
        else
            ftime << time_dq[0][i] << endl;
    }

    ftime << "(2, 1009)" << endl;
    for (int i = 0; i < 5; i++)
    {
        if (i != 4)
            ftime << time_dq[1][i] << " ";
        else
            ftime << time_dq[1][i] << endl;
    }

    ftime << "(10, 13)" << endl;
    for (int i = 0; i < 5; i++)
    {
        if (i != 4)
            ftime << time_dq[2][i] << " ";
        else
            ftime << time_dq[2][i] << endl;
    }

    ftime << "(10,1009)" << endl;
    for (int i = 0; i < 5; i++)
    {
        if (i != 4)
            ftime << time_dq[3][i] << " ";
        else
            ftime << time_dq[3][i] << endl;
    }
}

int compare_text(int m, int s)
{
    for (int i = 1; i <= m; i++)
    {
        if (pattern[i] != text[s + i])
            return 0;
    }
    return 1;
}

long mod(long n, long k, long m)
//计算 （n^k)%m
{
    long mod = 1;
    long base = n;
    long res = 1;
    if (n > m)
    { //先减小以下n的值,不然容易超long的范围
        n = n % m;
        base = n;
    }
    else if (n == m)
    {
        return 1;
    }
    while (k != 0)
    {
        if ((k & 1) == 1)
        { //取k的二进制最后一位,若为1,则表示存在该项
            mod *= (base % m);
            if (mod == 0)
            {
                return 0; //只要有一个数模为0,直接返回0
            }
            else if (mod > m)
            {
                mod %= m; //若模大于除数,则可以进行一次求模
            }
            base = base % m; // base求余,根据余数来算模,以免超出long的范围
        }
        base *= base; //将余数进行平方来算模,能减小数的大小
        base = base % m;
        k >>= 1; //将k的二进制往右移动一位
    }
    return mod;
}

void RKMATCH(int d, int q, int index)
//(d, q) 分别为：(2, 13), (2, 1009), (10, 13), (10, 1009)
{
    int t[5000];
    int n = strlen(text + 1);
    int m = strlen(pattern + 1);
    // int h = (long long)pow(d, m - 1) % q;
    int h = mod(d, m - 1, q);
    int p = 0;
    count = 0;
    false_hit[index] = 0;
    for (int i = 0; i < 5000; i++)
    {
        t[i] = 0;
    }
    for (int i = 1; i <= m; i++)
    {
        p = ((d * p + pattern[i]) % q + q) % q;
        t[0] = ((d * t[0] + text[i]) % q + q) % q;
    }
    for (int s = 0; s <= n - m; s++)
    {
        if ((p - t[s]) % q == 0)
        {
            if (compare_text(m, s))
            {
                count++;
                begin_pos[count] = s + 1;
            }
            else
                false_hit[index]++;
        }

        if (s < n - m)
            t[s + 1] = (((d * (t[s] - text[s + 1] * h) + text[s + m + 1]) % q) + q) % q;
    }
}
