/*Proyect: Inventory Management. Buil a basic inventory management system for a store.
Allow users add products, update stock y generate inventory reports.
Author: Bryan Hernandez A.
Delivery date: 8 January 2024*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//To eliminate the error with ftruncate
#include <unistd.h>


/*Functions, structs to Add users*/
//Declaration of Function to add users
void agregarUsuarios();

//Functions to fix the bug of ID's
int leerUltimoID();
void escribirUltimoID(int ultimoID);

// Struct to add to the pointer *Empleados
struct AgregarEmpleado
{
    char nombre[50];
    char ID[5];  // Change the ID numerical to manage as string
    int ID_entero;  // Field to storage the string ID in int
    char contraseña[50];
};

/*Function and structs to add products*/
//Function declarated to 'agregar productos'
void agregarProductos();

//Struct to show list of products to any file 
struct Producto
{
    char nombre[50];
    float cantidad;
};
//Declaration of Function to show a list of products
void mostrarProductos(FILE *archivo);



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
        agregarProductos();
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

            //update the last ID with the file 'ultimoID'
            ultimoID = leerUltimoID();

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
            escribirUltimoID(ultimoID);
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
                //File to restart the ID's because all data is eliminated
                FILE *eliminarEmpleados = fopen("ultimoID.txt","w");
                if (eliminarEmpleados == NULL)
                {
                    perror("Error al reiniciar ID en ultimoID.txt");
                }
                int ultimoID;
                //If the integer is different to 0, write 0 in the file
                if (fscanf(eliminarEmpleados, "%d", ultimoID) != 0)
                {
                    ultimoID = 0;
                    fseek(eliminarEmpleados, 0, SEEK_SET);
                    fprintf(eliminarEmpleados, "%d", ultimoID);
                }
                
                fclose(busquedaEmpleados);
                fclose(eliminarEmpleados);
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

//Functions to fix the bug of ID's different
int leerUltimoID()
{   
    //File to read the last ID with the protocol 'r+' if doesnt exists nothing at the file
    FILE *archivoID = fopen("ultimoID.txt","r+");
    if (archivoID == NULL)
    {
        perror("\nError al abrir el archivo ultimoID.txt \n");
        return;
    }
    int ultimoID;
    if (fscanf(archivoID,"%d",&ultimoID)!=1)
    {
        //If not is possible read a integer, assigns 0 to ultimoID
        ultimoID = 0;
        //Move the pointer to the start and write again
        fseek(archivoID,0,SEEK_SET);
        fprintf(archivoID,"%d",ultimoID);
    }
    
    fclose(archivoID);
    return ultimoID;
}
void escribirUltimoID(int ultimoID)
{
    //File to write the last ID with the protocol 'w' to just write
    FILE *archivoID = fopen("ultimoID.txt","w");
    if (ultimoID == NULL)
    {
        perror("Error al abrir el archivo ultimoID.txt");
    }

    fprintf(archivoID,"%d",ultimoID);
    fclose(archivoID);
}


