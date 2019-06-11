#include <stdio.h>
#include "../include/menu.h"
#include "../include/menu_ventas.h"
#include "../include/libro.h"
#include "../include/libro_buscar.h"

void showVentasMenu()
{
    clearScreen();
	printHastagLine();
	printLineWithText("    VENTA DE EJEMPLARES");
	printLineWithText("");
	printLineWithText("        1 - LISTAR");
	printLineWithText("        2 - BUSCAR POR TITULO");
	printLineWithText("        3 - BUSCAR POR NOMBRE DE AUTOR");
	printLineWithText("        4 - BUSCAR POR APELLIDO DE AUTOR");
	printLineWithText("        5 - BUSCAR POR ISBN");
	printLineWithText("        0 - Volver");
    printf("\nIngrese opcion: ");
}

void ventasMenu()
{
    showVentasMenu();
    enum VENTAS_OP opVentas = getOption();
    while(opVentas != VENTAS_END)
    {
        switch ( opVentas )
        {
            case VENTAS_LISTAR:
                listarLibros();
                pressAnyKeyToContinue("");
                break;
            case VENTAS_BUSCAR_TITULO:
                buscarLibroPorTitulo();
                pressAnyKeyToContinue("");
                break;
            case VENTAS_BUSCAR_AUTOR_NOMBRE:
                buscarLibroPorNombreDeAutor();
                pressAnyKeyToContinue("");
                break;
            case VENTAS_BUSCAR_AUTOR_APELLIDO:
                buscarLibroPorApellidoDeAutor();
                pressAnyKeyToContinue("");
                break;
            case VENTAS_BUSCAR_ISBN:
                buscarLibroPorISBN();
                break;
            default:
                printOptionInvalid();
                break;
        }
        showVentasMenu();
        opVentas = getOption();
    }
}
