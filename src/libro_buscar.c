#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/libro_buscar.h"

void mensajeDeBusquedasinResultados()
{
    printf("\nNo se encontro ningun libro.\n");
}

void buscarLibroPorTitulo()
{
    FILE *pArchivo = abrirArchivoLibros("rb");
    ST_LIBRO * Libro = (ST_LIBRO*) malloc(sizeof(ST_LIBRO));

    clearScreen();

    printf("\nBUSCAR TITULO: ");
    char buscar[50];
    fflush(stdin);
    gets(buscar);

    librosImprimirCabezeraTabla("RESULTADO DE BUSQUEDA");

    bool encontrado = false;
    char *busqueda = NULL;
    long pos;

    fread(Libro, sizeof(ST_LIBRO), 1, pArchivo);
    while (!feof(pArchivo))
    {
        busqueda = strstr(strlwr(Libro->titulo), strlwr(buscar));
        if (busqueda != NULL)// if (strcmp(Libro->titulo, buscar) == 0)
        {
            encontrado = true;
            pos = ftell(pArchivo) - sizeof(ST_LIBRO);
            imprimirLibro(pos);
        }
        fread(Libro, sizeof(ST_LIBRO), 1, pArchivo);
    }

    if (encontrado == false)
    {
        mensajeDeBusquedasinResultados();
    }

    fclose(pArchivo);
}

void buscarLibroPorNombreDeAutor()
{
    FILE *pArchivo = abrirArchivoLibros("rb");
    ST_LIBRO * Libro = (ST_LIBRO*) malloc(sizeof(ST_LIBRO));

    clearScreen();

    printf("\nBUSCAR NOMBRE DE AUTOR: ");
    char buscar[50];
    fflush(stdin);
    gets(buscar);

    librosImprimirCabezeraTabla("RESULTADO DE BUSQUEDA");

    bool encontrado = false;
    char *busqueda = NULL;
    long pos;

    fread(Libro, sizeof(ST_LIBRO), 1, pArchivo);
    while (!feof(pArchivo))
    {
        busqueda = strstr(strlwr(Libro->autor.nombre), strlwr(buscar));
        if (busqueda != NULL)// if (strcmp(Libro->autor.nombre, buscar) == 0)
        {
            encontrado = true;
            pos = ftell(pArchivo) - sizeof(ST_LIBRO);
            imprimirLibro(pos);
        }
        fread(Libro, sizeof(ST_LIBRO), 1, pArchivo);
    }

    if (encontrado == false)
    {
        mensajeDeBusquedasinResultados();
    }

    fclose(pArchivo);
}

void buscarLibroPorApellidoDeAutor()
{
    FILE *pArchivo = abrirArchivoLibros("rb");
    ST_LIBRO * Libro = (ST_LIBRO*) malloc(sizeof(ST_LIBRO));

    clearScreen();

    printf("\nBUSCAR APPELIDO DE AUTOR: ");
    char buscar[50];
    fflush(stdin);
    gets(buscar);

    librosImprimirCabezeraTabla("RESULTADO DE BUSQUEDA");

    bool encontrado = false;
    char *busqueda = NULL;
    long pos;

    fread(Libro, sizeof(ST_LIBRO), 1, pArchivo);
    while (!feof(pArchivo))
    {
        busqueda = strstr(strlwr(Libro->autor.apellido), strlwr(buscar));
        if (busqueda != NULL)
        {
            encontrado = true;
            pos = ftell(pArchivo) - sizeof(ST_LIBRO);
            imprimirLibro(pos);
        }
        fread(Libro, sizeof(ST_LIBRO), 1, pArchivo);
    }

    if (encontrado == false)
    {
        mensajeDeBusquedasinResultados();
    }

    fclose(pArchivo);
}
