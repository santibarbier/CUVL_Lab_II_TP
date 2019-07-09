#include "menu.h"
#include "menu_entregas.h"
#include "ayuda.h"
#include "_ventas.h"

#define ENVIOS 5

static void _envioADomicilio()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> ENTREGAS -> ENVIO A DOMICILIO\n\n");

    int contador = 0;
    Venta* pAux = pVentasDomocilio;
    while(pAux != NULL && contador < ENVIOS)
    {
        Venta_imprimir(pAux);
        printf("\n");
        pAux = pAux->pSig;
        contador++;
    }

    if (contador == 0)
    {
        printf("No hay ningun envio a realizar.\n");
    }

    printf("\n");
    presioneUnaTeclaParaContinuar();
}

static void _retiroPorSucursal()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> ENTREGAS -> ENVIO A DOMICILIO\n\n");
    printf("\n");
    presioneUnaTeclaParaContinuar();
}

void menuEntregas()
{
    Menu menus[] =
    {
        Menu_crear("Envio a domicilio", &_envioADomicilio),
        Menu_crear("Retiro por sucursal", &_retiroPorSucursal),
    };
    Menu_loopBasico(menus, 2, "MENU PRINCIPAL -> ENTREGAS", MSJ_VOLVER);
}
