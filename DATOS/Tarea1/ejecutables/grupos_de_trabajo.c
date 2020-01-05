#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "obtenerCurso.c"
#include "obtenerAlumnos.c"
#include "obtenernumero.c"
#include "archivocurso1.c"


int main(){

    int i,j;
    curso *x;
    alumno *y;
    int cur,alu;


    x = obtenerCurso("cursos.dat");
    y = obtenerAlumnos("alumnos.dat");


    cur= obtenernumero("cursos.dat");
    alu= obtenernumero("alumnos.dat");


    ArchivoCurso(x,y,cur,alu);

    free((void *)x);

    free((void *)y);

    return 0;

    }
