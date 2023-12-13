/*Proyect: Inventory Management. Buil a basic inventory management system for a store.
Allow users add products, update stock y generate inventory reports.
Author: Bryan Hernandez A.
Delivery date: 8 January 2024*/
#include <stdio.h>
#include <string.h>

//Declaration of Function to add users
void agregarUsuarios();
// Estructura para crear un array y añadirla al archivo *Empleados
struct AgregarEmpleado
{
    char nombre[50];
    char ID[5];  // Cambié el tipo a char para almacenar como cadena
    int ID_entero;  // Nuevo campo para almacenar el ID como un entero
    char contraseña[50];
};

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
        agregarUsuarios();
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

    if (opcion ==5)
    {
        break;
    }
    
    } while (1);
    
    return 0;
}

//Create Admin, employe to manage the inventory
void agregarUsuarios()
{
    //Modo escritura y lectura para administrador, considerar cambiar binario a texto
    FILE *Administrador = fopen("Administrador.bin", "a+");
    if (Administrador == NULL)
    {
        perror("Error al abrir Administrador.bin");
        return 1;
    }
    
    FILE *Empleados = fopen("Empleados.bin", "ab");
    if (Empleados == NULL)
    {
        perror("Error al abrir Empleados.bin");
        return 1;
    }
    
    int menuUsuario;
    //pedir cantidad de empleados a ingresar, variables para utilizar en Agregar Empleado
    int cantidadEmpleados;
    int ultimoID = 0;

    struct AgregarEmpleado empleados[9999];

    //Case 3
    char validarContraseña[50];
    char compararContraseñas[50];

    do
    {
        printf("\nIngrese usuario a crear\n");
        printf("1. Administrador (Solo es posible crear un administrador)\n");
        printf("2. Empleado\n");
        printf("3. Eliminar admin\n");
        printf("4. Eliminar empleado\n");
        scanf("%d", &menuUsuario);

        switch (menuUsuario)
        {
        case 1:
            // Verificar si el archivo está vacío con fseek
            fseek(Administrador, 0, SEEK_END);
    
            // Obtener el tamaño del archivo
            long sizeFile = ftell(Administrador);
    
            // Verificar si el archivo está vacío
            if (sizeFile == 0) {
                // Añadir Admin al archivo
                char contraseña[50];
                printf("Escribe la contraseña del usuario Admin\n:");
                scanf("%s", contraseña);
                fprintf(Administrador, "Admin %s\n", contraseña);
                printf("Administrador agregado con éxito.");
            } else {
                printf("Ya existe un Administrador en el sistema");
            }
    
        break;

        case 2:
            printf("Ingresa la cantidad de empleados a agregar\n");
            scanf("%d",&cantidadEmpleados);

            for (int i = 0; i < cantidadEmpleados; i++)
            {
                //incrementar el ultimo ID
                ultimoID++;
                //llenar con ceros a la izquierda los ID
                sprintf(empleados[i].ID, "%04d", ultimoID);
                //Asignar el ultimoID a empleados 
                empleados[i].ID_entero = ultimoID;

                printf("Ingrese el nombre del empleado sin espacios %d\n",ultimoID);
                scanf("%s",empleados[i].nombre);

                printf("Ingrese la contraseña del empleado %d\n",ultimoID);
                scanf("%s",empleados[i].contraseña);
            }
            //empleados, puntero que contiene los datos a escribir
            // sizeof tamaño de bytes por cada empleado ingresado
            //cantidadEmpleados, cuantos elementos se desean escribir
            //Empleados, el archivo fijado con un puntero al que se desea escribir
            fwrite(empleados, sizeof(struct AgregarEmpleado), cantidadEmpleados, Empleados);
            break;

            /*Now develops the two last options of this menu to eliminate admin or employee*/
        case 3:
            printf("Ingrese la contraseña para validar y eliminar usuario Administrador\n:");
            scanf("%s", validarContraseña);

            // Abrimos el archivo para lectura y escritura
            FILE *adminArchivo = fopen("Administrador.bin", "r+");
            if (adminArchivo == NULL) {
                perror("Error al abrir Administrador.bin");
                return 1;
            }

            // Leemos el administrador existente
            char usuario[50], contraseña[50];
            fscanf(adminArchivo, "%s %s", usuario, contraseña);

            // Comparamos la contraseña
            if (strcmp(validarContraseña, contraseña) == 0) {
                // Volvemos al inicio del archivo
                fseek(adminArchivo, 0, SEEK_SET);

                // Truncamos el archivo para borrar su contenido
                ftruncate(fileno(adminArchivo), 0);

                printf("\nAdministrador eliminado con éxito\n");
            } else {
                printf("\nContraseña incorrecta, vuelva a ingresarla\n");
            }

            fclose(adminArchivo);
        break;

        }
    } while (1);
    
    fclose(Administrador);
    fclose(Empleados);
}