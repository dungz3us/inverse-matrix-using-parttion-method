#include <stdio.h>
#include <math.h>
// find determinant of a matrix
// using Gaussian elimination

float det (float matrix[10][10], int n)
{
    float b[10][10];
    int i, j, t, count;
    float temp;
    float det = 1;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n ; j++)
        {
            b[i][j] = matrix[i][j];
        }
    }
    i = 0;
    j = 0;
    while (i < n && j < n)
    {
        if (b[i][j] == 0)
        {
            t = i + 1;
            while (t < n)
            {
                if (b[t][j] != 0)
                {
                    count++;
                    for (int k = 0; k < n; k++) {
                        temp = b[t][k];
                        b[t][k] = b[i][k];
                        b[i][k] = temp;
                    }
                    t++;
                }
            }
        }
        for (int k = i + 1; k < n; k++)
        {
            float c = b[k][j]/b[i][j];
            for (int y = j; y < n; y++)
                b[k][y] = b[k][y] - b[i][y] * c;
        }
        i++; j++;
    }
    for (i = 0; i < n; i++)
        det = det * b[i][i] * pow(-1, count);
    return det;
}

// identity matrix
void identity( float matrix[10][10], int n )
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j)
            {
                matrix[i][j] = 1;
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }
}
// Multiplication of two matrices
void multiply(float a[10][10], float b[10][10], float result[10][10], int arows, int acolumns, int brows, int bcolumns)
{
    int i, j, k;
    if (brows != acolumns) return;
    else
    {
        for(i = 0; i < arows; i++)
        {
            for(j = 0; j < bcolumns; j++)
            {
                result[i][j] = 0;
                for(k = 0; k < brows; k++)
                {
                    result[i][j] = result[i][j] + a[i][k] * b[k][j];
                }
            }
        }
    }
}

// inverse matrix using partitioning method
void inverse(float input[10][10], float result[10][10], int n) {
    float theta;
//    stop recursive condition
    if (n == 2) {
        float d = det(input, n);
        result[0][0] = input[1][1] / d;
        result[0][1] = -input[0][1] / d;
        result[1][0] = -input[1][0] / d;
        result[1][1] = input[0][0] / d;
    }
    else
    {
        float matrix1[n - 1][n - 1], matrix2[10][10], matrix3[1][n - 1], matrix4 = input[n - 1][n - 1];
        for(int i = 0; i < n - 1; i++)
        {
            for(int j = 0; j < n - 1; j++)
            {
                matrix1[i][j] = input[i][j];
            }
        }
        for (int i = 0; i < n - 1; i++)
        {
            matrix2[i][0] = input[i][n - 1];
            matrix3[0][i] = input[n - 1][i];
        }
        float invMatrix1[10][10], matrix11[10][10];
        for(int i = 0; i < n - 1; i++)
        {
            for(int j = 0; j < n - 1; j++)
            {
                    matrix11[i][j] = matrix1[i][j];
            }
        }
//        call recursive
        inverse(matrix11, invMatrix1, n - 1);
        float result1[10][10], result2[10][10], result3[10][10], identity_matrix[10][10];
        multiply(matrix3, invMatrix1, result1, 1, n - 1, n - 1, n - 1);
        multiply(invMatrix1, matrix2, result3, n - 1, n - 1, n - 1, 1);
        multiply(result1, matrix2, result2, 1, n - 1, n - 1, 1);
//        find theta
        theta = matrix4 - result2[0][0];
        if (theta == 0.0)
        {
            printf("Mathematical Error! - theta\n");
            return;
        }
        float result4[10][10], invB1[10][10], invB2[10][10], invB3[10][10], result5[10][10];
        for (int i = 0; i < n - 1; i++)
        {
            invB3[0][i] = result1[0][i] / (-theta);
            invB2[i][0] = result3[i][0] / (-theta);
        }
        multiply(matrix2, invB3, result4, n - 1, 1, 1, n - 1);
        identity(identity_matrix, n - 1);
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - 1; j++)
            {
                result5[i][j] = identity_matrix[i][j] - result4[i][j];
            }
        }
        multiply(invMatrix1, result5, invB1, n - 1, n - 1, n - 1, n - 1);
        result[n - 1][n - 1] = 1 / theta;
        for (int i = 0; i < n - 1; i++)
        {
            result[i][n - 1] = invB2[i][0];
            result[n - 1][i] = invB3[0][i];
        }
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - 1; j++)
            {
                result[i][j] = invB1[i][j];
            }
        }
    }
}

// main program
int main()
{
    int n;
    float matrix[10][10], invMatrix[10][10];
//    input matrix
    printf("Enter order of matrix: ");
    scanf("%d", &n);
    printf("\nEnter Coefficients of Matrix: \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n ; j++)
        {
            scanf("%f", &matrix[i][j]);
        }
    }
    float d = det(matrix, n);
//       Check if there is inverse matrix
    printf("\nDeterminant of Matrix: %f\n", d);
    if (d == 0)
    {
        printf("There is no inverse matrix\n");
        return 0;
    }
    else
    {
//        partitioning method
        inverse(matrix, invMatrix, n);
    }
//        print inverse matrix
    printf("Inverse matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f\t", invMatrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
