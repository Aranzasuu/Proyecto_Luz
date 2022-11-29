#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "Funciones.h"

// *** FUNCIONES DEL MAIN ***

// Función para la estructura Map.
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

// Función para crear la variable donde guardaremos toda la información y 
// almacenaremos memoria para esta.
Red *crearRed(){

    Red *usuarios = (Red *) malloc(sizeof(Red));

    if (usuarios == NULL){
        printf("No se pudo crear el usuario");
        return NULL;
    }
    
    usuarios->totalUsuarios = createMap(is_equal_string);
    usuarios->cantParcelas = 0;

    return usuarios;
}

// Función para imprimir el menú.
void impresionMenu(){
    printf("\n\n   *********** MENU **********\n");
    printf("   1. Agregar Parcela\n");
    printf("   2. Buscar Personas\n");
    printf("   3. Informacion usuario\n");
    printf("   4. Cuadratura gastos\n");
    printf("   5. Salir\n");
    printf("\n--------------------------------\n\n");
}

// Función para ejecutar las funciones del menú. 
void menu(Red *Usuarios){

    // Declaración de variables.
    int opcion;
    bool def;

    impresionMenu();
    printf("Ingrese la opcion que quiere realizar: ");
    scanf("%d", &opcion);
    printf("\n");

    // Funciones para ingresar a las opciones del menú.
    while(opcion >= 0){
        def = false;
        switch(opcion){
        case 1:
            guardarUsuarios(Usuarios);
            break;
        case 2: 
            break;
        case 3: 
            break;
        case 4:
            break;
        case 5: 
            printf("\n\n****** Se ha cerrado correctamente la sesion, nos vemos! ******\n\n\n");
            return;
        default:
            printf("\n\n(!!) Ingrese una opcion valida (!!)\n");
            def = true;
        }

        impresionMenu();
        if (def == false) printf("\nDesea realizar otra operacion?\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);
    }
}

// *** PRIMERA OPCIÓN DEL MENÚ ***

// Función para ingresar un nuevo(s) usuario(s) y guardarlo en el mapa general

void guardarUsuarios(Red *Usuarios){

    // Declaración variables ciclo
    int total, i = 1;

    printf("Ingrese la cantidad de usuarios a ingresar:\n> ");
    scanf("%d", &total);

    while(i <= total){
        // Función que crea el usuario para guardar la información.
        Usuario *new = crearUsuario();

        // Declaración de variables auxiliares a utilizar.
        char nombreU[100];
        int numeroP, volts, tel;

        printf("\n\n |         R E G I S T R O   U S U A R I O  N %d         |", i);
        printf("\n\n- Ingrese el numero de la parcela:\n> ");
        scanf("%d", &numeroP);

        printf("\n- Ingrese el nombre y apellido del dueno de la parcela\n> ");
        getchar();
        scanf("%[^\n]s", nombreU);

        // Validación para no guardar dos veces el mismo dueño
        while(validarInfo(Usuarios->totalUsuarios,numeroP) == true){
            printf("\n(!!) Ese nombre ya esta registrado, ingrese otro:\n> ");
            getchar();
            scanf("%[^\n]s", nombreU);
        }

        printf("\n\n- Ingrese el numero celular del dueno/a de la parcela:\n> ");
        scanf("%d", &tel);

        printf("\n\n- Ingrese la cantidad de volts gastados por la parcela n° %d.\n> ", numeroP);
        scanf("%d", &volts);

        // Validación gasto sea mayor o igual a 0
        while(volts < 0){
            printf("Ingrese un valor valido !!\n> ");
            scanf("%d", &volts);
        }

        // Asignamos las variables auxiliares al usuario.
        new->numParcela = numeroP;
        strcpy(new->Nombre,nombreU);
        new->telefono = tel;
        new->gastoActual = volts;

        // Revisamos si la información se guardó correctamente
        printf("\nNumero parcela > %d\n", new->numParcela);
        printf("Nombre usuario > %s\n", new->Nombre);
        printf("Numero telefono > %d\n", new->telefono);
        printf("Gasto en volts > %d\n", new->gastoActual);

        // Guardamos el nuevo usuario en el mapa con toda la información.
        insertMap(Usuarios->totalUsuarios,&(new->numParcela),new);
        Usuarios->cantParcelas++;
        printf("\n\n ** SU INFORMACION HA SIDO GUARDADA EXISTOSAMENTE!\n");
        i++;
        mostrarUsuario(Usuarios->totalUsuarios,new->numParcela);
    }
}

// Función que inicializa y almacena memoria para crear un usuario.
Usuario *crearUsuario(){
    Usuario *aux = (Usuario *) malloc(sizeof(Usuario));
    aux->gastoActual = 0;
    aux->gastoMesA = 0;
    aux->numeroLectura = 0;
    aux->telefono = 0;
    aux->numParcela = 0;
    
    return aux;
}

// Función que valida que el usuario no este registrado, para no guardarlo 2 veces.
// Si retorna false no está registrado, en caso contrario retorna true.

bool validarInfo(Map *totalUsuarios, int numeroP){
    Usuario *buscado = searchMap(totalUsuarios,numeroP);
    if (buscado == NULL) return false;
    else return true;
}

// Función que muestra toda la información respecto a la parcela y su dueño/a
void mostrarUsuario(Map *totalUsuarios, int numParcela){
    

}




