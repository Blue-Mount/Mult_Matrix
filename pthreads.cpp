#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "Matrix.h"

using namespace std;

typedef struct param
{
    int row;
} Param;

int SIZE = 100;
int L = 2;
Matrix a(SIZE);
Matrix b(SIZE);
Matrix c(SIZE, 1);

void *func(void *param)
{
    Param *p = (Param *)param;
    int row = p->row;
    int *ans = new int[L];

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int k = 0; k < L; ++k)
            {
                ans[k] += a.mat[row + k][j] * b.mat[j][i];
            }
        }

        for (int k = 0; k < 4; ++k)
        {
            c.mat[row][i] = ans[k];
            ans[k] = 0;
        }
    }
}

int main()
{
    int count = 10;
    double total_time;
    pthread_t *threads = new pthread_t[SIZE];
    Param *param = new Param[SIZE];

    srand(time(NULL)); // 通过时间初始化随机种子
    struct timeval start;
    struct timeval end;
    for (int time = 0; time < count; ++time)
    {
        gettimeofday(&start, NULL);
        for (int i = 0; i < SIZE; i += L)
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
    double avreage_time = total_time / count;
    cout << "threads_num:" << SIZE / L << endl;
    cout << "avreage_time:" << avreage_time << endl;

    a.del();
    b.del();
    c.del();

    delete[] threads;
    delete[] param;
}