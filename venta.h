#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED

#include "libro.h"
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
    int factura;
    double dinero;
    VentaLibro* pLibros;
    struct Venta* pSig;
} Venta;

#endif // VENTAS_H_INCLUDED
