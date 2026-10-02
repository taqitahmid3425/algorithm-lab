#include <stdio.h>

void greedy(int m, int A[m][m], int B[m][m], int C[m][m])
{
    for (int row = 0; row < m; row++)
    {
        for (int col = 0; col < m; col++)
        {
            C[row][col] = 0;
            for (int i = 0; i < m; i++)
            {
                C[row][col] += A[row][i] * B[i][col];
            }
        }
    }
}

void print(int m, int A[m][m])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int m;
    printf("Enter number of row and column (both should be equal): ");
    scanf("%d", &m);
    int A[m][m], B[m][m], C[m][m];

    printf("Enter first matrix.\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }
    printf("Enter second matrix.\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    greedy(m, A, B, C);
    printf("\nMultiplication of both matrices is \n");
    print(m, C);

    return 0;
}