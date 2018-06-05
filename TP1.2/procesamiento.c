#include "simpletron.h"

/*Funcion de procesamiento de ordenes*/

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
				printf("%s:%02d\n\n", MSJ_JMP, (simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100));

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

				/*Esto se hace para en el final restarle a program counter la cantidad de veces que se paso por una "Orden" no valida, por ejemplo un numero dentro del array*/

				break;
			}
		
		}

	simpletron->pc -= j;
	return ST_OK;

}