#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void llenarMatriz(int **matriz, int tamaño) {
    srand(time(NULL));
    for (int i = 0; i < tamaño; ++i) {
        for (int j = 0; j < tamaño; ++j) {
            matriz[i][j] = rand() % 100 + 1;
        }
    }
}

void mostrarMatriz(int **matriz, int tamaño) {
    for (int i = 0; i < tamaño; ++i) {
        for (int j = 0; j < tamaño; ++j) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void multiplicarMatrices(int **A, int **B, int **Result, int tamaño) {
    #pragma omp parallel for
    for (int i = 0; i < tamaño; ++i) {
        for (int j = 0; j < tamaño; ++j) {
            int temp = 0;
            for (int k = 0; k < tamaño; ++k) {
                temp += A[i][k] * B[k][j];
            }
            Result[i][j] = temp;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso incorrecto. Por favor, ingrese el tamaño de la matriz como argumento.\n");
        return 1;
    }

    int tamaño = atoi(argv[1]);
    int imprimir = atoi(argv[2]);

    int **A, **B, **Result;

    A = (int **)malloc(tamaño * sizeof(int *));
    B = (int **)malloc(tamaño * sizeof(int *));
    Result = (int **)malloc(tamaño * sizeof(int *));

    for (int i = 0; i < tamaño; ++i) {
        A[i] = (int *)malloc(tamaño * sizeof(int));
        B[i] = (int *)malloc(tamaño * sizeof(int));
        Result[i] = (int *)malloc(tamaño * sizeof(int));
    }

    llenarMatriz(A, tamaño);
    llenarMatriz(B, tamaño);

    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();
    multiplicarMatrices(A, B, Result, tamaño);
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    if (imprimir == 1) {
        printf("Matriz A:\n");
        mostrarMatriz(A, tamaño);

        printf("Matriz B:\n");
        mostrarMatriz(B, tamaño);

        printf("Matriz Resultado:\n");
        mostrarMatriz(Result, tamaño);
    }
    printf("%f Segundos\n", cpu_time_used);

    for (int i = 0; i < tamaño; ++i) {
        free(A[i]);
        free(B[i]);
        free(Result[i]);
    }
    free(A);
    free(B);
    free(Result);

    return 0;
}
