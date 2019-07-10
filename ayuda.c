#include "ayuda.h"

#include <stdio.h>
#include <stdlib.h>

// windows
// https://docs.microsoft.com/en-us/cpp/c-runtime-library/c-run-time-library-reference?view=vs-2019
#include <conio.h>
#include <direct.h>

// linux
// https://linux.die.net/man/

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

/** https://stackoverflow.com/questions/23271990/how-to-create-a-folder-in-c-need-to-run-on-both-linux-and-windows */
void crearDirectorio(const char *name)
{
   #ifdef __linux__
       mkdir(name, 777);
   #else
       _mkdir(name);
   #endif
}
