/*Proteccion contra inclusion multiple*/

#ifndef SIMPLETRON__H 
#define SIMPLETRON__H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CONS.h"
#include "HEADER.h"

/*Seleccion del lenguaje, ES ESPAÑOL, US INGLES*/

#define LANG__ES

#include "LANG.h"


/*PROTOTIPOS*/

status_t leer_stdin(simpletron_t *simpletron);
status_t leer_fichero_bin(simpletron_t *simpletron, FILE *pf);
status_t leer_fichero_txt(simpletron_t *simpletron, FILE *pf);
status_t grabar_fichero_bin(simpletron_t *simpletron, FILE **pf);
status_t grabar_fichero_txt(simpletron_t *simpletron, FILE **pf);
status_t proceso_argumentos(int argc,char **argv,simpletron_t *simpletron,PARAMETROS_T *flags, char **nomin, char **nomout);
status_t procesamiento(simpletron_t *simpletron);

/*Funciones que se usan en el procesamiento*/
void op_cargar(simpletron_t *simpletron);
void op_guardar(simpletron_t *simpletron);
void op_sumar(simpletron_t *simpletron);
void op_restar(simpletron_t *simpletron);
void op_dividir(simpletron_t *simpletron);
void op_multiplicar(simpletron_t *simpletron);
void op_jmp(simpletron_t *simpletron);
bool op_jmpneg(simpletron_t *simpletron);
bool op_jmpzero(simpletron_t *simpletron);
bool op_jmz(simpletron_t *simpletron);
bool op_djnz(simpletron_t *simpletron);
void op_cargarp(simpletron_t *simpletron);
void op_guardarp(simpletron_t *simpletron);
status_t op_leer(simpletron_t *simpletron);
void imprimir_memo(simpletron_t *simpletron);
status_t imprimir_txt(char *file);



#endif