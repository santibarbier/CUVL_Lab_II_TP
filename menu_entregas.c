#include "menu.h"
#include "menu_entregas.h"
#include "ayuda.h"
#include "_ventas.h"

#include <stdlib.h>

#define ENVIOS 5

static void _disminuirStockDeLibros(VentaLibro* pLibros)
{
    while(pLibros != NULL)
    {
        archLibrosDisminuirStock(pLibros->isbn);
        pLibros = pLibros->pSig;
    }
}

static void _envioADomicilio()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> ENTREGAS -> ENVIO A DOMICILIO\n\n");

    archLibrosImprimirTodos();

    int total = 0;
    Venta* pAux = pVentasDomocilio;
    while(pAux != NULL && total < ENVIOS)
    {
        Venta_fprintf(stdout, pAux);
        printf("\n");
        pAux = pAux->pSig;
        total++;
    }

    if (total > 0)
    {
        int despachar = 0;
        printf("DESPACHAR (1 = Si | Otro numero = No): ");
        scanf("%i", &despachar);
        if (despachar == 1)
        {
            int contador = 0;
            while(pVentasDomocilio != NULL && contador < ENVIOS)
            {
                pAux = Venta_popFront(&pVentasDomocilio);
                _disminuirStockDeLibros(pAux->pLibros);
                free(pAux);
                contador++;
            }
            printf("Despacho concretado.\nEl stock se ha modificado.\n\n");
            archLibrosImprimirTodos();
        }
        else
        {
            printf("Despacho cancelado.\n");
        }
    }
    else
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

    archLibrosImprimirTodos();

    int total = 0;
    Venta* pAux = pVentasSucursal;
    while(pAux != NULL && total < ENVIOS)
    {
        Venta_fprintf(stdout, pAux);
        printf("\n");
        pAux = pAux->pSig;
        total++;
    }

    if (total > 0)
    {
        int retirar = total + 1;// lo inciamos en algo no valido asi se mete al while y no escribimos de mas
        while(retirar != -1 && retirar > total)
        {
            printf("RETIRAR (Seleccionar 1 a %i | -1 = Cancelar): ", total);
            scanf("%i", &retirar);
        }
        if (retirar > 0)
        {
            retirar -= 1;// esto porque el usario puede ingresar 1, para retirar el primero, y asi asa
            Venta* pAux = pVentasSucursal;
            int contador = 0;
            while(contador != retirar)
            {
                pAux = pAux->pSig;
                contador++;
            }
            _disminuirStockDeLibros(pAux->pLibros);
            printf("Retiro realizado.\nEl stock se ha modificado.\n\n");
            archLibrosImprimirTodos();
        }
        else
        {
            printf("Operacion cancelada.\n");
        }
    }
    else
    {
        printf("No hay pedidos para retirar.\n");
    }
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
