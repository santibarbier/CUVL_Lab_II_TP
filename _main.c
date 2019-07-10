#include "menu.h"
#include "menu_gestion.h"
#include "menu_ventas.h"
#include "menu_entregas.h"
#include "venta.h"
#include "_ventas.h"
#include "ayuda.h"

#include <stdio.h>

static void _menuInstrucciones()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> INSTRUCCIONES\n\n");
    printf("Los libros se imprimen en forma de tabla, pero solo es legible con nombres cortos.\n");
    printf("Por esto, es recomendado agrandar el buffer de la consola para una impresion legible.\n");
    printf("Unos 200 estan mas que bien.\n");
    printf("\n");
    printf("Las facturas de las ventas son guardadas en la carpeta 'data', junto con el archivo de libros.\n");
    printf("Dicha carpeta se crea al agregar un nuevo libro por primara vez, en la locacion del ejecutable.\n");
    printf("\n");
    printf("Copate, no ingreses chars, donde no te lo pide c;.\n");
    printf("\n");
    presioneUnaTeclaParaContinuar();
}

int main()
{
    ventasInit();
    Menu menus[] =
    {
        Menu_crear("Gestion de libros", &menuGestion),
        Menu_crear("Venta de libros", &menuVentas),
        Menu_crear("Entrega de articulos", &menuEntregas),
        Menu_crear("Instrucciones", &_menuInstrucciones),
    };
    Menu_loopBasico(menus, 4, "MENU PRINCIPAL", MSJ_SALIR);
    ventasClear();
    return 0;
}
