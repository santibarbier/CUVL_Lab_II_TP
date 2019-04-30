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

    printf("\nBUSCAR: ");
    char buscar[50];
    fflush(stdin);
    gets(buscar);

    bool encontrado = false;
    char *busqueda = NULL;
    long pos;

    fread(Libro, sizeof(ST_LIBRO), 1, pArchivo);
    while (!feof(pArchivo))
    {
        busqueda = strstr( Libro->titulo, buscar );
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

    printf("\nBUSCAR: ");
    char buscar[50];
    fflush(stdin);
    gets(buscar);

    bool encontrado = false;
    char *busqueda = NULL;
    long pos;

    fread(Libro, sizeof(ST_LIBRO), 1, pArchivo);
    while (!feof(pArchivo))
    {
        busqueda = strstr( Libro->autor.nombre, buscar );
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
