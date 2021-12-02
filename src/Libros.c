#include "Libros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>
#include "inputsGets.h"
#include <ctype.h>
#include <conio.h>
#define PLANETA 1
#define SIGLO_XXI_EDITORES 2
#define PEARSON 3
#define MINOTAURO 4
#define SALAMANDRA 5
#define PENGUIN_BOOKS 6

/**
 * @brief crea un nuevo elemento de la estructura libros.
 * @return pLibros, puntero al elemento.
 */

Libros* Libros_new(void)
{
	Libros* pLibros = (Libros*) malloc(sizeof(Libros));

	return pLibros;
}

/**
 * @brief funcion donde se reciben los datos desde parser(lectura del archivo) y se utilizan los seters para formar la entidad.
 * @param id dato ID del libro
 * @param titulo dato titulo del libro
 * @param autor del libro
 * @param precio del libro
 * @param editorial del libro
 * @return puntero a la entidad cargada.
 */

Libros* Libros_newParametros(char* id,char* titulo,char* autor,char* precio,char* editorial)
{

       Libros* pLibros = Libros_new();


       if(pLibros!=NULL && id!=NULL && titulo!=NULL && autor!=NULL  && precio!=NULL  && editorial!=NULL)
       {

    	   setlocale(LC_ALL, "");
    	   Libros_setAutor(pLibros, autor);
    	   Libros_setIdEditorialTxt(pLibros, editorial);
    	   Libros_setIdTxt(pLibros, id);
    	   Libros_setPrecioTxt(pLibros, precio);
    	   Libros_setTitulo(pLibros, titulo);

		  printf("Libro ID: %s - Titulo: %s - autor: %s - precio: %s - editorial: %s \n",id,titulo,autor,precio,editorial);

       }
return pLibros;
}



/**
 * @brief libera el espacio de memoria ocupado por la entidad.
 * @param pLibro puntero a la entidad pLibro.
 */

void Libros_delete(Libros* pLibro)
{

	if(pLibro!=NULL)
	{
		free(pLibro);
	}

}

/**
 * @brief guarda el campo id dentro de la entidad con el operador flecha.
 * @param pLibro puntero a la entidad.
 * @param id dato entero del id del libro
 * @return retorno, retorna -1 si hay ERROR, 0 si esta OK.
 */

int Libros_setIdInt(Libros* pLibro,int id)
{

	int retorno = -1 ;

	if(pLibro!= NULL && id>=0)
	{

		pLibro->id=id;
		retorno=0;
	}

return retorno;
}

/**
 * @brief funcion que utiliza los geters para obtener desde la entidad el campo que se mostrara en controller list
 * @param pLibro puntero a la entidad
 * @return retorna -1 en caso de ERROR y 0 en caso de funcionar correctamente.
 */

int Libros_printLibros(Libros* pLibro)
{
	int estado = -1;
    int precio;
    char autor[LEN_NOMBRE];
    char editorial[LEN_NOMBRE];
    int id;
    char titulo[LEN_NOMBRE];

    if(pLibro!=NULL)
    {
      if(Libros_getPrecio(pLibro, &precio)==0 &&
		Libros_getIdInt(pLibro,&id)==0 &&
		Libros_getAutor(pLibro, autor)==0 &&
		Libros_getIdEditorial(pLibro,editorial)==0 &&
		Libros_getTitulo(pLibro, titulo)==0)
        {
    		printf("Libro ID: %-2d	-	Titulo: %-50s  -	Autor: %-17s  -	Precio: %d	-	Editorial: %s\n",id,titulo,autor,precio,editorial);

    	    estado = 0;
        }
    }

    return estado;
}

/**
 * @brief guarda el campo id dentro de la entidad con el operador flecha.
 * @param pLibro puntero a la entidad.
 * @param id dato entero del id del libro
 * @return retorno, retorna -1 si hay ERROR, 0 si esta OK.
 */

int Libros_setIdTxt(Libros* pLibro, char* id)
{

	int retorno = -1;
	//int IdTrabj;
	int idAux;
	if(pLibro!= NULL && id!=NULL && (esNumerica(id)==0))
	{
		idAux=atoi(id);
		pLibro->id=idAux;
		retorno=0;
	}

	return retorno;
}

