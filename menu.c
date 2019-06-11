#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ayuda.h"
#include "menu.h"

void Menu_inicializar(Menu* mo, const char* titulo, void (*pFuncion)())
{
    strcpy((*mo).titulo, titulo);
    (*mo).pFuncion = pFuncion;
}

void Menu_imprimirTitulo(Menu* mo)
{
    printf("%s", (*mo).titulo);
}

void Menu_llamarFuncion(Menu* mo)
{
    (*(*mo).pFuncion)();
}

Menu Menu_crear(const char* titulo, void (*pFuncion)())
{
    Menu mo;
    Menu_inicializar(&mo, titulo, pFuncion);
    return mo;
}

void Menu_imprimirVector(Menu menus[], int n, const char* cabezera, const char* msj_cero)
{
    printf("%s\n\n", cabezera);
    for(int i = 0; i < n; i++)
    {
        printf("\t%i - ", i + 1);
        Menu_imprimirTitulo(&menus[i]);
        printf("\n");
    }
    printf("\t0 - %s", msj_cero);
    printf("\n");
}

void Menu_loopBasico(Menu menus[], int n, const char* cabezera, const char* msj_cero)
{
    int opcion = -1;// -1 para que entre al while
    while(opcion != 0)
    {
        limpiarPantalla();
        Menu_imprimirVector(menus, n, cabezera, msj_cero);
        printf("\n\tIngrese opcion: ");
//        scanf("%i", &opcion);
        opcion = getInt();
        if (opcion > 0 && opcion <= n)
        {
            Menu_llamarFuncion(&menus[opcion - 1]);
        }
        else if (opcion != 0)
        {
            printf("\n\t\tOPCION NO VALIDA!\n");
            printf("\t\t");
            presioneUnaTeclaParaContinuar();
        }
    }
}
