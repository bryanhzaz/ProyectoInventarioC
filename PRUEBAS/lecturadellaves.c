#include <stdio.h>
#include <stdlib.h>

struct Producto {
    char nombre[50];
    float cantidad;
};

void mostrarListaProductos(FILE *archivo);

int main() {
    FILE *abarrotesLista = fopen("Abarrotes.txt", "r");

    if (abarrotesLista == NULL) {
        perror("Error al abrir Abarrotes.txt para mostrar lista\n");
        return 1;
    }

    mostrarListaProductos(abarrotesLista);

    fclose(abarrotesLista);
    return 0;
}

void mostrarListaProductos(FILE *archivo) {
    printf("\nLista de productos:\n");

    char buffer[100];  // Ajusta el tamaño según tus necesidades

    // Lee el contenido del archivo
    while (fscanf(archivo, "{%[^}]}%*c", buffer) == 1) {
        printf("%s\n", buffer);
    }
}
