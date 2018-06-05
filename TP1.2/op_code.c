#include "simpletron.h"

/*Funciones del correspondientes al OP CODE*/

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
	
	if(*pnl != '\0' && *pnl != '\n'){
		return ST_ERROR_NO_NUM;
	}

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

	simpletron->pc = (simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100) - 1 ;

}	


bool op_jmpneg(simpletron_t *simpletron){

	/*Salta a la orden especificada SOLO SI el acumulador es negativo*/

	if(simpletron->acumulador < 0){
		simpletron->pc = (simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100) - 1 ;
		return true;
	}

	else{
		return false;
	}
}


bool op_jmpzero(simpletron_t *simpletron){

	/*Salta a la orden especificada SOLO SI el acumulador es 0*/
	
	if(simpletron->acumulador == 0){
		simpletron->pc = (simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100) - 1 ;
		return true;
	}

	else{
		return false;
	}
}


bool op_jmz(simpletron_t *simpletron){

	/*Salta a la orden especificada SOLO SI el acumulador es distinto de 0*/

	if((simpletron->acumulador)){
		simpletron->pc = (simpletron->palabras[simpletron->pc]) - 100*((simpletron->palabras[simpletron->pc])/100) - 1 ;
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