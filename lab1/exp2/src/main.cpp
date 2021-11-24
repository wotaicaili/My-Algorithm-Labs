#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
ifstream fin;
ofstream fresult, ftime;
vector<string> veclcs;

void Lcs(int n, string X, string Y, int **c)
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

void Trace(int i, int j, string X, string Y, int **c, string Lcs_str)
{
    while (i != 0 && j != 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            Lcs_str = X[i - 1] + Lcs_str;
            --i;
            --j;
        }
        else
        {
            if (c[i - 1][j] > c[i][j - 1])
                --i;
            else if (c[i - 1][j] < c[i][j - 1])
                --j;
            else
            {
                Trace(i - 1, j, X, Y, c, Lcs_str);
                Trace(i, j - 1, X, Y, c, Lcs_str);
                return;
            }
        }
    }
    veclcs.push_back(Lcs_str);
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
    while (!fin.eof())
    {
        int n;
        if (!(fin >> n))
            break;
        count++;
        fresult.open("../output/result_" + std::to_string(count) + ".txt");
        string X, Y;
        fin >> X;
        fin >> Y;

        int **c = new int *[n + 1];
        for (int i = 0; i <= n; i++)
            c[i] = new int[n + 1];

        start = clock();
        Lcs(n, X, Y, c);
        end = clock();
        ftime << long(end - start) / (CLOCKS_PER_SEC / 1000000) << "us" << endl;
        string Lcs_str;
        Trace(n, n, X, Y, c, Lcs_str);
        fresult << veclcs.size() << endl;
        for (int i = 0; i < veclcs.size(); i++)
        {
            fresult << veclcs[i] << endl;
        }
        veclcs.clear();
        fresult.close();
    }

    return 0;
}