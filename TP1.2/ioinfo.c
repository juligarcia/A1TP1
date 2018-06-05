#include "simpletron.h"

/*Funciones para manejo de informacion de entrada y salida*/

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

		if(*pnl != '\0' && *pnl != '\n'){
			return ST_ERROR_NO_NUM;
		}
		
		/*Validamos el valor de aux antes de pasarlo al vector de ordenes*/
		if(temp == END_READ){
			break;
		}
		else{

			if(temp < MIN_VALIDO || temp > MAX_VALIDO){
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

		/*Nos aseguramos de que la palabra esta en el rango aceptado*/

		if(aux < MIN_VALIDO || aux > MAX_VALIDO){
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