#include "simpletron.h"

int main(int argc,char *argv[]){

	PARAMETROS_T flags;
	simpletron_t simpletronp;
	char *nomin = MSJ_NO_OUT, *nomout = MSJ_NO_OUT, *ayuda = AR_AYUDA, *bienvenida = AR_BIENVENIDA;
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
				if((pf=fopen(nomin,"r")) == NULL){
					return ST_ERROR_PTR_NULL;
				}
				if(leer_fichero_txt(&simpletronp, pf) != ST_OK){
					return EXIT_FAILURE;
				}
					
					break;

			case false:	
				if((pf=fopen(nomin,"rb")) == NULL){
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
	return EXIT_SUCCESS;
	}

	/*Finalizacion de guardar archivos de OUTPUT*/

status_t grabar_fichero_txt(simpletron_t *simpletron, FILE **pf){
	
	int i=0;	
	
	fprintf(*pf, "%02d", simpletron->palabras[i]);
	
	for(i = 1; i < simpletron->cant; i++){
		
		fputc('\n', *pf);
		fprintf(*pf, "%02d", simpletron->palabras[i]);

	}

	return ST_OK;

}

status_t leer_stdin(simpletron_t *simpletron){
	
	int k, temp;
	char buff[MAX_BUFF],*pnl;
	
	simpletron->palabras = (palabra_t *)calloc(simpletron->cant, sizeof(palabra_t));
	
	for(k = 0; k < simpletron->cant && temp != END_READ; k++){

		printf("%02d %s ", k, OPC_SEP);
		
		if(!(fgets(buff, sizeof(buff), stdin))){
			return ST_ERROR_EOF;
		}

		temp = strtol(buff, &pnl, 10);


		
		/*Validamos el valor de aux antes de pasarlo al vector de ordenes*/
		if(temp == END_READ){
			break;
		}
		else{

			if(temp < -9999 || temp > 9999){
				return ST_ERROR_INVALPAL;
			}

		simpletron->palabras[k] = temp;

		}
	}

	return ST_OK;
}

status_t leer_fichero_bin(simpletron_t *simpletron, FILE *pf){
	
	int i;
	
	simpletron->palabras = (palabra_t *)calloc(simpletron->cant, sizeof(palabra_t));

	for(i = 0; i < simpletron->cant; i++){
		if(fread(&(simpletron->palabras[i]), sizeof(int), 1,pf) != 1){
			return ST_ERROR_ARG_LEIDOS;
		}
	}
	
	if(i < simpletron->cant || i > simpletron->cant){
		return ST_ERROR_OUT_RANG;
	}
	
	return ST_OK;
	
}


status_t leer_fichero_txt(simpletron_t *simpletron, FILE *pf){
	
	int k = 0, aux;
	char buff[MAX_BUFF], *pnl;

	simpletron->palabras = (palabra_t *)calloc(simpletron->cant, sizeof(palabra_t));
	while((fgets(buff, sizeof(buff), pf))){
		
		aux = strtol(buff, &pnl, 10); 
		
		/*Nos aseguramos de que las ordenes son todas positivas*/
		if(aux < 0){
			free(simpletron->palabras);
			return ST_ERROR_NEG;
		}

		/*Nos aseguramos de que la palabra esta en el rango aceptado de 4 digitos*/
		if(aux < -9999 || aux > 9999){
			free(simpletron->palabras);
			return ST_ERROR_INVALPAL;
		}
		
		/*Si paso las validaciones, entonces la orden es valida y se guarda en el vector de ordenes*/
		simpletron->palabras[k] = aux;
		
		k++;

	}
	
	return ST_OK;
	
}


status_t grabar_fichero_bin(simpletron_t *simpletron, FILE **pf){
	
	int i;	
	
	for(i = 0; i < simpletron->cant; i++){
		
		if(fwrite(&(*simpletron).palabras[i], 1, sizeof(int), *pf) != sizeof(int)){
			return ST_ERROR_ARG_LEIDOS;
		}
		
	}
	return ST_OK;
}

status_t proceso_argumentos(int argc, char **argv, simpletron_t *simpletron, PARAMETROS_T *flags, char **nomin, char **nomout){
	
	int i, j;
	char *pnl;
	
	if((argc < MIN_ARGC) || (argc > MAX_ARGC)){
		return ST_ERROR_MISS_ARG;
	}

	for(i = 1; i < argc; i++){
        for(j = 0; j < ARG_INVALIDO; j++){
            if(!strcmp(argv[i], argumentos_validos[j]))
                break;
        }

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

				if((*pnl = '\0') && *pnl!='\n'){
					return ST_ERROR_NO_NUM;
				}

				if(simpletron->cant == 0){
					simpletron->cant=CANT_DEFAULT;
					break;
				}

				i++;

				break;

	        case ARG_I:
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

status_t procesamiento(simpletron_t *simpletron){

	int i = 0, j = 0;

	
	printf("%s\n\n", MSJ_COMIENZO_PROC);

	for(simpletron->pc = 0; simpletron->pc < simpletron->cant && !i; (simpletron->pc)++){
		switch ((simpletron->palabras[simpletron->pc])/100){
			
			case ARG_LEER: 
				printf("%s [%02d]\n", MSJ_INGRESE_POS, simpletron->palabras[simpletron->pc] - 100*((simpletron->palabras[simpletron->pc])/100));
				if(op_leer(&(*simpletron)) != ST_OK){
					return EXIT_FAILURE;
				}
				printf("\n");

				break;

			case ARG_ESCRIBIR: 		
				printf("%s:%02d %s:%02d\n\n", MSJ_POS, (simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100), MSJ_STOUT, simpletron->palabras[(simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100)]);
				
				break;								
			
			case ARG_CARGAR: 		
				op_cargar(&(*simpletron));
				printf("%s:%02d\n\n", MSJ_CARGA, simpletron->palabras[simpletron->pc] - 100*((simpletron->palabras[simpletron->pc])/100));
				
				break;
			
			case ARG_GUARDAR:
				op_guardar(&(*simpletron));
				printf("%s:%02d\n\n", MSJ_GUARDAR, simpletron->palabras[simpletron->pc] - 100*((simpletron->palabras[simpletron->pc])/100));
				
				break;

			case ARG_PCARGAR: 
				op_cargarp(&(*simpletron));
				printf("%s:%02d\n\n", MSJ_CARGARP, simpletron->palabras[simpletron->pc] - 100*((simpletron->palabras[simpletron->pc])/100));

				break;

			case ARG_PGUARDAR: 
				op_guardarp(&(*simpletron));
				printf("%s:%02d\n\n", MSJ_GUARDARP, simpletron->palabras[simpletron->pc] - 100*((simpletron->palabras[simpletron->pc])/100));

				break;

			case ARG_SUMAR: 
				op_sumar(&(*simpletron));
				printf("%s:%02d\n\n", MSJ_SUMA, simpletron->palabras[simpletron->pc] - 100*((simpletron->palabras[simpletron->pc])/100));		
				
				break;

			case ARG_RESTAR:
				op_restar(&(*simpletron));
				printf("%s:%02d\n\n", MSJ_RESTA, simpletron->palabras[simpletron->pc] - 100*((simpletron->palabras[simpletron->pc])/100));

				break;

			case ARG_DIVIDIR: 	
				op_dividir(&(*simpletron));
				printf("%s:%02d\n\n", MSJ_DIV, simpletron->palabras[simpletron->pc] - 100*((simpletron->palabras[simpletron->pc])/100));

				break;

			case ARG_MULTIPLICAR: 	
				op_multiplicar(&(*simpletron));
				printf("%s:%02d\n\n", MSJ_MULT, simpletron->palabras[simpletron->pc] - 100*((simpletron->palabras[simpletron->pc])/100));

				break;

			case ARG_JMP: 
				op_jmp(&(*simpletron));
				printf("%s:%02d\n\n", MSJ_JMP, simpletron->palabras[(simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100)]);

				break;

			case ARG_JMPNEG: 
				if((op_jmpneg(&(*simpletron))) == true){
					printf("%s:%02d\n\n", MSJ_JMP, simpletron->palabras[simpletron->pc] - 100*((simpletron->palabras[simpletron->pc])/100));
				}
				
				break;

			case ARG_JMPZERO: 
				if((op_jmpzero(&(*simpletron))) == true){
					printf("%s:%02d\n\n", MSJ_JMP, simpletron->palabras[simpletron->pc] - 100*((simpletron->palabras[simpletron->pc])/100));
				}

				break;

			case ARG_JNZ: 
				if((op_jmz(&(*simpletron))) == true){
					printf("%s:%02d\n\n", MSJ_JMP, simpletron->palabras[simpletron->pc] - 100*((simpletron->palabras[simpletron->pc])/100));
				}

				break;

			case ARG_DJNZ: 		
				if((op_djnz(&(*simpletron))) == true){
					printf("%s:%02d y %s:%02d\n\n", MSJ_RESTA, simpletron->palabras[simpletron->pc] - 100*((simpletron->palabras[simpletron->pc])/100), MSJ_JMP, 0);
				}
				else{
					printf("%s:%02d\n\n", MSJ_RESTA, simpletron->palabras[simpletron->pc] - 100*((simpletron->palabras[simpletron->pc])/100));
				}

				break;	

			case ARG_HALT: 
				i = 1;
				printf("%s\n\n", MSJ_FIN_DEL_PROGRAMA);		
				
				break;		
										
			default: 

				j += 1; 

				break;
			}
		
		}

	simpletron->pc -= j;
	return ST_OK;

}

status_t op_leer(simpletron_t *simpletron){
	
	char buff[MAX_BUFF];
	char *pnl;
		
	if(!(fgets(buff, sizeof(buff), stdin))){
		return ST_ERROR_INGRESO_POSICION;
	}

	if((pnl = strchr(buff, '\n'))){
		*pnl='\0';
	}

	simpletron->palabras[(simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100)] = strtol(buff, &pnl, 10);
	/*validar el strtol*/
	return ST_OK;
}	

void op_cargar(simpletron_t *simpletron){
	
	/*Carga una palabra de la memoria al acumulador*/

	simpletron->acumulador = simpletron->palabras[(simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100)];

}

void op_guardar(simpletron_t *simpletron){

	/*Guarda el contenido del acumulador en una posicion de memoria*/

	simpletron->palabras[(simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100)] = simpletron->acumulador;

}

void op_sumar(simpletron_t *simpletron){

	/*Suma una palabra al acumulador*/

	simpletron->acumulador += simpletron->palabras[(simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100)];

}

void op_restar(simpletron_t *simpletron){

	/*Resta una palabra al acumulador*/

	simpletron->acumulador -= simpletron->palabras[(simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100)];

}

void op_dividir(simpletron_t *simpletron){

	/*Divide al acumulador por el contenido de la posicion de memoria indicada por el interador "i"*/

	simpletron->acumulador /= simpletron->palabras[(simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100)];	

}

void op_multiplicar(simpletron_t *simpletron){

	/*Multiplicar al acumulador por el contenido de la posicion de memoria indicada por el interador "i"*/

	simpletron->acumulador *= simpletron->palabras[(simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100)];
	
}

void op_jmp(simpletron_t *simpletron){

	/*Salta a la orden especificada*/

	simpletron->pc = (simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100) - 2 ;

}	

bool op_jmpneg(simpletron_t *simpletron){

	/*Salta a la orden especificada SOLO SI el acumulador es negativo*/

	if(simpletron->acumulador < 0){
		simpletron->pc = (simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100) - 2 ;
		return true;
	}

	else{
		return false;
	}
}

bool op_jmpzero(simpletron_t *simpletron){

	/*Salta a la orden especificada SOLO SI el acumulador es 0*/
	
	if(simpletron->acumulador == 0){
		simpletron->pc = (simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100) - 2 ;
		return true;
	}

	else{
		return false;
	}
}

bool op_jmz(simpletron_t *simpletron){

	/*Salta a la orden especificada SOLO SI el acumulador es distinto de 0*/

	if((simpletron->acumulador)){
		simpletron->pc = (simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100) - 2 ;
		return true;
	}

	else{
		return false;
	}
}

bool op_djnz(simpletron_t *simpletron){

	/*Decrementa el acumulador por el contenido de la posicion de memoria indicado y, si este no es 0, vuelve al comienzo del ciclo*/

	if(!(simpletron->acumulador -= simpletron->palabras[(simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100)])){
		simpletron->pc = -1;
		return true;
	}

	else{
		simpletron->acumulador -= simpletron->palabras[(simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100)];
		return false;
	}
}	

void op_cargarp(simpletron_t *simpletron){

	/*Es homologa a la funcion cargar, pero se indica una posicion de memoria donde se sacara un puntero*/

	simpletron->acumulador = simpletron->palabras[simpletron->palabras[(simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100)]];

	}

void op_guardarp(simpletron_t *simpletron){

	/*Es homologa a la funcion guardar, pero con puntero como operando*/

	simpletron->palabras[simpletron->palabras[(simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100)]] = simpletron->acumulador;

	}

void imprimir_memo(simpletron_t *simpletron){

	int fil, i, j = 0, k, l = 0;

	printf("%s\n", MSJ_REGISTRO);
    printf("%s %d\n", MSJ_ACUMULADOR , simpletron->acumulador);
    printf("%s %02ld\n", MSJ_PCOUNT, simpletron->pc);
    printf("%s %+05d\n", MSJ_INSTRUCCION, simpletron->palabras[simpletron->pc]);
    printf("%s %02d\n", MSJ_OPCODE, simpletron->palabras[simpletron->pc]/100);
    printf("%s %02d\n", MSJ_OPERANDO, (simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100));

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

