#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****
*
TipoFunción NombreFunción
alumno* obtenerAlumnos
******
*
Resumen Función: Funcion implementada para obtener los alumnos del archivo "alumnos.dat" y guardarlos en un arreglo

******
*
Input:
char* archi_alumnos: puntero del tipo caracter que apunta el nombre del archivo "alumnos.dat"

*
.......
******
*
Returns:
TipoRetorno, Descripción retorno
retorna un puntero del tipo alumno que apunta a un arreglo con todos los alumnos que hay en el archivo "alumnos.dat"
*****/

typedef struct {
char rol_estudiante [12];
char carrera [4];
char nombre_completo [41];
int numero_cursos ;
int id_cursos_inscritos [50];
} alumno ;


alumno* obtenerAlumnos (char *archi_alumnos){     // recibe el nombre del archivo alumnos
  FILE *fp;
  int a,b,n;
  alumno *w,aux;


  fp = fopen(archi_alumnos, "r"); // aqui abro el archivo de alumnos
  if (fp == NULL) {
    printf ("No es posible abrir el archivo %s para su lectura\n" , archi_alumnos);
    return NULL;
    }

  b = fread(&n, sizeof(int),1,fp); //esto es un booleano, para ver si es posible abrir el archivo  , ademas leo el primer numero n del archivo
  if (b == 0){
      printf("No es posible abrir el archivo\n" );
      return NULL;
    }

  w = (alumno*)malloc(sizeof(alumno)*n); // reservo memoria  n variables del tipo alumno y ademas compruebo si hay memoria suficiente
  if (w == NULL){
    printf("No hay memoria suficiente\n");
    return NULL;
    }

  b = fread(w,sizeof(alumno),n,fp);
    if (b != n){
        printf("No es posible abrir el archivo\n");
        }

      fclose(fp);
      return w;
    }
