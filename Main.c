/*Proyect: Inventory Management. Buil a basic inventory management system for a store.
Allow users add products, update stock y generate inventory reports.
Author: Bryan Hernandez A.
Delivery date: 8 January 2024*/
#include <stdio.h>
#include <string.h>
//To eliminate the error with ftruncate
#include <unistd.h>


//Declaration of Function to add users
void agregarUsuarios();
// Array to add to the pointer *Empleados
struct AgregarEmpleado
{
    char nombre[50];
    char ID[5];  // Change the ID numerical to manage as string
    int ID_entero;  // Field to storage the string ID in int
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
    printf("5. Salir del programa\n");
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
    //The pointer *Administrador will open in protocol open and append to update in each aperture 
    FILE *Administrador = fopen("Administrador.txt", "a+");
    if (Administrador == NULL)
    {
        perror("Error al abrir Administrador.txt");
        return 1;
    }
    //To open the file in writing mode and add to the end of the file, in adittion, if doesnt exist, creates the file   
    FILE *Empleados = fopen("Empleados.txt", "a");
    if (Empleados == NULL)
    {
        perror("Error al abrir Empleados.txt");
        return 1;
    }

    // Abre el archivo de empleados en modo lectura para el caso 4
    FILE *EmpleadosLista = fopen("Empleados.txt", "rb");
    
    int menuUsuario;
    //variables creates to use in AgregarEmpleado
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
        printf("4. Ver listados de empleados\n");
        printf("5. Eliminar empleados\n");
        printf("6. Regresar al menu principal\n:");
        scanf("%d", &menuUsuario);

        switch (menuUsuario)
        {
        case 1:
            // Verify if fseek is empty
             fseek(Administrador, 0, SEEK_END);
    
            // Obtain the size of file
            long sizeFile = ftell(Administrador);
    
            // Verify if file is empty
            if (sizeFile == 0) {
                // Add Admin to file
                char contraseña[50];
                printf("Escribe la contraseña del usuario Admin\n:");
                scanf("%s", contraseña);
                fprintf(Administrador, "Admin %s\n", contraseña);
                printf("Administrador agregado con éxito.");
            } else {
                printf("Ya existe un Administrador en el sistema");
            }
            fclose(Administrador);
    
        break;

        case 2:
            printf("Ingresa la cantidad de empleados a agregar\n");
            scanf("%d",&cantidadEmpleados);

            for (int i = 0; i < cantidadEmpleados; i++)
            {
                //increase the last ID
                ultimoID++;
                //fill with 0 to the left 
                sprintf(empleados[i].ID, "%04d", ultimoID);
                //Add the last ID to empleado 
                empleados[i].ID_entero = ultimoID;

                printf("Ingrese el nombre del empleado sin espacios %d\n",ultimoID);
                scanf("%s",empleados[i].nombre);

                printf("Ingrese la contraseña del empleado %d\n",ultimoID);
                scanf("%s",empleados[i].contraseña);
            }
            //empleados, pointer that contents the data
            // sizeof size of bytes for each empleado
            //cantidadEmpleados, elemnts to write
            //Empleados, the file set with a pointer to which you want to write
            fwrite(empleados, sizeof(struct AgregarEmpleado), cantidadEmpleados, Empleados);
            break;
            //Close the file of Empleados to update in each change of menu option
            fclose(Empleados);

            /*Now develops the two last options of this menu to eliminate admin or employee*/
        case 3:
            printf("Ingrese la contraseña para validar y eliminar usuario Administrador\n:");
            scanf("%s", validarContraseña);

            // Open the file to write and read
            FILE *adminArchivo = fopen("Administrador.txt", "r+");
            if (adminArchivo == NULL) {
                perror("Error al abrir Administrador.txt");
                return 1;
            }

            // Read the admin actual
            char usuario[50], contraseña[50];
            fscanf(adminArchivo, "%s %s", usuario, contraseña);

            // Compare the password
            if (strcmp(validarContraseña, contraseña) == 0) {
                // We go back to the  start of file
                fseek(adminArchivo, 0, SEEK_SET);

                // Truncate the file to delete the content (truncate the file to the size of the file that is 0)
                ftruncate(fileno(adminArchivo), 0);

                printf("\nAdministrador eliminado con éxito\n");
            } else {
                printf("\nContraseña incorrecta, vuelva a ingresarla\n");
            }

            fclose(adminArchivo);
            fclose(Administrador);
        break;

        case 4:
            printf("\nPara ver el listado de empleados verifique que es el admin\n");
            printf("\nIngrese su contraseña\n:");
            scanf("%s", validarContraseña);
            FILE *listaEmpleadosAdmin = fopen("Administrador.txt", "r+");
            if (listaEmpleadosAdmin == NULL)
            {
                perror("Error al abrir Administrador.txt");
                return 1;
            }
            // Read the admin actual
            char usuario2[50], contraseña2[50];
            fscanf(listaEmpleadosAdmin, "%s %s", usuario2, contraseña2);
            if (strcmp(validarContraseña, contraseña2) == 0)
            {
                if (EmpleadosLista == NULL)
                {
                    perror("Error al abrir Empleados.txt");
                    return;
                }

                // Declara una estructura temporal para leer cada empleado
                struct AgregarEmpleado empleado;

                // Lee y muestra la información de cada empleado hasta el final del archivo
                printf("\nListado de empleados:\n");
                while (fread(&empleado, sizeof(struct AgregarEmpleado), 1, EmpleadosLista) == 1)
                {
                    printf("ID: %s | Nombre: %s | Contraseña: %s\n", empleado.ID, empleado.nombre, empleado.contraseña);
                }

                // Cierra el archivo de empleados
                fclose(EmpleadosLista);
            }
            else
            {
                printf("Error de contraseña");
            }
        
            break;

        case 5:
            printf("¿Está seguro de que desea eliminar todos los empleados? (Esta acción no se puede deshacer)\n");
            printf("1. Sí\n");
            printf("2. No\n");
    
            int confirmacion;
            scanf("%d", &confirmacion);

            if (confirmacion == 1)
            {
                //Opens in binary to delete all data
                FILE *busquedaEmpleados = fopen("Empleados.txt", "wb");
                if (busquedaEmpleados == NULL)
                {
                    perror("Error al abrir Empleados.txt");
                    return 1;
                }

                fclose(busquedaEmpleados);
                printf("Todos los empleados han sido eliminados con éxito.\n");
            }
            else
            {
                printf("Operación cancelada. No se han realizado cambios en la lista de empleados.\n");
            }

            break;


        case 6:
            printf("Regresando a menu principal");
            return;
        }
    } while (1);
    //Release the memory and close the files, without errors on the files
    fclose(Administrador);
    fclose(Empleados);
}