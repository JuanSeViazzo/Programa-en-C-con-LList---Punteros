#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "parser.h"
#include "inputsGets.h"
#include "Libros.h"

int menu()
{

  int opcion = 0;
  printf("..............................................\n"
		  "                 Archivo de Libros               \n"
		  ".............................................\n\n"
		  "1. Cargar los datos de los Libros desde el archivo Libros.csv (modo texto).\n"
		  "2. Imprimir lista ordenada por Autor\n"
		  "3. Imprimir todos los datoss de los libros\n"
		  "4. Descuentos por Editoriales\n"
		  "5. Generar archivo de salida mapeado\n"
		  "6. Filtrar por editorial de Minotauro\n"
		  "7. Generar archivos con editorial de Minotauro.\n"
		  "8. Guardar los datos de los Libros en el archivo Libros.csv (modo texto).\n"
		  "9. Salir\n\n");

  utn_obtenerEnteroConReintentosMinMax(&opcion,"\nIngrese la opcion deseada: ","La opcion elegida es invalida",0,11,3);
  return opcion;
}






/** \brief Carga los datos de los Libros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListLibros LinkedList*
 * \return int
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
 * \param path char*
 * \param pArrayListLibros LinkedList*
 * \return int
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

/** \brief Alta de Libros
 *
 * \param path char*
 * \param pArrayListLibros LinkedList*
 * \return int
 *
 */

static int createId(void)
{
    static int createId = 1000;

    createId++;

    return createId;

}
/**
 *
 * @param pArrayListLibros
 * @return
 */

int controller_addLibros(LinkedList* pArrayListLibros)
{
	int estado = -1;
	int precio;
	int id;
	char titulo[LEN_NOMBRE];
	char autor[LEN_NOMBRE];
	char editorial[LEN_NOMBRE];
	Libros* auxLibros;

	auxLibros=Libros_new();
	//id	titulo	autor	precio	editorialId

	if (pArrayListLibros!=NULL)
	{
		utn_getDescripcion(titulo,LEN_NOMBRE, "ingrese el titulo: ","Dato Invalido\n",3);
		utn_getDescripcion(autor,LEN_NOMBRE, "ingrese la Nacionalidad: ","Dato Invalido\n",3);
		utn_obtenerNumeroEntero(&precio, "Ingrese la cantidad maxima de fichas: ", "Dato invalido\n");
		utn_getDescripcion(editorial,LEN_NOMBRE, "ingrese la Nacionalidad: ","Dato Invalido\n",3);

		id=createId();
		Libros_setTitulo(auxLibros, titulo);
		Libros_setAutor(auxLibros, autor);
		Libros_setPrecio(auxLibros, precio);
		Libros_setIdEditorialTxt(auxLibros, editorial);
		Libros_setIdInt(auxLibros,id);
		estado = 0;

		ll_add(pArrayListLibros,auxLibros);


	}
	return estado;
}

/** \brief Modificar datos de Libro
 *
 * \param path char*
 * \param pArrayListLibros LinkedList*
 * \return int
 *
 */
int controller_editLibros(LinkedList* pArrayListLibros)
{

	int estado = -1;
	int bufferIndex;
	int id;
	int option;
	int precio;
	char titulo[LEN_NOMBRE];
	char autor[LEN_NOMBRE];
	char editorial[LEN_NOMBRE];
	Libros* auxLibros;
	int lenLista;

	lenLista=ll_len(pArrayListLibros);


	if(lenLista>0)
	{
		if(pArrayListLibros!=NULL)
		{
			if(utn_obtenerEnteroConReintentos(&id, "Por favor ingrese el ID: ","Dato invalido",3)==0)
			{
				printf("ID cargado %d \n",id);
			}else
			{
				printf("ID no encontrado, reintentos maximos");
			}
		}
		if(id>=0)
		{
			bufferIndex=Libros_findById(pArrayListLibros,(id));

			auxLibros = ll_get(pArrayListLibros, bufferIndex);

			if(auxLibros!=NULL)
			{

				puts("Por favor ingrese la opcion que desea modificar: 1: Titulo, 2: Autor, 3: Precio, 4: Editorial");

				if(utn_obtenerEnteroConReintentos(&option, "Por favor ingrese la opcion: ","Dato invalido",3)==0)
				{

					printf("opcion elegida: %d \n",option);
				}else
				{
					printf("opcion no valida, reintentos maximos");
				}

				switch (option)

				{
					case 1:

						if(utn_getDescripcion(titulo,256, "ingrese el titulo: ","Dato Invalido",3)==0)
							Libros_setTitulo(auxLibros, titulo);
						else
							puts("No se pudo cambiar el titulo");

						break;
					case 2:
							if(utn_getDescripcion(autor,256, "ingrese el autor: ","Dato Invalido",3)==0)
								Libros_setAutor(auxLibros, autor);
							else
								puts("No se pudo cambiar el autor");

						break;
					case 3:
						if(utn_obtenerEnteroConReintentos(&precio, "\nIngrese el precio: ", "Dato invalido",3)==0)
								Libros_setPrecio(auxLibros,precio);
							else
								puts("No se pudo cambiar el precio");
					break;
					case 4:
						if(utn_getDescripcion(editorial,256, "ingrese el titulo: ","Dato Invalido",3)==0)
							Libros_setIdEditorialTxt(auxLibros, editorial);
						else
							puts("No se pudo cambiar la editorial");
					break;

						estado=0;
				}
			}
		}
	}
return estado;
}


/** \brief Baja de Libro
 *
 * \param path char*
 * \param pArrayListLibros LinkedList*
 * \return int
 *
 */
int controller_removeLibros(LinkedList* pArrayListLibros)
{

	int bufferIndex;
	Libros* auxLibros;
	int estado=-1;
	int id;

	if(pArrayListLibros!=NULL)
	{
		if(utn_obtenerEnteroConReintentos(&id, "Por favor ingrese el ID: ","Dato invalido",3)==0)
		{
			printf("ID cargado: %d\n",id);
		}else
		{

			printf("ID no encontrado, reintentos maximos");
		}
	}
	if(id>0)

	{

		bufferIndex=Libros_findById(pArrayListLibros,id);
		printf("%d\n",bufferIndex);

		//bufferIndex=bufferIndex-1;
		auxLibros = ll_get(pArrayListLibros, (bufferIndex));


		if(auxLibros!=NULL)
		{

			ll_remove(pArrayListLibros,bufferIndex);

			free(auxLibros);


			estado=0;
		}

	}

    return estado;
}

/** \brief Listar Libros
 *
 * \param path char*
 * \param pArrayListLibros LinkedList*
 * \return int
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







/** \brief Ordenar Libros
 *
 * \param path char*
 * \param pArrayListLibros LinkedList*
 * \return int
 *
 */
int controller_sortLibros(LinkedList* pArrayListLibros)
{
    int retorno=-1;
	int option;
	int lenght;
	int optionSeg;

	lenght=ll_len(pArrayListLibros);


	if(lenght>0)
	{
		printf("Elija la opcion para el criterio de orden?\n"
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
		}
	}else
	{
		printf("\nNo hay Libros cargados para ordenar\n");
	}

    return retorno;
}


/** \brief Guarda los datos de los Libros en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListLibros LinkedList*
 * \return int
 *
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

/** \brief Guarda los datos de los Libros en el archivo data.csv (modo pFileario).
 *
 * \param path char*
 * \param pArrayListLibros LinkedList*
 * \return int
 *
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
/**
 *
 * @param pArrayListLibros
 * @return
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
