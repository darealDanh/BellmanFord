#include <iostream>

using namespace std;

int main()
{
    // for (int i = 0; i < 10; i++)
    // {
    //     for (int j = 0; j < 10; j++)
    //     {
    //         if (i & (1 << j))
    //         {
    //             cout << i << " " << j << endl;
    //             cout << i || 2;
    //         }
    //     }
    // }
    int i = 1;
    int j = 2;
    int s = i | j;
    cout << s << endl;
}