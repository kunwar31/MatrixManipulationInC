#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>



struct Matrix
{
    int rows;
    int cols;
};

int* InputMatrix(int *mat,int n,bool debug,bool square)
{
    int rows, cols;
    int * r;
    int * c;
    printf("\nEnter number of rows and columns: ");
    scanf("%d%d", &rows, &cols);
    if (rows != cols && square)
    {
        printf("\nRows not equal to columns.\n");
        r = (int*)malloc(sizeof(int));
        *r = -1;
        return r;
    }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("\nEnter element(%d,%d): ", i + 1, j + 1);
                scanf("%d", mat + (i * n + j));
            }
        }

    r = (int*)malloc(sizeof(int));
    c = (int*)malloc(sizeof(int));
    c = r - 1;
    *(r) = rows;
    *(c) = cols;
    if (debug)
    {
        printf("\nMatrix address: %u\n",mat);
        printf("\nAddress: %u Value: %d\nAddress: %u Value:%d\n",r,*r,c,*c);
    }
    return r;
}

struct Matrix GetMatrix(int *mat,int n,bool debug,bool square)
{
    struct Matrix matrix;
    int * rc = InputMatrix(mat,n,debug,square);
    matrix.rows = *(rc);
    matrix.cols = *(rc - 1);
    printf("\n");
    return matrix;
}

void PrintMatrix(struct Matrix matrix,int cols,int * mat1)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++) {
            printf("%d  ",*(mat1 + (i * cols + j)));
        }
        printf("\n\n");
    }
}
void PrintMatrixf(struct Matrix matrix,int cols,float * mat1)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++) {
            printf("%.2f  ",*(mat1 + (i * cols + j)));
        }
        printf("\n\n");
    }
}


void TransMatrix(int* mat, struct Matrix *m,int cols,bool debug)
{
    if (debug)
    {
        printf("\nBefore Transpose: \n");
        PrintMatrix(*m,cols,mat);
    }

    int matrix[cols][cols];
    int * result = &matrix[0][0];

    for (int i = 0;i<m->rows;i++)
    {
        for (int j = 0;j<m->cols;j++)
        {
            *(result + (j * cols + i)) = *(mat + (i * cols + j));
        }
    }
    int temp = m->cols;
    m->cols = m->rows;
    m->rows = temp;

    for (int i = 0;i<m->rows;i++)
    {
        for (int j = 0;j<m->cols;j++)
        {
            *(mat + (i * cols + j)) = *(result + (i * cols + j));
        }
    }
    if (debug)
    {
        printf("\nAfter Transpose: \n");
        PrintMatrix(*m,cols,mat);
    }

}



void AddMatrix(int* mat1,int* mat2,int* result,int rows,int cols,int n,bool debug)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(result + (i * n + j)) = *(mat1 + (i * n + j)) + *(mat2 + (i * n + j));
        }
    }
}

void DivideMatrixByInt(int* mat1,float *result,int divide,int rows,int cols,int n,bool debug)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(result + (i * n + j)) = ((float)*(mat1 + (i * n + j)) / (float)divide);
            if (debug)
            {
                printf("\nAfter Divide: %f\n",*(result + (i * n + j)));
            }
        }
    }


}

void MulMatrix(int *mat1,int *mat2,int *result,struct Matrix *mresult,struct Matrix m1,struct Matrix m2,int cols,bool debug)
{
    mresult->rows = m1.rows;
    mresult->cols = m2.cols;

    if (debug)
    {
        printf("\nFirst Matrix:\n");
        PrintMatrix(m1,cols,mat1);
        printf("\nSecond Matrix:\n");
        PrintMatrix(m2,cols,mat2);
    }

    for (int i = 0;i<mresult->rows;i++)
    {
        for (int j = 0;j<mresult->cols;j++)
        {
            for (int k = 0;k<m2.rows;k++)
            {
                *(result + (i * cols + j)) += *(mat1 + (i * cols + k)) * (*(mat2 + (k * cols + j)));
            }
        }
    }


}

//These Declarations are necessary for these functions to work correctly, Can't directly define here.

