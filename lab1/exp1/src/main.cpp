#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;
ifstream fin;
ofstream fresult, ftime;
void CalculateMin(int i, int j, long long p[], long long **m, long long **s)
{
    m[i][j] = m[i][i] + m[i + 1][j] + p[i - 1] * p[i] * p[j];
    s[i][j] = i;
    for (int k = i + 1; k < j; k++)
    {
        long long curr = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
        if (curr < m[i][j])
        {
            m[i][j] = curr;
            s[i][j] = k;
        }
    }
}
void MatrixChain(int n, long long p[], long long **m, long long **s)
{
    for (int i = n; i >= 1; i--)
        for (int j = i; j <= n; j++)
        {
            if (i == j)
                m[i][j] = 0;
            else
                CalculateMin(i, j, p, m, s);
        }
}

void PrintScheme(int i, int j, long long **s)
{
    if (i == j)
        fresult << "A" << i;
    else
    {
        fresult << "(";
        PrintScheme(i, s[i][j], s);
        PrintScheme(s[i][j] + 1, j, s);
        fresult << ")";
    }
}

int main()
{
    clock_t start, end;

    fin.open("../input/1_1_input.txt", ios::in);
    if (!fin.is_open())
    {
        std::cerr << "cannot open the file";
        exit(1);
    }
    fresult.open("../output/result.txt", ios::out);
    ftime.open("../output/time.txt", ios::out);

    while (!fin.eof())
    {
        int n;
        if (!(fin >> n))
            break;
        long long *p = new long long[n + 1];
        for (int i = 0; i < n + 1; i++)
            fin >> p[i];
        long long **m = new long long *[n + 1];
        long long **s = new long long *[n + 1];
        for (int i = 1; i <= n; i++)
        {
            m[i] = new long long[n + 1];
            s[i] = new long long[n + 1];
        }
        start = clock();
        MatrixChain(n, p, m, s);
        end = clock();
        fresult << m[1][n] << endl;
        PrintScheme(1, n, s);
        fresult << endl;
        ftime << long(end - start) / (CLOCKS_PER_SEC / 1000000) << "us" << endl;

        if (n == 5)
        {
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                {
                    cout << setiosflags(ios::left) << setw(15);
                    cout << m[i][j] << " ";
                    if (j == n)
                        cout << endl;
                }
        }
    }
    fin.close();
    fresult.close();
    ftime.close();
    return 0;
}
