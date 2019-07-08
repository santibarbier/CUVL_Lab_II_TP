#ifndef ALTA_LIBRO_H_
#define ALTA_LIBRO_H_

#define AUTOR_CHARS 20
#define LIBRO_CHARS 50

#include <stdio.h>

typedef struct ST_AUTOR
{
    char nombre[AUTOR_CHARS];
    char apellido[AUTOR_CHARS];
} ST_AUTOR;

typedef struct ST_LIBRO
{
    char titulo[LIBRO_CHARS];
    ST_AUTOR autor;
    double precio;
    int isbn;
    int stockDisponible;
    int stockReservado;
} ST_LIBRO;

FILE* archLibrosAbrir(const char* modo);

void ST_LIBRO_set( ST_LIBRO *pLibro, const char *titulo, const char *nombreAutor, const char *apellidoAutor, double precio,int isbn, int stockDisponible, int stockReservado);

void imprimirListadoDeLibros();
void imprimirLibro(long pos);

void menuBuscarLibroPorISBN();
void menuBuscarLibroPorTitulo();
void menuBuscarLibroPorNombreDeAutor();
void menuBuscarLibroPorApellidoDeAutor();

void menuEditarLibro();
void menuEliminarLibro();
void menuNuevoLibro();

#endif // ALTA_LIBRO_H_
