#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/libro.h"

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
    if((pArchivo = fopen("libros.dat", modo)) == NULL)
    {
        printf("\n\nCerrando programa. Hubo problemas al tratar abrir \"libros.dar\"\n\n");
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
    printf("\nSTOCK RESERVADO: ");
    scanf("%i", &pLibro->stockReservado);

    fwrite(pLibro, sizeof(ST_LIBRO), 1,pArchivo);
    fclose(pArchivo);
}

void listarLibros()
{
    FILE *pArchivo = abrirArchivoLibros("rb");
    ST_LIBRO * pLibro = (ST_LIBRO*) malloc(sizeof(ST_LIBRO));
    fread(pLibro, sizeof(ST_LIBRO), 1, pArchivo);

    printf("\nLISTAR LIBROS\n");
    long pos;
    while(!feof(pArchivo))
    {
        pos = ftell(pArchivo) - sizeof(ST_LIBRO);
        imprimirLibro(pos);
        fread(pLibro, sizeof(ST_LIBRO), 1, pArchivo);
    }
    fclose(pArchivo);
}

void imprimirLibro(long pos)
{
    FILE *pArchivo = abrirArchivoLibros("rb");
    ST_LIBRO * pLibro = (ST_LIBRO*) malloc(sizeof(ST_LIBRO));

    fseek(pArchivo, pos, SEEK_SET);
    fread(pLibro, sizeof(ST_LIBRO), 1, pArchivo);

    printf("\nTITULO: %s", pLibro->titulo);
    printf("\nNOMBRE AUTOR: %s", pLibro->autor.nombre);
    printf("\nAPELLIDO AUTOR: %s", pLibro->autor.apellido);
    printf("\nPRECIO: %.2lf", pLibro->precio);
    printf("\nISBN: %i", pLibro->isbn);
    printf("\nSTOCK DISPONIBLE: %i", pLibro->stockDisponible);
    printf("\nSTOCK RESERVADO: %i", pLibro->stockReservado);
    puts("");

    fclose(pArchivo);
}