int Determinant(int *mat1,int order,int cols,bool PrintExtraInfo);
int Cofactor(int *mat1,int order,int cols,bool PrintExtraInfo,int i,int j); // THE main function for finding adjoint,determinant, or inverse.
void Adjoint(int *mat1,int order,int cols,bool PrintExtraInfo);
bool MatrixInverse(int *mat1,int order,int cols,bool PrintExtraInfo);




void DoTaskAccordingTo(int choice,int cols,int *mat1,int *mat2,bool PrintExtraInfo)
{
    switch (choice)
    {
        case 1:
            // PRINT THE MATRIX
            printf("\n\n");
            PrintMatrix(GetMatrix(mat1,cols,PrintExtraInfo,false),cols,mat1);
            break;
        case 2:
            // ADD MATRICES
            printf("\n\n");
            struct Matrix m1;
            m1 = GetMatrix(mat1,cols,PrintExtraInfo,false);
            struct Matrix m2;
            m2 = GetMatrix(mat2,cols,PrintExtraInfo,false);
            if (m1.rows == m2.rows && m1.cols == m2.cols)
            {
                int result[cols][cols];
                AddMatrix(mat1,mat2,&result[0][0],m1.rows,m1.cols,cols,PrintExtraInfo);
                PrintMatrix(m1,cols,&result[0][0]);
            }
            break;
        case 3:
            // MULTIPLY MATRICES
            printf("\n\n");
            struct Matrix one;
            one = GetMatrix(mat1,cols,PrintExtraInfo,false);
            struct Matrix two;
            two = GetMatrix(mat2,cols,PrintExtraInfo,false);

            if (one.cols == two.rows)
            {
                int result[cols][cols];
                struct Matrix resultm;

                MulMatrix(mat1,mat2,&result[0][0],&resultm,one,two,cols,PrintExtraInfo);

                PrintMatrix(resultm,cols,&result[0][0]);
            }
            else
            {
                printf("\nMake sure columns of first matrix are equal to rows of second matrix!\n");
            }
        case 4:
            // ADJOINT of Matrix
            printf("\n\n");
            struct Matrix AdjointIt;
            AdjointIt = GetMatrix(mat1,cols,PrintExtraInfo,true);
            if (AdjointIt.rows != -1)
            {
                printf("\nMatrix: \n");
                PrintMatrix(AdjointIt,cols,mat1);

                Adjoint(mat1,AdjointIt.rows,cols,PrintExtraInfo);

                printf("\nAdjoint: \n");
                PrintMatrix(AdjointIt,cols,mat1);
            }
            break;
        case 5:
            // DETERMINANT of Matrix
            printf("\n\n");
            struct Matrix DetIt;
            DetIt = GetMatrix(mat1,cols,PrintExtraInfo,true);
            if (DetIt.rows != -1)
            {
                printf("\nDeterminant : %d\n",Determinant(mat1,DetIt.rows,cols,PrintExtraInfo));
            }
            break;
        case 6:
            // TRANSPOSE of Matrix
            printf("\n\n");
            struct Matrix TransIt;
            TransIt = GetMatrix(mat1,cols,PrintExtraInfo, false);
            TransMatrix(mat1,&TransIt,cols,true);
            break;
        case 7:
            // INVERSE of Matrix
            printf("\n\n");
            struct Matrix InvertIt;
            InvertIt = GetMatrix(mat1,cols,PrintExtraInfo,true);
            if (InvertIt.rows != -1)
            {
                if(!MatrixInverse(mat1,InvertIt.rows,cols,PrintExtraInfo))
                {
                    printf("\nInverse does not exist.\n");
                }

            }
            break;
        default:
            printf("\nWrong option selected\n");
    }
}

int main()

{
    int choice,n = 100;
    int mat[n][n];
    int mat2[n][n];
    bool debug;
    char debugchoice;
    printf("Debug? (Y/N) ");
    scanf("%c",&debugchoice);

    printf("\nSELECT OPTION :\n1. print\n2. addition of matrix\n3. multiplication\n4. Adjoint of Matrix\n5. Determinant of Matrix\n6. Transpose of Matrix \n7. Inverse of Matrix\n ");
    scanf("%d", &choice);
    if (debugchoice == 'y' || debugchoice == 'Y' )
        debug = true;
    else debug = false;
    DoTaskAccordingTo(choice,n,&mat[0][0],&mat2[0][0], debug);
}



