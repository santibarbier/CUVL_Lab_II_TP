#include <stdio.h>
#include "../include/menu.h"
#include "../include/menu_entregas.h"

void showEntregasMenu()
{
    clearScreen();
	printHastagLine();
	printLineWithText("    ENTREGA DE ARTICULO");
	printLineWithText("");
	printLineWithText("        1 - RETIRO EN TIENDA");
	printLineWithText("        2 - ENVIOS A DOMICILIO");
	printLineWithText("        0 - Volver");
	printf("\nIngrese opcion: ");
}

void entregasMenu()
{
    showEntregasMenu();
    enum ENTREGAS_OP opEntregas = getOption();
    while(opEntregas != ENT_END)
    {
        switch (opEntregas)
        {
            case ENT_RETIRO:
            case ENT_ENVIO:
                printOptionWIP();
                break;
            default:
                printOptionInvalid();
                break;
        }
        showEntregasMenu();
        opEntregas = getOption();
    }
}