/**
 * @brief funcion para obtener el valor de la variable desde la entidad mediante operador ->
 * @param pLibro puntero a la entidad.
 * @param idLibro puntero al dato .
 * @return retorna -1 en caso de ERROR retorna 0 en caso de OK.
 */
int Libros_getIdInt(Libros* pLibro,int* idLibro)
{

	int retorno = -1 ;

	if(pLibro!= NULL && idLibro!=NULL)
	{
		*idLibro=pLibro->id;
		retorno=0;
	}

	return retorno;

}

/**
 * @brief funcion para obtener el valor de la variable desde la entidad mediante operador ->
 * @param pLibro puntero a la entidad.
 * @param idLibro puntero al dato .
 * @return retorna -1 en caso de ERROR retorna 0 en caso de OK.
 */

int Libros_getIdTxt(Libros* pLibro, char* id)
{

	int retorno = -1 ;

	if(pLibro!= NULL && (esNumerica(id)==0))
	{
		sprintf(id,"%d",pLibro->id);
		retorno=0;
	}

	return retorno;
}

/**
 * @brief guarda el campo titulo dentro de la entidad con el operador flecha.
 * @param pLibro puntero a la entidad.
 * @param titulo dato char del titulo del libro
 * @return retorno, retorna -1 si hay ERROR, 0 si esta OK.
 */

int Libros_setTitulo(Libros* pLibro,char* titulo) //set para escribir en la posicion
{

	int retorno = -1;

	if(pLibro!=NULL && titulo!=NULL)
	{
			strncpy(pLibro->titulo,titulo,LEN_NOMBRE);
			retorno = 0;
	}

return retorno;
}

/**
 * @brief funcion para obtener el valor de la variable desde la entidad mediante operador ->
 * @param pLibro puntero a la entidad.
 * @param idLibro puntero al dato.
 * @return retorna -1 en caso de ERROR retorna 0 en caso de OK.
 */
int Libros_getTitulo(Libros* pLibro,char* titulo) //get para leer de la posicion.
{
	int retorno = -1;

		if(pLibro!=NULL && titulo!=NULL)
		{
			retorno = 0;
			strncpy(titulo,pLibro->titulo,LEN_NOMBRE);

		}

	return retorno;
}

/**
 * @brief guarda el campo precio dentro de la entidad con el operador flecha.
 * @param pLibro puntero a la entidad.
 * @param titulo dato char del precio del libro
 * @return retorno, retorna -1 si hay ERROR, 0 si esta OK.
 */

int Libros_setPrecioTxt(Libros* pLibro, char* precio)
{

	int retorno = -1 ;
	int precioTrabj;


	if(pLibro!= NULL && precio!=NULL && precio>=0 &&(esNumerica(precio)==0))
	{
		precioTrabj=atoi(precio);
		pLibro->precio=precioTrabj;
		retorno=0;
	}

	return retorno;
}

/**
 * @brief guarda el campo precio dentro de la entidad con el operador flecha.
 * @param pLibro puntero a la entidad.
 * @param titulo dato int del precio del libro
 * @return retorno, retorna -1 si hay ERROR, 0 si esta OK.
 */

int Libros_setPrecio(Libros* pLibro,int precio)
{


	int retorno = -1 ;

	if(pLibro!= NULL && precio>=0)
	{

		pLibro->precio=precio;
		retorno=0;
	}

return retorno;
}



/**
 * @brief funcion para obtener el valor de la variable desde la entidad mediante operador ->
 * @param pLibro puntero a la entidad.
 * @param idLibro puntero al dato.
 * @return retorna -1 en caso de ERROR retorna 0 en caso de OK.
 */

int Libros_getPrecio(Libros* pLibro,int* precio)
{

	int retorno = -1 ;

	if(pLibro!= NULL && precio!=NULL)
	{

		*precio=pLibro->precio;
		retorno=0;
	}

	return retorno;
}


