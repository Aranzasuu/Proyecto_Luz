#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Funciones.h"

int main(){

    Red *Usuarios = crearRed();

    menu(Usuarios);
    
    return 0;
}