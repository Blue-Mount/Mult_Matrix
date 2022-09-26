#include <iostream>
#include <time.h>
#include <sys/time.h>
#include "Matrix.h"

using namespace std;

typedef struct param
{
    int row;
} Param;

int SIZE = 1000;
Matrix a(SIZE);
Matrix b(SIZE);
Matrix c(SIZE, 1);

void *func(void *param)
{
    Param *p = (Param *)param;
    int row = p->row;
    int ans1, ans2 = 0;

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            ans1 += a.mat[row][j] * b.mat[j][i];
            ans2 += a.mat[row + 1][j] * b.mat[j][i];
        }
        c.mat[row][i] = ans1;
        c.mat[row + 1][i] = ans1;
        ans1 = 0;
        ans2 = 0;
    }
}

int main()
{
    int count = 1;
    double total_time;
    pthread_t *threads = new pthread_t[SIZE];
    Param *param = new Param[SIZE];

    srand(time(NULL)); // 通过时间初始化随机种子
    struct timeval start;
    struct timeval end;
    for (int time = 0; time < count; ++time)
    {
        gettimeofday(&start, NULL);
        for (int i = 0; i < SIZE; i += 2)
        {
            param[i].row = i;
            pthread_create(&threads[i], NULL, func, &param[i]);
        }
        for (int i = 0; i < SIZE; ++i)
        {
            pthread_join(threads[i], NULL);
        }
        gettimeofday(&end, NULL);
        total_time += 1000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000;
    }

    // a.display();
    // b.display();
    // c.display();

    cout << "total_time:" << total_time << endl;

    a.del();
    b.del();
    c.del();

    delete[] threads;
    delete[] param;
}