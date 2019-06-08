#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/libro.h"
#include "../include/menu.h"

#define ARCHIVO "libros.dat"
#define ARCHIVOAUX "libros_aux.dat"

void librosImprimirCabezeraTabla(const char* tituloTabla)
{
    printf("\t\t\t\t\t%s\n\n", tituloTabla);
    printf("%20s\t", "TITULO");
    printf("%15s\t", "AUTOR");
    printf("%15s\t", "APELLIDO");
    printf("%12s\t", "PRECIO");
    printf("%9s\t", "ISBN");
    printf("%s\t", "STOCK");
    printf("%s\t", "RESERVADO");
    printf("\n\n");
}

void iniciarLibro( ST_LIBRO *Libro, const char *titulo, const char *nombreAutor, const char *apellidoAutor, double precio,int isbn, int stockDisponible, int stockReservado)
{
    strcpy(Libro->titulo, titulo);
    strcpy(Libro->autor.nombre, nombreAutor);
    strcpy(Libro->autor.apellido, apellidoAutor);
    Libro->precio = precio;
    Libro->isbn = isbn;
    Libro->stockDisponible = stockDisponible;
    Libro->stockReservado = stockReservado;
}

FILE* abrirArchivoLibros(const char* modo)
{
    FILE *pArchivo = NULL;
    if((pArchivo = fopen(ARCHIVO, modo)) == NULL)
    {
        printf("\n\nCerrando programa. Hubo problemas al tratar abrir \"libros.dat\"\n\n");
        exit(EXIT_FAILURE);
    }
    return pArchivo;
}

void nuevoLibro()
{
    FILE *pArchivo = abrirArchivoLibros("ab+");
    ST_LIBRO * pLibro = (ST_LIBRO*) malloc(sizeof(ST_LIBRO));

    printf("\nALTA NUEVO LIBRO\n");

    fflush(stdin);

    printf("\nTITULO: ");
    gets(pLibro->titulo);
    printf("\nNOMBRE AUTOR: ");
    gets(pLibro->autor.nombre);
    printf("\nAPELLIDO AUTOR: ");
    gets(pLibro->autor.apellido);
    printf("\nPRECIO: ");
    scanf("%lf", &pLibro->precio);
    printf("\nISBN: ");
    scanf("%i", &pLibro->isbn);
    printf("\nSTOCK DISPONIBLE: ");
    scanf("%i", &pLibro->stockDisponible);
    // printf("\nSTOCK RESERVADO: ");
    // scanf("%i", &pLibro->stockReservado);
    pLibro->stockReservado = 0;

    fwrite(pLibro, sizeof(ST_LIBRO), 1,pArchivo);
    fclose(pArchivo);
}

void listarLibros()
{
    clearScreen();
    FILE *pArchivo = abrirArchivoLibros("rb");
    ST_LIBRO * pLibro = (ST_LIBRO*) malloc(sizeof(ST_LIBRO));
    fread(pLibro, sizeof(ST_LIBRO), 1, pArchivo);

    librosImprimirCabezeraTabla("LISTADO DE LIBROS");

    long pos;
    while(!feof(pArchivo))
    {
        pos = ftell(pArchivo) - sizeof(ST_LIBRO);
        imprimirLibro(pos);
        fread(pLibro, sizeof(ST_LIBRO), 1, pArchivo);
    }

    fclose(pArchivo);

    printf("\n");
}

void imprimirLibro(long pos)
{
    FILE *pArchivo = abrirArchivoLibros("rb");
    ST_LIBRO * pLibro = (ST_LIBRO*) malloc(sizeof(ST_LIBRO));

    fseek(pArchivo, pos, SEEK_SET);
    fread(pLibro, sizeof(ST_LIBRO), 1, pArchivo);

//    printf("\nTITULO: %s", pLibro->titulo);
//    printf("\nNOMBRE AUTOR: %s", pLibro->autor.nombre);
//    printf("\nAPELLIDO AUTOR: %s", pLibro->autor.apellido);
//    printf("\nPRECIO: %.2lf", pLibro->precio);
//    printf("\nISBN: %i", pLibro->isbn);
//    printf("\nSTOCK DISPONIBLE: %i", pLibro->stockDisponible);
//    printf("\nSTOCK RESERVADO: %i", pLibro->stockReservado);
//    printf("\n");

    printf("%20s\t", pLibro->titulo);
    printf("%15s\t", pLibro->autor.nombre);
    printf("%15s\t", pLibro->autor.apellido);
    printf("%12.2lf\t", pLibro->precio);
    printf("%9i\t", pLibro->isbn);
    printf("%5i\t", pLibro->stockDisponible);
    printf("%9i\t", pLibro->stockReservado);
    printf("\n");

    fclose(pArchivo);
}

