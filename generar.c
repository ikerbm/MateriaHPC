#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generarMatrizArchivo(int n, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        fprintf(stderr, "Error al abrir el archivo %s para escribir.\n", nombreArchivo);
        exit(1);
    }

    fprintf(archivo, "%d\n", n);

    srand(time(NULL)); // Inicializar la semilla para números aleatorios

    // Generar y escribir la matriz aleatoria en el archivo
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fprintf(archivo, "%d ", rand() % 100 + 1); // Números aleatorios entre 1 y 100
        }
        fprintf(archivo, "\n");
    }

    fclose(archivo);
}

int main() {
    int n=0;

    // Generar la matriz y guardarla en un archivo
    generarMatrizArchivo(n, "matriz_generada.txt");

    printf("Matriz generada y guardada en el archivo 'matriz_generada.txt'\n");

    return 0;
}
