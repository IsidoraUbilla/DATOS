#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tda1.c"
#include "f1.c"

/*****
*
TipoFunción NombreFunción : main
******
*
Resumen Función : funcion principal que recibe el input con los comandos malloc y free, esta funcion crea las listas, trabaja en 3 casos segun sea malloc sin haber realizado free anteriormente, con malloc con un free ya realizado y con el caso de hacer free
******
*
Input: void
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno : retorna int, la funcion retornara 0 si funciona bien, ademas crea un archivo output.dat para retornar con la ejecucion de cada comando solicitado en el input
*****/

int main (){

    int m, n, i,l,l1;   // m : memoria , n : cant operaciones ,  i: contadores de for , l1 : para arreglar los nodos
    int suma = 0; int flag = 0;

    FILE *fp;
    FILE *fp_out;
    tLista *lista1;
    tLista *lista2;

    fp = fopen("input1.dat", "r");
    fp_out = fopen("output1.dat", "w");
    fscanf(fp, "%d %d" , &m, &n);

    lista1 = constructor();
    lista2 = constructor();

    append1(lista1,1,m);
    fprintf(fp_out,"\n");

    for(i=0; i<n; ++i){
        char mf[10];
        int o,x,r, pf;  // o:operacion, x:malloc o free, r: revisar memoria, pf: posicion del fit
        int new = 0;


        fscanf(fp,"%s %d", mf, &o);
        x = MoF(mf);
        suma = o + suma;

        if (x == 0 && flag == 0){ //entonces es malloc
            if (length(lista2) == 0){ //si es lista vacia
                append1(lista2,1,o);
                fprintf(fp_out,"Bloque de %d bytes asignado a partir del byte 1\n", o);
                l = ObtenerValor2(lista2,i);
                l1 = l+1;
                update(lista1, l1);
            }

            else {
                r = revisar(lista1,o); //revisa si queda memoria
                if (r != 0){
                    fprintf(fp_out,"Bloque de %d bytes NO puede ser asignado\n",o);
                }

                else{

                    append1(lista2,l1,suma);
                    fprintf(fp_out,"Bloque de %d bytes asignado a partir del byte %d\n",o,l1);
                    moveToEnd(lista2);
                    new = suma+1;
                    update(lista1, new);
                    l = ObtenerValor2(lista2,i);
                    l1= l + 1;

                }
            }
        }

        else if (x == 0 && flag == 1) {
            r = revisar(lista1,o);
            if (r == -1){
                fprintf(fp_out,"Bloque de %d bytes NO puede ser asignado \n",o);

            }

            else{
                pf = fit(lista2, o);
                if (pf != -1){
                    l = ObtenerValor2(lista2,pf) + 1;
                    l1 = ObtenerValor2(lista2,pf) + o;
                    insert1(lista2,l,l1);
                    fprintf(fp_out,"Bloque de %d bytes asignado a partir del byte %d\n",o,l);
                    new = ObtenerValor1(lista1,r)+ o;
                    update(lista1,new);

                }
                else{
                    moveToEnd(lista2);
                    l = ObtenerValor2(lista2,GetValue(lista2)) + 1;
                    l1 = ObtenerValor2(lista2,GetValue(lista2)) + o;
                    append1(lista2,l,l1);
                    fprintf(fp_out,"Bloque de %d bytes asignado a partir del byte %d\n",o,l);
                    moveToPos(lista1,r);

                    new = l+o;
                    update(lista1, new);

                }
            }

        }

        else {
            flag = 1;
            buscar_eliminar_Nodo_l2(lista1,lista2,o, fp_out);
            moveToStar(lista1);
        }

}
    fclose(fp);
    fclose(fp_out);

    clear(lista1);
    clear(lista2);

    destructor(lista1);
    destructor(lista2);

    return 0;
}
