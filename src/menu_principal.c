#include <stdio.h>
#include <stdlib.h>
#include "../include/menu.h"
#include "../include/menu_principal.h"
#include "../include/menu_entregas.h"
#include "../include/menu_gestion.h"
#include "../include/menu_ventas.h"

void showStartMenu()
{
    clearScreen();
	printHastagLine();
	printLineWithText("    INGRESE LA OPCION DESEADA");
	printLineWithText("");
	printLineWithText("        1 - GESTION DE LIBROS");
	printLineWithText("        2 - VENTA DE EJEMPLARES");
	printLineWithText("        3 - ENTREGA DE ARTICULOS");
	printLineWithText("        0 - Finalizar");
    printf("\nIngrese opcion: ");
}

void startMenuLoop()
{
    showStartMenu();
	enum PRINCIPAL_OP option = getOption();
	while(option != PRIN_END)
    {
		switch(option){
			case PRIN_GESTION:
				gestionMenu();
				break;
			case PRIN_VENTAS:
				ventasMenu();
				break;
			case PRIN_ENTREGA:
				entregasMenu();
				break;
			default:
				printOptionInvalid();
				break;
		}

		printf("\n\n------0------\n\n");
		clearScreen();
		showStartMenu();
		option = getOption();
	}
}
