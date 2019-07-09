#include "ayuda.h"
#include "libro.h"
#include "venta.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct VentaLibro
{
    int isbn;
    double precio;
    char titulo[LIBRO_CHARS];
    struct VentaLibro* pSig;
} VentaLibro;

typedef struct Venta
{
    time_t fecha;
    long int factura;
    double dinero;
    VentaLibro* pLibros;
    struct Venta* pSig;
} Venta;

static Venta* pVentaSucurcual;
static Venta* pVentaDomocilio;

static void VentaLibro_imprimir(VentaLibro* pVentaLibro)
{
    printf("- [%i] %s $%0.2f\n", pVentaLibro->isbn, pVentaLibro->titulo, pVentaLibro->precio);
}

static void VentaLibro_imprimirMultiples(VentaLibro* pVentaLibro)
{
    while(pVentaLibro != NULL)
    {
        VentaLibro_imprimir(pVentaLibro);
        pVentaLibro = pVentaLibro->pSig;
    }
}

static void VentaLibro_pushFront(VentaLibro** ppVentaLibro, int isbn, double precio, const char* titulo)
{
    VentaLibro* pAux = (VentaLibro*)malloc(sizeof(VentaLibro));
    pAux->isbn = isbn;
    pAux->precio = precio;
    strncpy(pAux->titulo, titulo, LIBRO_CHARS);
    pAux->pSig = NULL;

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

static VentaLibro* VentaLibro_popFront(VentaLibro** ppVentaLibro)
{
    VentaLibro* pAux = (*ppVentaLibro);
    (*ppVentaLibro) = (*ppVentaLibro)->pSig;
    pAux->pSig = NULL;
    return pAux;
}

static void VentaLibro_clear(VentaLibro** ppVentaLibro)
{
    while((*ppVentaLibro) != NULL)
    {
        VentaLibro* pAux = VentaLibro_popFront(ppVentaLibro);
        free(pAux);
    }
}

static void Venta_pushEnd(Venta** ppVenta, VentaLibro* pLibros)
{
    Venta* pNewVenta = (Venta*)malloc(sizeof(Venta));
    pNewVenta->pSig = NULL;
    pNewVenta->pLibros = pLibros;

    // numero factura random
    srand(time(0));
    pNewVenta->factura = rand();

    // usar fecha del sistema
    time(&pNewVenta->fecha);

    // acumular precio de libros
    pNewVenta->dinero = 0;
    VentaLibro* pLibrosAux = pLibros;
    while(pLibrosAux != NULL)
    {
        pNewVenta->dinero += pLibrosAux->precio;
        pLibrosAux = pLibrosAux->pSig;
    }

    // buscar el ultimo nodo de la lista
    Venta* pVentaAux = (*ppVenta);
    while(pVentaAux != NULL && pVentaAux->pSig != NULL)
    {
        pVentaAux = pVentaAux->pSig;
    }

    if (pVentaAux == NULL) // insertar primero
    {
        (*ppVenta) = pNewVenta;
    }
    else // insertar ultimo
    {
        pVentaAux->pSig = pNewVenta;
    }
}

static Venta* Venta_popFront(Venta** ppVenta)
{
    Venta* pAux = (*ppVenta);
    (*ppVenta) = (*ppVenta)->pSig;
    pAux->pSig = NULL;
    return pAux;
}

static void Venta_clear(Venta** ppVenta)
{
    while((*ppVenta) != NULL)
    {
        Venta* pAux = Venta_popFront(ppVenta);
        VentaLibro_clear(&pAux->pLibros);
        free(pAux);
    }
}

static void Venta_imprimir(Venta* pVenta)
{
    struct tm* timeinfo;

    char buffer[256];

    timeinfo = localtime(&pVenta->fecha);
    strftime(buffer, 256, "%Y/%m/%d %H:%M:%Shs", timeinfo);

    printf("FACTURA N-%li\n", pVenta->factura);
    printf("FECHA: %s\n", buffer);
    printf("LIBROS:\n");
    VentaLibro_imprimirMultiples(pVenta->pLibros);
    printf("TOTAL: $%0.2f\n", pVenta->dinero);
}

static void Venta_imprimirMultiples(Venta* pVenta)
{
    while(pVenta != NULL)
    {
        Venta_imprimir(pVenta);
        pVenta = pVenta->pSig;
    }
}

void initVentas()
{
    pVentaDomocilio = NULL;
    pVentaSucurcual = NULL;
}

void clearVentas()
{
    printf("\n");
    Venta_imprimirMultiples(pVentaDomocilio);
    printf("\n");
    Venta_imprimirMultiples(pVentaSucurcual);
    Venta_clear(&pVentaDomocilio);
    Venta_clear(&pVentaSucurcual);
}

void menuVentas()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> VENTAS\n\n");
    // listar libros: titulo, autor, isbn, precio y stock
    archLibrosImprimirTodos();

    // seleccionar libros por isbn y meterlos a una lista, excluir libros sin stock, solo se puede vender un ejemplar por libro
    int isbn;
    printf("\nIngrese ISBN de libro a vender o un numero menor a cero para terminar.\n\n");

    printf("- ISBN: ");
    scanf("%i", &isbn);

    VentaLibro* pLibrosAVender = NULL;

    while (isbn >= 0)// ingresar libros mientras que quiera el usuario
    {
        long archPos = archLibrosConseguirPosPorISBN(isbn);
        if (archPos != -1)
        {
            ST_LIBRO libro = archLibrosConseguirLibroPorPos(archPos);
            VentaLibro_pushFront(&pLibrosAVender, isbn, libro.precio, libro.titulo);
            printf("Libro agregado.\n");
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
        VentaLibro_imprimirMultiples(pLibrosAVender);

        int confirmacion = 0;
        printf("\nCONFIRMAR (1 = Si, X = No): ");
        scanf("%i", &confirmacion);
        if (confirmacion == 1)
        {
            printf("- Venta confirmada.\n");
            printf("\nTIPO DE ENTREGA (1 = Envio a domicilio | X = Retiro por sucursal): ");
            scanf("%i", &confirmacion);
            if (confirmacion == 1)
            {
                // ENVIO: agergar a una cola
                printf("- Envio a domicilio.\n");
                Venta_pushEnd(&pVentaSucurcual, pLibrosAVender);
            }
            else
            {
                // RETIRO: agregar a una lista
                printf("- Retiro por sucursal.\n");
                Venta_pushEnd(&pVentaSucurcual, pLibrosAVender);
            }
            // si se confirma, generar factura.txt e incrementar en uno el stock reservado para cada libro
        }
        else
        {
            printf("- Venta cancelada.\n");
            VentaLibro_clear(&pLibrosAVender);
        }
    }

    printf("\n");
    presioneUnaTeclaParaContinuar();
}
