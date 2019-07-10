#ifndef ALTA_LIBRO_H_
#define ALTA_LIBRO_H_

#define CARPETA "data"
#define ARCHIVO "data/libros.dat"
#define ARCHIVOAUX "data/libros_aux.dat"

#define AUTOR_CHARS 20
#define LIBRO_CHARS 50

#include <stdio.h>
#include <stdbool.h>

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

//void ST_LIBRO_set(ST_LIBRO *pLibro, const char *titulo, const char *nombreAutor, const char *apellidoAutor,
//               double precio,int isbn, int stockDisponible, int stockReservado)
//{
//    strcpy(pLibro->titulo, titulo);
//    strcpy(pLibro->autor.nombre, nombreAutor);
//    strcpy(pLibro->autor.apellido, apellidoAutor);
//    pLibro->precio = precio;
//    pLibro->isbn = isbn;
//    pLibro->stockDisponible = stockDisponible;
//    pLibro->stockReservado = stockReservado;
//}

FILE* archLibrosAbrir(const char* modo);
ST_LIBRO archLibrosConseguirLibroPorPos(long pos);
long archLibrosConseguirPosPorISBN(int isbn);
void archLibrosEliminarPorPos(long pos);
void archLibrosImprimirTodos();
bool archLibrosDisminuirStock(int isbn);
bool archLibrosReservarUno(int isbn);

void menuLibroBuscarPorISBN();
void menuLibroBuscarPorTitulo();
void menuLibroBuscarPorNombreDeAutor();
void menuLibroBuscarPorApellidoDeAutor();

void menuLibroEditar();
void menuLibroEliminar();
void menuLibroNuevo();

#endif // ALTA_LIBRO_H_
