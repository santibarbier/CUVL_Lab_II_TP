#include "menu_ventas.h"
#include "ayuda.h"
#include "_ventas.h"

void menuVentas()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> VENTAS\n\n");
    menuVenta(&pVentasDomocilio, &pVentasSucursal);
    printf("\n");
    presioneUnaTeclaParaContinuar();
}
