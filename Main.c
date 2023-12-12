/*Proyect: Inventory Management. Buil a basic inventory management system for a store.
Allow users add products, update stock y generate inventory reports.
Author: Bryan Hernandez A.
Delivery date: 8 January 2024*/
#include <stdio.h>

//Main:
int main()
{
    //Create of menu to manage/add users, stock and informs.
    int opcion;
    do
    {
    printf("\nMenu de opciones\n");
    printf("1. Agregar usarios\n");
    printf("2. Agregar Productos\n");
    printf("3. Actualizar stock\n");
    printf("4. Reporte de inventario\n");
    printf("5. Salir del menú\n");
    printf("Seleccione una opcion\n:");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
        //Function to add users is developed
        printf("Agregar funcion de usuarios");
        break;
    case 2:
        //Function to add products is developed
        printf("Agregar funcion de añadir productos");
        break;
    case 3:
        //Function to update stock is developed
        printf("Agregar funcion de actualizacion de stock");
        break;
    case 4:
        //Function to generate inventory reports is developed
        printf("Agregar funcion de generador de reportes de inventario");
        break;
    case 5:
        printf("Saliendo del programa");
        break;
    
    default:
        printf("Opción no válida, intentelo de nuevo.");
        break;
    }

    } while (opcion != 5);
    
}