/**
 * @brief guarda el campo autor dentro de la entidad con el operador flecha.
 * @param pLibro puntero a la entidad.
 * @param titulo dato char del autor del libro
 * @return retorno, retorna -1 si hay ERROR, 0 si esta OK.
 */


int Libros_setAutor(Libros* pLibro,char* autor) //set para escribir en la posicion
{

	int retorno = -1;


	if(pLibro!=NULL && autor!=NULL && (esDescripcion(autor,LEN_NOMBRE)==0))
	{
			strncpy(pLibro->autor,autor,LEN_NOMBRE);
			retorno = 0;
	}

return retorno;
}


/**
 * @brief funcion para obtener el valor de la variable desde la entidad mediante operador ->
 * @param pLibro puntero a la entidad.
 * @param idLibro puntero al dato.
 * @return retorna -1 en caso de ERROR retorna 0 en caso de OK.
 */

int Libros_getAutor(Libros* pLibro,char* autor) //get para leer de la posicion.
{
	int retorno = -1;

		if(pLibro!=NULL && autor!=NULL)
		{
			retorno = 0;
			strncpy(autor,pLibro->autor,LEN_NOMBRE);

		}

	return retorno;
}



/**
 * @brief busca la posicion de una entidad en base a su ID.
 * @param pListLibros puntero a la lista
 * @param id valor del ID
 * @return retorna -1 en caso de ERROR retorna 0 en caso de OK.
 */

int Libros_findById(LinkedList* pListLibros,int id)
{
	int retorno = -1;
	int lenLibros;
	int i;
	Libros* auxLibros;
	int idLeido;

	if(pListLibros!=NULL && id>=0)
	{
		lenLibros=ll_len(pListLibros);

		for(i=0;i<lenLibros;i++)
		{
			auxLibros=ll_get(pListLibros,i);
			if(Libros_getIdInt(auxLibros,&idLeido)==0)
			{
				if(idLeido==id)
				{
					retorno = i;
					break;
				}
			}
		}
	}
return retorno;
}
/*


void showLibros(Libros* pArrayLibros)
{


  if(pArrayLibros!=NULL)
    {
      printf("\n%5d %10s %10s %15d %5s",pArrayLibros->id,pArrayLibros->titulo,pArrayLibros->autor,pArrayLibros->precio,pArrayLibros->editorial);
    }
  else
    {
      printf("\nNo se encontraron Libros para mostrar.");
    }
}*/

/**
 * @brief funcion para ordenar por ID.
 * @param parametroUno variable que le paso desde ll_sort a la funcion sortId
 * @param parametroDos variable que le paso desde ll_sort a la funcion sortId
 * @return retorna 1 si el elemento 1 es menor al 2, retorna -1 si el elemento 1 es mayor al 2.
 */

int Libros_sortId(void* parametroUno,void* parametroDos)
{
    int retorno;
    int idAuxUno;
    int idAuxDos;

    if(parametroUno!=NULL&&parametroDos!=NULL)
	{
		Libros_getIdInt((Libros*)parametroUno,&idAuxUno);
		Libros_getIdInt((Libros*)parametroDos,&idAuxDos);
		if (idAuxUno<idAuxDos)
		{
			retorno=1;
		}
		else
		{
			if (idAuxUno>idAuxDos)
			{
				retorno=-1;
			} else
			{
				retorno=0;
			}
		}
	}

    return retorno;
}
/*
int Libros_sort(void* parametroUno,void* parametroDos)
{
    int retorno;
    int AuxUno;
    int AuxDos;

    if(parametroUno!=NULL&&parametroDos!=NULL)
	{
		Libros_getPrecio((Libros*)parametroUno,&AuxUno);
		Libros_getPrecio((Libros*)parametroDos,&AuxDos);

		if (AuxUno<AuxDos)
		{
			retorno=1;
		}
		else
		{
			if (AuxUno>AuxDos)
			{
				retorno=-1;
			} else
			{
				retorno=0;
			}
		}
	}

    return retorno;
}
*/