void agregarProductos()
{
    do
    {
        int menuAgregarProductos;
        int menuListadoproductos;
        printf("\nElija lo que requiere\n");
        printf("1. Agregar Productos\n");
        printf("2. Ver listas de productos\n");
        printf("3. Eliminar productos\n");
        printf("4. Salir\n:");
        scanf("%d",&menuAgregarProductos);

        //Variable to compare password
        char validarContraseña[50];
        switch (menuAgregarProductos)
        {
        case 1:
            //Process to validation passowrd admin
            printf("\nPara poder agregar productos, por favor ingrese la contraseña de admin\n");
            scanf("%s", validarContraseña);
            FILE *agregarProdAdmin = fopen("Administrador.txt", "r+");
            if (agregarProdAdmin == NULL)
            {
                perror("Error al abrir Administrador.txt para agregar productos");
            }
            char usuario[50],contraseña[50];
            fscanf(agregarProdAdmin, "%s %s",usuario,contraseña);

            //Add products after of password admin validation
            if (strcmp(validarContraseña, contraseña) == 0)
            {
                int menuProductos;
                printf("Ingresa el tipo de producto a registrar\n");
                printf("\n1. Abarrotes\n");
                printf("2. Enlatados\n");
                printf("3. Lácteos\n");
                printf("4. Botanas\n");
                printf("5. Frutas y verduras\n");
                printf("6. Bebidas alcoholicas\n");
                printf("7. Higiene personal\n");
                printf("8. Limpieza\n");
                printf("\n9. Salir \n:");
                scanf("%d",&menuProductos);

                int cantidadProductos;

                do
                {
                    //Menu to add each product that the admin choose (must testing)
                    switch (menuProductos)
                    {
                    //ABARROTES
                    case 1:
                        printf("Ingrese la cantidad de productos de abarrotes a ingresar\n");
                        scanf("%d",&cantidadProductos);
                        //File to add 'abarrotes' in .txt
                        FILE *abarrotes = fopen("Abarrotes.txt","a");
                        if (abarrotes == NULL)
                        {
                            perror("Error al abrir Abarrotes.txt para agregar productos\n");
                        }

                        for (int i = 0; i < cantidadProductos; i++)
                        {
                            char producto[50];
                            float cantidad;

                            printf("Ingrese el nombre del producto %d\n:",i+1);
                            scanf("%s", producto);
                            printf("Ingrese las unidades o cantidad de producto en kg\n:");
                            scanf("%f",&cantidad);

                            fprintf(abarrotes, "{%s,%.2f},", producto,cantidad);
                        }
                        fclose(abarrotes);
                        
                        return;
                    //ENLATADOS
                    case 2:
                        printf("Ingrese la cantidad de productos de enlatados a ingresar\n");
                        scanf("%d",&cantidadProductos);
                        //File to add 'abarrotes' in .txt
                        FILE *enlatados = fopen("Enlatados.txt","a");
                        if (enlatados == NULL)
                        {
                            perror("Error al abrir Abarrotes.txt para agregar productos\n");
                        }

                        for (int i = 0; i < cantidadProductos; i++)
                        {
                            char producto[50];
                            float cantidad;

                            printf("Ingrese el nombre del producto %d\n:",i+1);
                            scanf("%s", producto);
                            printf("Ingrese las unidades o cantidad de producto en kg\n:");
                            scanf("%f",&cantidad);

                            fprintf(enlatados, "{%s,%.2f},", producto,cantidad);
                        }
                        fclose(enlatados);
                        
                        return;
                    //Lacteos    
                    case 3:
                        printf("Ingrese la cantidad de productos de lacteos a ingresar\n");
                        scanf("%d",&cantidadProductos);
                        //File to add 'abarrotes' in .txt
                        FILE *lacteos = fopen("Lacteos.txt","a");
                        if (lacteos == NULL)
                        {
                            perror("Error al abrir Lacteos.txt para agregar productos\n");
                        }

                        for (int i = 0; i < cantidadProductos; i++)
                        {
                            char producto[50];
                            float cantidad;

                            printf("Ingrese el nombre del producto %d\n:",i+1);
                            scanf("%s", producto);
                            printf("Ingrese las unidades o cantidad de producto en kg\n:");
                            scanf("%f",&cantidad);

                            fprintf(lacteos, "{%s,%.2f},", producto,cantidad);
                        }
                        fclose(lacteos);
                        
                        return;
                    //botanas
                    case 4:
                        printf("Ingrese la cantidad de productos de botanas a ingresar\n");
                        scanf("%d",&cantidadProductos);
                        //File to add 'abarrotes' in .txt
                        FILE *botanas = fopen("Botanas.txt","a");
                        if (botanas == NULL)
                        {
                            perror("Error al abrir Botanas.txt para agregar productos\n");
                        }

                        for (int i = 0; i < cantidadProductos; i++)
                        {
                            char producto[50];
                            float cantidad;

                            printf("Ingrese el nombre del producto %d\n:",i+1);
                            scanf("%s", producto);
                            printf("Ingrese las unidades o cantidad de producto en kg\n:");
                            scanf("%f",&cantidad);

                            fprintf(botanas, "{%s,%.2f},", producto,cantidad);
                        }
                        fclose(botanas);
                        
                        return;
                    //Frutas y verduras
                    case 5:
                        printf("Ingrese la cantidad de productos de Frutas y Verduras a ingresar\n");
                        scanf("%d",&cantidadProductos);
                        //File to add 'abarrotes' in .txt
                        FILE *fyv = fopen("FrutasYVeruras.txt","a");
                        if (fyv == NULL)
                        {
                            perror("Error al abrir FrutasYVerduras.txt para agregar productos\n");
                        }

                        for (int i = 0; i < cantidadProductos; i++)
                        {
                            char producto[50];
                            float cantidad;

                            printf("Ingrese el nombre del producto %d\n:",i+1);
                            scanf("%s", producto);
                            printf("Ingrese las unidades o cantidad de producto en kg\n:");
                            scanf("%f",&cantidad);

                            fprintf(fyv, "{%s,%.2f},", producto,cantidad);
                        }
                        fclose(fyv);
                        
                        return;
                    //Bebidas alcoholicas
                    case 6:
                        printf("Ingrese la cantidad de productos de bebidas alcoholicas a ingresar\n");
                        scanf("%d",&cantidadProductos);
                        //File to add 'abarrotes' in .txt
                        FILE *BA = fopen("BebidasAlcoholicas.txt","a");
                        if (BA == NULL)
                        {
                            perror("Error al abrir BebidasAlcoholicas.txt para agregar productos\n");
                        }

                        for (int i = 0; i < cantidadProductos; i++)
                        {
                            char producto[50];
                            float cantidad;

                            printf("Ingrese el nombre del producto %d\n:",i+1);
                            scanf("%s", producto);
                            printf("Ingrese las unidades o cantidad de producto en kg\n:");
                            scanf("%f",&cantidad);

                            fprintf(BA, "{%s,%.2f},", producto,cantidad);
                        }
                        fclose(BA);
                        
                        return;
                    case 7:
                        printf("Ingrese la cantidad de productos de higiene personal a ingresar\n");
                        scanf("%d",&cantidadProductos);
                        //File to add 'abarrotes' in .txt
                        FILE *HP = fopen("HigienePersonal.txt","a");
                        if (HP == NULL)
                        {
                            perror("Error al abrir HigienePersonal.txt para agregar productos\n");
                        }

                        for (int i = 0; i < cantidadProductos; i++)
                        {
                            char producto[50];
                            float cantidad;

                            printf("Ingrese el nombre del producto %d\n:",i+1);
                            scanf("%s", producto);
                            printf("Ingrese las unidades o cantidad de producto en kg\n:");
                            scanf("%f",&cantidad);

                            fprintf(HP, "{%s,%.2f},", producto,cantidad);
                        }
                        fclose(HP);
                        
                        return;   
                    case 8:
                        printf("Ingrese la cantidad de productos de limpieza a ingresar\n");
                        scanf("%d",&cantidadProductos);
                        //File to add 'abarrotes' in .txt
                        FILE *limpieza = fopen("Limpieza.txt","a");
                        if (limpieza == NULL)
                        {
                            perror("Error al abrir Limpieza.txt para agregar productos\n");
                        }

                        for (int i = 0; i < cantidadProductos; i++)
                        {
                            char producto[50];
                            float cantidad;

                            printf("Ingrese el nombre del producto %d\n:",i+1);
                            scanf("%s", producto);
                            printf("Ingrese las unidades o cantidad de producto en kg\n:");
                            scanf("%f",&cantidad);

                            fprintf(limpieza, "{%s,%.2f},", producto,cantidad);
                        }
                        fclose(limpieza);
                        
                        return;     
                    
                    case 9:
                        return;
                    }
                } while (1);
                   
            }
            else
            {
                printf("\nContraseña erronea");
            }
            break;
        //See all products of department specific
        case 2:
            
            printf("\n¿Qué lista quieres ver?\n");
            printf("\n1. Abarrotes\n");
            printf("2. Enlatados\n");
            printf("3. Lácteos\n");
            printf("4. Botanas\n");
            printf("5. Frutas y verduras\n");
            printf("6. Bebidas alcoholicas\n");
            printf("7. Higiene personal\n");
            printf("8. Limpieza\n");
            printf("\n9. Salir \n:");
            scanf("%d", &menuListadoproductos);

            FILE *listaproductos = NULL;
            switch (menuListadoproductos)
                {
                case 1:
                    listaproductos = fopen("Abarrotes.txt","r");
                    if (listaproductos == NULL)
                    {
                        perror("Error al abrir Abarrotes.txt para mostrar lista");
                    }
                    mostrarProductos(listaproductos);
                    fclose(listaproductos);
                    
                    break;
                case 2:
                    listaproductos = fopen("Enlatados.txt","r");
                    if (listaproductos == NULL)
                    {
                        perror("Error al abrir Enlatados.txt para mostrar lista");
                    }
                    mostrarProductos(listaproductos);
                    fclose(listaproductos);

                    break;
                case 3:
                    listaproductos = fopen("Lacteos.txt","r");
                    if (listaproductos == NULL)
                    {
                        perror("Error al abrir Lacteos.txt para mostrar lista");
                    }
                    mostrarProductos(listaproductos);
                    fclose(listaproductos);

                    break;
                case 4: 
                    listaproductos = fopen("Botanas.txt","r");
                    if (listaproductos == NULL)
                    {
                        perror("Error al abrir Botanas.txt para mostrar lista");
                    }
                    mostrarProductos(listaproductos);
                    fclose(listaproductos);

                    break;
                case 5:
                    listaproductos = fopen("FrutasYVeruras.txt","r");
                    if (listaproductos == NULL)
                    {
                        perror("Error al abrir FrutasYVeruras.txt para mostrar lista");
                    }
                    mostrarProductos(listaproductos);
                    fclose(listaproductos);

                    break;
                case 6:
                    listaproductos = fopen("BebidasAlcoholicas.txt","r");
                    if (listaproductos == NULL)
                    {
                        perror("Error al abrir BebidasAlcoholicas.txt para mostrar lista");
                    }
                    mostrarProductos(listaproductos);
                    fclose(listaproductos);

                    break;
                
                case 7:
                    listaproductos = fopen("HigienePersonal.txt","r");
                    if (listaproductos == NULL)
                    {
                        perror("Error al abrir HigienePersonal.txt para mostrar lista");
                    }
                    mostrarProductos(listaproductos);
                    fclose(listaproductos);

                    break;
                case 8:
                    listaproductos = fopen("Limpieza.txt","r");
                    if (listaproductos == NULL)
                    {
                        perror("Error al abrir Limpieza.txt para mostrar lista");
                    }
                    mostrarProductos(listaproductos);
                    fclose(listaproductos);

                    break;
                case 9:
                    return;
                
                default:
                    printf("Opción no válida");
                    break;
                }
        //Delete products (first shows a list of product choosed and then the admin delete inside of file someone or all)
        case 3:

            break;
        fclose(agregarProdAdmin);
        case 4:
            return;
        }
    } while (1);
    
}


// Function to show the list of products
void mostrarProductos(FILE *archivo) {
    char nombre[50];
    float cantidad;

    printf("\nLista de productos:\n");
    printf("%-20s || %-20s\n", "Producto", "Cantidad en kg o unidades");

    // Read the content of file
    while (fscanf(archivo, "{%[^,],%f},", nombre, &cantidad) == 2) {
        printf("%-20s || %-20.2f\n", nombre, cantidad);
    }
}

