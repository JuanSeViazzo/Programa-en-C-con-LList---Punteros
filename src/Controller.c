#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "parser.h"
#include "inputsGets.h"
#include "Libros.h"
#include <string.h>

int menu()
{

  int opcion = 0;
  printf("..............................................\n"
		  "                 Archivo de Libros               \n"
		  ".............................................\n\n"
		  "1. Cargar los datos de los Libros desde el archivo Libros.csv (modo texto).\n"
		  "2. Imprimir lista ordenada por Autor\n"
		  "3. Imprimir todos los datos de los libros\n"
		  "4. Descuentos por Editoriales\n"
		  "5. Generar archivo de salida mapeado\n"
		  "6. Filtrar por autor la lista mapeada\n"
		  "6. Filtrar por editorial de Minotauro\n"
		  "7. Generar archivos con editorial de Minotauro.\n"
		  "8. Guardar los datos de los Libros en el archivo Libros.csv (modo texto).\n"
		  "9. Salir\n\n");

  utn_obtenerEnteroConReintentosMinMax(&opcion,"\nIngrese la opcion deseada: ","La opcion elegida es invalida",0,11,3);
  return opcion;
}






/** \brief Carga los datos de los Libros desde el archivo data.csv (modo texto).
 *
 * \param path char* nombre del archivo
 * \param pArrayListLibros LinkedList* linkedlist de los libros
 * \return int retorna -1 si hubo error, 0 si esta correcto
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListLibros)
{

	int estado=-1;

		FILE* pFileLibros; // para leer los Libros

		if(path!=NULL)
		{
			pFileLibros = fopen(path, "r");


				if(pFileLibros!=NULL)
				{

					if(parser_LibrosFromText(pFileLibros,pArrayListLibros)==0)
					{
						estado=0;
					}
				}else
				{
					printf("El archivo no se encuentra en la base de datos");
				}

				fclose(pFileLibros);

		}else
		{
			printf("El archivo no existe");
		}

    return estado;
}

/** \brief Carga los datos de los Libros desde el archivo data.csv (modo pFileario).
 *
 * \param path char* nombre del archivo
 * \param pArrayListLibros LinkedList* linkedlist de los libros
 * \return int retorna -1 si hubo error, 0 si esta correcto
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListLibros)
{

	int estado=-1;

		FILE* pFileLibros; // para leer los Libros


		pFileLibros = fopen(path, "rb");


		if(pFileLibros!=NULL)
		{
			parser_LibrosFromBinary(pFileLibros,pArrayListLibros);
			estado=0;
		}else
		{
			printf("El archivo no existe");
		}

		fclose(pFileLibros);

	return estado;

}

/** \brief Listar Libros, muestra los libros en forma de lista por columnas
 *
 * \param pArrayListLibros LinkedList* linkedlist de los libros
 * \return estado, retorna -1 si hubo error, 0 si esta bien.
 *
 */
int controller_ListLibros(LinkedList* pArrayListLibros)
{
    int estado=-1;
    int index;
    Libros* auxLibros;
    int lenLista;


    if(pArrayListLibros!=NULL)
    {
    	lenLista=ll_len(pArrayListLibros);

    	if(lenLista>0)
    	{
			for(index=0;index<lenLista;index++)
			  {
				auxLibros=ll_get(pArrayListLibros,index);

				if(auxLibros!=NULL)
					Libros_printLibros(auxLibros);

				estado=0;
			  }
		 }else
			 puts("No hay libros cargados");
    }

		return estado;
}







/**\brief ordena los libros, utilizando ll_sort y se pasa una funcion criterio como parametro.
 *
 * @param pArrayListLibros LinkedList* linkedlist de los libros
 * @return estado, retorna -1 si hubo error, 0 si esta bien.
 */
