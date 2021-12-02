#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Libros.h"
#include <string.h>
#include "inputsGets.h"

/****************************************************
    1) LEER Libros DESDE ARCHIVO CSV
Se lee de archivo Libros.csv provisto, la Lista de Libros del sistema, y se cargan en una LinkedLIst.
2) INCORPORAR ARCADE
Se da de alta un arcade con la nacionalidad, tipo de sonido, cantidad de jugadores, capacidad m��xima de
fichas, Nombre del sal��n al que pertenece y nombre del juego que contiene (hasta 63 caracteres).
Se generar�� un ID ��nico para gestionar los ARCADE. Actualizar el archivo CSV con el arcade agregado
3) MODIFICAR ARCADE
Se imprime la Lista de Libros con los ID y datos que lo componen.
Se pide que se ingrese un ID y se pueda modificar los campos cantidad de jugadores o juego que contiene.
Al elegir modificar el juego que contiene este arcade, mostrar en un listado los nombres de los juegos ya
cargados en el sistema y se permitir�� ingresar un texto con el nombre del nuevo juego. Actualizar el archivo CSV con
el arcade modificado.
4) ELIMINAR ARCADE
Se imprime la Lista de Libros con sus ID y datos que lo componen, junto con la informaci��n del sal��n y el
juego que contiene.
Se ingresa un ID y previo a dar de baja se deber�� solicitar confirmaci��n, imprimiendo el arcade a dar de baja y
confirmando si est�� seguro dar de baja est�� mismo. Actualizar el archivo CSV con el arcade aeliminado.
5) IMPRIMIR Libros ordenados por nombre de juego
Se imprime la Lista de Libros con ID, y sus datos.
6) Generar archivo con JUEGOS
Se generar�� un archivo .txt con los nombres de los juegos (uno por linea) sin repetir.
7) Generar un archivo con Libros ���Multijugador��� (mas de 1 jugador)
Se generar�� un archivo ���multijugador.csv��� con el mismo formato que Libros.csv (incluida la cabecera), que
contenga solo los Libros que tengan mas de 1 jugador.
8) Actualizar cantidad de fichas
La empresa compr�� una actualizacion para que los Libros soporten el doble de fichas, por lo que debe
actualizarse el valor de fichas en el archivo. Al elegir esta opcion, se duplicar�� el valor de cantidad de fichas de todos
los Libros.
DATOS
TIPOS DE SONIDO PARA ARCADE
MONO
EST��REO
Un arcade solo pertenece a un solo sal��n.
Un arcade solo contiene un juego.
Utilizar LinkedList para la Lista de Libros.
Implementar y utilizar la funcion ll_filter para el punto 7.
Implementar y utilizar la funcion ll_sort para el punto 5.
Implementar y utilizar la funcion ll_map para el punto 8.
Generar un ID auto incrementable para cada entidad.
Tratar a el ���tipo��� sonido como valor num��ricos relacionado con DEFINE.
Nota 1: Se deber��n desarrollar bibliotecas por cada entidad las cuales contendr��n las funciones (Alta, Baja, Modificar, etc.).
Los informes deber��n estar en una biblioteca aparte.
Nota 2: El c��digo deber�� tener comentarios con la documentaci��n de cada una de las funciones y respetar las reglas de estilo
de la c��tedra.
*****************************************************/



int main()
{

	setbuf(stdout,NULL);
	int flagCarga=0;
	int flagMinotauro=0;
    int option = 0;
    int flagDescuento=0;
   // char pResultado[100];
    int banderaListAutor=0;
    int puntoCuatro=0;
    LinkedList* listaLibros = ll_newLinkedList();
    LinkedList* listaAuxLibrosMinotauro;
    LinkedList* listaAuxLibrosDescuentos;
    LinkedList* listaAuxAutores;


    do{
    	option = menu();
    	switch(option)
    	        {
    	            case 1:
    	            	if(flagCarga==0)
    	            	{
    	            		/*utn_obtenerTextoconReintentos(pResultado,100, "Ingrese el nombre del archivo: ______ .csv: ","Nombre invalido",3);

    	            		if (!strcmp(pResultado,"libros") || !strcmp(pResultado,"mapeado")||!strcmp(pResultado,"minotauroLibros"))
    	            		{
    	            			if(controller_loadFromText(strcat(pResultado,".csv"),listaLibros)==0)
								{
									puts("----LA CARGA SE REALIZO CORRECTAMENTE----");
								}
							}else
								puts("El archivo no ha sido generado");*/

	            			if(controller_loadFromText("libros.csv",listaLibros)==0)
	            			{
								puts("----LA CARGA SE REALIZO CORRECTAMENTE----");
								flagCarga=1;
	            			}
						}else
							puts("Ya se ha cargado el archivo");

    	            break;
    	            case 2:
    	            	controller_sortLibros(listaLibros);
    	            	controller_ListLibros(listaLibros);
    	            break;
    	            case 3:
    	            	puts("------Lista de Libros-----");
    	            	controller_ListLibros(listaLibros);
    	            break;

    	            case 4:
    	            	if(puntoCuatro==1)
    	            	ll_clear(listaAuxLibrosDescuentos);
    	            	{
        	                listaAuxLibrosDescuentos=ll_clone(listaLibros);
        	                controller_EditorialConDescuento(listaAuxLibrosDescuentos);
        	            	puts("------Lista de Libros Con Descuento-----");
        	            	controller_ListLibros(listaAuxLibrosDescuentos);
        	            	flagDescuento=1;
        	            	banderaListAutor=1;
        	            	puntoCuatro=1;
    	            	}

					break;
    	            case 5:
    	            	if(flagDescuento==0)
						{
    	            		puts("Primero debera realizar el punto 4");
						}else
							controller_saveAsText("mapeado.csv",listaAuxLibrosDescuentos);
    	            break;
    	            case 6:
    	            	if(banderaListAutor==1)
    	            	{
    	            		controller_listaAutor(listaAuxLibrosDescuentos);
    	            		listaAuxAutores=ll_clone(listaAuxLibrosDescuentos);
							ll_filter(listaAuxAutores,libros_filterAutor);
							puts("------Lista de Libros Filtrada por Autor-----");
							controller_ListLibros(listaAuxAutores);
							banderaListAutor=0;
							controller_saveAsText("descuentoAutor.csv",listaAuxAutores);

    	            	}else
    	            		puts("No puede realizar el paso, ya ha generado el archivo, descuento por autor");

    	            break;
    	            case 7:
							listaAuxLibrosMinotauro=ll_clone(listaLibros);
							ll_filter(listaAuxLibrosMinotauro, libros_filterEditorial);
							puts("------Lista de Libros Editorial Minotauro-----");
							controller_ListLibros(listaAuxLibrosMinotauro);
							flagMinotauro=1;
    	            break;
    	            case 8:
							if(flagMinotauro==0)
								puts("Primero debera realizar el punto 6");
							else
								controller_saveAsText("minotauroLibros.csv",listaAuxLibrosMinotauro);
					break;
    	            case 9:
							if(flagCarga==0)
								puts("Primero debera realizar la carga para guardar el archivo");
							else
								controller_saveAsText("Libros",listaLibros);

    	            break;

    	        }

    }while(option != 10);
    return 0;
}

