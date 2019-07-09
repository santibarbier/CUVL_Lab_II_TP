#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "libro.h"
#include "ayuda.h"

#define ARCHIVO "_libros.dat"
#define ARCHIVOAUX "_libros_aux.dat"

static void _imprimirCabezeraDeTabla()
{
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

void _imprimirLibro(long pos)
{
    FILE *pArchivo = archLibrosAbrir("rb");
    ST_LIBRO libro;

    fseek(pArchivo, pos, SEEK_SET);
    fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);

    printf("%20s\t", libro.titulo);
    printf("%15s\t", libro.autor.nombre);
    printf("%15s\t", libro.autor.apellido);
    printf("%12.2lf\t", libro.precio);
    printf("%9i\t", libro.isbn);
    printf("%5i\t", libro.stockDisponible);
    printf("%9i\t", libro.stockReservado);
    printf("\n");

    fclose(pArchivo);
}

void _imprimirLibroEnVariasLineas(long pos)
{
    FILE *pArchivo = archLibrosAbrir("rb");
    ST_LIBRO libro;

    fseek(pArchivo, pos, SEEK_SET);
    fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);

    printf("\n          TITULO: %s", libro.titulo);
    printf("\n    NOMBRE AUTOR: %s", libro.autor.nombre);
    printf("\n  APELLIDO AUTOR: %s", libro.autor.apellido);
    printf("\n          PRECIO: %.2lf", libro.precio);
    printf("\n            ISBN: %i", libro.isbn);
    printf("\nSTOCK DISPONIBLE: %i", libro.stockDisponible);
    printf("\n STOCK RESERVADO: %i", libro.stockReservado);
    printf("\n");

    fclose(pArchivo);
}

FILE* archLibrosAbrir(const char* modo)
{
    FILE *pArchivo = NULL;
    if((pArchivo = fopen(ARCHIVO, modo)) == NULL)
    {
        printf("\n\nCerrando programa. Hubo problemas al tratar abrir \"libros.dat\"\n\n");
        exit(EXIT_FAILURE);
    }
    return pArchivo;
}

ST_LIBRO archLibrosConseguirLibroPorPos(long pos)
{
    FILE* pArchivo = archLibrosAbrir("rb");
    fseek(pArchivo, pos, SEEK_SET);
    ST_LIBRO libro;
    fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    fclose(pArchivo);
    return libro;
}

