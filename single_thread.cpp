#include <iostream>
#include <time.h>
#include <sys/time.h>
#include "Matrix.h"

using namespace std;

int main()
{
    int SIZE = 100;
    Matrix a(SIZE);
    Matrix b(SIZE);
    Matrix c(SIZE, 1);

    double total_time;
    int count = 10;

    srand(time(NULL));
    struct timeval start;
    struct timeval end;
    for (int time = 0; time < count; ++time)
    {
        gettimeofday(&start, NULL);
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < SIZE; ++k)
                {
                    c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
                }
            }
        }
        gettimeofday(&end, NULL);
        total_time += 1000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000;
    }

    // c.display();
    double avreage_time = total_time / count;
    cout << "avreage_time:" << avreage_time << endl;

    a.del();
    b.del();
    c.del();

    return 0;
}