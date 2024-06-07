#include "bellman.h"
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
static int INF = 2147483647;
void BF(int G[][20], int n, char start, int value[20], int prev[20])
{
    // Initialization step
    int a = start - 'A';
    value[a] = 0;
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if (value[i] == -1)
            count++;
    }
    if (count == n - 1)
    {
        // Set first value to the distance from start to other vertices, except itself
        for (int i = 0; i < n; i++)
        {
            if (i != a)
                value[i] = G[a][i];
        }
        // Set the prev
        for (int i = 0; i < n; i++)
        {
            if (i != a)
                prev[i] = a;
        }
        return;
    }
    int prev_val[n];
    int check[n];

    for (int u = 0; u < n; u++)
    {
        for (int v = 0; v < n; v++)
        {
            if (G[u][v] != 0 && G[u][v] != INF)
            {
                if (check[u] != 1)
                {
                    int distance = value[u] + G[u][v];
                    if (distance < value[v])
                    {
                        prev_val[v] = value[v];
                        value[v] = distance;
                        prev[v] = u;
                        check[v] = 1;
                    }
                }
                else
                {
                    int distance = prev_val[u] + G[u][v];
                    if (distance < value[v])
                    {
                        prev_val[v] = value[v];
                        value[v] = distance;
                        prev[v] = u;
                        check[v] = 1;
                    }
                }
            }
        }
    }
}

string BF_Path(int G[20][20], int num, char start, char goal)
{
    int BFValue[num];
    int BFPrev[num];
    for (int i = 0; i < num; i++)
    {
        BFValue[i] = INF; // Initialize all distances as infinite
        BFPrev[i] = -1;   // Initialize all previous vertices as undefined
    }

    int a = start - 'A';
    BFValue[a] = 0; // Distance from start to itself is 0

    // Relaxation step
    for (int i = 0; i < num - 1; i++)
    {
        for (int u = 0; u < num; u++)
        {
            for (int v = 0; v < num; v++)
            {
                if (G[u][v] != 0 && BFValue[u] != INF && BFValue[u] + G[u][v] < BFValue[v])
                {
                    BFValue[v] = BFValue[u] + G[u][v];
                    BFPrev[v] = u;
                }
            }
        }
    }

    // Check for negative cycles
    for (int u = 0; u < num; u++)
    {
        for (int v = 0; v < num; v++)
        {
            if (G[u][v] != 0 && BFValue[u] != INF && BFValue[u] + G[u][v] < BFValue[v])
            {
                return 0;
            }
        }
    }
    string path = "";
    int current = goal - 'A';
    while (current != -1)
    {

        // add a space between letters
        if (BFPrev[current] != -1)
        {
            path = " " + path;
        }
        path = (char)(current + 'A') + path;
        current = BFPrev[current];
    }
    return path;
}

void test_bf2()
{
    int graph[20][20] = {
        {0, 72, 89, 77, 2, 58, 13, 69},
        {77, 0, 69, 31, 57, 93, 83, 48},
        {52, 21, 0, 62, 8, 77, 32, 14},
        {33, 1, 40, 0, 72, 99, 72, 59},
        {89, 24, 1, 61, 0, 12, 78, 63},
        {36, 91, 98, 79, 26, 0, 28, 1},
        {18, 77, 49, 36, 98, 77, 0, 45},
        {75, 9, 59, 7, 77, 65, 45, 0}};
    int value[8];
    int prev[8];
    for (int i = 0; i < 8; i++)
    {
        value[i] = -1;
        prev[i] = -1;
    }
    for (int i = 0; i < 7; i++)
    {
        BF(graph, 8, 'D', value, prev);
        cout << "Step " << i << ": " << endl;
        for (int i = 0; i < 8; i++)
        {
            cout << value[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < 8; i++)
        {
            cout << prev[i] << " ";
        }
        cout << endl;
    }

    /*
    33 1 36 0 35 47 46 48
    3 3 4 -1 0 4 0 5
*/
}

void test_bf3()
{
    int graph[20][20] = {
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
    int graph[20][20] = {
        {0, 0, 0, 33, 0, 0, 0, 0}, // A
        {0, 0, 0, 3, 0, 0, 0, 0},  // B
        {0, 0, 0, 40, 0, 0, 0, 0}, // C
        {0, 0, 0, 0, 0, 0, 0, 0},  // D
        {0, 0, 0, 72, 0, 0, 0, 0}, // E
        {0, 0, 0, 99, 0, 0, 0, 0}, // F
        {0, 0, 0, 72, 0, 0, 0, 0}, // G
        {0, 0, 0, 59, 0, 0, 0, 0}  // H
    };
    int value[8];
    int prev[8];
    BF(graph, 8, 'D', value, prev);
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

void test_bf6()
{
    int graph[20][20] = {
        {0, 5, 0, 0}, // A
        {0, 0, 2, 0}, // B
        {0, 0, 0, 3}, // C
        {0, 0, 0, 0}  // D
    };
    int value[4];
    int prev[4];
    BF(graph, 4, 'A', value, prev);
    for (int i = 0; i < 4; i++)
    {
        cout << value[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << prev[i] << " ";
    }
}

void test_bf_path()
{
    int graph[20][20] = {
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // A
        {0, 0, 2, 0, 0, 0, 0, 0, 0, 0}, // B
        {0, 0, 0, 3, 0, 0, 0, 0, 0, 0}, // C
        {0, 0, 0, 0, 4, 0, 0, 0, 0, 0}, // D
        {0, 0, 0, 0, 0, 5, 0, 0, 0, 0}, // E
        {0, 0, 0, 0, 0, 0, 6, 0, 0, 0}, // F
        {0, 0, 0, 0, 0, 0, 0, 7, 0, 0}, // G
        {0, 0, 0, 0, 0, 0, 0, 0, 8, 0}, // H
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 9}, // I
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // J
    };
    int value[10] = {0, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX};
    int prev[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    BF_Path(graph, 10, 'A', 'J');
}

// void BF_Path(int graph[20][20], int num, char start, char goal)
// {
//     for (int i = 0; i < num; i++)
//     {
//         for (int j = 0; j < num; j++)
//         {
//             cout << graph[i][j] << " ";
//             if (j == num - 1)
//             {
//                 cout << endl;
//             }
//         }
//     }
// }

int main()
{
    test_bf2();
    return 0;
    // print the value and prev out
}
