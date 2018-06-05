#include "simpletron.h"

/*Funciones de impresion*/

void imprimir_memo(simpletron_t *simpletron){

	int fil, i, j = 0, k, l = 0;

	/*Se impriment los registros, luego la meoria en forma de matriz*/

	printf("%s\n", MSJ_REGISTRO);
    printf("%s %d\n", MSJ_ACUMULADOR , simpletron->acumulador);
    printf("%s %02ld\n", MSJ_PCOUNT, simpletron->pc);
    printf("%s %+05d\n", MSJ_INSTRUCCION, simpletron->palabras[simpletron->pc]);
    printf("%s %02d\n", MSJ_OPCODE, simpletron->palabras[simpletron->pc]/100);
    printf("%s %02d\n", MSJ_OPERANDO, (simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100));

    /*Se imprime la memoria en forma de matriz*/
    /*Se calcula la cantidad de filas correspondientes dependiendo de la cantidad de memoria que se pidio ingresando el argumento "-m"*/

    if(((simpletron->cant) % 10) != 0){
        fil = (simpletron->cant / 10) + 1;
    }
    else{
        fil = (simpletron->cant) / 10;
    }

    for(i = 0; i < 10; i++){
        printf("%7d", i);
    }

    printf("\n");

    for(i = 0; i < fil; i++){

    	if(i == 0){
    		k = 10 * i;
        	printf("%2d", k);
        }
        else{
       		printf("\n");
        	k = 10 * i;
        	printf("%2d", k);
        }

        for(j = 0; j < 10; j++){
           
            if(l < (simpletron->cant)){
                printf("%+7.04d", simpletron->palabras[l]);
            }
            else{
            	/*Se imprime +XXXX en las posiciones que en las que no se pidio memoria para que quede simetrica la matriz de impresion*/
                printf("%7s", NO_MEM);
            }

            l++;
        }
    }
    printf("\n");
}


status_t imprimir_txt(char *file){
	FILE *pf;
	char buff[MAX_BUFF];

	putchar('\n');

	if((pf = fopen(file, "r")) == NULL){
		return ST_ERROR_NO_LEIDO;
	}
	
	while(fgets(buff, sizeof(buff), pf)){
		printf("%s\n", buff);
	}

	fclose(pf);

	return ST_OK;
}

