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
int graph[MAX_N][MAX_N];                //邻接矩阵存储图 创造源点标号为0
int graph_new[MAX_N][MAX_N];            //邻接矩阵存储图 修改代价
int dis[MAX_N];                         //存储所有顶点到源点的距离
int a, b;                               //分别用来指定文件名的2个维度
int cost[MAX_N][MAX_N];                 //存储最终最短路径的长度

ofstream fresult,
    ftime;
FILE *fin; //吐槽下逗号分隔导致流读入比较麻烦，换成fscanf

void bellman_ford(int n);
void dijkstra(int n, int i);

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
            memset(graph, 0, sizeof(graph));     //初始化graph
            memset(graph_new, 0, sizeof(graph)); //初始化graph_new
            for (int i = 1; i <= N[a]; i++)      //初始化cost
            {
                for (int j = 1; j <= N[a]; j++)
                {
                    if (i == j)
                        cost[i][j] = 0;
                    else
                        cost[i][j] = INT_MAX;
                }
            }
            for (int i = 0; i <= N[a]; i++) //初始化dis
                dis[i] = INT_MAX;

            //读取输入
            for (int i = 1; i <= N[a]; i++)
                for (int j = 1; j <= N[a]; j++)
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
            //创造虚拟的0号结点
            for (int j = 0; j <= N[a]; j++)
                graph[0][j] = 0;

            // bellman_ford算法
            bellman_ford(N[a] + 1);

            // reweight操作
            for (int i = 1; i <= N[a]; i++)
                for (int j = 1; j <= N[a]; j++)
                {
                    if (graph[i][j] != INT_MAX)
                        graph_new[i][j] = graph[i][j] + dis[i] - dis[j];
                    else
                        graph_new[i][j] = graph[i][j];
                }

            //对每个点进行dijkstra算法
            for (int i = 1; i <= N[a]; i++)
                dijkstra(N[a], i);
            end = clock();

            //输出
            ftime << "input" + to_string(a) + to_string(b) + ".txt: ";
            ftime << long(end - start) / (CLOCKS_PER_SEC / 1000000) << "us" << endl;
            for (int i = 1; i <= N[a]; i++)
                for (int j = 1; j <= N[a]; j++)
                {
                    if (cost[i][j] != INT_MAX)
                        fresult << cost[i][j] << " ";
                    else
                        fresult << "X ";
                    if (j == N[a])
                        fresult << endl;
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
                }
            }
        }
}
void dijkstra(int n, int i)
// Dijkstra算法
// input:结点数目,源点标号
{
    //初始化 dij_dis 存储所有点到源点最短距离
    int dij_dis[n + 1];
    for (int j = 1; j <= n; j++)
    {
        dij_dis[j] = graph_new[i][j];
        cost[i][j] = graph[i][j];
    }

    //初始化 if_sure 标记确定的点
    int if_sure[n + 1];
    for (int j = 1; j <= n; j++)
        if_sure[j] = 0;
    if_sure[i] = 1;

    int min; //用来寻找ij_dis最小的点
    int u;   //每次找到的ij_dis最小的点

    for (int j = 1; j < n; j++)
    //循环n-1次
    {
        min = INT_MAX;
        for (int k = 1; k <= n; k++)
        // 找到ij_dis中未标记点中的最小值
        {
            if (if_sure[k] == 0 && dij_dis[k] < min)
            {
                min = dij_dis[k];
                u = k;
            }
        }
        if_sure[u] = 1;

        for (int m = 1; m <= n; m++)
        //更新dij_dis
        {
            if (graph[u][m] < INT_MAX)
            {
                if (dij_dis[m] > dij_dis[u] + graph_new[u][m])
                {
                    dij_dis[m] = dij_dis[u] + graph_new[u][m];
                    cost[i][m] = cost[i][u] + graph[u][m];
                }
            }
        }
    }
}