#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXROWS 10
typedef struct
{
    int rows, columns;
    float *elements[MAXROWS];
} matrix_t;

matrix_t newMatrix(int rows, int columns, char zeroOrRead);
void printMatrix(matrix_t m, char name);
void freeMatrixElements(matrix_t *m);
void addMatrices(matrix_t ma, matrix_t mb);
void transposeMatrix(matrix_t *m);
void multiplyMatrices(matrix_t ma, matrix_t mb, matrix_t *mc);
matrix_t minorMatrix(matrix_t *m, int row, int column);
float determinant (matrix_t *m);

int main(void)
{
    matrix_t ma = {-1, -1, { NULL,}};
    matrix_t mb = {-1, -1, { NULL,}};
    matrix_t mc = {-1, -1, { NULL,}};
    char cmd;
    int rows = 0, columns = 0;
    char zeroOrRead = '1';
    char name = {'\0'};
    while (1)
    {
        printf("Command? ");
        scanf(" %c", &cmd);
        switch (cmd)
        {
        case 'd':
        if(ma.rows <0 || ma.columns <0){
            printf("Matrix cannot be empty\n");
        }else if(ma.rows != ma.columns){
            printf("Matrix must be square\n");
        }else{
           float det = determinant(&ma);
           printf("\nThe determinant is %f\n", det);
        }
        break;
        case 'm':
        freeMatrixElements(&mc);
            int row = 0;
            int column = 0;
            printf("Remove which row & column? ");
            scanf(" %d %d", &row, &column);
            if (ma.rows < 2 || ma.columns< 2)
            {
                printf("Matrix must have at least two rows & columns\n");
            }
            else if (row > ma.rows || column > ma.columns)
            {
                printf("Row & column must be 0 up to %d & %d, respectively\n", ma.rows, ma.columns);
                
            }
            else
            {
                
                mc = minorMatrix(&ma, row, column);
            }

            break;
        case '*':
            freeMatrixElements(&mc);
            multiplyMatrices(ma, mb, &mc);
            break;
        case 't':
            transposeMatrix(&ma);
            break;
        case '+':
            addMatrices(ma, mb);
            break;
        case 'B':
            freeMatrixElements(&mb);
            mb.rows = ma.rows;
            mb.columns = ma.columns;
            for (int i = 0; i < ma.rows; i++)
            {
                mb.elements[i] = (float *)malloc(ma.columns * sizeof(float));
                for (int j = 0; j < ma.columns; j++)
                {
                    mb.elements[i][j] = ma.elements[i][j];
                }
            }
            break;
        case 'c':
            name = 'C';
            if (mc.rows == -1)
            {
                printf("Matrix C is empty\n");
            }
            else
            {
                printMatrix(mc, name);
            }

            break;

        case 'b':
            name = 'B';
            if (mb.rows == -1)
            {
                printf("Matrix B is empty\n");
            }
            else
            {
                printMatrix(mb, name);
            }

            break;

        case 'a':
            name = 'A';
            if (ma.rows == -1)
            {
                printf("Matrix A is empty\n");
            }
            else
            {
                printMatrix(ma, name);
            }
            break;
        case '0':
            zeroOrRead--;
        case 'A':
            printf("Size of matrix A (rows columns)? ");
            scanf(" %d %d", &rows, &columns);
            if (rows < 1 || rows > 10 || columns < 1)
            {
                printf("Rows must be 1 to 10, and columns must be at least 1\n");
            }
            else
            {
                freeMatrixElements(&ma);
                ma = newMatrix(rows, columns, zeroOrRead);
                zeroOrRead = '1';
            }

            break;
        case 'q':
            printf("Bye!\n");
            freeMatrixElements(&ma); // Free memory for matrix A
            freeMatrixElements(&mb); // Free memory for matrix B
            freeMatrixElements(&mc);
            return 0;
            break;
        default:
            printf("Unknown command '%c'\n", cmd);
        }
    }
    freeMatrixElements(&ma);
    freeMatrixElements(&mb);
    freeMatrixElements(&mc);
}

matrix_t newMatrix(int rows, int columns, char zeroOrRead)
{
    matrix_t m = {-1, -1, { NULL,  }};
    char k[20];
    strcpy(k, "0");
    float float_value;
    m.rows = rows;
    m.columns = columns;
    for (int i = 0; i < m.rows; i++)
    {
        m.elements[i] = (float *)malloc(columns * sizeof(float));
        if (zeroOrRead == '1')
        {
            printf("Row %d: ", i);
        }
        for (int j = 0; j < m.columns; j++)
        {
            if (zeroOrRead == '1')
            {
                scanf(" %s", k);
            }
            float_value = atof(k);
            m.elements[i][j] = float_value;
        }
        
    }
    zeroOrRead = '1';
    return m;
}