/**
 * @brief funcion para ordenar por Precio.
 * @param parametroUno variable que le paso desde ll_sort a la funcion sortPrecio
 * @param parametroDos variable que le paso desde ll_sort a la funcion sortPrecio
 * @return retorna 1 si el elemento 1 es menor al 2, retorna -1 si el elemento 1 es mayor al 2.
 */

int Libros_sortPrecio(void* parametroUno,void* parametroDos)
{
    int retorno;
    int precioAuxUno;
    int precioAuxDos;

    if(parametroUno!=NULL&&parametroDos!=NULL)
	{
		Libros_getPrecio((Libros*)parametroUno,&precioAuxUno);
		Libros_getPrecio((Libros*)parametroDos,&precioAuxDos);

		if (precioAuxUno<precioAuxDos)
		{
			retorno=1;
		}
		else
		{
			if (precioAuxUno>precioAuxDos)
			{
				retorno=-1;
			} else
			{
				retorno=0;
			}
		}
	}

    return retorno;
}
/**
 * @brief funcion para ordenar por Titulo.
 * @param parametroUno variable que le paso desde ll_sort a la funcion sortTitulo
 * @param parametroDos variable que le paso desde ll_sort a la funcion sortTitulo
 * @return retorna 1 si el elemento 1 es menor al 2, retorna -1 si el elemento 1 es mayor al 2.
 */
int Libros_sortTitulo(void* parametroUno,void* parametroDos)
{
    int retorno;
    char auxPriTitulo[LEN_NOMBRE];
    char auxSegTitulo[LEN_NOMBRE];

    if(parametroUno!=NULL&&parametroDos!=NULL)
	{
		Libros_getTitulo((Libros*)parametroUno,auxPriTitulo);
		Libros_getTitulo((Libros*)parametroDos,auxSegTitulo);

		if (strcmp(auxPriTitulo,auxSegTitulo)<0)
		{
			retorno=1;
		}
		else
		{
			if (strcmp(auxPriTitulo,auxSegTitulo)>0)
			{
				retorno=-1;
			} else
			{
				retorno=0;
			}
		}
	}

    return retorno;
}

/**
 * @brief funcion para ordenar por Autor.
 * @param parametroUno variable que le paso desde ll_sort a la funcion sortAutor
 * @param parametroDos variable que le paso desde ll_sort a la funcion sortAutor
 * @return retorna 1 si el elemento 1 es menor al 2, retorna -1 si el elemento 1 es mayor al 2.
 */

int Libros_sortAutor(void* parametroUno,void* parametroDos)
{
    int retorno;
    char auxPriAutor[LEN_NOMBRE];
    char auxSegAutor[LEN_NOMBRE];

    if(parametroUno!=NULL&&parametroDos!=NULL)
	{
		Libros_getAutor((Libros*)parametroUno,auxPriAutor);
		Libros_getAutor((Libros*)parametroDos,auxSegAutor);

		if (strcmp(auxPriAutor,auxSegAutor)<0)
		{
			retorno=1;
		}
		else
		{
			if (strcmp(auxPriAutor,auxSegAutor)>0)
			{
				retorno=-1;
			} else
			{
				retorno=0;
			}
		}
	}

    return retorno;
}

/**
 * @brief funcion para ordenar por Editorial.
 * @param parametroUno variable que le paso desde ll_sort a la funcion sortEditorial
 * @param parametroDos variable que le paso desde ll_sort a la funcion sortEditorial
 * @return retorna 1 si el elemento 1 es menor al 2, retorna -1 si el elemento 1 es mayor al 2.
 */
int Libros_sortEditorial(void* parametroUno,void* parametroDos)
{
    int retorno;
    char auxPriEditorial[LEN_NOMBRE];
    char auxSegEditorial[LEN_NOMBRE];

    if(parametroUno!=NULL&&parametroDos!=NULL)
	{
		Libros_getIdEditorial((Libros*)parametroUno,auxPriEditorial);
		Libros_getIdEditorial((Libros*)parametroDos,auxSegEditorial);

		if (strcmp(auxPriEditorial,auxSegEditorial)<0)
		{
			retorno=1;
		}
		else
		{
			if (strcmp(auxPriEditorial,auxSegEditorial)>0)
			{
				retorno=-1;
			} else
			{
				retorno=0;
			}
		}
	}

    return retorno;
}

