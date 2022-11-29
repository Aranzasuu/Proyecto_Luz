#ifndef Funciones_h
#define Funciones_h 
#include <stdbool.h>
#include "Map.h"

typedef struct Usuario
{
    char Nombre[100];
    int numParcela;
    int numeroLectura;
    char correo[100];
    int telefono;
    int gastoMesA;
    int gastoActual;
}Usuario;


typedef struct Red
{
    Map *totalUsuarios;
    int cantParcelas;
}Red;



Red *crearRed();
int is_equal_string(void * key1, void * key2);

void menu(Red *Usuarios);
void impresionMenu();

void guardarUsuarios(Red *Usuarios);
Usuario *crearUsuario();
bool validarInfo(Map *totalUsuarios, int numeroP);
void mostrarUsuario(Map *totalUsuarios, int numeroP);

#endif