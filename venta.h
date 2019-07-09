#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED

#include "libro.h"
#include <time.h>
#include <stdbool.h>

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

void menuVenta(Venta** ppVentasDomicilio, Venta** ppVentasSucursal);

void Venta_clear(Venta** ppVenta);
Venta* Venta_end(Venta* pVenta);
void Venta_imprimir(Venta* pVenta);
Venta* Venta_popFront(Venta** ppVenta);
void Venta_pushEnd(Venta** ppVenta, VentaLibro* pLibros);

void VentaLibro_clear(VentaLibro** ppVentaLibro);
double VentaLibro_costoTotal(VentaLibro* pVentaLibro);
bool VentaLibro_has(VentaLibro* pVentaLibro, int isbn);
void VentaLibro_imprimir(VentaLibro* pVentaLibro);
void VentaLibro_imprimirMultiples(VentaLibro* pVentaLibro);
void VentaLibro_pushFront(VentaLibro** ppVentaLibro, int isbn, double precio, const char* titulo);
VentaLibro* VentaLibro_popFront(VentaLibro** ppVentaLibro);

#endif // VENTAS_H_INCLUDED
