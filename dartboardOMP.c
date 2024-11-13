#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    long k, n , hits;
    const double factor = 1.0 / RAND_MAX;

    if (argc < 2){
        printf("Ingrese el número de intentos como argumento.\n");
        return 1;
    } else {
        n = atoi(argv[1]);
    }

    srand((int) time(NULL));

    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock();    

    #pragma omp parallel for reduction(+:hits)
    for (k = 0; k < n; ++k) {
        double y = rand() * factor;
        double x = rand() * factor;
        if (x * x + y * y < 1.0) {
            ++hits;
        }
    }

    double pi_approx = 4.0 * hits / n;
    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    //printf("Aproximación de pi después de %ld intentos: %lf\n", n, pi_approx);
    printf("%f segundos\n", cpu_time_used);
}
