#include <stdio.h>

#include "ayuda.h"
#include "menu.h"

#include "libro.h"
#include "libro_buscar.h"

void _buscarISBN()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> BUSCAR LIBROS -> ISBN\n\n");
    buscarLibroPorISBN();
    presioneUnaTeclaParaContinuar();
}

void _buscarTitulo()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> BUSCAR LIBROS -> TITULO\n\n");
    buscarLibroPorTitulo();
    presioneUnaTeclaParaContinuar();
}

void _buscarNombre()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> BUSCAR LIBROS -> NOMBRE\n\n");
    buscarLibroPorNombreDeAutor();
    presioneUnaTeclaParaContinuar();
}

void _buscarApellido()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> BUSCAR LIBROS -> APELLIDO\n\n");
    buscarLibroPorApellidoDeAutor();
    presioneUnaTeclaParaContinuar();
}

void menuGestionBuscar()
{
    Menu menus[] =
    {
        Menu_crear("ISBN", &_buscarISBN),
        Menu_crear("Titulo", &_buscarTitulo),
        Menu_crear("Nombre de autor", &_buscarNombre),
        Menu_crear("Appelido de auto", &_buscarApellido),
    };
    Menu_loopBasico(menus, 4, "MENU PRINCIPAL -> GESTION DE LIBROS -> BUSCAR LIBROS", MSJ_VOLVER);
}
