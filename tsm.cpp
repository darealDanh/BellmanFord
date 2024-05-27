#include <tsm.h>

template <size_t N>
string Travelling(int (&graph)[N][N], int n, char start)
{
    // the travelling salesman problem
    // initialize the dp array
    int dp[1 << n][n];
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = INT_MAX;
        }
    }
    dp[1 << (start - 'A')][start - 'A'] = 0;
    // start the dp
    for (int i = 1; i < (1 << n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                for (int k = 0; k < n; k++)
                {
                    if (i & (1 << k) && graph[k][j] != 0 && dp[i ^ (1 << j)][k] != INT_MAX)
                    {
                        dp[i][j] = min(dp[i][j], dp[i ^ (1 << j)][k] + graph[k][j]);
                    }
                }
            }
        }
    }
    // find the minimum path
    int min = INT_MAX;
    int minIndex = -1;
    for (int i = 0; i < n; i++)
    {
        if (dp[(1 << n) - 1][i] < min)
        {
            min = dp[(1 << n) - 1][i];
            minIndex = i;
        }
    }
    // print the path
    string path = "";
    int current = minIndex;
    int currentSet = (1 << n) - 1;
    while (currentSet != 0)
    {
        path = (char)(current + 'A') + path;
        int next = -1;
        for (int i = 0; i < n; i++)
        {
            if (currentSet & (1 << i) && graph[i][current] != 0 && dp[currentSet][current] == dp[currentSet ^ (1 << current)][i] + graph[i][current])
            {
                next = i;
                break;
            }
        }
        currentSet ^= (1 << current);
        current = next;
    }
}