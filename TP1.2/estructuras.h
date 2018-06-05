/*Proteccion contra inclusion multiple*/

#ifndef ESTRUCTURAS_H 
#define ESTRUCTURAS_H 

typedef enum {false = 0, true = 1}bool;

typedef enum{ST_OK, ST_ERROR_PROCESO_INVALIDO, ST_ERROR_INGRESO_POSICION, ST_ERROR_MISS_ARG, ST_ERROR_ARG_LEIDOS, ST_ERROR_ARG, ST_ERROR_PTR_NULL, ST_ERROR_NEG, ST_ERROR_INVALPAL, ST_ERROR_OUT_RANG, ST_ERROR_EOF, ST_ERROR_NO_NUM, ST_ERROR_NO_LEIDO}status_t;

typedef enum{ARG_LEER = LEER, ARG_ESCRIBIR = ESCRIBIR, ARG_CARGAR = CARGAR, ARG_GUARDAR = GUARDAR, ARG_PCARGAR = PCARGAR, ARG_PGUARDAR = PGUARDAR, ARG_SUMAR = SUMAR, ARG_RESTAR = RESTAR, ARG_DIVIDIR = DIVIDIR,
ARG_MULTIPLICAR = MULTIPLICAR, ARG_JMP = JMP, ARG_JMPNEG = JMPNEG, ARG_JMPZERO = JMPZERO, ARG_JNZ = JNZ, ARG_DJNZ = DJNZ, ARG_HALT = HALT}opcode;

typedef int palabra_t;

typedef struct simpletron_t {palabra_t *palabras; palabra_t acumulador; size_t pc; int cant;} simpletron_t;
							
typedef struct PARAMETROS_T{bool help; bool m; bool ent; bool stdo; bool stdi; bool itxt; bool otxt;}PARAMETROS_T;

typedef enum { ARG_I, ARG_IF, ARG_OF, ARG_O, ARG_H, ARG_M, ARG_INVALIDO }arg_t;

extern const char *argumentos_validos[];

/*Esta como variable global ya que es un diccionario*/

#endif