/*Proyect: Inventory Management. Buil a basic inventory management system for a store.
Allow users add products, update stock y generate inventory reports.
Author: Bryan Hernandez A.
Delivery date: 8 January 2024*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//To eliminate the error with ftruncate
#include <unistd.h>
#include <ctype.h>


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
//Struct use too in 'actualizasStock' 
struct Producto
{
    char nombre[50];
    float cantidad;
};
//Declaration of Function to show a list of products with any file 
void mostrarProductos(FILE *archivo);

//Function to delete lists of products with confirmation of user
void eliminarProductos(char *nombrearchivo);

/*Function and structs to update stock*/
//Function to update stock
void actualizarStock();
void mostrarProductosStock(struct Producto *productos, int numProductos);
struct Empleado
{
    char nombre[50];
    char ID[5];
    char contraseña[50];
};


/*Function to generate a report of the last week of inventory*/
void generarInformes();


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
        //Function to add users is ready (all data is in form matrix)
        agregarUsuarios();
        break;
    case 2:
        //Function to add products is ready (all data is in form matrix)
        agregarProductos();
        break;
    case 3:
        //Function to update stock is developed
        actualizarStock();
        break;
    case 4:
        //Function to generate inventory reports is developed
        generarInformes();
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

//Create Admin, employe to manage the inventory (is ready)
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
            //To update each ID if the list registers not is consecutive
            escribirUltimoID(ultimoID);
            //Matrix of 'empleados' in the form {Nombre, ID, Contraseña},
            for (int i = 0; i < cantidadEmpleados; i++)
            {
                fprintf(Empleados, "{%s, %s, %s},",empleados[i].nombre,empleados[i].ID, empleados[i].contraseña);
            }
            

            //Close the file of Empleados to update in each change of menu option
            fclose(Empleados);
            
            break;
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

                char nombre[50], ID[50], contraseñaEmpleados[50];
                printf("\nListado de empleados\n");
                while (fscanf(EmpleadosLista, "{%[^,],%[^,],%[^}]},",nombre,ID, contraseñaEmpleados) == 3)
                {
                    printf("Nombre: %s || ID: %s || Contraseña: %s\n",nombre,ID,contraseñaEmpleados);
                }
                

                // Close the files of 'empleados'
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

