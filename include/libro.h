#ifndef ALTA_LIBRO_H_
#define ALTA_LIBRO_H_


typedef struct ST_AUTOR
{
    char nombre[20];
    char apellido[20];
} ST_AUTOR;

typedef struct ST_LIBRO
{
    char titulo[50];
    ST_AUTOR autor;
    double precio;
    int isbn;
    int stockDisponible;
    int stockReservado;
} ST_LIBRO;

FILE* abrirArchivoLibros(const char* modo);
void iniciarLibro( ST_LIBRO *Libro, const char *titulo, const char *nombreAutor, const char *apellidoAutor, double precio,int isbn, int stockDisponible, int stockReservado);
void nuevoLibro();
void listarLibros();
void imprimirLibro(long pos);
#endif // ALTA_LIBRO_H_
