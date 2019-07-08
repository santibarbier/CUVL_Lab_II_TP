# Todo:
- [x] @COMPLETED cancelar ingreso de nuevo libro
- [ ] cuando se editan libros al finalizar imprimir como estaba y como quedo el libro
- [ ] @FIX no se tendrian que poder meter libros con mismo ISBN
- [x] @COMPLETED pulido de menues:
  - [x] @COMPLETED limpiar pantalla cada vez que se selecciona una opcion dentro de un submenu
  - [x] @COMPLETED imprimir cuando no se encuentra un libro
  - [x] @COMPLETED submenu para buscar
- [x] @COMPLETED usar strstr en busqueda de libros
- [ ] usar strncpy en inicializacion de libros
- [x] @COMPLETED @FIX la busqueda de libros es case-sensitive
- [x] @COMPLETED buscarLibro() se tendria que separar en varias funciones:
  - [x] @COMPLETED buscarLibroPorTitutlo()
  - [x] @COMPLETED buscarLibroPorAutorNombre()
  - [x] @COMPLETED buscarLibroPorAutorApellido()
- [ ] @POSTPONED hacer que funque en linux?
  - [ ] no usar:
    - [ ] fflush()
    - [ ] getch()
- [ ] @POSTPONED ayuda.h
  - [ ] limpiarPantalla()
  - [ ] saltoDeLinea()
  - [ ] indentar()
  - [ ] tomarCaracter()
  - [ ] tomarEntero() `{ return tomarCaracter() - '0'; }`

# Enunciado
- Las tres tareas principales sobre el que se apoya el proceso de venta son:
1. **Gestión libros:** *darlos de alta en el sistema, listarlos, editarlos y eliminarlos.
   1. Los artículos creados deben guardarse en un archivo binario; en lo particular, éste deberá mantenerse actualizado cada vez que se realicen tareas de modificación o eliminación sobre los libros.
   2. Al momento de listar los libros, es importante que el sistema permita realizar búsquedas a través del ISBN, título y autor; la búsqueda por ISBN debe ser exacta, mientras que en el caso del título y del autor debe admitir la búsqueda parcial del texto.
   3. Al momento de editar los datos de un libro, el usuario debe poder ver el "antes y el después" como paso previo a la confirmación (o cancelación) de los cambios.*
   - Todo:
     - [x] @COMPLETED Alta
     - [x] @COMPLETED Listar
     - [x] @COMPLETED Editarlos
     - [x] @COMPLETED Eliminarlos por ISBN
     - [x] @COMPLETED Busqueda (exacta) por ISBN
     - [x] @COMPLETED Busqueda (parcial) por titulo
     - [x] @COMPLETED Busqueda (parcial) por autor
2. **Venta de ejemplares:**  *operador utilizará para informarle al sistema qué libros serán vendidos.*
3. **Entrega de artículos comprados:**