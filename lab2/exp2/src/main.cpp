#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
ifstream fin;
ofstream fresult, ftime;

class DisjSet
{
private:
    vector<int> parent;
    vector<int> rank; // 秩

public:
    DisjSet(int max_size)
        : parent(vector<int>(max_size)), rank(vector<int>(max_size, 0))
    {
        for (int i = 0; i < max_size; ++i)
            parent[i] = i;
    }

    int find(int x)
    {
        if (x == parent[x])
            return x;
        else
        {
            parent[x] = find(parent[x]);
            return parent[x];
        }
    }

    void to_union(int x1, int x2)
    {
        int f1 = find(x1);
        int f2 = find(x2);
        if (rank[f1] > rank[f2])
            parent[f2] = f1;
        else
        {
            parent[f1] = f2;
            if (rank[f1] == rank[f2])
                ++rank[f2];
        }
    }

    bool is_same(int e1, int e2)
    {
        return find(e1) == find(e2);
    }
};

int BuildSet(int number, int size, vector<int> input)
{
    DisjSet *set;
    set = new DisjSet(size);
    int number1 = 0;
    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            number1 = number + size * i + j;
            if (input[number1] == 1)
            {
                set->to_union(i, j);
            }
        }
    }

    vector<int> vec;

    for (int i = 0; i < size; i++)
    {
        int value = set->find(i);
        if (find(vec.begin(), vec.end(), value) == vec.end())
        {
            vec.push_back(value);
        }
    }
    return vec.size();
}

int main()
{
    fin.open("../input/2_2_input.txt", ios::in);
    if (!fin.is_open())
    {
        std::cerr << "cannot open the file";
        exit(1);
    }
    fresult.open("../output/result.txt", ios::out);
    ftime.open("../output/time.txt", ios::out);
    vector<int> N = {10, 15, 20, 25, 30};
    vector<int> input;
    int number = 0;
    while (!fin.eof())
    {
        fin >> number;
        input.push_back(number);
    }
    fin.close();
    number = 0;
    clock_t start, end;
    for (int i = 0; i < N.size(); i++)
    {
        start = clock();
        fresult << BuildSet(number, N[i], input) << endl;
        end = clock();
        ftime << long(end - start) / (CLOCKS_PER_SEC / 1000000) << "us" << endl;
        number += N[i] * N[i];
    }
}