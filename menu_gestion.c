#include <stdio.h>

#include "ayuda.h"
#include "menu.h"
#include "menu_gestion_buscar.h"

#include "libro.h"

void _nuevoLibro()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> NUEVO\n\n");
    nuevoLibro();
    presioneUnaTeclaParaContinuar();
}

void _editarLibro()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> EDITAR\n\n");
    editarLibro();
    presioneUnaTeclaParaContinuar();
}

void _eliminarLibro()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> ELIMINAR\n\n");
    eliminarLibro();
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
        Menu_crear("Nuevo", &_nuevoLibro),
        Menu_crear("Editar", &_editarLibro),
        Menu_crear("Eliminar", &_eliminarLibro),
        Menu_crear("Listar", &_listarLibros),
        Menu_crear("Buscar", &menuGestionBuscar),
    };
    Menu_loopBasico(menus, 5, "MENU PRINCIPAL -> GESTION DE LIBROS", MSJ_VOLVER);
}
