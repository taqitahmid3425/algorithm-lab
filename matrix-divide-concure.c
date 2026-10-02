#include <stdio.h>

#define MAX 64 // Maximum matrix size supported statically

// Add two sub-matrices: C = A + B
void addMatrix(int A[MAX][MAX], int aRow, int aCol,
               int B[MAX][MAX], int bRow, int bCol,
               int C[MAX][MAX], int cRow, int cCol, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            C[cRow + i][cCol + j] = A[aRow + i][aCol + j] + B[bRow + i][bCol + j];
        }
    }
}

// Standard Divide and Conquer Matrix Multiplication using Static Memory and Offsets
void divideAndConquer(int A[MAX][MAX], int aRow, int aCol,
                      int B[MAX][MAX], int bRow, int bCol,
                      int C[MAX][MAX], int cRow, int cCol, int n)
{
    // Base Case: 1x1 matrix
    if (n == 1)
    {
        C[cRow][cCol] += A[aRow][aCol] * B[bRow][bCol];
        return;
    }

    int k = n / 2;

    // Sub-quadrant offsets
    // A11, B11 -> (aRow, aCol), (bRow, bCol)
    // A12, B12 -> (aRow, aCol + k), (bRow, bCol + k)
    // A21, B21 -> (aRow + k, aCol), (bRow + k, bCol)
    // A22, B22 -> (aRow + k, aCol + k), (bRow + k, bCol + k)

    // Temporary static buffer for sub-quadrant intermediate results
    int temp[MAX][MAX] = {0};

    // --- C11 = A11*B11 + A12*B21 ---
    divideAndConquer(A, aRow, aCol, B, bRow, bCol, C, cRow, cCol, k);
    divideAndConquer(A, aRow, aCol + k, B, bRow + k, bCol, temp, 0, 0, k);
    addMatrix(C, cRow, cCol, temp, 0, 0, C, cRow, cCol, k);

    // Reset temp buffer
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            temp[i][j] = 0;

    // --- C12 = A11*B12 + A12*B22 ---
    divideAndConquer(A, aRow, aCol, B, bRow, bCol + k, C, cRow, cCol + k, k);
    divideAndConquer(A, aRow, aCol + k, B, bRow + k, bCol + k, temp, 0, 0, k);
    addMatrix(C, cRow, cCol + k, temp, 0, 0, C, cRow, cCol + k, k);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            temp[i][j] = 0;

    // --- C21 = A21*B11 + A22*B21 ---
    divideAndConquer(A, aRow + k, aCol, B, bRow, bCol, C, cRow + k, cCol, k);
    divideAndConquer(A, aRow + k, aCol + k, B, bRow + k, bCol, temp, 0, 0, k);
    addMatrix(C, cRow + k, cCol, temp, 0, 0, C, cRow + k, cCol, k);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            temp[i][j] = 0;

    // --- C22 = A21*B12 + A22*B22 ---
    divideAndConquer(A, aRow + k, aCol, B, bRow, bCol + k, C, cRow + k, cCol + k, k);
    divideAndConquer(A, aRow + k, aCol + k, B, bRow + k, bCol + k, temp, 0, 0, k);
    addMatrix(C, cRow + k, cCol + k, temp, 0, 0, C, cRow + k, cCol + k, k);
}

void printMatrix(int matrix[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n = 4; // Dimensions must be a power of 2 (n <= MAX)

    int A[MAX][MAX] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 1, 2, 3},
        {4, 5, 6, 7}};

    int B[MAX][MAX] = {
        {1, 0, 2, 0},
        {0, 3, 0, 4},
        {5, 0, 6, 0},
        {0, 7, 0, 8}};

    int C[MAX][MAX] = {0};

    divideAndConquer(A, 0, 0, B, 0, 0, C, 0, 0, n);

    printf("Result Matrix C:\n");
    printMatrix(C, n);

    return 0;
}