long archLibrosConseguirPosPorISBN(int isbn)
{
    FILE* pArchivo = archLibrosAbrir("rb");
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

void archLibrosEliminarPorPos(long pos)
{
    FILE *pArchivo = archLibrosAbrir("rb");
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

void archLibrosImprimirTodos()
{
//    limpiarPantalla();
    FILE *pArchivo = archLibrosAbrir("rb");
    ST_LIBRO * pLibro = (ST_LIBRO*) malloc(sizeof(ST_LIBRO));
    fread(pLibro, sizeof(ST_LIBRO), 1, pArchivo);

    _imprimirCabezeraDeTabla();

    long pos;
    while(!feof(pArchivo))
    {
        pos = ftell(pArchivo) - sizeof(ST_LIBRO);
        _imprimirLibro(pos);
        fread(pLibro, sizeof(ST_LIBRO), 1, pArchivo);
    }

    fclose(pArchivo);

    printf("\n");
}

void menuLibroNuevo()
{
    FILE *pArchivo = archLibrosAbrir("ab+");
    ST_LIBRO libro;

    printf("ALTA DE NUEVO LIBRO\n");
    printf("- Para cancelar ingrese un string vacio o un numero menor a cero\n");

    fflush(stdin);

    printf("\nTITULO: ");
    gets(libro.titulo);
    if (esStringValido(libro.titulo) == false)
    {
        printOperacionCancelada();
        return;
    }

    printf("\nNOMBRE AUTOR: ");
    gets(libro.autor.nombre);
    if (esStringValido(libro.autor.nombre) == false)
    {
        printOperacionCancelada();
        return;
    }

    printf("\nAPELLIDO AUTOR: ");
    gets(libro.autor.apellido);
    if (esStringValido(libro.autor.apellido) == false)
    {
        printOperacionCancelada();
        return;
    }

    printf("\nPRECIO: ");
    scanf("%lf", &libro.precio);
    if (libro.precio < 0)
    {
        printOperacionCancelada();
        return;
    }

    printf("\nISBN: ");
    scanf("%i", &libro.isbn);
    if (libro.isbn < 0)
    {
        printOperacionCancelada();
        return;
    }

    printf("\nSTOCK DISPONIBLE: ");
    scanf("%i", &libro.stockDisponible);
    libro.stockReservado = 0;

    fwrite(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    fclose(pArchivo);
}

void menuLibroEliminar()
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

    long pos = archLibrosConseguirPosPorISBN(isbn);
    if (pos >= 0)
    {
        ST_LIBRO libro = archLibrosConseguirLibroPorPos(pos);
        if (libro.isbn != isbn)
        {
            printf("No se pudo eliminar el libro. No hay libro con el ISBN: %i\n", isbn);
            presioneUnaTeclaParaContinuar();
        }
        else
        {
//            fclose(pArchivo);
            archLibrosEliminarPorPos(pos);
        }
    }
    else
    {
        printf("No se pudo eliminar el libro. No hay libro con el ISBN: %i\n", isbn);
        presioneUnaTeclaParaContinuar();
    }
}

static void _imprimirBusquedaSinResultados()
{
    printf("\nNo se encontro ningun libro.\n");
}

void _editarLibroEnPantalla(long pos)
{
    ST_LIBRO libro = archLibrosConseguirLibroPorPos(pos);

    _imprimirLibroEnVariasLineas(pos);

    // EDITAR LIBRO
    ST_LIBRO libroAux;
    printf("\nEDITANDO LIBRO\n");
    printf("\t- Apriete enter para no editar strings\n");
    printf("\t- Ingrese -1 para no editar numeros\n");
    printf("\n\n");
    fflush(stdin);

    printf("TITULO: ");
    gets(libroAux.titulo);
//    if (libroAux.titulo[0] != '\0') // Si string no esta vacio
    if (esStringValido(libroAux.titulo)) // Si string no esta vacio
    {
        strcpy(libro.titulo, libroAux.titulo);
    }

    printf("NOMBRE AUTOR: ");
    gets(libroAux.autor.nombre);
//    if (libroAux.autor.nombre[0] != '\0') // Si string no esta vacio
    if (esStringValido(libroAux.autor.nombre)) // Si string no esta vacio
    {
        strcpy(libro.autor.nombre, libroAux.autor.nombre);
    }

    printf("APELLIDO AUTOR: ");
    gets(libroAux.autor.apellido);
//    if (libroAux.autor.apellido[0] != '\0') // Si string no esta vacio
    if (esStringValido(libroAux.autor.apellido)) // Si string no esta vacio
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

    FILE* pArchivo = archLibrosAbrir("rb+");
    fseek(pArchivo, pos, SEEK_SET);
    fwrite(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    fclose(pArchivo);

    presioneUnaTeclaParaContinuar("");
}

void menuLibroEditar()
{
    archLibrosImprimirTodos();

    int isbn = 0;
    printf("\n- ISBN: ");
    scanf("%i", &isbn);
    long pos = archLibrosConseguirPosPorISBN(isbn);
    if (pos >= 0)
    {
        ST_LIBRO libro = archLibrosConseguirLibroPorPos(pos);
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

void menuLibroBuscarPorApellidoDeAutor()
{
    FILE *pArchivo = archLibrosAbrir("rb");
    ST_LIBRO libro;

    limpiarPantalla();

    printf("\nBUSCAR APPELIDO DE AUTOR: ");
    char buscar[LIBRO_CHARS];
    fflush(stdin);
    gets(buscar);

    _imprimirCabezeraDeTabla();

    bool encontrado = false;
    char *busqueda = NULL;
    long pos;

    fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    while (!feof(pArchivo))
    {
        busqueda = strstr(strlwr(libro.autor.apellido), strlwr(buscar));
        if (busqueda != NULL)
        {
            encontrado = true;
            pos = ftell(pArchivo) - sizeof(ST_LIBRO);
            _imprimirLibro(pos);
        }
        fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    }

    if (encontrado == false)
    {
        _imprimirBusquedaSinResultados();
    }

    fclose(pArchivo);
}

void menuLibroBuscarPorISBN()
{
//    limpiarPantalla();
    int isbn = 0;
    printf("Buscar libro por ISBN.\n");
    printf("- ISBN: ");
    scanf("%i", &isbn);
    long pos = archLibrosConseguirPosPorISBN(isbn);
    if (pos >= 0)
    {
        ST_LIBRO libro = archLibrosConseguirLibroPorPos(pos);
        if (libro.isbn != isbn)
        {
            printf("No se encontre el libro con ISBN: %i\n", isbn);
            presioneUnaTeclaParaContinuar();
        }
        else
        {
            _imprimirLibroEnVariasLineas(pos);
            presioneUnaTeclaParaContinuar("");
        }
    }
    else
    {
        printf("No se encontre el libro con ISBN: %i\n", isbn);
        presioneUnaTeclaParaContinuar();
    }
}

void menuLibroBuscarPorNombreDeAutor()
{
    FILE *pArchivo = archLibrosAbrir("rb");
    ST_LIBRO libro;

//    limpiarPantalla();

    printf("\nBUSCAR NOMBRE DE AUTOR: ");
    char buscar[LIBRO_CHARS];
    fflush(stdin);
    gets(buscar);

    _imprimirCabezeraDeTabla();

    bool encontrado = false;
    char *busqueda = NULL;
    long pos;

    fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    while (!feof(pArchivo))
    {
        busqueda = strstr(strlwr(libro.autor.nombre), strlwr(buscar));
        if (busqueda != NULL)// if (strcmp(libro.autor.nombre, buscar) == 0)
        {
            encontrado = true;
            pos = ftell(pArchivo) - sizeof(ST_LIBRO);
            _imprimirLibro(pos);
        }
        fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    }

    if (encontrado == false)
    {
        _imprimirBusquedaSinResultados();
    }

    fclose(pArchivo);
}

void menuLibroBuscarPorTitulo()
{
    FILE *pArchivo = archLibrosAbrir("rb");
    ST_LIBRO libro;

//    limpiarPantalla();

    printf("\nBUSCAR TITULO: ");
    char buscar[LIBRO_CHARS];
    fflush(stdin);
    gets(buscar);

    _imprimirCabezeraDeTabla();

    bool encontrado = false;
    char *busqueda = NULL;
    long pos;

    fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    while (!feof(pArchivo))
    {
        busqueda = strstr(strlwr(libro.titulo), strlwr(buscar));
        if (busqueda != NULL)// if (strcmp(libro.titulo, buscar) == 0)
        {
            encontrado = true;
            pos = ftell(pArchivo) - sizeof(ST_LIBRO);
            _imprimirLibro(pos);
        }
        fread(&libro, sizeof(ST_LIBRO), 1, pArchivo);
    }

    if (encontrado == false)
    {
        _imprimirBusquedaSinResultados();
    }

    fclose(pArchivo);
}