void printMatrix(matrix_t m, char name)
{
    printf("Matrix %c (%d X %d):\n", name, m.rows, m.columns);
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {

            printf("%8.2f", m.elements[i][j]);
        }

        printf("\n");
    }
}

void freeMatrixElements(matrix_t *m)
{
    for (int i = 0; i < m->rows; i++)
    {
        free(m->elements[i]);
    }
    m->rows = -1;
    m->columns = -1;
}

void addMatrices(matrix_t ma, matrix_t mb)
{
    if (ma.rows <= 0 || ma.columns <= 0 || mb.columns <= 0 || mb.rows <= 0)
    {
        printf("Matrices cannot be empty\n");
    }
    else if (ma.rows != mb.rows || ma.columns != mb.columns)
    {
        printf("Matrix dimensions don't agree\n");
    }
    else
    {
        for (int i = 0; i < ma.rows; i++)
        {
            for (int j = 0; j < ma.columns; j++)
            {
                mb.elements[i][j] = mb.elements[i][j] + ma.elements[i][j];
            }
        }
    }
}

void transposeMatrix(matrix_t *m)
{
    if (m->rows <= 0 || m->columns <= 0)
    {
        printf("Matrix cannot be empty\n");
    }
    else
    {
        matrix_t md = newMatrix(m->columns, m->rows, '0');
        // Transpose the elements
        for (int i = 0; i < m->rows; i++)
        {
            for (int j = 0; j < m->columns; j++)
            {
                // printf("%d %d\n", i, j);
                md.elements[j][i] = m->elements[i][j]; // segmentation fault
            }
        }
        freeMatrixElements(m);
        // Copy the transpose back to the original matrix
        m->rows = md.rows;
        m->columns = md.columns;
        for (int i = 0; i < md.rows; i++)
        {
            m->elements[i] = (float *)malloc(md.columns * sizeof(float));
            for (int j = 0; j < md.columns; j++)
            {
                m->elements[i][j] = md.elements[i][j];
            }
        }

        freeMatrixElements(&md);
    }
}

void multiplyMatrices(matrix_t ma, matrix_t mb, matrix_t *mc)
{

    if (ma.columns <= 0 || mb.rows <= 0)
    {
        printf("Matrices cannot be empty\n");
    }
    else if (ma.columns != mb.rows)
    {
        printf("Matrix dimensions don't agree\n");
    }
    else
    {
        *mc = newMatrix(ma.rows, mb.columns, '0');

        for (int r = 0; r < ma.rows; r++)
        {
            for (int c = 0; c < mb.columns; c++)
            {
                for (int i = 0; i < ma.columns; i++)
                {
                    mc->elements[r][c] = mc->elements[r][c] + ma.elements[r][i] * mb.elements[i][c];
                }
            }
        }
    }
}

matrix_t minorMatrix(matrix_t *m, int row, int column)
{
    matrix_t md = newMatrix(m->rows - 1, m->columns - 1, '0');
    int md_row = 0;

    for (int i = 0; i < m->rows; i++)
    {
        if (i == row)
        {
            // Skip the specified row
            continue;
        }

        int md_col = 0;

        for (int j = 0; j < m->columns; j++)
        {
            if (j == column)
            {
                // Skip the specified column
                continue;
            }

            md.elements[md_row][md_col] = m->elements[i][j];
            md_col++;
        }

        md_row++;
    }

    return md;
}

float determinant (matrix_t *m) {
    float det = 0;
    if(m->rows == 1){
        det = m->elements[0][0];
    }else if(m->rows == 2){
        det = m->elements[0][0]*m->elements[1][1] - m->elements[0][1] * m->elements[1][0];
    }else{
        int r = 0;
        for(int c = 0; c < m->columns; c++){
       matrix_t minor = minorMatrix(m, r, c);
       int sign = (r+c) % 2 == 0 ? 1 : -1; // (-1)^(r+c)
        det = det+ sign * m->elements[r][c] *determinant(&minor); // here error
        freeMatrixElements(&minor);
    }
   
    }
    
    if(det == -0) det =0; // remove negative zeros;
    printf("%1.2f:", det);
    
    return det;
}
