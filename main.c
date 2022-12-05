#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Funciones.h"

int main(){

    // Declaración de variables
    Red *Usuarios = crearRed();

    printf("          BIENVENIDX !!\n\n");
    
    // Ingreso a la función que contiene todas las funcionalidades del programa
    menu(Usuarios);
    
    return 0;
}