#include "_ventas.h"

void ventasInit()
{
    pVentasDomocilio = NULL;
    pVentasSucursal = NULL;
}

void ventasClear()
{
    Venta_clear(&pVentasDomocilio);
    Venta_clear(&pVentasSucursal);
}
