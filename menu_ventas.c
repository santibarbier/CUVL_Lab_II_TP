#include "ayuda.h"
#include "menu_ventas.h"
#include "libro.h"

#include <stdio.h>

/*
VENTA DE EJEMPLARES
Este es el apartado que el operador utilizará para informarle al sistema qué libros serán vendidos

1. La operatoria común consiste en identificar los libros que se venderán, para lo cual el
usuario se valdrá de un listado sobre el que podrá realizar búsquedas, y luego ingresar
al sistema todos los ISBN para venderlos.

2. Los datos que deben mostrarse en el listado son: nombre del libro, autor, ISBN, precio y
si el artículo se encuentra en stock.

3. Si uno de los artículos no se encuentra en stock, el sistema deberá informarlo para que
se excluya de la operación.

4. Por políticas empresariales, únicamente puede venderse un único ejemplar de cada
libro por transacción.

5. Cuando el vendedor haya ingresado todos los ISBN, el sistema deberá mostrar un
resumen de los artículos que serán vendidos y aguardará a que el vendedor confirme la operación.

6. Las operaciones canceladas dejarán sin efecto la venta y deberá regresar al menú
principal del apartado.

7. Si se confirma, el paso siguiente será generar la factura digital (archivo de texto) e
incrementar en uno el stock reservado para cada uno de los libros involucrados.

8. Una vez generada la factura el sistema solicitará que se informe el modo de entrega de los ítems:
    - Retirar el libro por sucursal: los datos de la venta deberán ser agregados a una lista.
    - Envío a domicilio: el pedido será ingresado a una cola de espera de modo tal
    que se despachen por orden de generación de venta.
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
