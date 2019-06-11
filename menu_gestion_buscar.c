#include <stdio.h>

#include "ayuda.h"
#include "menu.h"

void buscarLibro()
{
    limpiarPantalla();
    printf("buscarLibro()\n");
    presioneUnaTeclaParaContinuar();
}

void menuGestionBuscar()
{
    Menu menus[] =
    {
        Menu_crear("ISBN", &buscarLibro),
        Menu_crear("Titulo", &buscarLibro),
        Menu_crear("Nombre de autor", &buscarLibro),
        Menu_crear("Appelido de auto", &buscarLibro),
    };
    Menu_loopBasico(menus, 4, "MENU PRINCIPAL -> GESTION DE LIBROS -> BUSCAR LIBROS", MSJ_VOLVER);
}
