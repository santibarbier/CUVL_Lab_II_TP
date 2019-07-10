#include "ayuda.h"
#include "libro.h"
#include "venta.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

void VentaLibro_fprintf(FILE* stream, VentaLibro* pVentaLibro)
{
    fprintf(stream, "- [%i] %s $%0.2f\n", pVentaLibro->isbn, pVentaLibro->titulo, pVentaLibro->precio);
}

void VentaLibro_fprintfMulti(FILE* stream, VentaLibro* pVentaLibro)
{
    while(pVentaLibro != NULL)
    {
        VentaLibro_fprintf(stream, pVentaLibro);
        pVentaLibro = pVentaLibro->pSig;
    }
}

void VentaLibro_pushFront(VentaLibro** ppVentaLibro, int isbn, double precio, const char* titulo)
{
    // CREAMOS NUEVO NODO
    VentaLibro* pAux = (VentaLibro*)malloc(sizeof(VentaLibro));
    pAux->isbn = isbn;
    pAux->precio = precio;
    strncpy(pAux->titulo, titulo, LIBRO_CHARS);
    pAux->pSig = NULL;

    // INSERTAMOS NUEVO NODO
    if ((*ppVentaLibro) == NULL)
    {
        (*ppVentaLibro) = pAux;
    }
    else
    {
        pAux->pSig = (*ppVentaLibro);
        (*ppVentaLibro) = pAux;
    }
}

VentaLibro* VentaLibro_popFront(VentaLibro** ppVentaLibro)
{
    VentaLibro* pAux = (*ppVentaLibro);
    (*ppVentaLibro) = (*ppVentaLibro)->pSig;
    pAux->pSig = NULL;
    return pAux;
}

void VentaLibro_clear(VentaLibro** ppVentaLibro)
{
    while((*ppVentaLibro) != NULL)
    {
        VentaLibro* pAux = VentaLibro_popFront(ppVentaLibro);
        free(pAux);
    }
}

double VentaLibro_costoTotal(VentaLibro* pVentaLibro)
{
    double costo = 0;
    while(pVentaLibro != NULL)
    {
        costo += pVentaLibro->precio;
        pVentaLibro = pVentaLibro->pSig;
    }
    return costo;
}

Venta* Venta_end(Venta* pVenta)
{
    while(pVenta != NULL && pVenta->pSig != NULL)
    {
        pVenta = pVenta->pSig;
    }
    return pVenta;
}

Venta* Venta_popFront(Venta** ppVenta)
{
    Venta* pAux = (*ppVenta);
    (*ppVenta) = (*ppVenta)->pSig;
    pAux->pSig = NULL;
    return pAux;
}

void Venta_clear(Venta** ppVenta)
{
    while((*ppVenta) != NULL)
    {
        Venta* pAux = Venta_popFront(ppVenta);
        VentaLibro_clear(&pAux->pLibros);
        free(pAux);
    }
}

void Venta_fprintf(FILE* stream, Venta* pVenta)
{
    // primero convertimos el rawtime (time_t) a algo que se pueda usar
    // y luego llamamos srtime para armar un string con la fecha en el formato deseado
    struct tm* timeinfo;
    char buffer[256];
    timeinfo = localtime(&pVenta->fecha);
    strftime(buffer, 256, "%Y/%m/%d %H:%M:%Shs", timeinfo);
    // impresion
    fprintf(stream, "FACTURA N-%li\n", pVenta->factura);
    fprintf(stream, "FECHA: %s\n", buffer);
    fprintf(stream, "LIBROS:\n");
    VentaLibro_fprintfMulti(stream, pVenta->pLibros);
    fprintf(stream, "TOTAL: $%0.2f\n", pVenta->dinero);
}

void Venta_pushEnd(Venta** ppVenta, VentaLibro* pLibros)
{
    // CREAMOS NUEVO NODO
    Venta* pNewVenta = (Venta*)malloc(sizeof(Venta));
    pNewVenta->pSig = NULL;
    pNewVenta->pLibros = pLibros;
    // numero factura random
    srand(time(0));
    pNewVenta->factura = rand();
    // usar fecha del sistema
    time(&pNewVenta->fecha);
    // llamamos a la funcion para calcular el precio
    pNewVenta->dinero = VentaLibro_costoTotal(pLibros);
    // INSERTAMOS NUEVO NODO
    // llamamos a la funcion para buscar el ultimo nodo de la lista
    Venta* pVentaAux = Venta_end((*ppVenta));
    if (pVentaAux == NULL) // insertar primero
    {
        (*ppVenta) = pNewVenta;
    }
    else // insertar ultimo
    {
        pVentaAux->pSig = pNewVenta;
    }
}

