#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <utility>
#include <queue>
#include <set>
#include <assert.h>

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
• Updated Bellman-Ford Previous matrix based on the current Graph.
The input graphs will be weight matrices, where all the connected weights are positive integers,
and 0 means not-connected. (Datatype int[][])
• The Value array for Bellman-Ford is initiated as an all -1 array, Element [i] is the distance of
the path from the Start vertex to vertex ith. (Datatype int[])
• The Previous array for Bellman-Ford is initiated as an all -1 array, Element [i] is the previous
vertex on the path to vertex ith from the Start vertex. (Datatype int[])
• The output of the BF_Path() function is a string containing the names of the vertices in the
path separate by a whitespace for example: "A D C B" representing the path going from A
to D to C and then B. (Datatype string)
• The Start and Goal are type char. The Vertices will always be named using the uppercase
alphabet in order where vertex 0th is ’A’, 1st is ’B’, and so on. (Datatype char)*/

template <size_t N>
void BF(int (&graph)[N][N], int numOfVertex, char start, int *value, int *prev)
{
    // Initialize the value of the start vertex to 0
    // every value must be set to infinity
    for (int i = 0; i < numOfVertex; i++)
    {
        if (i != start - 'A')
        {
            value[i] = INT_MAX;
        }
    }
    value[start - 'A'] = 0;
    prev[start - 'A'] = 0;

    cout << "Start: " << start << endl;

    // Relax edges numOfVertex - 1 times
    for (int u = 0; u < numOfVertex; u++)
    {
        for (int v = 0; v < numOfVertex; v++)
        {
            if (graph[u][v] != 0 && graph[u][v] != INT_MAX && value[u] != INT_MAX && value[u] + graph[u][v] < value[v])
            {
                cout << "before update:" << endl;
                cout << u << " " << v << endl;
                cout << value[u] << " " << graph[u][v] << " " << value[v] << endl;
                value[v] = value[u] + graph[u][v];
                cout << "after update:" << endl;
                cout << value[u] << " " << graph[u][v] << " " << value[v] << endl;
                prev[v] = u;
            }
        }
    }
    // remove the negative circle
    for (int u = 0; u < numOfVertex; u++)
    {
        for (int v = 0; v < numOfVertex; v++)
        {
            if (graph[u][v] != 0 && graph[u][v] != INT_MAX && value[u] != INT_MAX && value[u] + graph[u][v] < value[v])
            {
                return;
            }
        }
    }
}

// template <size_t N>
// void BF(int (*graph)[N], int numOfVertex, char start, int *value, int *prev)
// {
//     // Initialize the value of the start vertex to 0
//     value[start - 'A'] = 0;
//     // every value must be set to infinity
//     for (int i = 0; i < numOfVertex; i++)
//     {
//         if (i != start - 'A')
//         {
//             value[i] = INT_MAX;
//         }
//     }

//     // Relax edges numOfVertex - 1 times
//     for (int u = 0; u < numOfVertex; u++)
//     {
//         for (int v = 0; v < numOfVertex; v++)
//         {
//             if (graph[u][v] != INT_MAX && value[u] != INT_MAX && value[u] + graph[u][v] < value[v])
//             {
//                 value[v] = value[u] + graph[u][v];
//                 prev[v] = u;
//             }
//         }
//     }
// }

void test_bf()
{
    int graph[6][6] = {
        {0, 1, 4, 0, 0, 0},
        {0, 0, 2, 2, 0, 0},
        {0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 2},
        {0, 0, 0, 1, 0, 2},
        {0, 0, 0, 0, 0, 0}};
    int value[6];
    int prev[6];
    BF(graph, 6, 'A', value, prev);
    for (int i = 0; i < 6; i++)
    {
        cout << value[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << prev[i] << " ";
    }
}

void test_bf2()
{
    int graph[8][8] = {
        {0, 1, 2, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 4, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    int value[8];
    int prev[8];
    BF(graph, 8, 'A', value, prev);
    for (int i = 0; i < 8; i++)
    {
        cout << value[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << prev[i] << " ";
    }
}

void test_bf3()
{
    int graph[8][8] = {
        {0, 1, 2, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 4, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 6},
        {0, 0, 0, 0, 0, 7, 0, 0},
        {0, 0, 0, 0, 0, 0, 8, 0},
        {0, 0, 0, 0, 0, 0, 0, 9},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    int value[8];
    int prev[8];
    BF(graph, 8, 'A', value, prev);
    for (int i = 0; i < 8; i++)
    {
        cout << value[i] << " ";
    }
}

void test_bf4()
{
    int graph[8][8] = {
        {0, 1000, 2000, 0, 0, 0, 0, 0},
        {0, 0, 0, 3000, 4000, 0, 0, 0},
        {0, 0, 0, 0, 0, 5000, 6000, 0},
        {0, 0, 0, 0, 0, 0, 0, 7000},
        {0, 0, 0, 0, 0, 8000, 0, 0},
        {0, 0, 0, 0, 0, 0, 9000, 0},
        {0, 0, 0, 0, 0, 0, 0, 10000},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    int value[8];
    int prev[8];
    BF(graph, 8, 'A', value, prev);
    for (int i = 0; i < 8; i++)
    {
        cout << value[i] << " ";
    }
}

void test_bf6()
{
    int graph[6][6] = {
        {0, 20, 40, 0, 0, 0},
        {0, 0, 40, 20, 40, 0},
        {0, 0, 0, 40, 60, 0},
        {0, 0, 0, 0, 20, 40},
        {0, 0, 0, 0, 0, 10},
        {0, 0, 0, 0, 0, 0}};
    int value[6];
    int prev[6];
    BF(graph, 6, 'A', value, prev);
    for (int i = 0; i < 6; i++)
    {
        cout << value[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << prev[i] << " ";
    }
}

int main()
{
    test_bf6();
    return 0;
    // print the value and prev out
}