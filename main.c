//#include <stdio.h>
//#include <stdlib.h>
#include "include/menu_principal.h"
int main()
{
	startMenuLoop();
	return 0;
}
/*
# TODO:
- [ ] submenu para buscar
- [ ] usar strstr en busqueda de libros
- [ ] usar strncpy en inicializacion de libros
- [X] imprimir cuando no se encuentra un libro
- [ ] FIX: la busqueda de libros es case-sensitive
- [ ] buscarLibro se tendria que separar en varias funciones: buscarLibroPorAutorNombre, buscarLibroPorAutorApellido, buscarLibroPorTitutlo
*/
