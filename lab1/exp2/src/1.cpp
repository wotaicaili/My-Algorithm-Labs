
// 动态规划求解并输出所有LCS
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

string X = "ABCBDAB";
string Y = "BDCABA";
vector<vector<int>> table; // 动态规划表
set<string> setOfLCS;      // set保存所有的LCS

int max(int a, int b)
{
    return (a > b) ? a : b;
}

/** 
 * 字符串逆序
 */
string Reverse(string str)
{
    int low = 0;
    int high = str.length() - 1;
    while (low < high)
    {
        char temp = str[low];
        str[low] = str[high];
        str[high] = temp;
        ++low;
        --high;
    }
    return str;
}

/** 
 * 构造表，并返回X和Y的LCS的长度
 */
int lcs(int m, int n)
{
    // 表的大小为(m+1)*(n+1)
    table = vector<vector<int>>(m + 1, vector<int>(n + 1));

    for (int i = 0; i < m + 1; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
        {
            // 第一行和第一列置0
            if (i == 0 || j == 0)
                table[i][j] = 0;

            else if (X[i - 1] == Y[j - 1])
                table[i][j] = table[i - 1][j - 1] + 1;

            else
                table[i][j] = max(table[i - 1][j], table[i][j - 1]);
        }
    }

    return table[m][n];
}

/** 
 * 求出所有的最长公共子序列，并放入set中 
 */
void traceBack(int i, int j, string lcs_str)
{
    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs_str.push_back(X[i - 1]);
            --i;
            --j;
        }
        else
        {
            if (table[i - 1][j] > table[i][j - 1])
                --i;
            else if (table[i - 1][j] < table[i][j - 1])
                --j;
            else // 相等的情况
            {
                traceBack(i - 1, j, lcs_str);
                traceBack(i, j - 1, lcs_str);
                return;
            }
        }
    }

    setOfLCS.insert(Reverse(lcs_str));
}

int main()
{
    int m = X.length();
    int n = Y.length();
    int length = lcs(m, n);
    cout << "The length of LCS is " << length << endl;
    string str;
    traceBack(m, n, str);

    set<string>::iterator beg = setOfLCS.begin();
    for (; beg != setOfLCS.end(); ++beg)
        cout << *beg << endl;

    getchar();
    return 0;
}
