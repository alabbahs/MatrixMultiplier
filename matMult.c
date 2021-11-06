#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//add random numbers to matrix
void matRand(int a, int b, int **mat){
    for(int i=0; i<a; i++){
        for(int j=0; j<b; j++){
            mat[i][j] = (rand() % 100);
        }
    }
}

//ALlocating memory for matrix
int memAllocMatrix(int a, int b, int **matrixName){
    matrixName = malloc(a * sizeof(int *));
    if(matrixName == NULL) return 0;

    for(int i=0; i<a; i++){
        matrixName[i] = malloc(b * sizeof(int));
        if(matrixName == NULL) return 0;
    }
}

//multiply matrices
void multMatrices(int a, int b, int **mat1, int **mat2, int **mat3){
    for(int i=0; i<a; i++){
        for(int j=0; j<a; j++){
            for(int k=0; k<b; k++){
                mat3[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

//print matrix
void printMatrix(int a, int b, int **mat){
    int row, column;
    for(column=0; column<a; column++){
        for(row=0; row<b; row++){
            printf("%d", mat[column][row]);
            printf(" ");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]){

    if (argc != 4){
        printf("ERROR: Invalid input\nPlease enter arguments in the form <MatrixY> <MatrixX> <seed>\n");
        return 0;
    }

    int M = atoi(argv[1]);
    int N = atoi(argv[2]);

    if (M == 0 || N == 0){
        printf("ERROR: Invalid input\nPlease enter arguments in the form <MatrixY> <MatrixX> <seed>\n");
        return 0;
    }

    struct timeval tv, start, stop, elapsed;
    int seed = atoi(argv[3]);
    srand(seed);
    int **matrix1;
    int **matrix2;
    int **resultMatrix;
    int row, column;


//ALlocating memory for matrix1
    matrix1 = malloc(M * sizeof(int*));
    if(matrix1 == NULL) return 0;

    for(int i=0; i<M; i++){
        matrix1[i] = malloc(N * sizeof(int));
        if(matrix1 == NULL) return 0;
    }


//ALlocating memory for matrix2
    matrix2 = malloc(N * sizeof(int *));
    if(matrix2 == NULL) return 0;

    for(int i=0; i<N; i++){
        matrix2[i] = malloc(M * sizeof(int));
        if(matrix2 == NULL) return 0;
    }

//ALlocating memory for resultMatrix
    resultMatrix = malloc(M * sizeof(int *));
    if(resultMatrix == NULL) return 0;

    for(int i=0; i<M; i++){
        resultMatrix[i] = malloc(M * sizeof(int));
        if(resultMatrix == NULL) return 0;
    }

    matRand(M,N,matrix1);
    matRand(N,M,matrix2);
    
    gettimeofday(&tv, NULL);

    gettimeofday(&start, NULL);
    multMatrices(M,N,matrix1,matrix2,resultMatrix);
    gettimeofday(&stop, NULL);
    timersub(&stop, &start, &elapsed);

    printf("MATRIX 1:");
    printMatrix(M,N,matrix1);

    printf("MATRIX 2:");
    printMatrix(N,M,matrix2);

    printf("RESULT:");
    printMatrix(M,M,resultMatrix);

    printf("EXECUTION TIME: %lu.%06lu\n", elapsed.tv_sec, elapsed.tv_usec);

    for(int i=0; i<M; i++){
        free(matrix1[i]);
    }
        free(matrix1);
    
    for(int i=0; i<M; i++){
        free(matrix2[i]);
    }
        free(matrix2);

    for(int i=0; i<M; i++){
        free(resultMatrix[i]);
    }
        free(resultMatrix);

}
