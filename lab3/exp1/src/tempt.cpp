/*
 * @Author       : zsr
 * @Date         : 2021-12-16 23:04:26
 * @LastEditors  : zsr
 * @LastEditTime : 2021-09-20 18:00:34
 * @Description  : Bellman_Ford
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
#include <map>
#include <iterator>
#include <list>
#include <set>
#include <functional>
#include <ctime>

void init()
{
    memset(dis, inf, sizeof(dis));
    memset(graph, inf, sizeof(graph));
}

int bellman_ford(int S)
{
    dis[S] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            //进行松弛操作
            if (dis[j] > dis[i] + graph[i][j])
            {
                dis[j] = dis[i] + graph[i][j];
            }
        }
    }
    int flag = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            //进行松弛操作
            if (dis[j] > dis[i] + graph[i][j])
            {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}
int main()
{
    while (cin >> n >> m)
    {
        int u, v, w;
        init();
        for (int i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            graph[u][v] = graph[v][u] = w;
        }
        int S, E; //起点与终点。
        cin >> S >> E;
        int result = bellman_ford(S);
        if (result)
            cout << "此存在负权回路，计算两点之间距离可能没有意义,输出的仅供参考" << endl;
        cout << dis[E] << endl;
    }
    return 0;
}
