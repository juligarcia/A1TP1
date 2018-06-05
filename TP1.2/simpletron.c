#include "simpletron.h"

const char *argumentos_validos[] = {PARAM1, PARAM2, PARAM3, PARAM4, PARAM5, PARAM6};

int main(int argc,char *argv[]){

	PARAMETROS_T flags;
	simpletron_t simpletronp;
	char *nomin = MSJ_NO_IN, *nomout = MSJ_NO_OUT, *ayuda = AR_AYUDA, *bienvenida = AR_BIENVENIDA;
	FILE *pf;
	
	simpletronp.acumulador = 0;
	simpletronp.pc = 0;
	
	/*Se comienza a procesar argumentos*/
	if(proceso_argumentos(argc, argv, &simpletronp, &flags, &nomin, &nomout) != ST_OK){
		return EXIT_FAILURE;
	}

	printf("%s\n",MSJ_BIENVENIDA);
	imprimir_txt(bienvenida);

	if(flags.help == true){
		imprimir_txt(ayuda);
	}

	printf("%s: %s\n", MSJ_AR_ENTRADA, nomin);
	printf("%s: %s\n", MSJ_AR_SALIDA, nomout);
	printf("%s: %d\n", MSJ_CANT_PROC, simpletronp.cant);
	
	/*Se lee y procesa datos por distintos tipos de data input*/
	
	if(flags.stdi == true){
		if(leer_stdin(&simpletronp) != ST_OK){
			return EXIT_FAILURE;
		}
	}
	
	else{
		switch(flags.itxt){
			case true: 
				if((pf = fopen(nomin,"r")) == NULL){
					return ST_ERROR_PTR_NULL;
				}

				if(leer_fichero_txt(&simpletronp, pf) != ST_OK){
					return EXIT_FAILURE;
				}
				
				break;

			case false:	
				if((pf = fopen(nomin,"rb")) == NULL){
					return ST_ERROR_PTR_NULL;
				}

				if(leer_fichero_bin(&simpletronp, pf) != ST_OK){
					return EXIT_FAILURE;
				}

				break;

			default:
				return EXIT_FAILURE;

				break;
		}

		if(fclose(pf)){
			return ST_ERROR_OUT_RANG;
		}
	}
	
	/*Finalizacion de lectura de archivo en input y guardado en estructuras*/
	
	/*INICIO Procesamiento datos*/
	
	if(procesamiento(&simpletronp) != ST_OK){
		return EXIT_FAILURE;
	}

	/*FIN Procesamiento datos*/
	/*Comienzo impresion de estados*/
	
	if(flags.stdo == true){
		imprimir_memo(&simpletronp);
	}

	else{
		switch(flags.otxt){
			case true:	
				if((pf = fopen(nomout,"w")) == NULL){
					return ST_ERROR_PTR_NULL;
				}

				printf("%s:%s\n", MSJ_AR_GUARDADO, nomout);

				if((grabar_fichero_txt(&simpletronp, &pf)) != ST_OK){
					return EXIT_FAILURE;
				}	
				
				break;

			case false:	
				if((pf=fopen(nomout, "wb"))==NULL){
					return ST_ERROR_PTR_NULL;
				}

				printf("%s:%s\n",MSJ_NOM_AR, nomout);

				if((grabar_fichero_bin(&simpletronp, &pf)) != ST_OK){
					return EXIT_FAILURE; 
				}
				
				break;

			default: 
				return EXIT_FAILURE;

				break;
			}

			if(fclose(pf)){
				return ST_ERROR_OUT_RANG;
			}
		}	

	free(simpletronp.palabras);

	return EXIT_SUCCESS;

	}