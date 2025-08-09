#include "tsm.h"
// const static int INF = 2147483647;

string Traveling(int adj[][20], int n, char start_vertex)
{
    // the traveling salemen problem optimal solution, dynamic programming
    int value[1 << n][n];
    int prev[1 << n][n];
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            value[i][j] = INF;
            prev[i][j] = -1;
        }
    }
    value[1 << (start_vertex - 'A')][start_vertex - 'A'] = 0;
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((i & (1 << j)) == 0 && j != start_vertex - 'A')
                continue;
            for (int k = 0; k < n; k++)
            {
                if ((i & (1 << k)) == 0 || k == j)
                    continue;
                if (value[i][j] > value[i ^ (1 << j)][k] + adj[k][j])
                {
                    value[i][j] = value[i ^ (1 << j)][k] + adj[k][j];
                    prev[i][j] = k;
                }
            }
        }
    }

    int min_index = -1;
    int min_value = INF;
    for (int i = 0; i < n; i++)
    {
        if (i != start_vertex - 'A' && value[(1 << n) - 1][i] + adj[i][start_vertex - 'A'] < min_value)
        {
            min_value = value[(1 << n) - 1][i] + adj[i][start_vertex - 'A'];
            min_index = i;
        }
    }
    string path = "";
    int cur = (1 << n) - 1;
    int cur_vertex = min_index;
    while (cur_vertex != -1)
    {
        if (path != "")
        {
            path = " " + path;
        }
        path = (char)(cur_vertex + 'A') + path;
        int next_vertex = prev[cur][cur_vertex];
        cur ^= (1 << cur_vertex);
        cur_vertex = next_vertex;
    }
    path = path + " " + start_vertex;
    return path;
}
