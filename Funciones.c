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
    usuarios->gastoBoleta = 0;

    return usuarios;
}

// Función para imprimir el menú.
void impresionMenu(){
    printf("\n\n   *********** MENU **********\n");
    printf("   1. Agregar Parcela\n");
    printf("   2. Ingresar Gastos\n");
    printf("   3. Informacion usuario\n");
    printf("   4. Cuadratura gastos\n");
    printf("   5. Enviar Recordatorio\n");
    printf("   6. Salir\n");
    printf("\n--------------------------------\n\n");
}

// Función para ejecutar las funciones del menú. 
void menu(Red *Usuarios){

    // Declaración de variables.
    int opcion;
    char num[100];
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
            // Función almacenar gastos
            break;
        case 3: 
            printf("Ingrese el numero de la parcela a buscar:\n> ");
            scanf("%s", num);
            mostrarUsuario(Usuarios->totalUsuarios, num);
            break;
        case 4:
            calcularGasto(Usuarios);
            break;
        case 5:
            break;
        case 6: 
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
        char nombreU[100], numeroP[100], corr[100];
        int tel, numl;

        printf("\n\n |         R E G I S T R O   U S U A R I O  N %d         |", i);
        printf("\n\n- Ingrese el numero de la parcela:\n> ");
        getchar();
        scanf("%[^\n]s", numeroP);

        printf("\n- Ingrese el nombre y apellido del dueno de la parcela\n> ");
        getchar();
        scanf("%[^\n]s", nombreU);

        // Validación para no guardar dos veces el mismo dueño
        while(validarInfo(Usuarios->totalUsuarios, numeroP) == true){
            printf("\n(!!) Ese nombre ya esta registrado, ingrese otro:\n> ");
            getchar();
            scanf("%[^\n]s", nombreU);
        }

        printf("\n\n- Ingrese el numero celular del dueno/a de la parcela:\n> ");
        scanf("%d", &tel);

        printf("\n\n- Ingrese el correo electronico del dueno/a de la parcela:\n> ");
        getchar();
        scanf("%[^\n]s", corr);

        printf("\n\n- Ingrese el numero de boleta:\n> ");
        scanf("%d", &numl);

        // Asignamos las variables auxiliares al usuario.
        strcpy(new->numParcela, numeroP);
        strcpy(new->Nombre,nombreU);
        strcpy(new->correo,corr);
        new->telefono = tel;
        new->numeroLectura = numl;   
        
        // Guardamos el nuevo usuario en el mapa con toda la información.
        insertMap(Usuarios->totalUsuarios,new->numParcela,new);
        Usuarios->cantParcelas++;
        printf("\n\n ** SU INFORMACION HA SIDO GUARDADA EXISTOSAMENTE!\n");
        i++;
    }
}

// Función que inicializa y almacena memoria para crear un usuario.
Usuario *crearUsuario(){
    Usuario *aux = (Usuario *) malloc(sizeof(Usuario));
    aux->gastoActual = 0;
    aux->gastoAnterior = 0;
    aux->gastoTotal = 0;
    aux->numeroLectura = 0;
    aux->telefono = 0;
    aux->pago = 0;
    
    return aux;
}

// Función que valida que el usuario no este registrado, para no guardarlo 2 veces.
// Si retorna false no está registrado, en caso contrario retorna true.

bool validarInfo(Map *totalUsuarios, char *numeroP){
    Usuario *buscado = searchMap(totalUsuarios, numeroP);
    if (buscado == NULL) return false;
    else return true;
}

// Función que muestra toda la información respecto a la parcela y su dueño/a
void mostrarUsuario(Map *totalUsuarios, char *numParcela){

    // Buscamos en nuestro mapa la información del usuario buscado.
    Usuario *usu = searchMap(totalUsuarios, numParcela);
    
    // Si lo encuentra, imprime su información correspondiente.
    if (usu != NULL){
        printf("----------------------------------------------------\n\n");
        printf("INFORMACION PARCELA: \n\n");
        printf("Numero Parcela > %s\nNumero Boleta > %d\nGasto Mes Actual > %d\n Gasto Total > %d\n\n", usu->numParcela, usu->numeroLectura, usu->gastoActual, usu->gastoTotal);
        printf("INFORMACION DUENO/A:\n\n");
        printf("Nombre > %s\nCorreo > %s\nTelefono > %d", usu->Nombre, usu->correo, usu->telefono);
    }

    // Si no, imprime un mensaje de error
    else printf("ERROR (!!) No existe informacion o no esta registrada la parcela buscada\n");

}

 void calcularGasto(Red *Usuarios){
    // Declaración de variables.
    char numPar[100];

    printf("Ingrese el numero de parcela que quiere calcular:\n> ");
    scanf("%s", numPar);

    // Buscamos en nuestro mapa la información del usuario buscado.
    Usuario *usu = searchMap(Usuarios->totalUsuarios, numPar);
    
    usu->gastoActual = usu->gastoTotal - usu->gastoAnterior;
    printf("Su gasto de este mes han sido: %d kWh\n", usu->gastoActual);

    // 140 pesos por kWh
    usu->pago = usu->gastoActual * 140;

    printf("Su total a pagar durante este mes es un total de $ %d\n\n", usu->pago);

    mostrarBoleta(Usuarios);
 }

// Función que imprime el resumen, visualmente como una boleta, cuadrando los gastos realizados por c/parcela.
 void mostrarBoleta(Red *Usuarios){
    printf(" PARCELAS       |        KW GASTADOS       |        $ GASTADO     |     BOLETA \n");

    Usuario *aux = firstMap(Usuarios->totalUsuarios);
    int copia = 0;

    if (aux == NULL){
        printf("No hay registros de nada, saliendo ...\n");
        return;
    }

    while(aux != NULL){
        printf("     %s                        %d                          %d          \n", aux->numParcela, aux->gastoActual, aux->pago);
        copia += aux->pago;
        aux = nextMap(Usuarios->totalUsuarios);
    }
    printf("                                          TOTAL GASTO = $%d | $%d\n", copia, Usuarios->gastoBoleta);

    if(copia == Usuarios->gastoBoleta) printf("La cuadratura ha tenido exito :)");
    else printf("Hay una discrepancia en el pago de las parcelas (!!)");
 }