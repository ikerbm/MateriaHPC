#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    long k, n, hits;
    const double factor = 1.0 / RAND_MAX;

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 2)
    {
        if (rank == 0)
        {
            printf("Ingrese el número de intentos como argumento.\n");
        }
        MPI_Finalize();
        return 1;
    }
    else
    {
        n = atoi(argv[1]);
    }

    srand((int)time(NULL) + rank); // Añadir el rank para obtener semillas diferentes en cada proceso

    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock();

    long local_hits = 0;
    for (k = 0; k < n; ++k)
    {
        double y = rand() * factor;
        double x = rand() * factor;
        if (x * x + y * y < 1.0)
            ++local_hits;
    }

    MPI_Reduce(&local_hits, &hits, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        double pi_approx = 4.0 * hits / (n * size);
        end_time = clock();
        cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        printf("Aproximación de pi después de %ld intentos: %lf\n", n * size, pi_approx);

        FILE *fp;
        fp = fopen("tiempos.txt", "a");
        fprintf(fp, "Tiempo en segundos para %d procesos: %f\n", size, cpu_time_used);
        fclose(fp);
    }

    MPI_Finalize();

    return 0;
}
