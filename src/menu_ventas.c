#include <stdio.h>
#include "../include/menu.h"
#include "../include/menu_ventas.h"

void showVentasMenu()
{
    clearScreen();
	printHastagLine();
	printLineWithText("    VENTA DE EJEMPLARES");
	printLineWithText("");
	printLineWithText("        1 - LISTAR");
	printLineWithText("        2 - BUSCAR ISBN");
	printLineWithText("        3 - BUSCAR TITULO ");
	printLineWithText("        4 - BUSCAR AUTOR ");
	printLineWithText("        0 - Volver");
    printf("\nIngrese opcion: ");
}

enum VENTAS_ERRORS validVentasOption(enum VENTAS_OP option)
{
	if(option < LISTAR || option > BUSCAR_AUTOR)
		return ERR_INVALID_VENTAS;
	else
		return ERR_VENTAS_OK;
}

void ventasMenu()
{
    showVentasMenu();
    enum VENTAS_OP opVentas = getOption();
    while(opVentas != END_VENTAS)
    {
        switch ( opVentas )
        {
            case LISTAR:
            case BUSCAR_ISBN:
            case BUSCAR_TITULO:
            case BUSCAR_AUTOR:
                printOptionWIP();
                break;
            default:
                printOptionInvalid();
                break;
        }
        showVentasMenu();
        opVentas = getOption();
    }
}
