#include <stdio.h>
#include <stdlib.h>

#include "Libros.h"
#include "LinkedList.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListLibros LinkedList*
 * \return int
 *
 */
int parser_LibrosFromText(FILE* pFile , LinkedList* pArrayListLibros)
{

	int estado =-1;
	Libros* auxLibros;
	char auxId[256];
	char auxTitulo[256];
	char auxAutor[256];
	char auxPrecio[256];
	char auxEditorial[256];
	int contador=0;

		if(pFile!=NULL && pArrayListLibros!=NULL)
		{
			//fgets() otra opcion para leer la 1er linea desde el archivo.

			fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxTitulo,auxAutor,auxPrecio,auxEditorial); // salteo la 1era

			do
			{
				if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxTitulo,auxAutor,auxPrecio,auxEditorial)==5)
				{
		    		 //  printf("Libro ID: %s - Titulo: %s - autor: %s - precio: %s - editorial: %s \n",auxId,auxTitulo,auxAutor,auxPrecio,auxEditorial);
						auxLibros=Libros_newParametros(auxId,auxTitulo,auxAutor,auxPrecio,auxEditorial);


						if (auxLibros!=NULL)
						{

							ll_add(pArrayListLibros,auxLibros);
							estado = 0;
							contador++;
						}
						else
						{

							printf("Error en el Archivo id: %s\n", auxId); //solo muestro los Id de los Empleados con errores ( MOSTRE SOLO NOMBRE NO TOMO NOMBRES CON ESPACIO)
							Libros_delete(auxLibros);
							break;
						}

				}else
				{
					puts("Error en el archivo");
					continue;

				}
			}while(feof(pFile)==0);
			printf("La cantidad de libros cargados es: %d\n",contador);
		}
	return estado;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListLibros LinkedList*
 * \return int
 *
 */
int parser_LibrosFromBinary(FILE* pFile , LinkedList* pArrayListLibros)
{

	int estado =-1;
	Libros* auxLibros;
	int elPrimeroEsError=0;

		if(pFile!=NULL && pArrayListLibros!=NULL)
		{
			//fgets() otra opcion para leer la 1er linea desde el archivo.

			do
			{
				auxLibros=Libros_new();
				if(auxLibros!=NULL)
				{
					if(fread(auxLibros,sizeof(Libros),1,pFile)==1)
					{
						ll_add(pArrayListLibros,auxLibros);
						estado = 0;
					}else
					{
					    Libros_delete(auxLibros);
						break;
						elPrimeroEsError++;
					}
				}
			}while(feof(pFile)==0);
			fclose(pFile);

		}

		if(elPrimeroEsError>1)
		{
			puts("Hubo un error en la carga");
		}

	return estado;
}
