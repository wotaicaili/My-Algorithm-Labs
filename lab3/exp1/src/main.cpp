/*
 * @Author       : zongzi
 * @Date         : 2021-12-16 23:04:26
 * @LastEditors  : zongzi
 * @LastEditTime : 2021-12-20 18:00:34
 */
#include <iostream>
#include <fstream>
#include <ctime>
#include <climits>
#include <cstring>

#define MAX_N 1000

using namespace std;

const int N[5] = {0, 27, 81, 243, 729}; //顶点数
int graph[MAX_N][MAX_N];                //邻接矩阵存储图
int dis[MAX_N];                         //存储所有顶点到源点的距离
int road[MAX_N];                        //存储每个点的前驱
int a, b;                               //分别用来指定文件名的2个维度

ofstream fresult, ftime;
FILE *fin;

void bellman_ford(int n);
void output_road(int j, int flag);

int main()
{
    clock_t start, end;
    ftime.open("../output/time.txt", ios::out);
    for (a = 1; a <= 4; a++)
    {
        for (b = 1; b <= 2; b++)
        {
            string filename = "../input/input" + to_string(a) + to_string(b) + ".txt";
            fin = fopen(filename.data(), "r");

            fresult.open("../output/result" + to_string(a) + to_string(b) + ".txt", ios::out);

            //初始化
            memset(graph, 0, sizeof(graph));
            memset(road, 0, sizeof(road));
            for (int i = 0; i < N[a]; i++)
                dis[i] = INT_MAX;
            dis[0] = 0;

            //读取输入
            for (int i = 0; i < N[a]; i++)
                for (int j = 0; j < N[a]; j++)
                {
                    int tempt;
                    fscanf(fin, "%d,", &tempt);
                    if (tempt != 0)
                        graph[i][j] = tempt;
                    else if (i == j)
                        graph[i][j] = 0;
                    else
                        graph[i][j] = INT_MAX;
                }
            start = clock();
            // bellman_ford算法
            bellman_ford(N[a]);
            end = clock();

            //输出
            ftime << "input" + to_string(a) + to_string(b) + ".txt: ";
            ftime << long(end - start) / (CLOCKS_PER_SEC / 1000000) << "us" << endl;
            for (int j = 0; j < N[a]; j++)
            {
                if (dis[j] != INT_MAX)
                {
                    fresult << "0"
                            << ",";
                    fresult << j
                            << ",";
                    fresult << dis[j]
                            << ";";
                    output_road(j, 1);
                    fresult << endl;
                }
            }
            fresult.close();
        }
    }
}

void bellman_ford(int n)
// Bellman_Ford算法
// input:结点数目
{
    dis[0] = 0; // 初始可达0
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                //进行松弛操作
                if (graph[i][j] != INT_MAX && dis[i] != INT_MAX && dis[j] > dis[i] + graph[i][j])
                {
                    dis[j] = dis[i] + graph[i][j];
                    road[j] = i;
                }
            }
        }
}

void output_road(int j, int flag)
{
    if (j != 0)
        output_road(road[j], 0);
    if (flag == 0)
        fresult << j << ",";
    else
        fresult << j;
}
