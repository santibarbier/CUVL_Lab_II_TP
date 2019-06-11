#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "libro.h"
#include "ayuda.h"

#define ARCHIVO "_libros.dat"
#define ARCHIVOAUX "_libros_aux.dat"

void librosImprimirCabezeraTabla(const char* tituloTabla)
{
//    printf("\t\t\t\t\t%s\n\n", tituloTabla);
    printf("\t\t\t\t\t%s\n", tituloTabla);
    printf("%20s\t", "TITULO");
    printf("%15s\t", "AUTOR");
    printf("%15s\t", "APELLIDO");
    printf("%12s\t", "PRECIO");
    printf("%9s\t", "ISBN");
    printf("%s\t", "STOCK");
    printf("%s\t", "RESERVADO");
//    printf("\n\n");
    printf("\n=========================================================================================================\n");
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
//    limpiarPantalla();
    FILE *pArchivo = abrirArchivoLibros("rb");
    ST_LIBRO * pLibro = (ST_LIBRO*) malloc(sizeof(ST_LIBRO));
    fread(pLibro, sizeof(ST_LIBRO), 1, pArchivo);

//    librosImprimirCabezeraTabla("LISTADO DE LIBROS");
    librosImprimirCabezeraTabla("");

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

long conseguirPosicionDeLibroEnArchivoPorISBN(int isbn)
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
//    limpiarPantalla();
    int isbn = 0;
    printf("Buscar libro por ISBN.\n");
    printf("- ISBN: ");
    scanf("%i", &isbn);
    long pos = conseguirPosicionDeLibroEnArchivoPorISBN(isbn);
    if (pos >= 0)
    {
        ST_LIBRO libro = conseguirLibroEnArchivo(pos);
        if (libro.isbn != isbn)
        {
            printf("No se encontre el libro con ISBN: %i\n", isbn);
            presioneUnaTeclaParaContinuar();
        }
        else
        {
            imprimirLibroEnVariasLineas(pos);
            presioneUnaTeclaParaContinuar("");
        }
    }
    else
    {
        printf("No se encontre el libro con ISBN: %i\n", isbn);
        presioneUnaTeclaParaContinuar();
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
        if (cur != pos)
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
        printf("Libro eliminado\n");
        presioneUnaTeclaParaContinuar();
    }
    else
    {
        printf("No se pudo eliminar\n");
        presioneUnaTeclaParaContinuar();
    }
    fclose(pArchivo);
    fclose(pArchivoAux);
    if (remove(ARCHIVO) != 0)
    {
        limpiarPantalla();
        printf("Hubo un error al tratar de eliminar el archivo: %s\n", ARCHIVO);
        presioneUnaTeclaParaContinuar();
    }
    rename(ARCHIVOAUX, ARCHIVO);
}

void eliminarLibro()
{
    limpiarPantalla();
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
    long pos = conseguirPosicionDeLibroEnArchivoPorISBN(isbn);
    if (pos >= 0)
    {
        ST_LIBRO libro = conseguirLibroEnArchivo(pos);
        if (libro.isbn != isbn)
        {
            printf("No se pudo eliminar el libro. No hay libro con el ISBN: %i\n", isbn);
            presioneUnaTeclaParaContinuar();
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
        presioneUnaTeclaParaContinuar();
    }
}

void _editarLibroEnPantalla(long pos)
{
    ST_LIBRO libro = conseguirLibroEnArchivo(pos);

    imprimirLibroEnVariasLineas(pos);

    // EDITAR LIBRO
    ST_LIBRO libroAux;
    printf("\nEDITANDO LIBRO\n");
    printf("\t- Apriete enter para no editar strings\n");
    printf("\t- Ingrese -1 para no editar numeros\n");
    printf("\n\n");
    fflush(stdin);

    printf("TITULO: ");
    gets(libroAux.titulo);
    if (libroAux.titulo[0] != '\0') // Si string no esta vacio
    {
        strcpy(libro.titulo, libroAux.titulo);
    }

    printf("NOMBRE AUTOR: ");
    gets(libroAux.autor.nombre);
    if (libroAux.autor.nombre[0] != '\0') // Si string no esta vacio
    {
        strcpy(libro.autor.nombre, libroAux.autor.nombre);
    }

    printf("APELLIDO AUTOR: ");
    gets(libroAux.autor.apellido);
    if (libroAux.autor.apellido[0] != '\0') // Si string no esta vacio
    {
        strcpy(libro.autor.apellido, libroAux.autor.apellido);
    }

    printf("PRECIO: ");
    scanf("%lf", &libroAux.precio);
    if (libroAux.precio >= 0)
    {
        libro.precio = libroAux.precio;
    }

    printf("ISBN: ");
    scanf("%i", &libroAux.isbn);
    if (libroAux.isbn >= 0)
    {
        libro.isbn = libroAux.isbn;
    }

    printf("STOCK DISPONIBLE: ");
    scanf("%i", &libroAux.stockDisponible);
    if (libroAux.stockDisponible >= 0)
    {
        libro.stockDisponible = libroAux.stockDisponible;
    }

    FILE* pArchivo = abrirArchivoLibros("rb+");
    fseek(pArchivo, pos, SEEK_SET);
    fwrite(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    fclose(pArchivo);

    presioneUnaTeclaParaContinuar("");
}

void editarLibro()
{
    limpiarPantalla();
    int isbn = 0;
    printf("EDICION DE LIBRO.\n");
    printf("Buscar libro por ISBN.\n");
    printf("- ISBN: ");
    scanf("%i", &isbn);
    long pos = conseguirPosicionDeLibroEnArchivoPorISBN(isbn);
    if (pos >= 0)
    {
        ST_LIBRO libro = conseguirLibroEnArchivo(pos);
        if (libro.isbn != isbn)
        {
            printf("No se encontre el libro con ISBN: %i\n", isbn);
            presioneUnaTeclaParaContinuar();
        }
        else
        {
            _editarLibroEnPantalla(pos);
        }
    }
    else
    {
        printf("No se encontre el libro con ISBN: %i\n", isbn);
        presioneUnaTeclaParaContinuar();
    }
}