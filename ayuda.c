#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "ayuda.h"

int getInt()
{
    return getch() - '0'; // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
}

void limpiarPantalla()
{
    system("cls");
}

void presioneUnaTeclaParaContinuar()
{
    printf("Presione una tecla para continuar.");
    getch();
}

bool esStringValido(const char* pChar)
{
    return (*pChar) != '\0';
}

void printOperacionCancelada()
{
    printf("Operacion cancelada.\n");
}
