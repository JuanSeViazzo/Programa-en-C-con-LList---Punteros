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
Se da de alta un arcade con la nacionalidad, tipo de sonido, cantidad de jugadores, capacidad máxima de
fichas, Nombre del salón al que pertenece y nombre del juego que contiene (hasta 63 caracteres).
Se generará un ID único para gestionar los ARCADE. Actualizar el archivo CSV con el arcade agregado
3) MODIFICAR ARCADE
Se imprime la Lista de Libros con los ID y datos que lo componen.
Se pide que se ingrese un ID y se pueda modificar los campos cantidad de jugadores o juego que contiene.
Al elegir modificar el juego que contiene este arcade, mostrar en un listado los nombres de los juegos ya
cargados en el sistema y se permitirá ingresar un texto con el nombre del nuevo juego. Actualizar el archivo CSV con
el arcade modificado.
4) ELIMINAR ARCADE
Se imprime la Lista de Libros con sus ID y datos que lo componen, junto con la información del salón y el
juego que contiene.
Se ingresa un ID y previo a dar de baja se deberá solicitar confirmación, imprimiendo el arcade a dar de baja y
confirmando si está seguro dar de baja esté mismo. Actualizar el archivo CSV con el arcade aeliminado.
5) IMPRIMIR Libros ordenados por nombre de juego
Se imprime la Lista de Libros con ID, y sus datos.
6) Generar archivo con JUEGOS
Se generará un archivo .txt con los nombres de los juegos (uno por linea) sin repetir.
7) Generar un archivo con Libros “Multijugador” (mas de 1 jugador)
Se generará un archivo “multijugador.csv” con el mismo formato que Libros.csv (incluida la cabecera), que
contenga solo los Libros que tengan mas de 1 jugador.
8) Actualizar cantidad de fichas
La empresa compró una actualizacion para que los Libros soporten el doble de fichas, por lo que debe
actualizarse el valor de fichas en el archivo. Al elegir esta opcion, se duplicará el valor de cantidad de fichas de todos
los Libros.
DATOS
TIPOS DE SONIDO PARA ARCADE
MONO
ESTÉREO
Un arcade solo pertenece a un solo salón.
Un arcade solo contiene un juego.
Utilizar LinkedList para la Lista de Libros.
Implementar y utilizar la funcion ll_filter para el punto 7.
Implementar y utilizar la funcion ll_sort para el punto 5.
Implementar y utilizar la funcion ll_map para el punto 8.
Generar un ID auto incrementable para cada entidad.
Tratar a el “tipo” sonido como valor numéricos relacionado con DEFINE.
Nota 1: Se deberán desarrollar bibliotecas por cada entidad las cuales contendrán las funciones (Alta, Baja, Modificar, etc.).
Los informes deberán estar en una biblioteca aparte.
Nota 2: El código deberá tener comentarios con la documentación de cada una de las funciones y respetar las reglas de estilo
de la cátedra.
*****************************************************/



int main()
{

	setbuf(stdout,NULL);
	int flagCarga=0;
	int flagMinotauro=0;
    int option = 0;
    int flagDescuento=0;
   // char pResultado[100];

    LinkedList* listaLibros = ll_newLinkedList();
    LinkedList* listaAuxLibrosMinotauro;
    LinkedList* listaAuxLibrosDescuentos;

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
    	            	controller_ListLibros(listaLibros);
    	            	controller_sortLibros(listaLibros);
    	            	controller_ListLibros(listaLibros);
    	            	//controller_addLibros(listaLibros);
    	            	break;
    	            case 3:
    	            	puts("------Lista de Libros-----");
    	            	controller_ListLibros(listaLibros);
    	            	//controller_editLibros(listaLibros);
    	            	break;
    	           /* case 4:
    	            	puts("------Lista de Libros-----");
    	            	controller_ListLibros(listaLibros);
    	            	controller_removeLibros(listaLibros);
    	            	break;*/
    	            case 4:
    	                listaAuxLibrosDescuentos=ll_clone(listaLibros);
    	                controller_EditorialConDescuento(listaAuxLibrosDescuentos);
    	            	puts("------Lista de Libros Con Descuento-----");
    	            	controller_ListLibros(listaAuxLibrosDescuentos);
    	            	flagDescuento=1;
						break;
    	            case 5:
    	            	if(flagDescuento==0)
						{
    	            		puts("Primero debera realizar el punto 6");
						}else
							controller_saveAsText("mapeado.csv",listaAuxLibrosDescuentos);
    	            	break;
    	            case 6:
    	                listaAuxLibrosMinotauro=ll_clone(listaLibros);
    	            	ll_filter(listaAuxLibrosMinotauro, libros_filterEditorial);
    	            	puts("------Lista de Libros Editorial Minotauro-----");
    	            	controller_ListLibros(listaAuxLibrosMinotauro);
    	            	flagMinotauro=1;
    	            	break;
    	            case 7:
    	            	if(flagMinotauro==0)
						{
						puts("Primero debera realizar el punto 6");
						}else
						controller_saveAsText("minotauroLibros.csv",listaAuxLibrosMinotauro);
						break;
    	            case 8:
						if(flagCarga==0)
						{
						puts("Primero debera realizar la carga para guardar el archivo");
						}else
						controller_saveAsText("Libros",listaLibros);
						break;
    	        }

    }while(option != 9);
    return 0;
}

