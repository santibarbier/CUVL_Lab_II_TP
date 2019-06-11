#include "menu.h"
#include "menu_principal.h"
#include "menu_gestion.h"
#include "menu_ventas.h"
#include "menu_entregas.h"

void menuPrincipal()
{
    Menu menus[] =
    {
        Menu_crear("Gestion de libros", &menuGestion),
        Menu_crear("Venta de libros", &menuVentas),
        Menu_crear("Entrega de articulos", &menuEntregas),
    };
    Menu_loopBasico(menus, 3, "MENU PRINCIPAL", MSJ_SALIR);
}