int controller_sortLibros(LinkedList* pArrayListLibros)
{
    int retorno=-1;
	//int option;
	int lenght;
	//int optionSeg;

	lenght=ll_len(pArrayListLibros);


	if(lenght>0)
	{
		ll_sort(pArrayListLibros,Libros_sortAutor,0);

		/*printf("Elija la opcion para el criterio de orden?\n"
				" 1)ID\n"
				" 2)titulo\n"
				" 3)autor\n"
				" 4)precio\n"
				" 5)editorialId\n"
				" 6)Volver al menu principal\n");

		if(utn_obtenerEnteroConReintentosMinMax(&option,"Ingrese la opcion elegida: ","Error",0,6,3)==0)
		{
			printf("Elija la opcion 0 de menor a mayor, y la opcion 1 de mayor a menor\n");
			utn_obtenerEnteroConReintentosMinMax(&optionSeg,"Ingrese la opcion elegida: ","Error",0,1,3);

		    if (pArrayListLibros!=NULL)
		    {

		    	switch (option)
		    	{
		    	case 1:
		    		printf("\n ordenando...\n");
		    		printf("\n ordenando...\n");
		    		ll_sort(pArrayListLibros,Libros_sortId,optionSeg); // 0 menor a mayor, 1 mayor a menor.
		    		printf("\nLista ordenada por ID\n");
		    		retorno=0;
		    		break;
		    	case 2:
		    		printf("\n ordenando...\n");
		    		printf("\n ordenando...\n");
		    		ll_sort(pArrayListLibros,Libros_sortTitulo,optionSeg);
		    		printf("\nLista ordenada por Titulo\n");
		    		retorno=0;
		    		break;
		    	case 3:
		    		printf("\n ordenando...\n");
		    		printf("\n ordenando...\n");
		    		ll_sort(pArrayListLibros,Libros_sortAutor,optionSeg);
		    		printf("\nLista ordenada por autor \n");
		    		retorno=0;
		    		break;
		    	case 4:
		    		printf("\n ordenando...\n");
		    		printf("\n ordenando...\n");
		    		ll_sort(pArrayListLibros,Libros_sortPrecio,optionSeg);
		    		printf("\nLista ordenada por Precio\n");
		    		retorno=0;
		    		break;
		    	case 5:
		    		printf("\n ordenando...\n");
		    		printf("\n ordenando...\n");
		    		ll_sort(pArrayListLibros,Libros_sortEditorial,optionSeg);
		    		printf("\nLista ordenada por Editorial\n");
		    		retorno=0;
		    		break;
		    	case 6:
		    		printf("\n regreso al menu principal");
		    		retorno=0;
		    		break;
		    	}
		    }
		}*/
	}else
	{
		printf("\nNo hay Libros cargados para ordenar\n");
	}

    return retorno;
}

/** \brief Guarda los datos de los Libros en el archivo path.csv (modo texto).
 *
 * @param path, se pasa por parametro el nombre del archivo
 * @param pArrayListLibros lista dinamica de los libros
 * @return estado, -1 si hubo ERROR, 0 si esta correcto.
 */
int controller_saveAsText(char* path , LinkedList* pArrayListLibros)
{
  int estado=-1;
  FILE* pFile;
  Libros* bufferLibros;
  int precio;
  int id;
  char titulo[LEN_NOMBRE];
  char autor[LEN_NOMBRE];
  char editorial[LEN_NOMBRE];
  int index;
  int ll_tam;


	  if(path!=NULL && pArrayListLibros!=NULL)
	  {

		  ll_tam=ll_len(pArrayListLibros);

		if(ll_tam>0)
		{
			 pFile = fopen(path,"w");
			 if(pFile!=NULL)
			 {
				 fprintf(pFile,"id,titulo,autor,precio,editorial\n");
				 for(index=0;index<ll_tam;index++)
				 {
					 bufferLibros=(Libros*) ll_get(pArrayListLibros,index);
					 if(bufferLibros!=NULL)
					 {
						 Libros_getIdInt(bufferLibros, &id);
						 Libros_getTitulo(bufferLibros, titulo);
						 Libros_getAutor(bufferLibros, autor);
						 Libros_getPrecio(bufferLibros, &precio);
						 Libros_getIdEditorial(bufferLibros, editorial);


						  fprintf(pFile,"%d,%s,%s,%d,%s\n",id,titulo,autor,precio,editorial);
						  estado =0;
					 }

				  }
			  fclose(pFile);

			}
		}
	  }

		  if(estado==0)
		  puts("Guardando.......................\nGuardando.......................\ndatos guardados\n");
		  else
		  puts("Guardando.......................\nGuardando.......................\nNo se pudo guardar\n");



return estado;
}