//Add products, see lists and delete data (is ready)
void agregarProductos()
{
    do
    {
        int menuAgregarProductos;
        int menuListadoproductos;
        int menuBorrarproductos;
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
            printf("\n¿Qué lista quieres eliminar?\n");
            printf("\n1. Abarrotes\n");
            printf("2. Enlatados\n");
            printf("3. Lácteos\n");
            printf("4. Botanas\n");
            printf("5. Frutas y verduras\n");
            printf("6. Bebidas alcoholicas\n");
            printf("7. Higiene personal\n");
            printf("8. Limpieza\n");
            printf("\n9. Salir \n:");
            scanf("%d", &menuBorrarproductos);
            switch (menuBorrarproductos)
            {
            case 1:
                eliminarProductos("Abarrotes.txt");
                break;
            case 2: 
                eliminarProductos("Enlatados.txt");
                break;
            case 3:
                eliminarProductos("Lacteos.txt");
                break;
            case 4:
                eliminarProductos("Botanas.txt");
                break;
            case 5:
                eliminarProductos("FrutasYVeruras.txt");
                break;
            case 6:
                eliminarProductos("BebidasAlcoholicas.txt");
                break;
            case 7:
                eliminarProductos("HigienePersonal.txt");
                break;
            case 8:
                eliminarProductos("Limpieza.txt");
                break;
            case 9:
                return;
            
            default:
                break;
            }

            break;
        fclose(agregarProdAdmin);
        //Option to can out of this menu
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

//Function to delete lists of products with confirmation of user
void eliminarProductos(char *nombrearchivo)
{
    char respuesta;
    printf("\n¿Estás seguro que deseas eliminar toda la lista de productos seleccionada?\n");
    printf("Escribe 'S' para confirmar o 'N' para eliminar seleccion\n:");
    scanf(" %c", &respuesta);

    char validarContraseña[50];
    printf("\nPara poder validar seleccion, por favor ingrese la contraseña de admin\n");
    scanf("%s", validarContraseña);
    FILE *seguridadAdmin = fopen("Administrador.txt", "r+");
    if (seguridadAdmin == NULL)
    {
        perror("Error al abrir Administrador.txt para agregar productos");
    }
    char usuario[50],contraseña[50];
    fscanf(seguridadAdmin, "%s %s",usuario,contraseña);

    if (strcmp(validarContraseña,contraseña) == 0)
    {
        if (respuesta == 'S' || respuesta == 's')
        {
            FILE *archivo = fopen(nombrearchivo,"w");
            if (archivo == NULL)
            {
                perror("\nError al abrir archivo para borrar");
            }
            
            //Delete all file of directory
            remove(nombrearchivo);
            printf("Se han eliminado todos los productos\n");
        }
        else
        {
            printf("\nNo se eliminaron los productos\n");
        }
        
    }
    else
    {
        printf("\nContraseña erronea");
    }
    fclose(seguridadAdmin);

}
//Update the stock of inventory per week by each user without the admin (is ready)
void actualizarStock()
{
    int menuStock;
    int menuArea;
    printf("\nElige la opción de actualizacion\n");
    printf("Borrar el historial de stock cada semana o después de generar un reporte de inventario\n");
    printf("1. Agregar unidades\n");
    printf("2. Descartar unidades\n");
    printf("3. Borrar historial de productos agregados\n");
    printf("4. Borrar historial de productos quitados\n");
    printf("\n5. Salir\n:");
    scanf("%d", &menuStock);

    // Validate the ID with password
    FILE *empleadosArchivo = fopen("Empleados.txt", "r");
    if (empleadosArchivo == NULL)
    {
        perror("No es posible abrir Empleados.txt");
        return;
    }

    // Verification of empleado
    char empleadoID[5];
    char contraseña[50];

    printf("Ingrese su ID de empleado (4 digitos sin espacio)\n:");
    scanf("%s", empleadoID);

    printf("\nIngrese su contraseña sin espacios\n");
    scanf("%s", contraseña);

    struct Empleado empleadoActual;
    int empleadoEncontrado = 0;

    while (fscanf(empleadosArchivo, "{%[^,], %[^,], %[^}]}%*c", empleadoActual.nombre, empleadoActual.ID, empleadoActual.contraseña) == 3)
    {
        // Case insensitive comparison
        if (strcasecmp(empleadoActual.ID, empleadoID) == 0 && strcasecmp(empleadoActual.contraseña, contraseña) == 0)
        {
            empleadoEncontrado = 1;
            printf("\nCONTRASEÑA coincide con ID del empleado ingresado\n");
            break;
        }
    }

    fclose(empleadosArchivo);

    // Colocar la verificación aquí
    if (!empleadoEncontrado)
    {
        printf("ID de empleado o contraseña incorrectos,\n");
        return;
    }



    //File to Abarrotes
    FILE *archivo;
    char *nombreArchivo = "Abarrotes.txt";
    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL)
    {
        perror("Error al abrir Abarrotes.txt para mostrar lista de productos");
        return;
    }

    //File to Enlatados
    FILE *archivo2;
    char *nombreArchivo2 = "Enlatados.txt";
    archivo2 = fopen(nombreArchivo2, "r");
    if (archivo2 == NULL)
    {
        perror("Error al abrir Enlatados.txt para mostrar lista de productos");
        return;
    }

    //File to Lacteos
    FILE *archivo3;
    char *nombreArchivo3 = "Lacteos.txt";
    archivo3 = fopen(nombreArchivo3, "r");
    if (archivo3 == NULL)
    {
        perror("Error al abrir Lacteos.txt para mostrar lista de productos");
        return;
    }

    //File to Botanas 
    FILE *archivo4;
    char *nombreArchivo4 = "Botanas.txt";
    archivo4 = fopen(nombreArchivo4, "r");
    if (archivo4 == NULL)
    {
        perror("Error al abrir Botanas.txt para mostrar lista de productos");
        return;
    }

    //File to FrutasYVeruras 
    FILE *archivo5;
    char *nombreArchivo5 = "FrutasYVeruras.txt";
    archivo5 = fopen(nombreArchivo5, "r");
    if (archivo5 == NULL)
    {
        perror("Error al abrir FrutasYVeruras.txt para mostrar lista de productos");
        return;
    }

    //File to BebidasAlcoholicas HigienePersonal
    FILE *archivo6;
    char *nombreArchivo6 = "BebidasAlcoholicas.txt";
    archivo6 = fopen(nombreArchivo6, "r");
    if (archivo6 == NULL)
    {
        perror("Error al abrir BebidasAlcoholicas.txt para mostrar lista de productos");
        return;
    }

    //File to HigienePersonal
    FILE *archivo7;
    char *nombreArchivo7 = "HigienePersonal.txt";
    archivo7 = fopen(nombreArchivo7, "r");
    if (archivo7 == NULL)
    {
        perror("Error al abrir HigienePersonal.txt para mostrar lista de productos");
        return;
    }
    //File to Limpieza
    FILE *archivo8;
    char *nombreArchivo8 = "Limpieza.txt";
    archivo8 = fopen(nombreArchivo8, "r");
    if (archivo8 == NULL)
    {
        perror("Error al abrir HigienePersonal.txt para mostrar lista de productos");
        return;
    }

    // To count products
    int numProductos = 0;
    char c;

    //To validate admin
    char validarContraseña[50];

    switch (menuStock)
    {
    // Increase the products
    case 1:
        printf("\nAhora elige el área a actualizar\n");
        printf("1. Abarrotes\n");
        printf("2. Enlatados\n");
        printf("3. Lácteos\n");
        printf("4. Botanas\n");
        printf("5. Frutas y verduras\n");
        printf("6. Bebidas alcoholicas\n");
        printf("7. Higiene personal\n");
        printf("8. Limpieza\n");
        printf("\n:");
        scanf("%d", &menuArea);
        switch (menuArea)
        {
        // Abarrotes
        case 1:
            
            while ((c = fgetc(archivo)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo);

            struct Producto *productos = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo, "{%[^,],%f},", productos[i].nombre, &productos[i].cantidad);
            }

            fclose(archivo);

            mostrarProductosStock(productos, numProductos);


            int cantidad;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad);

            if (cantidad<=0 || cantidad > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos);
                return;
            }
            
            int *opciones = (int *)malloc(cantidad * sizeof(int));
            if (opciones == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad; i++)
            {
                
                int indice = opciones[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a agregar de %s: ", productos[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos[indice].cantidad += cantidadAgregar;
                
            }

            FILE *archivoEmpleados = fopen("AbarrotesEmpleados.txt", "a+");
            if (archivoEmpleados == NULL)
            {
                perror("Error al abrir o crear AbarrotesEmpleados.txt");
                free(productos);
                free(opciones);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados, "{%s,%.2f,%s},", productos[i].nombre, productos[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados);
            free(productos);
            free(opciones);

            break;
        case 2:
            //Enlatados.txt
            while ((c = fgetc(archivo2)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo2);

            struct Producto *productos2 = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos2 == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo2);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo2, "{%[^,],%f},", productos2[i].nombre, &productos2[i].cantidad);
            }

            fclose(archivo2);

            mostrarProductosStock(productos2, numProductos);


            int cantidad2;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad2);

            if (cantidad2<=0 || cantidad2 > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos2);
                return;
            }
            
            int *opciones2 = (int *)malloc(cantidad2 * sizeof(int));
            if (opciones2 == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos2);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad2; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones2[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad2; i++)
            {
                
                int indice = opciones2[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a agregar de %s: ", productos2[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos2[indice].cantidad += cantidadAgregar;
                
            }

            FILE *archivoEmpleados2 = fopen("EnlatadosEmpleados.txt", "a+");
            if (archivoEmpleados2 == NULL)
            {
                perror("Error al abrir o crear EnlatadosEmpleados.txt");
                free(productos2);
                free(opciones2);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados2, "{%s,%.2f,%s},", productos2[i].nombre, productos2[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados2);
            free(productos2);
            free(opciones2);
            break;
        case 3:
            //Lacteos.txt
            while ((c = fgetc(archivo3)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo3);

            struct Producto *productos3 = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos3 == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo3);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo3, "{%[^,],%f},", productos3[i].nombre, &productos3[i].cantidad);
            }

            fclose(archivo3);

            mostrarProductosStock(productos3, numProductos);


            int cantidad3;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad3);

            if (cantidad3<=0 || cantidad3 > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos3);
                return;
            }
            
            int *opciones3 = (int *)malloc(cantidad3 * sizeof(int));
            if (opciones3 == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos3);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad3; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones3[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad3; i++)
            {
                
                int indice = opciones3[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a agregar de %s: ", productos3[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos3[indice].cantidad += cantidadAgregar;
                
            }

            FILE *archivoEmpleados3 = fopen("LacteosEmpleados.txt", "a+");
            if (archivoEmpleados3 == NULL)
            {
                perror("Error al abrir o crear LacteosEmpleados.txt");
                free(productos3);
                free(opciones3);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados3, "{%s,%.2f,%s},", productos3[i].nombre, productos3[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados3);
            free(productos3);
            free(opciones3);
            break;

        case 4:
            //Botanas
            while ((c = fgetc(archivo4)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo4);

            struct Producto *productos4 = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos4 == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo4);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo4, "{%[^,],%f},", productos4[i].nombre, &productos4[i].cantidad);
            }

            fclose(archivo4);

            mostrarProductosStock(productos4, numProductos);


            int cantidad4;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad4);

            if (cantidad4<=0 || cantidad4 > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos4);
                return;
            }
            
            int *opciones4 = (int *)malloc(cantidad4 * sizeof(int));
            if (opciones4 == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos4);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad4; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones4[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad4; i++)
            {
                
                int indice = opciones4[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a agregar de %s: ", productos4[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos4[indice].cantidad += cantidadAgregar;
                
            }

            FILE *archivoEmpleados4 = fopen("BotanasEmpleados.txt", "a+");
            if (archivoEmpleados4 == NULL)
            {
                perror("Error al abrir o crear BotanasEmpleados.txt");
                free(productos4);
                free(opciones4);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados4, "{%s,%.2f,%s},", productos4[i].nombre, productos4[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados4);
            free(productos4);
            free(opciones4);
            break;
        case 5:
            //Frutas y verduras
            while ((c = fgetc(archivo5)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo5);

            struct Producto *productos5 = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos5 == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo5);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo5, "{%[^,],%f},", productos5[i].nombre, &productos5[i].cantidad);
            }

            fclose(archivo5);

            mostrarProductosStock(productos5, numProductos);


            int cantidad5;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad5);

            if (cantidad5<=0 || cantidad5 > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos5);
                return;
            }
            
            int *opciones5 = (int *)malloc(cantidad5 * sizeof(int));
            if (opciones5 == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos5);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad5; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones5[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad5; i++)
            {
                
                int indice = opciones5[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a agregar de %s: ", productos5[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos5[indice].cantidad += cantidadAgregar;
                
            }

            FILE *archivoEmpleados5 = fopen("FrutasYVerurasEmpleados.txt", "a+");
            if (archivoEmpleados5 == NULL)
            {
                perror("Error al abrir o crear FrutasYVerurasEmpleados.txt");
                free(productos5);
                free(opciones5);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados5, "{%s,%.2f,%s},", productos5[i].nombre, productos5[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados5);
            free(productos5);
            free(opciones5);
            break;
        case 6:
            //Bebidas Alcoholicas
            while ((c = fgetc(archivo6)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo6);

            struct Producto *productos6 = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos6 == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo6);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo6, "{%[^,],%f},", productos6[i].nombre, &productos6[i].cantidad);
            }

            fclose(archivo6);

            mostrarProductosStock(productos6, numProductos);


            int cantidad6;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad6);

            if (cantidad6<=0 || cantidad6 > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos6);
                return;
            }
            
            int *opciones6 = (int *)malloc(cantidad6 * sizeof(int));
            if (opciones6 == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos6);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad6; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones6[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad6; i++)
            {
                
                int indice = opciones6[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a agregar de %s: ", productos6[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos6[indice].cantidad += cantidadAgregar;
                
            }

            FILE *archivoEmpleados6 = fopen("BebidasAlcoholicasEmpleados.txt", "a+");
            if (archivoEmpleados6 == NULL)
            {
                perror("Error al abrir o crear BebidasAlcoholicasEmpleados.txt");
                free(productos6);
                free(opciones6);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados6, "{%s,%.2f,%s},", productos6[i].nombre, productos6[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados6);
            free(productos6);
            free(opciones6);
            break;
        
        case 7: 
            //HigienePersonal
            while ((c = fgetc(archivo7)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo7);

            struct Producto *productos7 = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos7 == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo7);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo7, "{%[^,],%f},", productos7[i].nombre, &productos7[i].cantidad);
            }

            fclose(archivo7);

            mostrarProductosStock(productos7, numProductos);


            int cantidad7;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad7);

            if (cantidad7<=0 || cantidad7 > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos7);
                return;
            }
            
            int *opciones7 = (int *)malloc(cantidad7 * sizeof(int));
            if (opciones7 == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos7);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad7; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones7[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad7; i++)
            {
                
                int indice = opciones7[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a agregar de %s: ", productos7[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos7[indice].cantidad += cantidadAgregar;
                
            }

            FILE *archivoEmpleados7 = fopen("HigienePersonalEmpleados.txt", "a+");
            if (archivoEmpleados7 == NULL)
            {
                perror("Error al abrir o crear HigienePersonalEmpleados.txt");
                free(productos7);
                free(opciones7);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados7, "{%s,%.2f,%s},", productos7[i].nombre, productos7[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados7);
            free(productos7);
            free(opciones7);
            break;
        case 8:
            //Limpieza
            while ((c = fgetc(archivo8)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo8);

            struct Producto *productos8 = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos8 == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo8);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo8, "{%[^,],%f},", productos8[i].nombre, &productos8[i].cantidad);
            }

            fclose(archivo8);

            mostrarProductosStock(productos8, numProductos);


            int cantidad8;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad8);

            if (cantidad8<=0 || cantidad8 > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos8);
                return;
            }
            
            int *opciones8 = (int *)malloc(cantidad8 * sizeof(int));
            if (opciones8 == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos8);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad8; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones8[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad; i++)
            {
                
                int indice = opciones8[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a agregar de %s: ", productos8[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos8[indice].cantidad += cantidadAgregar;
                
            }

            FILE *archivoEmpleados8 = fopen("LimpiezaEmpleados.txt", "a+");
            if (archivoEmpleados8 == NULL)
            {
                perror("Error al abrir o crear LimpiezaEmpleados.txt");
                free(productos8);
                free(opciones8);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados8, "{%s,%.2f,%s},", productos[i].nombre, productos[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados8);
            free(productos8);
            free(opciones8);
            break;


        default:
            break;
        }
        break;
    case 2:
        //Decrease the products
        printf("\nAhora elige el área a actualizar\n");
        printf("1. Abarrotes\n");
        printf("2. Enlatados\n");
        printf("3. Lácteos\n");
        printf("4. Botanas\n");
        printf("5. Frutas y verduras\n");
        printf("6. Bebidas alcoholicas\n");
        printf("7. Higiene personal\n");
        printf("8. Limpieza\n");
        printf("\n:");
        scanf("%d", &menuArea);
        switch (menuArea)
        {
        // Abarrotes
        case 1:
            
            while ((c = fgetc(archivo)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo);

            struct Producto *productos = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo, "{%[^,],%f},", productos[i].nombre, &productos[i].cantidad);
            }

            fclose(archivo);

            mostrarProductosStock(productos, numProductos);


            int cantidad;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad);

            if (cantidad<=0 || cantidad > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos);
                return;
            }
            
            int *opciones = (int *)malloc(cantidad * sizeof(int));
            if (opciones == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad; i++)
            {
                
                int indice = opciones[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a quitar de %s: ", productos[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos[indice].cantidad -= cantidadAgregar;
                
            }

            FILE *archivoEmpleados = fopen("AbarrotesEmpleadosN.txt", "a+");
            if (archivoEmpleados == NULL)
            {
                perror("Error al abrir o crear AbarrotesEmpleadosN.txt");
                free(productos);
                free(opciones);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados, "{%s,%.2f,%s},", productos[i].nombre, productos[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados);
            free(productos);
            free(opciones);

            break;
        case 2:
            //Enlatados.txt
            while ((c = fgetc(archivo2)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo2);

            struct Producto *productos2 = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos2 == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo2);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo2, "{%[^,],%f},", productos2[i].nombre, &productos2[i].cantidad);
            }

            fclose(archivo2);

            mostrarProductosStock(productos2, numProductos);


            int cantidad2;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad2);

            if (cantidad2<=0 || cantidad2 > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos2);
                return;
            }
            
            int *opciones2 = (int *)malloc(cantidad2 * sizeof(int));
            if (opciones2 == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos2);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad2; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones2[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad2; i++)
            {
                
                int indice = opciones2[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a quitar de %s: ", productos2[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos2[indice].cantidad -= cantidadAgregar;
                
            }

            FILE *archivoEmpleados2 = fopen("EnlatadosEmpleadosN.txt", "a+");
            if (archivoEmpleados2 == NULL)
            {
                perror("Error al abrir o crear EnlatadosEmpleadosN.txt");
                free(productos2);
                free(opciones2);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados2, "{%s,%.2f,%s},", productos2[i].nombre, productos2[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados2);
            free(productos2);
            free(opciones2);
            break;
        case 3:
            //Lacteos.txt
            while ((c = fgetc(archivo3)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo3);

            struct Producto *productos3 = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos3 == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo3);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo3, "{%[^,],%f},", productos3[i].nombre, &productos3[i].cantidad);
            }

            fclose(archivo3);

            mostrarProductosStock(productos3, numProductos);


            int cantidad3;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad3);

            if (cantidad3<=0 || cantidad3 > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos3);
                return;
            }
            
            int *opciones3 = (int *)malloc(cantidad3 * sizeof(int));
            if (opciones3 == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos3);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad3; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones3[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad3; i++)
            {
                
                int indice = opciones3[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a quitar de %s: ", productos3[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos3[indice].cantidad -= cantidadAgregar;
                
            }

            FILE *archivoEmpleados3 = fopen("LacteosEmpleadosN.txt", "a+");
            if (archivoEmpleados3 == NULL)
            {
                perror("Error al abrir o crear LacteosEmpleadosN.txt");
                free(productos3);
                free(opciones3);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados3, "{%s,%.2f,%s},", productos3[i].nombre, productos3[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados3);
            free(productos3);
            free(opciones3);
            break;

        case 4:
            //Botanas
            while ((c = fgetc(archivo4)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo4);

            struct Producto *productos4 = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos4 == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo4);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo4, "{%[^,],%f},", productos4[i].nombre, &productos4[i].cantidad);
            }

            fclose(archivo4);

            mostrarProductosStock(productos4, numProductos);


            int cantidad4;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad4);

            if (cantidad4<=0 || cantidad4 > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos4);
                return;
            }
            
            int *opciones4 = (int *)malloc(cantidad4 * sizeof(int));
            if (opciones4 == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos4);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad4; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones4[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad4; i++)
            {
                
                int indice = opciones4[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a quitar de %s: ", productos4[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos4[indice].cantidad -= cantidadAgregar;
                
            }

            FILE *archivoEmpleados4 = fopen("BotanasEmpleadosN.txt", "a+");
            if (archivoEmpleados4 == NULL)
            {
                perror("Error al abrir o crear BotanasEmpleadosN.txt");
                free(productos4);
                free(opciones4);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados4, "{%s,%.2f,%s},", productos4[i].nombre, productos4[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados4);
            free(productos4);
            free(opciones4);
            break;
        case 5:
            //Frutas y verduras
            while ((c = fgetc(archivo5)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo5);

            struct Producto *productos5 = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos5 == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo5);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo5, "{%[^,],%f},", productos5[i].nombre, &productos5[i].cantidad);
            }

            fclose(archivo5);

            mostrarProductosStock(productos5, numProductos);


            int cantidad5;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad5);

            if (cantidad5<=0 || cantidad5 > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos5);
                return;
            }
            
            int *opciones5 = (int *)malloc(cantidad5 * sizeof(int));
            if (opciones5 == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos5);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad5; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones5[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad; i++)
            {
                
                int indice = opciones5[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a quitar de %s: ", productos5[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos5[indice].cantidad -= cantidadAgregar;
                
            }

            FILE *archivoEmpleados5 = fopen("FrutasYVerurasEmpleadosN.txt", "a+");
            if (archivoEmpleados5 == NULL)
            {
                perror("Error al abrir o crear FrutasYVerurasEmpleadosN.txt");
                free(productos5);
                free(opciones5);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados5, "{%s,%.2f,%s},", productos5[i].nombre, productos5[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados5);
            free(productos5);
            free(opciones5);
            break;
        case 6:
            //Bebidas Alcoholicas
            while ((c = fgetc(archivo6)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo6);

            struct Producto *productos6 = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos6 == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo6);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo6, "{%[^,],%f},", productos6[i].nombre, &productos6[i].cantidad);
            }

            fclose(archivo6);

            mostrarProductosStock(productos6, numProductos);


            int cantidad6;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad6);

            if (cantidad6<=0 || cantidad6 > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos6);
                return;
            }
            
            int *opciones6 = (int *)malloc(cantidad6 * sizeof(int));
            if (opciones6 == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos6);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad6; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones6[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad; i++)
            {
                
                int indice = opciones6[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a quitar de %s: ", productos6[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos6[indice].cantidad -= cantidadAgregar;
                
            }

            FILE *archivoEmpleados6 = fopen("BebidasAlcoholicasEmpleadosN.txt", "a+");
            if (archivoEmpleados6 == NULL)
            {
                perror("Error al abrir o crear BebidasAlcoholicasEmpleadosN.txt");
                free(productos6);
                free(opciones6);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados6, "{%s,%.2f,%s},", productos6[i].nombre, productos6[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados6);
            free(productos6);
            free(opciones6);
            break;
        
        case 7: 
            //HigienePersonal
            while ((c = fgetc(archivo7)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo7);

            struct Producto *productos7 = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos7 == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo7);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo7, "{%[^,],%f},", productos7[i].nombre, &productos7[i].cantidad);
            }

            fclose(archivo7);

            mostrarProductosStock(productos7, numProductos);


            int cantidad7;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad7);

            if (cantidad7<=0 || cantidad7 > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos7);
                return;
            }
            
            int *opciones7 = (int *)malloc(cantidad7 * sizeof(int));
            if (opciones7 == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos7);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad7; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones7[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad7; i++)
            {
                
                int indice = opciones7[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a quitar de %s: ", productos7[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos7[indice].cantidad -= cantidadAgregar;
                
            }

            FILE *archivoEmpleados7 = fopen("HigienePersonalEmpleadosN.txt", "a+");
            if (archivoEmpleados7 == NULL)
            {
                perror("Error al abrir o crear HigienePersonalEmpleadosN.txt");
                free(productos7);
                free(opciones7);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados7, "{%s,%.2f,%s},", productos7[i].nombre, productos7[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados7);
            free(productos7);
            free(opciones7);
            break;
        case 8:
            //Limpieza
            while ((c = fgetc(archivo8)) != EOF)   
            {
                if (c == '}')
                {
                    numProductos++;
                }
            }

            rewind(archivo8);

            struct Producto *productos8 = (struct Producto *)malloc(numProductos * sizeof(struct Producto));
            if (productos8 == NULL)
            {
                perror("Error al asignar memoria\n");
                fclose(archivo8);
                return;
            }

            for (int i = 0; i < numProductos; i++)
            {
                fscanf(archivo8, "{%[^,],%f},", productos8[i].nombre, &productos8[i].cantidad);
            }

            fclose(archivo8);

            mostrarProductosStock(productos8, numProductos);


            int cantidad8;
            printf("Ingresa la cantidad de productos de la lista que actualizaras\n");
            scanf("%d", &cantidad8);

            if (cantidad8<=0 || cantidad8 > numProductos)
            {
                printf("Cantidad no valida.\n");
                free(productos8);
                return;
            }
            
            int *opciones8 = (int *)malloc(cantidad8 * sizeof(int));
            if (opciones8 == NULL)
            {
                perror("Error al asignar memoria\n");
                free(productos8);
                return;
            }
            

            printf("\nSeleccione las opciones de productos a actualizar en la lista\n:");
            for (int i = 0; i < cantidad8; i++)
            {
                int opcion;
                scanf("%d", &opcion);

                opcion--;

                if (opcion<0 || opcion>=numProductos)
                {
                    printf("Opcion no valida");
                    i--;
                }
                else
                {
                    opciones8[i] = opcion;
                }
                
            }

            // Update the amount of products
            for (int i = 0; i < cantidad8; i++)
            {
                
                int indice = opciones8[i];
                float cantidadAgregar;
                printf("Ingrese la cantidad a quitar de %s: ", productos8[indice].nombre);
                scanf("%f", &cantidadAgregar);

                productos8[indice].cantidad -= cantidadAgregar;
                
            }

            FILE *archivoEmpleados8 = fopen("LimpiezaEmpleadosN.txt", "a+");
            if (archivoEmpleados8 == NULL)
            {
                perror("Error al abrir o crear LimpiezaEmpleadosN.txt");
                free(productos8);
                free(opciones8);
                return;
            }

            // Save the products
            for (int i = 0; i < numProductos; i++)
            {
                fprintf(archivoEmpleados8, "{%s,%.2f,%s},", productos8[i].nombre, productos8[i].cantidad, empleadoID);
            }

            fclose(archivoEmpleados8);
            free(productos8);
            free(opciones8);
            break;


        default:
            break;
        }

        break;
    case 3:
        printf("\nPara poder eliminar historial, por favor ingrese la contraseña de admin\n");
        scanf("%s", validarContraseña);
        FILE *eliminarIncrementoStock = fopen("Administrador.txt", "r+");
        if (eliminarIncrementoStock == NULL)
        {
            perror("Error al abrir Administrador.txt para agregar productos");
        }
        char usuario[50],contraseña[50];
        fscanf(eliminarIncrementoStock, "%s %s",usuario,contraseña);

        //Add products after of password admin validation
        if (strcmp(validarContraseña, contraseña) == 0)
        {   
            printf("¿Estás seguro de que desea borrar el historial (se eliminara todo)\n?");
            printf("1. Si\n");
            printf("2. No\n:");
            int respuesta;
            scanf("%d", &respuesta);
            if (respuesta == 1)
            {
                remove("AbarrotesEmpleados.txt");
                remove("EnlatadosEmpleados.txt");
                remove("LacteosEmpleados.txt");
                remove("BotanasEmpleados.txt");
                remove("FrutasYVerurasEmpleados.txt");
                remove("BebidasAlcoholicasEmpleados.txt");
                remove("HigienePersonalEmpleados.txt");
                remove("LimpiezaEmpleados.txt");
                printf("Historial eliminado exitosamente\n");
            }
            else
            {
                printf("No se elimino nada\n");
                return;
            }
            fclose(eliminarIncrementoStock);
            
        }
        break;
    case 4:
        printf("\nPara poder eliminar historial, por favor ingrese la contraseña de admin\n");
        scanf("%s", validarContraseña);
        FILE *eliminarDecrementoStock = fopen("Administrador.txt", "r+");
        if (eliminarDecrementoStock == NULL)
        {
            perror("Error al abrir Administrador.txt para agregar productos");
        }
        char usuario2[50],contraseña2[50];
        fscanf(eliminarDecrementoStock, "%s %s",usuario2,contraseña2);

        //Add products after of password admin validation
        if (strcmp(validarContraseña, contraseña2) == 0)
        {   
            printf("¿Estás seguro de que desea borrar el historial (se eliminara todo)\n?");
            printf("1. Si\n");
            printf("2. No\n:");
            int respuesta2;
            scanf("%d", &respuesta2);
            if (respuesta2 == 1)
            {
                remove("AbarrotesEmpleadosN.txt");
                remove("EnlatadosEmpleadosN.txt");
                remove("LacteosEmpleadosN.txt");
                remove("BotanasEmpleadosN.txt");
                remove("FrutasYVerurasEmpleadosN.txt");
                remove("BebidasAlcoholicasEmpleadosN.txt");
                remove("HigienePersonalEmpleadosN.txt");
                remove("LimpiezaEmpleadosN.txt");
                printf("Historial eliminado exitosamente\n");
            }
            else
            {
                printf("No se elimino nada\n");
                return;
            }
            fclose(eliminarDecrementoStock);
            
        }

        break;
    case 5:
        return;

    default:
        break;
    }
}