/**
 * @brief guarda el campo editorial dentro de la entidad con el operador flecha.
 * @param pLibro puntero a la entidad.
 * @param titulo dato char de la editorial del libro
 * @return retorno, retorna -1 si hay ERROR, 0 si esta OK.
 */

int Libros_setIdEditorialTxt(Libros* pLibro, char* idEditorial)
{

	int retorno = -1;

	if(pLibro!= NULL && idEditorial!=NULL && idEditorial>=0 && (esNombre(idEditorial,LEN_NOMBRE)==0))
	{
		if(!stricmp(idEditorial,"PLANETA"))
			pLibro->idEditorial=PLANETA;
		else
			if(!stricmp(idEditorial,"SIGLO XXI EDITORES"))
			pLibro->idEditorial=SIGLO_XXI_EDITORES;
			else
				if(!stricmp(idEditorial,"PEARSON"))
				pLibro->idEditorial=PEARSON;
				else
					if(!stricmp(idEditorial,"MINOTAURO"))
					pLibro->idEditorial=MINOTAURO;
					else
						if(!stricmp(idEditorial,"SALAMANDRA"))
						pLibro->idEditorial=SALAMANDRA;
						else
							if(!stricmp(idEditorial,"PENGUIN BOOKS"))
							pLibro->idEditorial=PENGUIN_BOOKS;
	}

	return retorno;
}


/**
 * @brief guarda el campo editorial dentro de la entidad con el operador flecha.
 * @param pLibro puntero a la entidad.
 * @param titulo dato int de la editorial del libro
 * @return retorno, retorna -1 si hay ERROR, 0 si esta OK.
 */

int Libros_setIdEditorial(Libros* pLibro,int idEditorial)
{

	int retorno = -1;

	if(pLibro!= NULL && idEditorial>=0 &&(idEditorial==PLANETA || idEditorial==SIGLO_XXI_EDITORES || idEditorial==PEARSON || idEditorial==MINOTAURO || idEditorial==SALAMANDRA || idEditorial==PENGUIN_BOOKS))
		pLibro->idEditorial=idEditorial;

	return retorno;
}

/**
 * @brief funcion para obtener el valor de la variable desde la entidad mediante operador ->
 * @param pLibro puntero a la entidad.
 * @param idEditorial puntero al dato
 * @return retorna -1 en caso de ERROR retorna 0 en caso de OK.
 */

int Libros_getIdEditorial(Libros* pLibro,char* idEditorial)
{
	int retorno = -1 ;
	int iDeditor;

	if(pLibro!= NULL && idEditorial!=NULL)
	{
		//get_obtener numero tipo idEditorial de la estructura
		Libros_getEditorial(pLibro,&iDeditor);

		switch(iDeditor)
		{
			case PLANETA:
				strcpy(idEditorial,"PLANETA");
				;
				break;
			case SIGLO_XXI_EDITORES:
				strcpy(idEditorial,"SIGLO_XXI_EDITORES");
				break;
			case PEARSON:
				strcpy(idEditorial,"PEARSON");
				;
				break;
			case MINOTAURO:
				strcpy(idEditorial,"MINOTAURO");
				break;
			case SALAMANDRA:
				strcpy(idEditorial,"SALAMANDRA");
				;
				break;
			case PENGUIN_BOOKS:
				strcpy(idEditorial,"PENGUIN_BOOKS");
				break;
		}
		retorno=0;
	}
	return retorno;
}
/**
 * @brief funcion para obtener el valor de la variable desde la entidad mediante operador ->
 * @param pLibro puntero a la entidad.
 * @param idEditorial  puntero al dato
 * @return retorna -1 en caso de ERROR retorna 0 en caso de OK.
 */

int Libros_getEditorial(Libros* pLibro,int* idEditorial)
{

	int retorno = -1 ;

	if(pLibro!= NULL && idEditorial!=NULL)
	{

		*idEditorial=pLibro->idEditorial;
		retorno=0;
	}

	return retorno;
}