bool VentaLibro_has(VentaLibro* pVentaLibro, int isbn)
{
    while(pVentaLibro != NULL)
    {
        if (pVentaLibro->isbn == isbn)
        {
            return true;
        }
        pVentaLibro = pVentaLibro->pSig;
    }
    return false;
}

static void _generarArchFactura(Venta* pVenta)
{
    // declaramos una cadena donde meteremos el nombre del archivo
    char fname[400];
    memset(fname, '\0', 400);
    strcat(fname, CARPETA);
    strcat(fname, "/");

    // declaramos un puntero a char y lo movemos al final de la cadena para el nombre del archivo
    char* pChar = fname;
    int c = 0;
    while ((*pChar) != '\0')
    {
        pChar++;
        c++;
    }

    // metemos la fecha en el nombre del archivo
    struct tm* timeinfo;
    timeinfo = localtime(&pVenta->fecha);
    strftime(pChar, 400 - c, "fact%Y%m%d%H%M%S", timeinfo);

    // movemos el puntero al final de la cadena para el nombre del archivo
    pChar = fname;
    while ((*pChar) != '\0'&& (*(pChar + 1)) != '\0')
    {
        pChar++;
    }

    // en el final de la cadena, agregamos el numero de factura y la extension del archivo
    sprintf(pChar, "%-li.txt", pVenta->factura);

    // abrimos el archivo, imprimimos y cerramos
    FILE* pFile = fopen(fname, "w");
    Venta_fprintf(pFile, pVenta);
    fclose(pFile);
}

static void _procesarVentaLibros(VentaLibro* pLibros)
{
    while(pLibros != NULL)
    {
        archLibrosReservarUno(pLibros->isbn);
        pLibros = pLibros->pSig;
    }
}

void menuVenta(Venta** ppVentasDomicilio, Venta** ppVentasSucursal)
{
    // listar libros: titulo, autor, isbn, precio y stock
    archLibrosImprimirTodos();

    // seleccionar libros por isbn y meterlos a una lista
    int isbn;
    VentaLibro* pLibrosAVender = NULL;

    printf("\nIngrese ISBN de libro a vender o un numero menor a cero para terminar.\n\n");

    printf("- ISBN: ");
    scanf("%i", &isbn);


    while (isbn >= 0)// ingresar libros mientras que quiera el usuario
    {
        long archPos = archLibrosConseguirPosPorISBN(isbn);
        if (archPos != -1)
        {
            ST_LIBRO libro = archLibrosConseguirLibroPorPos(archPos);
            // excluir libros que ya estan en la venta
            if (VentaLibro_has(pLibrosAVender, isbn))
            {
                printf("Libro NO agregado. Ya esta en la lista para vender. Solo se puede vender una copia por original.\n");
            }
            // excluir libros sin stock
            else if (libro.stockDisponible > libro.stockReservado)
            {
                VentaLibro_pushFront(&pLibrosAVender, isbn, libro.precio, libro.titulo);
                printf("Libro agregado.\n");
            }
            else
            {
                printf("Libro NO agregado. No hay stock disponible.\n");
            }
        }
        else
        {
            printf("Libro NO agregado. ISBN incorecto.\n");
        }
        printf("\n- ISBN: ");
        scanf("%i", &isbn);
    }

    if(pLibrosAVender == NULL)
    {
        printf("- Venta cancelada. No se ingreso ningun libro.\n");
    }
    else
    {
        // al finalizar el ingreso, mostrar resumen y pedir confirmacion
        printf("\nRESUMEN DE VENTA\n");
        VentaLibro_fprintfMulti(stdout, pLibrosAVender);
        printf("TOTAL: $%0.2f\n", VentaLibro_costoTotal(pLibrosAVender));

        int confirmacion = 0;
        printf("\nCONFIRMAR (1 = Si, Otro numero = No): ");
        scanf("%i", &confirmacion);
        if (confirmacion == 1)
        {
            printf("- Venta confirmada.\n");
            printf("\nTIPO DE ENTREGA (1 = Envio a domicilio | Otro numero = Retiro por sucursal): ");
            scanf("%i", &confirmacion);
            // generar factura.txt e incrementar en uno el stock reservado para cada libro
            if (confirmacion == 1)
            {
                // ENVIO: agergar a una cola
                printf("- Envio a domicilio.\n");
                Venta_pushEnd(ppVentasDomicilio, pLibrosAVender);
                _generarArchFactura(Venta_end((*ppVentasDomicilio)));
            }
            else
            {
                // RETIRO: agregar a una lista
                printf("- Retiro por sucursal.\n");
                Venta_pushEnd(ppVentasSucursal, pLibrosAVender);
                _generarArchFactura(Venta_end((*ppVentasSucursal)));
            }
            _procesarVentaLibros(pLibrosAVender);
        }
        else
        {
            printf("- Venta cancelada.\n");
            VentaLibro_clear(&pLibrosAVender);
        }
    }
}
