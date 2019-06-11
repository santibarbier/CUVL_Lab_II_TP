#include <stdio.h>

#include "ayuda.h"
#include "menu.h"
#include "menu_gestion_buscar.h"

#include "libro.h"

void _agregarLibro()
{
    limpiarPantalla();
    printf("agregarLibro()\n");
    presioneUnaTeclaParaContinuar();
}

void _editarLibro()
{
    limpiarPantalla();
    printf("editarLibro()\n");
    presioneUnaTeclaParaContinuar();
}

void _eliminarLibro()
{
    limpiarPantalla();
    printf("eliminarLibro()\n");
    presioneUnaTeclaParaContinuar();
}

void _listarLibros()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> LISTAR\n\n");
    listarLibros();
    presioneUnaTeclaParaContinuar();
}

void menuGestion()
{
    Menu menus[] =
    {
        Menu_crear("Agregar", &_agregarLibro),
        Menu_crear("Editar", &_editarLibro),
        Menu_crear("Eliminar", &_eliminarLibro),
        Menu_crear("Listar", &_listarLibros),
        Menu_crear("Buscar", &menuGestionBuscar),
    };
    Menu_loopBasico(menus, 5, "MENU PRINCIPAL -> GESTION DE LIBROS", MSJ_VOLVER);
}