void imprimirLibroEnVariasLineas(long pos)
{
    FILE *pArchivo = abrirArchivoLibros("rb");
    ST_LIBRO * pLibro = (ST_LIBRO*) malloc(sizeof(ST_LIBRO));

    fseek(pArchivo, pos, SEEK_SET);
    fread(pLibro, sizeof(ST_LIBRO), 1, pArchivo);

    printf("\n          TITULO: %s", pLibro->titulo);
    printf("\n    NOMBRE AUTOR: %s", pLibro->autor.nombre);
    printf("\n  APELLIDO AUTOR: %s", pLibro->autor.apellido);
    printf("\n          PRECIO: %.2lf", pLibro->precio);
    printf("\n            ISBN: %i", pLibro->isbn);
    printf("\nSTOCK DISPONIBLE: %i", pLibro->stockDisponible);
    printf("\n STOCK RESERVADO: %i", pLibro->stockReservado);
    printf("\n");

    fclose(pArchivo);
}

long conseguirPosicionDeLibroEnArchivo(int isbn)
{
    FILE* pArchivo = abrirArchivoLibros("rb");
    long pos = 0;
    ST_LIBRO libro;
    fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    while(!feof(pArchivo) && libro.isbn != isbn)
    {
        fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
        pos = ftell(pArchivo) - sizeof(ST_LIBRO);
    }
    fclose(pArchivo);
    if (libro.isbn != isbn)
    {
        return -1;
    }
    return pos;
}

ST_LIBRO conseguirLibroEnArchivo(long pos)
{
    FILE* pArchivo = abrirArchivoLibros("rb");
    fseek(pArchivo, pos, SEEK_SET);
    ST_LIBRO libro;
    fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    fclose(pArchivo);
    return libro;
}

void buscarLibroPorISBN()
{
    clearScreen();
    int isbn = 0;
    printf("Buscar libro por ISBN.\n");
    printf("- ISBN: ");
    scanf("%i", &isbn);
    long pos = conseguirPosicionDeLibroEnArchivo(isbn);
    if (pos >= 0)
    {
        ST_LIBRO libro = conseguirLibroEnArchivo(pos);
        if (libro.isbn != isbn)
        {
            printf("No se encontre el libro con ISBN: %i\n", isbn);
            pressAnyKeyToContinue();
        }
        else
        {
            imprimirLibroEnVariasLineas(pos);
            pressAnyKeyToContinue("");
        }
    }
    else
    {
        printf("No se encontre el libro con ISBN: %i\n", isbn);
        pressAnyKeyToContinue();
    }
}

void eliminarLibroEnArchivo(long pos)
{
    FILE *pArchivo = abrirArchivoLibros("rb");
    FILE *pArchivoAux = fopen(ARCHIVOAUX, "wb");
    fseek(pArchivo, 0, SEEK_END);
    bool eliminado = false;
    // long posicion = ftell(pArchivo) - sizeof(ST_LIBRO);
    rewind(pArchivo);
    ST_LIBRO libro;
    fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    while (!feof(pArchivo))
    {
        long cur = ftell(pArchivo) - sizeof(ST_LIBRO);
        if (cur == pos)
        {
            eliminado = true;
        }
        else
        {
            fwrite(&libro, sizeof(ST_LIBRO), 1, pArchivoAux);
        }
        fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    }
    if (eliminado)
    {
        printf("Libro eliminado\n");
        pressAnyKeyToContinue();
    }
    else
    {
        printf("No se pudo eliminar\n");
        pressAnyKeyToContinue();
    }
    fclose(pArchivo);
    fclose(pArchivoAux);
    if (remove(ARCHIVO) != 0)
    {
        clearScreen();
        printf("Hubo un error al tratar de eliminar el archivo: %s\n", ARCHIVO);
        pressAnyKeyToContinue();
    }
    rename(ARCHIVOAUX, ARCHIVO);
}

void eliminarLibro()
{
    clearScreen();
    int isbn = 0;
    printf("Ingrese ISBN del libro que de sea eliminar.\n");
    printf("- ISBN: ");
    scanf("%i", &isbn);
//    FILE* pArchivo = abrirArchivoLibros("rb");
//    long pos = 0;
//    ST_LIBRO libro;
//    fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
//    while(!feof(pArchivo) && libro.isbn != isbn)
//    {
//        fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
//        pos = ftell(pArchivo) - sizeof(ST_LIBRO);
//    }
//    if (libro.isbn != isbn)
    long pos = conseguirPosicionDeLibroEnArchivo(isbn);
    if (pos >= 0)
    {
        ST_LIBRO libro = conseguirLibroEnArchivo(pos);
        if (libro.isbn != isbn)
        {
            printf("No se pudo eliminar el libro. No hay libro con el ISBN: %i\n", isbn);
            pressAnyKeyToContinue();
        }
        else
        {
//            fclose(pArchivo);
            eliminarLibroEnArchivo(pos);
        }
    }
    else
    {
        printf("No se pudo eliminar el libro. No hay libro con el ISBN: %i\n", isbn);
        pressAnyKeyToContinue();
    }
}
