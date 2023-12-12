/*Proyect: Inventory Management. Buil a basic inventory management system for a store.
Allow users add products, update stock y generate inventory reports.
Author: Bryan Hernandez A.
Delivery date: 8 January 2024*/
#include <stdio.h>


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
    //pedir cantidad de empleados a ingresar
    int cantidadEmpleados;
    int ultimoID = 0;

    struct AgregarEmpleado empleados[9999];

    do
    {
        printf("\nIngrese usuario a crear\n");
        printf("1. Administrador (Solo es posible crear un administrador)\n");
        printf("2. Empleado\n");
        scanf("%d", &menuUsuario);

        switch (menuUsuario)
        {
        case 1:
        /*verificar si el archivo está vacío con fseek, hacemos uso del puntero *Administrador
        no nos movemos con el parametro 0 y nos situamos al final del archivo con SEEK_END*/
            fseek(Administrador, 0, SEEK_END);
        /*ftell() en C se utiliza para averiguar 
        la posición del puntero del archivo en el archivo con respecto al inicio del archivo.
        en este caso con ftell si la posicion es 0, entonces no hay nada en el archivo, por lo que
        es el primer y único Admin*/
            long sizeFile = ftell(Administrador);
            if (sizeFile == 0)
            {
                //Añadir Admin al archivo
                fprintf(Administrador,"Admin ");

                char contraseña[50];
                printf("Escribe la contraseña del usuario Admin\n");
                scanf("%s", contraseña);
                fprintf(Administrador,"%s",contraseña);
                printf("Administrador agregado con éxito.");
            }
            else
            {
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
        
        default:
        printf("Opcion no valida, ingrese de nuevo.");
            break;
        }
    } while (1);
    
    fclose(Administrador);
    fclose(Empleados);
}