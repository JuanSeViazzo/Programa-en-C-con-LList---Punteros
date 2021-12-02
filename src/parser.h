/*
 * parser.h
 *
 *  Created on: 12 nov 2021
 *      Author: Juan Sebastian
 */

#ifndef PARSER_H_
#define PARSER_H_


int parser_LibrosFromText(FILE* pFile , LinkedList* pArrayListLibros);
int parser_LibrosFromBinary(FILE* pFile , LinkedList* pArrayListLibros);


#endif /* PARSER_H_ */
