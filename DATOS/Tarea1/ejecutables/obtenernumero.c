#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****
*
TipoFunción NombreFunción
int obtenernumero
******
*
Resumen Función: Funcion que recibe un puntero al nombre del archivo para abrir el archivo y obtener el primer numero de este, retorna el numero.
******
*
Input:
tipoParámetro NombreParámetro : Descripción Parámetro
char *archi : puntero que apunta el nombre del archivo a abrir y registrar para obtener el numero
*
.......
******
*
Returns: n
*
TipoRetorno, Descripción retorno
int,retorna el entero que se encuentra al comienzo del archivo
*****/

int obtenernumero(char *archi){     // recibe el nombre del archivo alumnos
  FILE *fp;
  int b,n;

    fp = fopen(archi, "r"); // aqui abro el archivo de alumnos
    fread(&n, sizeof(int),1,fp); //esto es un booleano, para ver si es posible abrir el archivo  , ademas leo el primer numero n del archivo

    fclose(fp);
    return n;
    }
