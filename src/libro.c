#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/libro.h"
#include "../include/menu.h"

#define ARCHIVO "libros.dat"
#define ARCHIVOAUX "libros_aux.dat"

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

    printf("\t\t\t\t\t\tLISTADO DE LIBROS\n\n");
    printf("%23s\t", "TITULO");
    printf("%15s\t", "AUTOR");
    printf("%15s\t", "APELLIDO");
    printf("%12s\t", "PRECIO");
    printf("%9s\t", "ISBN");
    printf("%s\t", "STOCK");
    printf("%s\t", "RESERVADO");
    printf("\n\n");

    long pos;
    int i = 0;
    while(!feof(pArchivo))
    {
        printf("%2i.", i + 1);
        i++;
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

void eliminarLibro(long pos)
{
    FILE *pArchivo = abrirArchivoLibros("wb+");
    FILE *pArchivoAux = fopen(ARCHIVOAUX, "wb");
    fseek(pArchivo, 0, SEEK_END);
    bool eliminado = false;
    long posicion = ftell(pArchivo) - sizeof(ST_LIBRO);
    rewind(pArchivo);
    ST_LIBRO libro;
    fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    while (!feof(pArchivo))
    {
        if (ftell(pArchivo) != posicion)
        {
            fwrite(&libro, sizeof(ST_LIBRO), 1, pArchivoAux);
        }
        else
        {
            eliminado = true;
        }
        fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    }
    if (eliminado)
    {
        printf("No se pudo eliminar\n");
        pressAnyKeyToContinue();
    }
    else
    {
        printf("Libro eliminado\n");
        pressAnyKeyToContinue();
    }
    fclose(pArchivo);
    fclose(pArchivoAux);
    rename(ARCHIVO, ARCHIVOAUX);
    rename(ARCHIVOAUX, ARCHIVO);
    if (remove(ARCHIVOAUX) != 0)
    {
        clearScreen();
        printf("Hubo un error al tratar de eliminar el archivo: %s\n", ARCHIVOAUX);
        pressAnyKeyToContinue();
    }
}