//Function to show the products and can update the stock
void mostrarProductosStock(struct Producto *productos, int numProductosStock)
{
    printf("\nLista de productos\n");
    for (int i = 0; i < numProductosStock; i++)
    {
        printf("%d. %s || Cantidad (En unidades o kg) %.2f\n", i + 1, productos[i].nombre, productos[i].cantidad);
    }
}


//
void generarInformes()
{
    int menuInformes;
    int menuOpcion1;
    printf("\nPuedes generar los siguientes informes de la ultima semana\n");
    printf("1. Ingresados al principio\n");
    printf("2. Actualizados de stock (unidades agregadas)\n");
    printf("3. Actualizados de stock (unidades quitadas)\n");
    printf("4. Total\n");
    printf("\n5. SALIR \n:");
    scanf("%d", &menuInformes);

    switch (menuInformes)
    {
    case 1:
        printf("Elige para cual departamento quieres tu informe\n");
        printf("1. Abarrotes\n");
        printf("2. Enlatados\n");
        printf("3. Lacteos\n");
        printf("4. Botanas\n");
        printf("5. Frutas y verduras \n");
        printf("6. Bebidas Alcoholicas\n");
        printf("7. Higiene\n");
        printf("8. Limpieza\n");
        printf("\n 9. Salir \n:");
        scanf("%d",&menuOpcion1);
        switch (menuOpcion1)
        {
        case 1:
            generarinformeInicial("Abarrotes.txt");
            break;
        case 2:
            generarinformeInicial("Enlatados.txt");
            break;
        case 3:
            generarinformeInicial("Lacteos.txt");
            break;
        case 4:
            generarinformeInicial("Botanas.txt");
            break;
        case 5:
            generarinformeInicial("FrutasYVeruras.txt");
            break;
        case 6:
            generarinformeInicial("BebidasAlcoholicas.txt");
            break;
        case 7:
            generarinformeInicial("HigienePersonal.txt");
            break;
        case 8:
            generarinformeInicial("Limpieza.txt");
            break;
        case 9:
            return;
        default:
            break;
        }
        break;
    case 5:
        return;
    
    default:
        break;
    }


}

void imprimirGrafica(float cantidad)
{
    printf(" ||");
    for (int i = 0; i < (int)cantidad; i++)
    {
        printf("|");
    }
    printf("\n");
}

void generarinformeInicial (const char *nombrearchivo)
{
    FILE *archivo = fopen(nombrearchivo, "r");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
    }

    printf("Reporte inicial de semana para %s\n",nombrearchivo);

    struct Producto producto;

    while (fscanf(archivo, "{%[^,],%f},", producto.nombre, &producto.cantidad) == 2)
    {
        printf("Producto : %s || Cantidad en unidades o KG: %.2f\n", producto.nombre,producto.cantidad);
        printf("Grafica de barras de %s\n", producto.nombre);
        imprimirGrafica(producto.cantidad);
    }
    
    fclose(archivo);
}


