#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "random.c"

/*****
*
int ArchivoCurso(curso* arreglo_de_cursos, alumno* arreglo_de_alumnos, int cantidad_de_cursos_total, int cantidad_de_alumnos_total){

******
*
Resumen Función:
Esta función recorre los arreglos de cursos para luego ir revisando alumno por alumno si esta dentro del curso en cuestion, con todos los alumnos que esten en el curso se crea un arreglo nuevo, el arreglo se envia a la funcion random y finalmente crea el archivo correspondiente segun un algoritmo de creacion de grupos
******
*
Input:
tipoParámetro NombreParámetro : Descripción Parámetro

curso* arreglo_de_cursos : puntero del tipo curso que apunta al arreglo con todos los cursos que hay en el archivo que se debe leer.
alumno* arreglo_de_alumnos : puntero del tipo alumno que apunta al arreglo con todos los alumnos que hay en el archivo que se debe leer.
int cantidad_de_cursos_total : puntero al entero con la cantidad total de cursos en el arreglo de cursos.
int cantidad_de_alumnos_total : puntero al entero con la cantidad total de alumnos en el arreglo de alumnos.

*
.......
******
*
Returns:
TipoRetorno, Descripción retorno
retorno 0, no retorna nada.
*****/




// funcion para crear archivos

int ArchivoCurso(curso* arreglo_de_cursos, alumno* arreglo_de_alumnos, int cantidad_de_cursos_total, int cantidad_de_alumnos_total){

    int e;
    srand(time(NULL));
    int i,j,count; //contadores de for
    int c;
    int* c1; 
    int cant_ramos, cant_alumnos_por_grupo, cant_de_grupos,cant_alum_grupos_incom;
    int suma=0;
    char** alumnos_en_el_curso;
    char *nombre, *sigla;
    for (i=0; i<cantidad_de_cursos_total; ++i){
    	suma = 0;
        c = arreglo_de_cursos[i].id_curso;
        cant_alumnos_por_grupo = arreglo_de_cursos[i].integrantes_por_grupo;
        nombre = arreglo_de_cursos[i].nombre_curso;
        sigla = arreglo_de_cursos[i].sigla_curso;
        alumnos_en_el_curso = (char**)malloc(sizeof(char*)*cantidad_de_alumnos_total);
        for (j=0; j<cantidad_de_alumnos_total; ++j){
            cant_ramos = arreglo_de_alumnos[j].numero_cursos;
            c1 = arreglo_de_alumnos[j].id_cursos_inscritos;
            for (count=0; count<cant_ramos; ++count){
                if (c1[count]==c){
                    alumnos_en_el_curso[suma]=(char*)malloc(sizeof(char)*41); // 41 numero maximo de caracteres por nombre
                    strcpy(alumnos_en_el_curso[suma],arreglo_de_alumnos[j].nombre_completo);
                    suma=suma+1;
                    count=cant_ramos;


                }

            }
        }
        if (cant_alumnos_por_grupo <= 0){ //Comprobación para ver si la cantidad de alumnos por grupos es 0
            return 0;
        }

        FILE *fp;
        char n1[50] = "grupos_";
        char boi[3] = " - ";
        char* nombrearchivo;
        char* primera_fila;


        cant_alum_grupos_incom = suma%cant_alumnos_por_grupo;
        if (cant_alum_grupos_incom==0){
            cant_de_grupos = suma/cant_alumnos_por_grupo;
        }
        else{
            cant_de_grupos = (suma/cant_alumnos_por_grupo)+1;
        }


        strcat(n1,sigla);
        nombrearchivo= strcat(n1,".txt");

        fp = fopen(nombrearchivo,"w");

        if (fp == NULL){
            printf ("No es posible abrir el archivo para su lectura\n");
            return 0;
        }


        char** a;
        a = random2(suma,alumnos_en_el_curso);
        fprintf(fp,"%s - %s\n",sigla,nombre);
        fprintf(fp,"\n");


        int contador1=0;

        if (cant_alum_grupos_incom == 0){
            int guarda_pos=0;
            while (cant_de_grupos > contador1){
            	fprintf(fp,"\n");
                fprintf(fp, "Grupo %d:\n",contador1+1);
                int contador3=0;
                while (contador3 < cant_alumnos_por_grupo){
                    fprintf (fp, "%s\n", a[guarda_pos]);
                    contador3 = contador3 + 1;
                    guarda_pos = guarda_pos+1;
                }
                contador1 = contador1 + 1;
                fprintf(fp,"\n");
            }
        }
        else {
            int guarda_pos=0;
            while (contador1 < cant_de_grupos){
                fprintf(fp, "Grupo %d:\n",contador1+1);
                int contador2=0;

                while (contador2<cant_alumnos_por_grupo){
                    fprintf (fp, "%s\n", a[guarda_pos]);
                    contador2 = contador2 + 1;
                    e=suma-1;
                    if (e==guarda_pos){
                        break;
                    }
                    guarda_pos = guarda_pos+1;
                }
                contador1 = contador1 + 1;
                fprintf(fp,"\n");
            }

        }
        fclose(fp);


        //Free

        int a1;
        for (a1=0;a1<suma;a1++){
            free(a[a1]);
        }
        free(a);

        int i1;
        for (i1=0; i1<suma; ++i1){
            free(alumnos_en_el_curso[i1]);
        }

        free(alumnos_en_el_curso);

    }
    return 0;
}
