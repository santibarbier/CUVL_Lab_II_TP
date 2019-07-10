#ifndef AYUDA_H_INCLUDED
#define AYUDA_H_INCLUDED

#include <stdbool.h>

int getInt();
void limpiarPantalla();
bool esStringValido(const char* pChar);
void presioneUnaTeclaParaContinuar();
void printOperacionCancelada();
void crearDirectorio(const char *name);

#endif // AYUDA_H_INCLUDED
