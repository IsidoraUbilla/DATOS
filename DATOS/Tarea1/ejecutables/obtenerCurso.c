#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*****
*
TipoFunción NombreFunción
curso* obtenerCurso
******
*
Resumen Función: Funcion implementada para obtener los cursos del archivo "cursos.dat" y guardarlos en un arreglo

******
*
Input:
char* archi_cursos: puntero del tipo caracter que apunta el nombre del archivo "alumnos.dat"

*
.......
******
*
Returns:
TipoRetorno, Descripción retorno
retorna un puntero del tipo curso que apunta a un arreglo con todos los cursos que hay en el archivo "cursos.dat"
*****/

typedef struct {
  int id_curso;
  char sigla_curso [7];
  char nombre_curso [30];
  int integrantes_por_grupo;
} curso;



curso* obtenerCurso (char *archi_cursos){  // tiene que recibi el char con el nombre del archivo cursos
  FILE *fp;
  int m,z,i;
  curso *c, aux;


  fp = fopen(archi_cursos, "r");   // aqui abro el archivo de cursos :D
  if (fp == NULL) {
    printf ("No es posible abrir el archivo %s para su lectura\n" , archi_cursos);
    return NULL;
  }

  z = fread(&m, sizeof(int),1,fp);
  if (z == 0) {
    printf("No es posible abrir el archivo\n" );
    return NULL;
    }

  c = (curso*)malloc(sizeof(curso)*m);
  if (c == NULL){
    printf("No hay memoria suficiente\n");
    return NULL;
    }
  z = fread(c,sizeof(curso),m,fp);
    if (z != m) {
      printf("No se leyeron todos los cursos\n" );
      }

   fclose(fp);
   return c;
}
