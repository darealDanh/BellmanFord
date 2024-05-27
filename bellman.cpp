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
static const int INF = 2147483647;
void BF(int graph[20][20], int numOfVertex, char start, int *value, int *prev)
{
    // Initialize the value of the start vertex to 0
    // every value must be set to infinity
    // cout << "Start: " << start << endl;
    // Relax edges numOfVertex - 1 times
    static int step = 0;

    if (step == 0)
    {
        for (int i = 0; i < numOfVertex; i++)
        {
            value[i] = INF;
            prev[i] = -1;
        }
        value[start - 'A'] = 0;
    }
    for (int u = 0; u < numOfVertex; u++)
    {
        for (int v = 0; v < numOfVertex; v++)
        {
            if (graph[u][v] != 0 && value[u] != INF && value[u] + graph[u][v] < value[v])
            {
                value[v] = value[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }
    // check for negative circle
    if (step >= numOfVertex)
    {
        for (int u = 0; u < numOfVertex; u++)
        {
            for (int v = 0; v < numOfVertex; v++)
            {
                if (value[u] != INT_MAX && value[u] + graph[u][v] < value[v])
                {
                    return;
                }
            }
        }
        return;
    }
    step++;
}

void BF_Path(int graph[20][20], int num, char start, char goal)
{
    int value[num];
    int prev[num];
    BF(graph, num, start, value, prev);
    // print the value and prev out
    cout << "Value: ";
    // for (int i = 0; i < num; i++)
    // {
    //     cout << value[i] << " ";
    // }
    // cout << endl;
    // cout << "Prev: ";
    // for (int i = 0; i < num; i++)
    // {
    //     cout << prev[i] << " ";
    // }
    // cout << endl;
    // print the path
    string path = "";
    int current = goal - 'A';
    while (current != -1)
    {
        path = (char)(current + 'A') + path;
        // add a space between letters
        if (prev[current] != -1)
        {
            path = " " + path;
        }
        current = prev[current];
    }
    cout << path << endl;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            cout << graph[i][j] << " ";
            if (j == num - 1)
            {
                cout << endl;
            }
        }
    }
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
    }
    for (int i = 0; i < 8; i++)
    {
        cout << value[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << prev[i] << " ";
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
