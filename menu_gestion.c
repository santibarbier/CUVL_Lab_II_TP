#include "ayuda.h"
#include "menu.h"
#include "libro.h"

static void _nuevoLibro()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> NUEVO\n\n");
    menuLibroNuevo();
    presioneUnaTeclaParaContinuar();
}

static void _editarLibro()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> EDITAR\n\n");
    menuLibroEditar();
    presioneUnaTeclaParaContinuar();
}

static void _eliminarLibro()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> ELIMINAR\n\n");
    menuLibroEliminar();
    presioneUnaTeclaParaContinuar();
}

static void _listarLibros()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> LISTAR\n\n");
    archLibrosImprimirTodos();
    presioneUnaTeclaParaContinuar();
}

static void _buscarISBN()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> BUSCAR LIBROS -> ISBN\n\n");
    menuLibroBuscarPorISBN();
    presioneUnaTeclaParaContinuar();
}

static void _buscarTitulo()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> BUSCAR LIBROS -> TITULO\n\n");
    menuLibroBuscarPorTitulo();
    presioneUnaTeclaParaContinuar();
}

static void _buscarNombre()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> BUSCAR LIBROS -> NOMBRE\n\n");
    menuLibroBuscarPorNombreDeAutor();
    presioneUnaTeclaParaContinuar();
}

static void _buscarApellido()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> GESTION DE LIBROS -> BUSCAR LIBROS -> APELLIDO\n\n");
    menuLibroBuscarPorApellidoDeAutor();
    presioneUnaTeclaParaContinuar();
}

static void _menuGestionBuscar()
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

void menuGestion()
{
    Menu menus[] =
    {
        Menu_crear("Nuevo", &_nuevoLibro),
        Menu_crear("Editar", &_editarLibro),
        Menu_crear("Eliminar", &_eliminarLibro),
        Menu_crear("Listar", &_listarLibros),
        Menu_crear("Buscar", &_menuGestionBuscar),
    };
    Menu_loopBasico(menus, 5, "MENU PRINCIPAL -> GESTION DE LIBROS", MSJ_VOLVER);
}