/** \brief Guarda los datos de los Libros en el archivo path.csv (modo binario).
 * @param path, se pasa por parametro el nombre del archivo
 * @param pArrayListLibros lista dinamica de los libros
 * @return estado, -1 si hubo ERROR, 0 si esta correcto.
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListLibros)
{
	int estado = -1;
	FILE* pFile;
	Libros* bufferLibros;
	int ll_tam=-1;
	int index;

	if(path!=NULL && pArrayListLibros!=NULL)
	 {

		ll_tam=ll_len(pArrayListLibros);
		if(ll_tam>=0)
		{

			if((pFile = fopen(path,"w+b"))!=NULL)
			{

				for(index=0;index<ll_tam;index++)
				{

					bufferLibros=ll_get(pArrayListLibros,index);
					if(bufferLibros!=NULL)
					{

						fwrite(bufferLibros,sizeof(Libros),1,pFile);
						estado=0;

					}
				}
			fclose(pFile);
			}
		 }
	 }
	if(estado==0)
		puts("Datos guardados");
	else
		puts("No se pudo guardar");





    return estado;
}
/**@brief es la funcion donde se utiliza ll_map para mapear, y recibe por parametro la funcion para aplicar el descuento
 * @param pArrayListLibros lista dinamica de los libros
 */
int controller_EditorialConDescuento(LinkedList* pArrayListLibros)
{
	int retorno = 0;
	int length;

	if(pArrayListLibros!=NULL)
	{
		length=ll_len(pArrayListLibros);

		if(length>0)
		{

			if(!ll_map(pArrayListLibros,libros_EditorialConDescuento))
			{
				puts("Procesando descuento");
				puts(".....................");
				puts("Procesando descuento");
				puts(".....................");
				puts("Descuento Realizado");
			}

		}
	}

	return retorno;
}

/**
 * @brief obtengo la linkedlist, la recorro y voy uno por uno comparando, si hay igual salgo, sino sigo y lo muestro
 * @param pListLibros
 * @return retorno 1 si la lista no es NULL, 0 si esta ok, -1 si Hay error.
 */
int controller_listaAutor(LinkedList* pListLibros)
{
	int index;
	int j;
	int banderaHay;
	Libros* pLibroUno;
	Libros* pLibroDos;
	char nombreAutor[LEN_NOMBRE];
	char nombreAutorDos[LEN_NOMBRE];
	int retorno = -1;
	int length;
	int contador=0;

	length=ll_len(pListLibros);

	if(pListLibros != NULL)
	{

		retorno = 1;
		for(index = 0; index < length; index++)
		{

			pLibroUno = (Libros*)ll_get(pListLibros, index);
			if(pLibroUno != NULL)
			{
				if(!Libros_getAutor(pLibroUno, nombreAutor))
				{
					banderaHay = 0;
					for(j = 0; j < index ; j++)
					{
						pLibroDos = (Libros*)ll_get(pListLibros, j);
						if(pLibroDos != NULL)
						{
							if(!Libros_getAutor(pLibroDos, nombreAutorDos))
							{
								if(strcmp(nombreAutor, nombreAutorDos)==0)
								{
									banderaHay = 1;
									break;
								}
							}
						}
					}
					if(banderaHay == 0)
					{
						retorno=0;
						contador++;
						printf("\n%d, %s",contador,nombreAutor);
					}
				}
			}
		}
	}
	return retorno;
}
