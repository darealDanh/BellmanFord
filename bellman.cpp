#include "bellman.h"
void BF(int G[60][60], int n, char start, int value[60], int prev[60]) {
    int src = -1;
    if (start >= 'A' && start <= 'Z') {
        src = start - 'A';
    } else if (start >= 'a' && start <= 'z') {
        src = 26 + (start - 'a');
    }
    if (src < 0 || src >= n) return;

    // Detect first call: all entries are -1
    int first_call = 1;
    for (int i = 0; i < n; ++i) {
        if (value[i] != -1) { first_call = 0; break; }
    }

    if (first_call) {
        // Initialization
        for (int i = 0; i < n; ++i) {
            value[i] = -1;
            prev[i]  = -1;
        }
        value[src] = 0;

        // One-hop neighbors from src (0 => no edge)
        for (int i = 0; i < n; ++i) {
            if (i == src) continue;
            if (G[src][i] != 0) {
                value[i] = G[src][i];
                prev[i]  = src;
            }
        }
        return; // exactly one init step
    }

    // One relaxation pass (clone read, write to value/prev)
    int clone[60];
    for (int i = 0; i < n; ++i) clone[i] = value[i];

    for (int u = 0; u < n; ++u) {
        if (clone[u] == -1) continue;        // unreachable
        for (int v = 0; v < n; ++v) {
            if (G[u][v] == 0) continue;      // no edge u->v
            int cand = clone[u] + G[u][v];
            if (value[v] == -1 || cand < value[v]) {
                value[v] = cand;
                prev[v]  = u;
            }
        }
    }
}

// Returns the shortest path from `start` to `goal` as labels separated by spaces.
// Rules:
//  1) lowest total cost
//  2) if tied, fewer hops
//  3) if still tied, smaller predecessor index (earlier label)
// Assumes G[u][v] == 0 means "no edge".
string BF_Path(int G[60][60], int num, char start, char goal)
{
    const int INF = 1000000000;

    // label -> index (A..Z -> 0..25, a..z -> 26..51)
    int s = -1, t = -1;
    if (start >= 'A' && start <= 'Z') s = start - 'A';
    else if (start >= 'a' && start <= 'z') s = 26 + (start - 'a');
    if (goal  >= 'A' && goal  <= 'Z') t = goal  - 'A';
    else if (goal  >= 'a' && goal  <= 'z') t = 26 + (goal  - 'a');

    if (s < 0 || s >= num || t < 0 || t >= num) return "";

    // Trivial case
    if (s == t) {
        string one(1, (s < 26) ? char('A' + s) : char('a' + (s - 26)));
        return one;
    }

    // State
    int dist[60], hops[60], prev[60];
    for (int i = 0; i < num; ++i) {
        dist[i] = INF;
        hops[i] = INF;
        prev[i] = -1;
    }
    dist[s] = 0;
    hops[s] = 0;

    // Relax edges (Bellman–Ford) with deterministic tie-breaks
    for (int it = 0; it < num - 1; ++it) {
        int changed = 0;
        for (int u = 0; u < num; ++u) {
            if (dist[u] == INF) continue;
            for (int v = 0; v < num; ++v) {
                if (u == v || G[u][v] == 0) continue;
                const int nd = dist[u] + G[u][v];
                const int nh = hops[u] + 1;

                if (nd < dist[v]) {
                    dist[v] = nd; hops[v] = nh; prev[v] = u; changed = 1;
                } else if (nd == dist[v]) {
                    if (nh < hops[v]) {
                        hops[v] = nh; prev[v] = u; changed = 1;
                    } else if (nh == hops[v] && (prev[v] == -1 || u < prev[v])) {
                        prev[v] = u; changed = 1;
                    }
                }
            }
        }
        if (!changed) break;
    }

    // Negative-cycle reachable from s?
    for (int u = 0; u < num; ++u) {
        if (dist[u] == INF) continue;
        for (int v = 0; v < num; ++v) {
            if (u == v || G[u][v] == 0) continue;
            if (dist[u] + G[u][v] < dist[v]) return "";
        }
    }
    if (dist[t] == INF) return ""; // unreachable

    // Reconstruct s -> t
    int path[60], used[60], len = 0;
    for (int i = 0; i < num; ++i) used[i] = 0;

    for (int cur = t; cur != -1 && !used[cur] && len < num; cur = prev[cur]) {
        used[cur] = 1;
        path[len++] = cur;
    }

    // Emit labels with single spaces
    string out;
    for (int i = len - 1; i >= 0; --i) {
        const int idx = path[i];
        const char lbl = (idx < 26) ? char('A' + idx) : char('a' + (idx - 26));
        if (!out.empty()) out += " ";
        out += lbl;
    }
    return out;
}


