#include "ayuda.h"
#include "menu_ventas.h"
#include "libro.h"

#include <stdio.h>

/*
VENTA DE EJEMPLARES
Este es el apartado que el operador utilizar� para informarle al sistema qu� libros ser�n vendidos

1. La operatoria com�n consiste en identificar los libros que se vender�n, para lo cual el
usuario se valdr� de un listado sobre el que podr� realizar b�squedas, y luego ingresar
al sistema todos los ISBN para venderlos.

2. Los datos que deben mostrarse en el listado son: nombre del libro, autor, ISBN, precio y
si el art�culo se encuentra en stock.

3. Si uno de los art�culos no se encuentra en stock, el sistema deber� informarlo para que
se excluya de la operaci�n.

4. Por pol�ticas empresariales, �nicamente puede venderse un �nico ejemplar de cada
libro por transacci�n.

5. Cuando el vendedor haya ingresado todos los ISBN, el sistema deber� mostrar un
resumen de los art�culos que ser�n vendidos y aguardar� a que el vendedor confirme la operaci�n.

6. Las operaciones canceladas dejar�n sin efecto la venta y deber� regresar al men�
principal del apartado.

7. Si se confirma, el paso siguiente ser� generar la factura digital (archivo de texto) e
incrementar en uno el stock reservado para cada uno de los libros involucrados.

8. Una vez generada la factura el sistema solicitar� que se informe el modo de entrega de los �tems:
    - Retirar el libro por sucursal: los datos de la venta deber�n ser agregados a una lista.
    - Env�o a domicilio: el pedido ser� ingresado a una cola de espera de modo tal
    que se despachen por orden de generaci�n de venta.
*/

void menuVentas()
{
    limpiarPantalla();
    printf("MENU PRINCIPAL -> VENTAS\n\n");
    // listar libros: titulo, autor, isbn, precio y stock
    imprimirListadoDeLibros();
    // seleccionar libros por isbn y meterlos a una lista, excluir libros sin stock, solo se puede vender un ejemplar por libro
    // al finalizar el ingreso, mostrar resumen y pedir confirmacion
    // si se confirma, generar factura.txt e incrementar en uno el stock reservado para cada libro
    // RETIRO: agregar a una lista
    // ENVIO: agergar a una cola
    presioneUnaTeclaParaContinuar();
}
