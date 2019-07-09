#include "menu.h"
#include "menu_gestion.h"
#include "venta.h"
#include "ayuda.h"

#include <stdio.h>

void menuEntregas()
{
    limpiarPantalla();
    printf("menuEntregas()\n");
    presioneUnaTeclaParaContinuar();
}

int main()
{
    initVentas();

    Menu menus[] =
    {
        Menu_crear("Gestion de libros", &menuGestion),
        Menu_crear("Venta de libros", &menuVentas),
        Menu_crear("Entrega de articulos", &menuEntregas),
    };
    Menu_loopBasico(menus, 3, "MENU PRINCIPAL", MSJ_SALIR);

    clearVentas();
    return 0;
}