// void test_bf2()
// {
//     int graph[20][20] = {
//         {0, 72, 89, 77, 2, 58, 13, 69},  // A
//         {77, 0, 69, 31, 57, 93, 83, 48}, // B
//         {52, 21, 0, 62, 8, 77, 32, 14},  // C
//         {33, 1, 40, 0, 72, 99, 72, 59},  // D
//         {89, 24, 1, 61, 0, 12, 78, 63},  // E
//         {36, 91, 98, 79, 26, 0, 28, 1},  // F
//         {18, 77, 49, 36, 98, 77, 0, 45}, // G
//         {75, 9, 59, 7, 77, 65, 45, 0}};  // H
//     /*-377806379 32720 814159578 0 12721243 0 955760260 32767
//     6 0 955760324 32767 0 0 0 0
//     955760464 32767 -376077839 32720 1 0 -376179088 32720
//     -376184832 32720 -376183960 32720 0 0 0 0
//     0 0 -378288704 32720 -376189068 32720 1 32767
//     -376189068 32720 -376196544 32720 -376220648 32720 -376057449 32720
//     -376193023 0 6 0 -376193024 32720 955761472 32767
//     -376195368 32720 8064 65535 -376197112 32720 -376191328 32720
//     put this as graph2*/
//     int graph2[20][20] = {
//         {
//             -377806379,
//             32720,
//             814159578,
//             0,
//             12721243,
//             0,
//             955760260,
//             32767,
//         },
//         {
//             6,
//             0,
//             955760324,
//             32767,
//             0,
//             0,
//             0,
//             0,
//         },
//         {
//             955760464,
//             32767,
//             -376077839,
//             32720,
//             1,
//             0,
//             -376179088,
//             32720,
//         },
//         {
//             -376184832,
//             32720,
//             -376183960,
//             32720,
//             0,
//             0,
//             0,
//             0,
//         },
//         {
//             0,
//             0,
//             -378288704,
//             32720,
//             -376189068,
//             32720,
//             1,
//             32767,
//         },
//         {
//             -376189068,
//             32720,
//             -376196544,
//             32720,
//             -376220648,
//             32720,
//             -376057449,
//             32720,
//         },
//         {
//             -376193023,
//             0,
//             6,
//             0,
//             -376193024,
//             32720,
//             955761472,
//             32767,
//         },
//         {-376195368, 32720, 8064, 65535, -376197112, 32720, -376191328, 32720}}; // H
//     int value[20];
//     int prev[20];
//     for (int i = 0; i < 8; i++)
//     {
//         value[i] = -1;
//         prev[i] = -1;
//     }
//     for (int i = 0; i < 8; i++)
//     {
//         if (i % 2)
//         {
//             BF(graph, 8, 'D', value, prev);
//         }
//         else
//         {
//             BF(graph2, 8, 'D', value, prev);
//         }
//         cout << endl;
//         cout << endl;
//         for (int i = 0; i < 8; i++)
//         {
//             cout << value[i] << " ";
//         }
//         cout << endl;
//         for (int i = 0; i < 8; i++)
//         {
//             cout << prev[i] << " ";
//         }
//     }
//     cout << endl;
//     for (int i = 0; i < 8; i++)
//     {
//         cout << value[i] << " ";
//     }
//     cout << endl;
//     for (int i = 0; i < 8; i++)
//     {
//         cout << prev[i] << " ";
//     }

