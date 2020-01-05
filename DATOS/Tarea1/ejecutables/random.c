#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*****
*
TipoFunción NombreFunción
 char** random2
******
*
Resumen Función :
Función utilizada para crear un arreglo con los alumnos ordenados de manera aleatoria, a partir del arreglo recibido, a partir de un arreglo "usado" se evita que los alumnos sean elegidos más de una vez
******
*
Input:

int cant: entero que indica la cantidad de alumnos en el arreglo.

char** alumnos_en_el_curso: puntero a un puntero del arreglo con los alumnos del curso en cuestion.

*
.......
******
*
Returns:  alumnos_en_el_curso_random
*
TipoRetorno, Descripción retorno
char**, retorna un doble puntero al arreglo ordenado aleatoriamente de alumnos
*****/

char** random2(int cant, char** alumnos_en_el_curso){
    char** alumnos_en_el_curso_random;
    int usado[cant];
    int i;
    alumnos_en_el_curso_random = (char**)malloc(sizeof(char*)*cant);
    for(i = 0; i < cant; i++){
        alumnos_en_el_curso_random[i] = (char*)malloc(sizeof(char)*41);
    }
    for (i=0; i < cant; i++){
        usado[i]=0;
        }

    int index=0;
    for (i=0; i < cant; i++){
        do{
            index = (rand() % cant);
        }while(usado[index]);
        if (usado[index] == 0 ){
            strcpy(alumnos_en_el_curso_random[i], alumnos_en_el_curso[index]);
            usado[index]=1;
        }
    }

    return alumnos_en_el_curso_random;
}
