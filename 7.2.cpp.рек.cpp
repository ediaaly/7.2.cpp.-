
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// Заповнення матриці
void Create(int a[][5], const int k, const int n,
    const int Low, const int High, int i, int j)
{
    if (i >= k)
        return;

    a[i][j] = Low + rand() % (High - Low + 1);

    if (j + 1 < n)
        Create(a, k, n, Low, High, i, j + 1);
    else
        Create(a, k, n, Low, High, i + 1, 0);
}

// Виведення матриці
void Print(int a[][5], const int k, const int n, int i, int j)
{
    if (i >= k)
    {
        cout << endl;
        return;
    }

    cout << setw(5) << a[i][j];

    if (j + 1 < n)
        Print(a, k, n, i, j + 1);
    else
    {
        cout << endl;
        Print(a, k, n, i + 1, 0);
    }
}

// Пошук мінімуму одного стовпця
void FindMin(int a[][5], const int k, int j,
    int i, int& min, int& minRow)
{
    if (i >= k)
        return;

    if (a[i][j] < min)
    {
        min = a[i][j];
        minRow = i;
    }

    FindMin(a, k, j, i + 1, min, minRow);
}

// Найбільший серед мінімумів парних стовпців
void MaxMinEven(int a[][5], const int k, const int n,
    int& row, int& col, int j, int& maxMin, bool& found)
{
    if (j >= n)
        return;

    int min = a[0][j];
    int minRow = 0;

    FindMin(a, k, j, 1, min, minRow);

    if (!found || min > maxMin)
    {
        maxMin = min;
        row = minRow;
        col = j;
        found = true;
    }

    MaxMinEven(a, k, n, row, col, j + 2, maxMin, found);
}

// Пошук максимуму одного стовпця
void FindMax(int a[][5], const int k, int j,
    int i, int& max, int& maxRow)
{
    if (i >= k)
        return;

    if (a[i][j] > max)
    {
        max = a[i][j];
        maxRow = i;
    }

    FindMax(a, k, j, i + 1, max, maxRow);
}

// Найменший серед максимумів непарних стовпців
void MinMaxOdd(int a[][5], const int k, const int n,
    int& row, int& col, int j, int& minMax, bool& found)
{
    if (j >= n)
        return;

    int max = a[0][j];
    int maxRow = 0;

    FindMax(a, k, j, 1, max, maxRow);

    if (!found || max < minMax)
    {
        minMax = max;
        row = maxRow;
        col = j;
        found = true;
    }

    MinMaxOdd(a, k, n, row, col, j + 2, minMax, found);
}

// Перестановка двох елементів
void Swap(int a[][5], const int row1, const int col1,
    const int row2, const int col2)
{
    int temp = a[row1][col1];
    a[row1][col1] = a[row2][col2];
    a[row2][col2] = temp;
}

// Головна функція
int main()
{
    srand((unsigned)time(0));

    const int k = 5;
    const int n = 5;
    const int Low = -20;
    const int High = 20;

    int a[k][n];

    Create(a, k, n, Low, High, 0, 0);

    cout << "Original matrix:" << endl;
    Print(a, k, n, 0, 0);

    int row1 = 0, col1 = 0;
    int row2 = 0, col2 = 0;

    int maxMin = 0;
    int minMax = 0;

    bool found1 = false;
    bool found2 = false;

    MaxMinEven(a, k, n, row1, col1, 1, maxMin, found1);
    MinMaxOdd(a, k, n, row2, col2, 0, minMax, found2);

    if (found1 && found2)
    {
        cout << "MaxMinEven = " << maxMin << endl;
        cout << "MinMaxOdd = " << minMax << endl;

        Swap(a, row1, col1, row2, col2);

        cout << endl;
        cout << "Modified matrix:" << endl;
        Print(a, k, n, 0, 0);
    }

    return 0;
}
