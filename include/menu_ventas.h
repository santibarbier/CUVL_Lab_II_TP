#ifndef MENU_VENTAS_H_
#define MENU_VENTAS_H_

typedef enum VENTAS_OP {END_VENTAS, LISTAR, BUSCAR_ISBN, BUSCAR_TITULO, BUSCAR_AUTOR} VENTAS_OP;
typedef enum VENTAS_ERRORS {ERR_VENTAS_OK, ERR_INVALID_VENTAS} VENTAS_ERRORS;
void ventasMenu();
VENTAS_ERRORS validVentasOption(enum VENTAS_OP option);

#endif // MENU_VENTAS_H_