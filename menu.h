/*
EJEMPLO DE COMO USAR
    void menuAlgo()
    {
        int n = 3;
        Menu menus[n];
        menus[0] = Menu_crear("Submenu 1", &funcion1);
        menus[1] = Menu_crear("Submenu 2", &funcion2);
        menus[2] = Menu_crear("Submenu 3", &funcion3);
        Menu_loopBasico(menus, n, "MENU DE ALGO", MSJ_SALIR);
    }
OTRO EJEMPLO DE COMO USAR
    void menuAlgo()
    {
        Menu menus[] =
        {
            Menu_crear("Submenu 1", &funcion1),
            Menu_crear("Submenu 2", &funcion2),
            Menu_crear("Submenu 3", &funcion3),
        };
        Menu_loopBasico(menus, 3, "MENU DE ALGO", MSJ_SALIR);
    }
*/

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#define MSJ_SALIR "Salir"
#define MSJ_VOLVER "Volver"

typedef struct Menu {
    char titulo[50];
    void (*pFuncion)();
} Menu;

Menu Menu_crear(const char* titulo, void (*pFuncion)());
void Menu_inicializar(Menu* mo, const char* titulo, void (*pFuncion)());

void Menu_imprimirTitulo(Menu* mo);
void Menu_llamarFuncion(Menu* mo);

void Menu_imprimirVector(Menu menus[], int n, const char* cabezera, const char* msj_cero);
void Menu_loopBasico(Menu menus[], int n, const char* cabezera, const char* msj_cero);

#endif // MENU_H_INCLUDED
