#include <iostream>
using namespace std;

class Matrix
{
public:
    int SIZE;
    int row;
    int col;
    int **mat;

    void display();
    Matrix(int SIZE)
    {
        int **a = new int *[SIZE];

        for (int i = 0; i < SIZE; ++i)
        {
            a[i] = new int[SIZE];
        }

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                a[i][j] = rand() % 10;
            }
        }

        mat = a;
        this->SIZE = SIZE;
    }

    Matrix(int SIZE, bool isZero)
    {
        int **a = new int *[SIZE];

        for (int i = 0; i < SIZE; ++i)
        {
            a[i] = new int[SIZE];
        }

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                a[i][j] = 0;
            }
        }

        mat = a;
        this->SIZE = SIZE;
    }

    void del()
    {
        for (int i = 0; i < SIZE; ++i)
        {
            delete[] mat[i];
        }
        delete[] mat;
    }
};

void Matrix::display()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}