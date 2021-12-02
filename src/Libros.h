#ifndef Libros_H_INCLUDED
#define Libros_H_INCLUDED
#define LEN_NOMBRE 256
#include "LinkedList.h"

typedef struct
{
    int id;
    char titulo[LEN_NOMBRE];
    int precio;
    char autor[LEN_NOMBRE];
    char editorial[LEN_NOMBRE];
    int idEditorial;

    //auxId,auxTitulo,auxPrecio,auxCantJugadores,auxFichasMax,auxSalon,auxGame
}Libros;

Libros* Libros_new(void);

Libros* Libros_newParametros(char* id,char* titulo,char* autor,char* precio,char* editorial);

void Libros_delete(Libros* pLibro);

int Libros_setIdInt(Libros* pLibro,int id);

int Libros_printLibros(Libros* pLibro);

int Libros_setIdTxt(Libros* pLibro, char* id);

int Libros_getIdInt(Libros* pLibro,int* id);

int Libros_getIdTxt(Libros* pLibro, char* id);

int Libros_setTitulo(Libros* pLibro,char* nacionalidad); //set para escribir en la posicion

int Libros_getTitulo(Libros* pLibro,char* nacionalidad); //get para leer de la posicion.

int Libros_setPrecioTxt(Libros* pLibro, char* precio);

int Libros_setPrecio(Libros* pLibro,int precio);

int Libros_getPrecio(Libros* pLibro,int* precio);

int Libros_setAutor(Libros* pLibro,char* nombreSalon); //set para escribir en la posicion

int Libros_getAutor(Libros* pLibro,char* nombreSalon); //get para leer de la posicion.

int Libros_setIdEditorialTxt(Libros* pLibro, char* idEditorial);

int Libros_setIdEditorial(Libros* pLibro,int idEditorial);

int Libros_getIdEditorial(Libros* pLibro,char* idEditorial);

int Libros_getEditorial(Libros* pLibro,int* idEditorial);

int Libros_findById(LinkedList* pListLibros,int id);

void showLibros(Libros* pArrayList);

int Libros_sortId(void* parametroUno,void* parametroDos);

int Libros_sortHoras(void* parametroUno,void* parametroDos);

int Libros_sortPrecio(void* parametroUno,void* parametroDos);

int Libros_sortTitulo(void* parametroUno,void* parametroDos);

int Libros_sortAutor(void* parametroUno,void* parametroDos);

int Libros_sortEditorial(void* parametroUno,void* parametroDos);

int libros_filterEditorial(void* pLibro);

int libros_EditorialConDescuento(void* pLibro);

#endif /* Libros_H_ */
