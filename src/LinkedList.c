#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= (LinkedList*) malloc (sizeof(LinkedList));


    if(this!=NULL)
    {

    	this->size=0;
    	this->pFirstNode=NULL;

    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{

	int retorno=-1;

	if(this!=NULL)
	{
		retorno = this->size;
	}

    return retorno;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{

	Node* auxNodo=NULL;
	int index;


	if(this!=NULL && nodeIndex>=0 && ll_len(this)>nodeIndex)
	{

		auxNodo=this->pFirstNode;

		for(index=0;index<nodeIndex;index++)
		{
			auxNodo=auxNodo->pNextNode;
		}


	}
    return auxNodo;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int retorno=-1;
    Node* nodoAux;
    int size;

    	if(this!=NULL && nodeIndex>=0 && nodeIndex<=ll_len(this))
    	{
    		Node* NuevoNodo = (Node*) malloc (sizeof(Node));
    	    if (NuevoNodo!=NULL) // se crea el nuevo espacio
    	    {
    	    	if(nodeIndex==0)
				{
					//SWAP DE NODOS. ESTOY METIENDO ENTRE LINKLIST Y 1ER NODO OTRO NODO
					// POR LO CUAL, GUARDO EL 1ER NODO EN AUX, AL NUEVO LE DOY LA POSICION PFIRSTNODE(QUE ESTA EN LA LLIST)
					//Y AL AUXILIAR (QUE ERA EL 1ERO) LO GUARDO (PUNTERO) DENTRO DEL NEXTNODE DEL 1ERO.
					nodoAux=this->pFirstNode;
					this->pFirstNode=NuevoNodo;
					NuevoNodo->pNextNode=nodoAux;
					retorno = 0;

				}else
				{
					nodoAux = getNode(this, nodeIndex-1);
					NuevoNodo->pNextNode=nodoAux->pNextNode;
					nodoAux->pNextNode=NuevoNodo;
					retorno=0;

				}

    	    	if(retorno==0)
    	    	{
					NuevoNodo->pElement=pElement;
					size=ll_len(this);
					size++;
					this->size=size;
    	    	}
    	    }

    	}

    return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL)
    {
    	returnAux=addNode(this, this->size, pElement);
    	return returnAux;
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* auxNode;

    // (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
    if(this!=NULL && index>=0 && index<ll_len(this))
    {
    	//nodo auxiliar, para obtener el nodo que contiene al pElement
    	auxNode=getNode(this, index);

    	  if(auxNode!=NULL)
    	    {
    	    	//return (pElement) Si funciono correctamente
    	    	returnAux=auxNode->pElement;
    	    }


    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{

    int retorno = -1;
    Node* auxNode;

    // (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
    if(this!=NULL && index>=0 && index<ll_len(this))
    {
    	//nodo auxiliar, para obtener el nodo que contiene al pElement
    	auxNode=getNode(this, index);

    	  if(auxNode!=NULL)
    	    {
    	    	//return (pElement) Si funciono correctamente
    	    	auxNode->pElement=pElement;
    	    	retorno = 0;
    	    }
    }
    return retorno;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* nodoAnterior;
    Node* nodoABorrar;
    int size;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
		nodoABorrar=getNode(this,index);

    	if(index==0)//el usuario quiere borrar la 1er posicion
    	{
    		//borro el 1ero, me lo guardo para borrarlo, pero antes pfirstnode debe apuntar al nodo siguiente
    		this->pFirstNode=nodoABorrar->pNextNode;
    		returnAux=0;

    	}else
    	{
    		//si borro el ultimo o el del medio
    		nodoAnterior=getNode(this,index-1);
    		nodoAnterior->pNextNode=nodoABorrar->pNextNode;
    		returnAux=0;
    	}

    	if(returnAux==0)
    	{
    		free(nodoABorrar);
			size=ll_len(this);
			size--;
			this->size=size;
    	}

    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int i;

    if(this!=NULL)
    {

    	for(i=0;i<ll_len(this);i++)
    	{
    		ll_remove(this, 0);
    		returnAux=0;
    	}

    }



    return returnAux;
}

/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this!=NULL)
    {
    	if(ll_clear(this)==0)
    	{
        	free(this);
        	returnAux=0;
    	}
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int index;
    Node* auxNodo;

    if(this!=NULL)
    {
    	for(index=0;index<ll_len(this);index++)
    	{
    		auxNodo=getNode(this, index);

			if(auxNodo!=NULL && auxNodo->pElement==pElement)
			{
				returnAux=index;
				break;
			}
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this!=NULL)
    {
    	if(this->size>0)
    		returnAux=0;
    	else
    		returnAux=1;
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL && index>=0 && index<=ll_len(this))
    {
    	addNode(this,index,pElement);
    	returnAux=0;
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    Node* auxElemento;

    if(this!=NULL && index>=0 && index<=ll_len(this))
    {
    	auxElemento=ll_get(this, index);
    		if(ll_remove(this, index)==0)
    		{
    			returnAux=auxElemento;
    		}
    }




    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int index = 0;
    int indicePositivo;


    if(this!=NULL)
    {
		returnAux=0;

    	for (index = 0; index < ll_len(this); ++index)
    	{

    		indicePositivo=ll_indexOf(this, pElement);

    		if(indicePositivo>=0)
    		{
    			returnAux=1;
    			break; // quiere decir que existe un elemento asi en la lista.
    		}
		}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int indexPriLista;

    //recorro la 2da lista, y cada elemento de esa lista, uso contains, y cuando no se cumpla rompo

    if(this!=NULL && this2!=NULL)
    {
    	returnAux=0;

    	if(ll_len(this2)<=ll_len(this))
    	{
    		returnAux=1;
    		for(indexPriLista=0;indexPriLista<ll_len(this2);indexPriLista++)
			{
				if(ll_contains(this, ll_get(this2, indexPriLista))==0)
				{
					returnAux=0;
					break;
				}
			}
    	}
    }



    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    int i;
    void* pElemento;
    if(this!=NULL)
    {
    	if(from>=0 && from<to && to<=ll_len(this))
    	{
    		cloneArray = ll_newLinkedList();

    		if(cloneArray!=NULL)
    		{
    			for(i=from;i<to;i++)
    			{
    				pElemento=ll_get(this, i);
    				ll_add(cloneArray, pElemento);
    			}
    		}
    	}
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    int i;
        void* pElemento;
        if(this!=NULL && ll_len(this))
        {
			cloneArray = ll_newLinkedList();

			if(cloneArray!=NULL)
			{
				for(i=0;i<ll_len(this);i++)
				{
					pElemento=ll_get(this, i);
					ll_add(cloneArray, pElemento);
				}
			}
        }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{

	int returnAux =-1;
	int flagSwap;
	void* pElementPri;
	void* pElementSeg;
	int index;
	int criterio; // criterio que devuelve la funcion para realizar SI/NO swap

	if(this!=NULL && (order==1 || order==0) && pFunc!=NULL)
	{
		do
		{
			flagSwap=0; 											// digo que esta ordenado
			for(index=0; index<(this->size)-1; index++)
			{
				pElementPri=ll_get(this, index);				 // traigo el 1er elemento  (1er vuelta index = 0)
				pElementSeg=ll_get(this,index+1); 				// traigo el 2do elemento  (1er vuelta index+1 = 0+1)
				criterio=pFunc(pElementPri, pElementSeg);
				if(order==1) 										// tipo de ordenamiento 1 ascendente else descendente
				{
					if(criterio==1)								 // si criterio me retorno 1 es porque tengo que swapear
					{
						ll_set(this, index, pElementSeg); 		 // llamo mi funcion ll_set y hago el swap
						ll_set(this, index+1, pElementPri);		 //  llamo mi funcion ll_set y hago el swap
						flagSwap=1;
					}
				}
				else 													// si el orden es descendente
				{
					if(criterio==-1)
					{
						ll_set(this, index, pElementSeg);
						ll_set(this, index+1, pElementPri);
						flagSwap=1;
					}
				}

			}

		}while(flagSwap); // si flagswap=0 se sale y finaliza

		returnAux = 0;


	}


	return returnAux;

}






int ll_map(LinkedList* this, int(*pFunc)(void*))
{
	int retorno = -1;
	void* pAuxiliar;

	if(this != NULL && pFunc != NULL)
	{
		for(int i = 0; i < ll_len(this); i++)
		{
			pAuxiliar = ll_get(this, i);
			if(!pFunc(pAuxiliar))
			{
				retorno = 0;
			}
		}
	}
	return retorno;
}

/** \brief Filtra los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param LinkedList* this - Puntero a la lista
 * \param int(*pFunc)(void*) - Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas o a la funcion es NULL
                        ( 0) Si ok
 */
int ll_filter(LinkedList* this, int (*pFunc)(void*))
{
	int i;
	void* pAuxiliar;
	int retornoFuncionCriterio;
	int retorno = -1;

	if(this != NULL && pFunc != NULL)
	{
		for(i = ll_len(this)-1; i >= 0; i--)
		{
			pAuxiliar = ll_get(this, i);
			retornoFuncionCriterio = pFunc(pAuxiliar);
			if(!retornoFuncionCriterio)
			{
				retorno = ll_remove(this, i);
			}
		}
	}
	return retorno;
}
