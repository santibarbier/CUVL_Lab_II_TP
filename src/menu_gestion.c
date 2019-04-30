#include <stdio.h>
#include "../include/menu.h"
#include "../include/menu_gestion.h"
#include "../include/libro.h"
#include "../include/libro_buscar.h"

void showGestionMenu()
{
    clearScreen();
	printHastagLine();
	printLineWithText("    GESTION DE LIBROS");
	printLineWithText("");
	printLineWithText("        1 - ALTA DE LIBRO");
	printLineWithText("        2 - LISTAR");
	printLineWithText("        3 - BUSCAR POR TITULO");
	printLineWithText("        4 - BUSCAR POR NOMBRE DE AUTOR");
	printLineWithText("        5 - EDITAR ");
	printLineWithText("        6 - ELIMINAR ");
	printLineWithText("        0 - Volver");
    printf("\nIngrese opcion: ");
}

void gestionMenu()
{
    showGestionMenu();
    enum GESTION_OP opGestion = getOption();
    while(opGestion != GES_END)
    {
        switch ( opGestion )
        {
            case GES_ALTA_DE_LIBRO:
                nuevoLibro();
                break;
            case GES_LISTADO:
                listarLibros();
                pressAnyKeyToContinue("");
                break;
            case GES_BUSCAR_TITULO:
                buscarLibroPorTitulo();
                pressAnyKeyToContinue("");
                break;
            case GES_BUSCAR_NOMBRE:
                buscarLibroPorNombreDeAutor();
                pressAnyKeyToContinue("");
                break;
            case GES_EDITAR:
            case GES_ELIMINAR:
                printOptionWIP();
                break;
            default:
                printOptionInvalid();
                break;
        }
        showGestionMenu();
        opGestion = getOption();
    }
}
