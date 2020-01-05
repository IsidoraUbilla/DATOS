#include <stdio.h>
#include <stdlib.h>


/*****
*
TipoFunción NombreFunción : Int MoF
******
*
Resumen Función : Funcion utilizada para revisar si la operacion a realizar es malloc o free por medio de una comparacion entre dos arreglos de caracteres
******
*
Input: puntero del tipo char que apunta al arreglo que almacena caracteres los cuales indican la operación a realiza
tipoParámetro NombreParámetro : int (char * mf)
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno : int, retorna 0 si es malloc, 1 si es free
*****/

int MoF( char* mf ){ //funcion para ver si es malloc o free
    char m[10]; char f[10];

    strcpy(m,"malloc");
    strcpy(f,"free");

    if (strcmp(mf,m) == 0) return 0;

    else {
        return 1;
    }
}

/*****
*
TipoFunción NombreFunción : void Regresar
******
*
Resumen Función : Funcion utilizada luego de un free para devolver la memoria liberada de la lista2 a la lista1 y en caso de que la lista 1 quede con bloques continuos de meoria, los unifica en un solo nodo; EL mecanismo utilizado se divide en dos casos, si la lista1 solo tiene un nodo o al contrario tiene mas de uno, si tiene mas de un nodo entonces revisa la lista1 hasta saber el espacio de insercion de la memoria a liberar
******
*
Input: puntero del tipo lista que apunta a la lista 1; entero con la informacion del byte inicial a devolver; entero con la informacion del byte final a devolver
tipoParámetro NombreParámetro : tLista* l; int info1; int info2
*
.......
******
*
Returns: void, funcion sin retorno.
*****/

void Regresar(tLista* l, int info1, int info2){

    int i;
    int x;
    int max, maxSig, pos;

    if (length(l) == 1) {  //si la lista1 solo tiene un elemento
        maxSig = l->curr->info1;

        if (maxSig-1 == info2 ){
            l->curr->info1 = info1;
        }

        else {
            moveToStar(l);
            insert1(l, info1, info2);
        }
    }

    else {
        for (i = 0; i < length(l); ++i){ //recorro nodo por nodo hasta saber donde va el que quiero regresar
            moveToPos(l,i);
            if ( l->curr->info2 < info1){
                max = l->curr->info2;
                maxSig = l->curr->sig->info1;
                pos = i;
            }

        }



        moveToPos(l,pos);

        if ( max+1 == info1 && maxSig-1 == info2 ){
            l->curr->info2 = l->curr->sig->info2;
            x = pos+1;
            moveToPos(l,x);
            remove1(l);
        }
        else if ( max+1 == info1){
            l->curr->info2 = info2;
        }

        else {
            insert1(l, info1, info2);
        }
    }

}

/*****
*
TipoFunción NombreFunción : int revisar
******
*
Resumen Función : funcion utilizada para revisar si queda memoria suficiente disponible para reservar a partir de la lista1, se analizan los casos cuando lista1 tiene un solo nodo o mas de 1
******
*
Input: puntero del tipo lista que apunta a la lista 1; entero con la cantidad de memoria que se quiere solicitar para reservar,es decir, la cantidad de memoria que se quiere revisar si esta disponible en la lista 1
tipoParámetro NombreParámetro : tLista* l, int cant
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno : int, retorna 0 si es que se puede en caso de que la lista1 solo esat formada por un nodo, en caso de que la lista1 tenga mas de un nodo retorna el entero i que indica la posicion del nodo donde se puede reservar la memoria solicitada, en caso de que la memoria este llena retorna un -1
*****/

int revisar(tLista* l, int cant){
    int tam,i;

    if (length(l) == 1){  //cuando l1 solo tiene un nodo
        tam = l->curr->info2 - l->curr->info1 + 1;

        if (cant > tam){
            return -1; //no se puede, memoria llena
        }

        else {
            return 0; //se puede
        }
    }

    else { // cuando l1 tiene mas de un nodo
        for (i=0; i < length(l);++i){
            moveToPos(l,i);
            tam = l->curr->info2 - l->curr->info1 +1;
            if (cant <= tam){
                return i; // se puede y retorna la pos donde se puede solicitar tal cantidad de memoria
            }

        }

        return -1; //no se puede, memoria llena

    }

}

/*****
*
TipoFunción NombreFunción : int fit
******
*
Resumen Función : funcion que busca si es posible calzar entre dos nodos una cantidad de memoria en la lista2
******
*
Input: puntero del tipo lista que apunta de a la lista2 ; entero que contiene la cantidad de memoria que se busca saber si es posible calzar entre nodos de la lista
tipoParámetro NombreParámetro : tLista* l ; int o
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno : Retorna enteros, si no es posible calzar la memoria entregada por el parametro entonces retorna -1, en cambio, si es posible calzar la memoria retorna el un entero i que indica la posicion donde calza
*****/

int fit(tLista* l, int o){

    int espacio,i,i1,aux1,aux2;

    for (i=0; i < length(l); ++i){
        aux2 = ObtenerValor2(l,i);
        i1 = i+1;
        aux1 = ObtenerValor1(l,i1);
        espacio = aux1-aux2-1;
        if (espacio != 0){
            if (o <= espacio ) {
                return i;
            }
        }
    }
    return -1;
}

/*****
*
TipoFunción NombreFunción : void buscar_eliminar_Nodo_l2
******
*
Resumen Función : funcion que busca el nodo a eliminar cuando se quiere hacer un free en la lista2 revisando cada nodo hasta encontrar el indicado, luego llamando a la funcion regresar libera el nodo de la lista2
******
*
Input: puntero del tipo lista que apunta a la lista1; puntero del tipo lista que apunta a la lista2; entero o que indica el primer byte del nodo que se necesita buscar; archivo output donde se imprime el bloque liberado
tipoParámetro NombreParámetro : tLista* l1,tLista* l2, int o, FILE* fp_out
*
.......
******
*
Returns: void
*****/

void buscar_eliminar_Nodo_l2 (tLista* l1,tLista* l2, int o, FILE* fp_out) {

    int i1, x_1, tam, aux1, aux2 ;


    for (i1=0; i1 < length(l2); ++i1){  //por cada nodo de la lista 2
        x_1 = ObtenerValor1(l2,i1);
        if (x_1 == o){
            aux1 = x_1;
            aux2 = ObtenerValor2(l2,i1);
            tam = aux2-aux1+1;
            moveToPos(l2,i1);
            remove1(l2);
            fprintf(fp_out,"Bloque de %d bytes liberado\n", tam);
            Regresar(l1,aux1,aux2);  //le envio el 31 y el 40

        }

    }

}
