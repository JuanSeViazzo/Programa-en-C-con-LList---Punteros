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



Libros* Libros_new(void)
{
	Libros* pLibros = (Libros*) malloc(sizeof(Libros));

	return pLibros;
}

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

void Libros_delete(Libros* pLibro)
{

	if(pLibro!=NULL)
	{
		free(pLibro);
	}

}

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
    		printf("Libro ID: %-2d	-	Titulo: %-50s	-	Autor: %-20s  -	Precio: %d				-		Editorial: %s\n",id,titulo,autor,precio,editorial);

    	    estado = 0;
        }
    }

    return estado;
}

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
}

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
int Libros_sortHoras(void* parametroUno,void* parametroDos)
{
    int retorno;
    int horasAuxUno;
    int horasAuxDos;

    if(parametroUno!=NULL&&parametroDos!=NULL)
	{
		Libros_getPrecio((Libros*)parametroUno,&horasAuxUno);
		Libros_getPrecio((Libros*)parametroDos,&horasAuxDos);

		if (horasAuxUno<horasAuxDos)
		{
			retorno=1;
		}
		else
		{
			if (horasAuxUno>horasAuxDos)
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

int Libros_setIdEditorial(Libros* pLibro,int idEditorial)
{

	int retorno = -1;

	if(pLibro!= NULL && idEditorial>=0 &&(idEditorial==PLANETA || idEditorial==SIGLO_XXI_EDITORES || idEditorial==PEARSON || idEditorial==MINOTAURO || idEditorial==SALAMANDRA || idEditorial==PENGUIN_BOOKS))
		pLibro->idEditorial=idEditorial;

	return retorno;
}
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

