#include "simpletron.h"

/*Funcion de procesamiento de argumentos*/

status_t proceso_argumentos(int argc, char **argv, simpletron_t *simpletron, PARAMETROS_T *flags, char **nomin, char **nomout){
	
	int i, j;
	char *pnl;
	
	/*Se valida la cantidad de argumentos recibidos*/

	if((argc < MIN_ARGC) || (argc > MAX_ARGC)){
		return ST_ERROR_MISS_ARG;
	}

	for(i = 1; i < argc; i++){
        for(j = 0; j < ARG_INVALIDO; j++){
            if(!strcmp(argv[i], argumentos_validos[j]))
                break;
        }

    /*Se recorren los argumentos, comparando con los validos hasta encontrar el coincidente, luego se entra al switch*/
    /*Se modifican los flags teniendo en cuenta lo ingresado por consola*/

	  	switch(j){

	        case ARG_H:
				flags->help = true;

				return ST_OK;

	        case ARG_M:
	            if(argv[i + 1][0] == FSIMBOL){
					simpletron->cant = CANT_DEFAULT;
					break;
				}

				simpletron->cant = strtol(argv[i + 1], &pnl, 10);

				if(*pnl != '\0' && *pnl != '\n'){
					return ST_ERROR_NO_NUM;
				}

				if(simpletron->cant == 0){
					simpletron->cant=CANT_DEFAULT;
					break;
				}

				i++;

				break;

	        case ARG_I:

	        	flags->stdi = false;

	            if((argv[i + 1][0]) != FSIMBOL){
					*nomin = argv[i+1];
					i++;

					break;
				}

				flags->stdi = true;

				break;

			case ARG_O:
	            if(argv[i+1][0]!=FSIMBOL){
					*nomout = argv[i+1];
					i++;
					break;
				}

				flags->stdo = true;

				break;

			case ARG_IF:
	            if(argv[i+1][0]==FSIMBOL){
					return ST_ERROR_MISS_ARG;
				}
					
				if(strcmp(argv[i+1],DE_TXT)==0){
					flags->itxt=true;
					i++;
					break;
				}
					
				if(strcmp(argv[i+1],DE_BIN)==0){
					flags->itxt=false;
					i++;
					break;
				}
					return ST_ERROR_ARG_LEIDOS;

			case ARG_OF:
	            if(argv[i+1][0]==FSIMBOL){
					return ST_ERROR_MISS_ARG;
				}

				if(strcmp(argv[i+1],DE_TXT)==0){
					flags->otxt=true;
					i++;
					break;
				}

				if(strcmp(argv[i+1],DE_BIN)==0){
					flags->otxt=false;
					i++;
					break;
				}

					return ST_ERROR_ARG_LEIDOS;

	        default:

	                return ST_ERROR_ARG_LEIDOS;
    	}
	}
	return EXIT_SUCCESS;
}