/**
 * @brief funcion que sera usada dentro de ll_filter, la misma se usa para pasar criterio de filtro.
 * @param pLibro puntero a la entidad
 * @return retorna -1 en caso de ERROR. y 0 en caso de que este OK.
 */

int libros_filterEditorial(void* pLibro)
{
	int retorno=-1;
	Libros* auxLibro=(Libros*)pLibro;
	char auxEditorial[LEN_NOMBRE];


	if(pLibro!=NULL)
	{
		Libros_getIdEditorial(auxLibro, auxEditorial);

		if(strcmp("MINOTAURO",auxEditorial)==0)
			retorno=1;
		else
		{
			retorno=0;
			Libros_delete(pLibro);
		}

	}

	return retorno;
}


/**
 * @brief funcion que se pasa como criterio a ll_map, para aplicar descuento al haber mapeado todo y coincidencia de criterio
 * @param pLibro puntero a la entidad.
 * @return retorna -1 en caso de ERROR. y 0 en caso de que este OK.
 */

int libros_EditorialConDescuento(void* pLibro)
{
	int retorno = -1;
	int auxEditorial;
	int auxPrecio;
	Libros* auxLibro=(Libros*)pLibro;
	if(pLibro!=NULL)
	{
		{
			if(!Libros_getEditorial(auxLibro,&auxEditorial))
			{

				switch(auxEditorial)
				{
					case PLANETA:
						Libros_getPrecio(pLibro, &auxPrecio);
						if(auxPrecio>=300)
						{
							auxPrecio=auxPrecio*0.2;
							Libros_setPrecio(pLibro, auxPrecio);
							retorno=0;
						}
						;
						break;
					case SIGLO_XXI_EDITORES:
						Libros_getPrecio(pLibro, &auxPrecio);
						if(auxPrecio<=200)
						{
							auxPrecio=auxPrecio*0.1;
							Libros_setPrecio(pLibro, auxPrecio);
							retorno=0;
						}
						break;
				}

			}
		}
	}
	return retorno;
}

/**
 * @brief filtra autor desde int (recibido por lista mostrada), y si hay coincidencia, realizo el filtro
 * @param pLibro puntero a la entidad;
 * @return retorna 0 si el elemento no cumple con el parametro de filtro, se realiza delete, para no perder la direccion, despues el remove, si es 0 se guarda en la lista.
 */
int libros_filterAutor(void* pLibro)
{
	int retorno=-1;
	Libros* auxLibro=(Libros*)pLibro;
	char auxGetAutor[LEN_NOMBRE];
	char auxAutor[LEN_NOMBRE];
	int estado;
	static int bandera=0;

	if(bandera==0)
	{
		bandera=1;
		utn_obtenerEnteroConReintentosMinMax(&estado, "\nIngrese el Numero de autor: ","\n Dato erroneo", 1, 9, 3);
	}
		switch (estado)
		{
			case 1:
				strncpy(auxAutor,"Pigna",sizeof(auxAutor));
				break;
			case 2:
				strncpy(auxAutor,"Paenza",sizeof(auxAutor));
				break;
			case 3:
				strncpy(auxAutor,"Deitel & Deitel",sizeof(auxAutor));
				break;
			case 4:
				strncpy(auxAutor,"Tolkien",sizeof(auxAutor));
				break;
			case 5:
				strncpy(auxAutor,"Rowling",sizeof(auxAutor));
				break;
			case 6:
				strncpy(auxAutor,"Collodi Carlo",sizeof(auxAutor));
				break;
			case 7:
				strncpy(auxAutor,"Baum Frank",sizeof(auxAutor));
				break;
			case 8:
				strncpy(auxAutor,"Swift Jonathan",sizeof(auxAutor));
				break;
			case 9:
				strncpy(auxAutor,"Carroll Lewis",sizeof(auxAutor));
				break;
		}
		if(pLibro!=NULL)
		{
			Libros_getAutor(auxLibro, auxGetAutor);
			if(stricmp(auxAutor,auxGetAutor)==0)
			{
				retorno=1;
			}
			else
			{
				retorno=0;
				Libros_delete(pLibro);
			}
		}
	return retorno;
}
