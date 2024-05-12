#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <utility>
#include <queue>
#include <set>

using namespace std;

// write function bf() to calculate 1 step of the Bellman-Ford on the input graph
/*
The Graph
• Number of vertices
• Start vertex (A-Z)
• Current Bellman-Ford Value array
• Current Bellman-Ford Previous array
Output:
• Updated Bellman-Ford Value array based on the current Graph.
• Updated Bellman-Ford Previous matrix based on the current Graph.*/
void bf(int n, char start, vector<int> &bfv, vector<char> &bfp, vector<vector<pair<char, int>>> &graph)
{
    // Initialize the Bellman-Ford Value array and Bellman-Ford Previous array
    vector<int> bfv_new(n, INT_MAX);
    vector<char> bfp_new(n, '0');

    // Update the Bellman-Ford Value array and Bellman-Ford Previous array
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < graph[i].size(); j++)
        {
            if (bfv_new[i] > bfv[graph[i][j].first - 'A'] + graph[i][j].second)
            {
                bfv_new[i] = bfv[graph[i][j].first - 'A'] + graph[i][j].second;
                bfp_new[i] = graph[i][j].first;
            }
        }
    }

    // Update the Bellman-Ford Value array and Bellman-Ford Previous array
    bfv = bfv_new;
    bfp = bfp_new;
}