//     /*
//     33 1 36 0 35 47 46 48
//     3 3 4 -1 0 4 0 5

//     G2 :
//     -377806379 32720 814159578 0 12721243 0 955760260 32767
//     6 0 955760324 32767 0 0 0 0
//     955760464 32767 -376077839 32720 1 0 -376179088 32720
//     -376184832 32720 -376183960 32720 0 0 0 0
//     0 0 -378288704 32720 -376189068 32720 1 32767
//     -376189068 32720 -376196544 32720 -376220648 32720 -376057449 32720
//     -376193023 0 6 0 -376193024 32720 955761472 32767
//     -376195368 32720 8064 65535 -376197112 32720 -376191328 32720
// */
// }

const int INF = 1000000;

void test_bf3()
{
    int graph[9][9] = {
        // A,  B,  C,  D,  E,  F,  G,  H,  I
        {0, 6, INF, 8, INF, INF, INF, INF, INF},    // A
        {INF, 0, -5, INF, 4, INF, INF, INF, -4},    // B
        {INF, INF, 0, INF, INF, INF, 3, INF, INF},  // C
        {INF, INF, INF, 0, 3, INF, INF, INF, INF},  // D
        {INF, INF, INF, INF, 0, -5, -4, INF, INF},  // E
        {INF, INF, -2, INF, INF, 0, 5, INF, INF},   // F
        {INF, INF, INF, INF, INF, INF, 0, 3, INF},  // G
        {INF, INF, INF, INF, INF, INF, INF, 0, -1}, // H
        {INF, INF, 3, INF, INF, INF, INF, INF, 0}   // I
    };
    int BFValue[9];
    int BFPrev[0];
    int n = 8;
    for (int i = 0; i < n; i++)
    {
        BFValue[i] = -1;
        BFPrev[i] = -1;
    }
    for (int i = 0; i < 3; i++)
    {
        BF(graph, n, 'A', BFValue, BFPrev);
        cout << "step: " << i + 1 << endl;
        for (int i = 0; i < n; i++)
        {
            cout << BFValue[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < n; i++)
        {
            cout << BFPrev[i] << " ";
        }
        cout << endl;
    }
    // cout << BF_Path(graph, n, 'A', 'H');
}

// void test_bf4()
// {
//     int graph[20][20] = {
//         {0, 0, 0, 33, 0, 0, 0, 0}, // A
//         {0, 0, 0, 3, 0, 0, 0, 0},  // B
//         {0, 0, 0, 40, 0, 0, 0, 0}, // C
//         {0, 0, 0, 0, 0, 0, 0, 0},  // D
//         {0, 0, 0, 72, 0, 0, 0, 0}, // E
//         {0, 0, 0, 99, 0, 0, 0, 0}, // F
//         {0, 0, 0, 72, 0, 0, 0, 0}, // G
//         {0, 0, 0, 59, 0, 0, 0, 0}  // H
//     };
//     int value[8];
//     int prev[8];
//     BF(graph, 8, 'D', value, prev);
//     for (int i = 0; i < 8; i++)
//     {
//         cout << value[i] << " ";
//     }
//     cout << endl;
//     for (int i = 0; i < 8; i++)
//     {
//         cout << prev[i] << " ";
//     }
// }

// void test_bf6()
// {
//     int graph[20][20] = {
//         {0, 5, 0, 0}, // A
//         {0, 0, 2, 0}, // B
//         {0, 0, 0, 3}, // C
//         {0, 0, 0, 0}  // D
//     };
//     int value[4];
//     int prev[4];
//     BF(graph, 4, 'A', value, prev);
//     for (int i = 0; i < 4; i++)
//     {
//         cout << value[i] << " ";
//     }
//     cout << endl;
//     for (int i = 0; i < 4; i++)
//     {
//         cout << prev[i] << " ";
//     }
// }

// void BF_P(int graph[20][20], int num, char start, char goal)
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
//     cout << endl;
//     cout << endl;
// }

int main()
{
    test_bf3();
    return 0;
}







