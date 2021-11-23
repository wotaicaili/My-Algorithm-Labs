#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
ifstream fin;
ofstream fresult, ftime;
vector<string> veclcs; // 保存LCS

void lcs(int n, string X, string Y, int **c)
{
    c[0][0] = 0;
    for (int i = 1; i <= n; ++i)
        c[i][0] = 0;
    for (int j = 1; j <= n; ++j)
        c[0][j] = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (X[i - 1] == Y[j - 1])
                c[i][j] = c[i - 1][j - 1] + 1;
            else
                c[i][j] = max(c[i - 1][j], c[i][j - 1]);
        }
    }
}

void traceBack(int i, int j, string X, string Y, int **c, string lcs_str)
{
    if (i == 0 || j == 0)
        veclcs.push_back(lcs_str);
    else
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs_str = X[i - 1] + lcs_str;
            --i;
            --j;
        }
        else
        {
            if (c[i - 1][j] > c[i][j - 1])
                --i;
            else if (c[i - 1][j] < c[i][j - 1])
                --j;
            else // 相等的情况
            {
                traceBack(i - 1, j, X, Y, c, lcs_str);
                traceBack(i, j - 1, X, Y, c, lcs_str);
                return;
            }
        }
    }
}

int main()
{
    clock_t start, end;
    fin.open("../input/1_2_input.txt", ios::in);
    if (!fin.is_open())
    {
        std::cerr << "cannot open the file";
        exit(1);
    }
    ftime.open("../output/time.txt", ios::out);
    int count = 0;

    int n;
    //if (!(fin >> n))
    //break;
    cout << n << endl;
    count++;
    cout << count << endl;
    fresult.open("../output/result_" + std::to_string(count) + ".txt");
    string X, Y;
    fin >> X;
    fin >> Y;

    int **c = new int *[n + 1];
    for (int i = 0; i <= n; i++)
        c[i] = new int[n + 1];

    start = clock();
    lcs(n, X, Y, c);
    end = clock();
    ftime << double(end - start) / CLOCKS_PER_SEC << "s" << endl;

    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j < n + 1; j++)
        {
            cout << c[i][j] << " ";
            if (j == n)
                cout << endl;
        }

    string lcs_str;
    traceBack(n, n, X, Y, c, lcs_str);
    fresult << veclcs.size() << endl;
    for (int i = 0; i < veclcs.size(); i++)
    {
        fresult << veclcs[i] << endl;
    }
    veclcs.clear();
    fresult.close();

    return 0;
}