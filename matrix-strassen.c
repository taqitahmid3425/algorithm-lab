#include <stdio.h>

#define MAX 64 // Maximum matrix dimension supported (must be a power of 2)

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

// Subtract two sub-matrices: C = A - B
void subtractMatrix(int A[MAX][MAX], int aRow, int aCol,
                    int B[MAX][MAX], int bRow, int bCol,
                    int C[MAX][MAX], int cRow, int cCol, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            C[cRow + i][cCol + j] = A[aRow + i][aCol + j] - B[bRow + i][bCol + j];
        }
    }
}

// Strassen's Matrix Multiplication using local stack memory and offsets
void strassen(int A[MAX][MAX], int aRow, int aCol,
              int B[MAX][MAX], int bRow, int bCol,
              int C[MAX][MAX], int cRow, int cCol, int n)
{
    // Base case: 1x1 matrix
    if (n == 1)
    {
        C[cRow][cCol] = A[aRow][aCol] * B[bRow][bCol];
        return;
    }

    int k = n / 2;

    // Local stack buffers for intermediate sums, differences, and sub-products
    int tempA[MAX][MAX], tempB[MAX][MAX];
    int P1[MAX][MAX], P2[MAX][MAX], P3[MAX][MAX], P4[MAX][MAX];
    int P5[MAX][MAX], P6[MAX][MAX], P7[MAX][MAX];

    // Sub-quadrant row/col offsets for clarity
    int a11R = aRow, a11C = aCol;
    int a12R = aRow, a12C = aCol + k;
    int a21R = aRow + k, a21C = aCol;
    int a22R = aRow + k, a22C = aCol + k;

    int b11R = bRow, b11C = bCol;
    int b12R = bRow, b12C = bCol + k;
    int b21R = bRow + k, b21C = bCol;
    int b22R = bRow + k, b22C = bCol + k;

    // --- Compute P1 through P7 ---

    // P1 = (A11 + A22) * (B11 + B22)
    addMatrix(A, a11R, a11C, A, a22R, a22C, tempA, 0, 0, k);
    addMatrix(B, b11R, b11C, B, b22R, b22C, tempB, 0, 0, k);
    strassen(tempA, 0, 0, tempB, 0, 0, P1, 0, 0, k);

    // P2 = (A21 + A22) * B11
    addMatrix(A, a21R, a21C, A, a22R, a22C, tempA, 0, 0, k);
    strassen(tempA, 0, 0, B, b11R, b11C, P2, 0, 0, k);

    // P3 = A11 * (B12 - B22)
    subtractMatrix(B, b12R, b12C, B, b22R, b22C, tempB, 0, 0, k);
    strassen(A, a11R, a11C, tempB, 0, 0, P3, 0, 0, k);

    // P4 = A22 * (B21 - B11)
    subtractMatrix(B, b21R, b21C, B, b11R, b11C, tempB, 0, 0, k);
    strassen(A, a22R, a22C, tempB, 0, 0, P4, 0, 0, k);

    // P5 = (A11 + A12) * B22
    addMatrix(A, a11R, a11C, A, a12R, a12C, tempA, 0, 0, k);
    strassen(tempA, 0, 0, B, b22R, b22C, P5, 0, 0, k);

    // P6 = (A21 - A11) * (B11 + B12)
    subtractMatrix(A, a21R, a21C, A, a11R, a11C, tempA, 0, 0, k);
    addMatrix(B, b11R, b11C, B, b12R, b12C, tempB, 0, 0, k);
    strassen(tempA, 0, 0, tempB, 0, 0, P6, 0, 0, k);

    // P7 = (A12 - A22) * (B21 + B22)
    subtractMatrix(A, a12R, a12C, A, a22R, a22C, tempA, 0, 0, k);
    addMatrix(B, b21R, b21C, B, b22R, b22C, tempB, 0, 0, k);
    strassen(tempA, 0, 0, tempB, 0, 0, P7, 0, 0, k);

    // --- Combine P1-P7 into Result Quadrants in C ---

    // C11 = P1 + P4 - P5 + P7
    addMatrix(P1, 0, 0, P4, 0, 0, tempA, 0, 0, k);
    subtractMatrix(tempA, 0, 0, P5, 0, 0, tempB, 0, 0, k);
    addMatrix(tempB, 0, 0, P7, 0, 0, C, cRow, cCol, k);

    // C12 = P3 + P5
    addMatrix(P3, 0, 0, P5, 0, 0, C, cRow, cCol + k, k);

    // C21 = P2 + P4
    addMatrix(P2, 0, 0, P4, 0, 0, C, cRow + k, cCol, k);

    // C22 = P1 + P3 - P2 + P6
    addMatrix(P1, 0, 0, P3, 0, 0, tempA, 0, 0, k);
    subtractMatrix(tempA, 0, 0, P2, 0, 0, tempB, 0, 0, k);
    addMatrix(tempB, 0, 0, P6, 0, 0, C, cRow + k, cCol + k, k);
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

    strassen(A, 0, 0, B, 0, 0, C, 0, 0, n);

    printf("Result Matrix C:\n");
    printMatrix(C, n);

    return 0;
}