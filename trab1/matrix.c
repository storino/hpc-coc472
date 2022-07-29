#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

double get_random_value(int size)
{
    return rand() % size + 1;
}

double *instantiate_vector(int vector_size)
{
    return (double *)malloc((vector_size + 1) * sizeof(double));
}

double *zero_vector(int vector_size)
{
    double *vector = instantiate_vector(vector_size);
    for (int i = 0; i <= vector_size; i++)
        vector[i] = 0;

    return vector;
}

double *generate_random_vector(int vector_size)
{
    double *vector = instantiate_vector(vector_size);
    for (int i = 0; i <= vector_size; i++)
        vector[i] = get_random_value(vector_size);

    return vector;
}

double **instantiate_matrix(int matrix_size)
{
    double **matrix = (double **)malloc((matrix_size + 1) * sizeof(double *));
    for (int i = 0; i <= matrix_size; i++)
        matrix[i] = instantiate_vector(matrix_size);

    return matrix;
}

void fill_matrix_line(int current_line, int matrix_size, double **matrix)
{
    for (int j = 0; j <= matrix_size; j++)
        matrix[current_line][j] = get_random_value(matrix_size);
}

double **generate_random_matrix(int matrix_size)
{
    double **matrix = instantiate_matrix(matrix_size);
    for (int i = 0; i <= matrix_size; i++)
        fill_matrix_line(i, matrix_size, matrix);

    return matrix;
}

void free_matrix(double **matrix, int matrix_size)
{
    for (int i = 0; i <= matrix_size; i++)
        free(matrix[i]);

    free(matrix);
}

double *matrixVectorProd_ij(int size, double **matrix, double *vector)
{
    double *result = zero_vector(size);

    for (int i = 0; i <= size; i++){
        for (int j = 0; j <= size; j++){
            result[i] += matrix[i][j] * vector[j];
        }
    }
    return result;
}

double *matrixVectorProd_ji(int size, double **matrix, double *vector)
{
    double *result = zero_vector(size);
    for (int j = 0; j <= size; j++){
        for (int i = 0; i <= size; i++){
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    clock_t antes, depois;
    double *result;

    int size = atoi(argv[1]);
    char operation_type = atoi(argv[2]);

    double **matrix = generate_random_matrix(size);
    double *vector = generate_random_vector(size);
    
    srand(time(NULL));

    if (operation_type == 1)
    {
        antes = clock();
        result = matrixVectorProd_ij(size, matrix, vector);
        depois = clock();
    }
    else if (operation_type == 2)
    {
        antes = clock();
        result = matrixVectorProd_ji(size, matrix, vector);
        depois = clock();
    }
    else
    {
        printf("Specify type 1 or 2 for operation type");
        return -1;
    }

    free_matrix(matrix, size);
    free(vector);
    free(result);

    printf("%d;%.6f\n", size, ((double)(depois - antes)) / CLOCKS_PER_SEC);

    return 0;
}