int Cofactor(int *mat1,int order,int cols,bool PrintExtraInfo,int i,int j)
{   //temp matrix
    int* ptemp = (int*)malloc(sizeof(int)*(order-1)*(order-1));
    int sign;
    int minor;
    struct Matrix Invert;
    Invert.cols = order;
    Invert.rows = order;

    if (PrintExtraInfo)
    {
        printf("\nInitial Matrix:\n");
        PrintMatrix(Invert,cols,mat1);
    }
    if (order == 2)
    {
        minor = *(mat1 + ((order - 1 - i) * cols + (order - 1 - j)));
        sign = pow(-1,(i+j));

        if (PrintExtraInfo)
        {
            printf("\nCofactor: %d\n",minor*sign);
        }

        return minor*sign;

    }
    if (order > 2)
    {
        int count= 0;
        for (int mrows = 0;mrows<order;mrows++)
        {
            for (int mcols = 0;mcols<order;mcols++)
            {
                if (mrows == i || mcols == j)
                {
                    continue;
                }
                else
                {
                    *(ptemp + count) = *(mat1 + (mrows * cols + mcols));
                    count++;
                }
            }
        }
        struct Matrix InvertIt;
        InvertIt.cols = order-1;
        InvertIt.rows = order-1;
        if (PrintExtraInfo)
        {
            printf("\nTrimmed Matrix:\n");
            PrintMatrix(InvertIt,order-1,ptemp);
        }
        minor = Determinant(ptemp,order-1,order-1,PrintExtraInfo);
        sign = pow(-1,(i+j));
        if (PrintExtraInfo)
        {
            printf("\nDeterminant: %d\n",minor*sign);
        }
        return minor*sign;
    }
}


int Determinant(int *mat1,int order,int cols,bool PrintExtraInfo)
{
    int det = 0;
    for (int i = 0;i<order;i++)
    {
        int cof = Cofactor(mat1,order,cols,PrintExtraInfo,0,i);
        det += cof * (*(mat1 + (i)));
        if (PrintExtraInfo)
        {
            printf("\nDeterminant += %d * %d, Determinant = %d\n",cof,(*(mat1 + (i))),det);
        }

    }

    return det;
}

void Adjoint(int *mat1,int order,int cols,bool PrintExtraInfo)
{
    int r[cols][cols];
    int *result = &r[0][0];
    struct Matrix m;
    m.rows = order;
    m.cols = m.rows;

    if (PrintExtraInfo)
    {
        printf("\nMatrix: \n");
        PrintMatrix(m,cols,mat1);
    }

    for (int i = 0;i<order;i++)
    {
        for (int j = 0;j<order;j++)
        {
            *(result + (i* cols + j)) = Cofactor(mat1,order,cols,PrintExtraInfo,i,j);
        }
    }
    //PUT VALUES FROM RESULT TO ORIGINAL MATRIX
    for (int i = 0;i<order;i++)
    {
        for (int j = 0;j<order;j++)
        {
            *(mat1 + (i* cols + j)) = *(result + (i* cols + j));
        }
    }

    if (PrintExtraInfo)
    {
        printf("\nAdjoint: \n");
        PrintMatrix(m,cols,mat1);
    }
}

bool MatrixInverse(int *mat1,int order,int cols,bool PrintExtraInfo)
{

    int det = Determinant(mat1,order,cols,PrintExtraInfo);

    if (det != 0)
    {
        struct Matrix InvertIt;
        InvertIt.cols = order;
        InvertIt.rows = order;
        float result[cols][cols];

        printf("\nMatrix: \n");
        PrintMatrix(InvertIt,cols,mat1);

        Adjoint(mat1,order,cols,PrintExtraInfo);

        TransMatrix(mat1,&InvertIt,cols,PrintExtraInfo);

        DivideMatrixByInt(mat1,&result[0][0],det,order,order,cols,PrintExtraInfo);

        printf("\nInverse: \n");
        PrintMatrixf(InvertIt,cols,&result[0][0]);
        return true;
    }
    else return false;

}