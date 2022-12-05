#ifndef Funciones_h
#define Funciones_h 
#include <stdbool.h>
#include "Map.h"
#include "List.h"

typedef struct Usuario
{
    char Nombre[100];
    char numParcela[100];
    int numeroLectura;
    char correo[100];
    int telefono;
    int gastoAnterior;
    int gastoTotal;
    int gastoActual;
    int pago;
}Usuario;


typedef struct Red
{
    Map *totalUsuarios;
    int cantParcelas;
    List *gastoCondominio;
    int gastoBoleta;
} Red;


Red *crearRed();
int is_equal_string(void * key1, void * key2);

void menu(Red *Usuarios);
void impresionMenu();

void guardarUsuarios(Red *Usuarios);
Usuario *crearUsuario();
bool validarInfo(Map *totalUsuarios, char *numeroP);
void mostrarUsuario(Map *totalUsuarios, char *numeroP);

void calcularGasto(Red *Usuarios);
void mostrarBoleta(Red *Usuarios);

#endif