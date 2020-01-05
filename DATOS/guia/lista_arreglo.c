#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10000

typedef struct {
    int maxSize;
    int tam;
    int curr;
    int *arreglo;
} tLista_arreglo;

tLista_arreglo* constructor (){
    tLista_arreglo* l;
    l = (tLista_arreglo*)malloc(sizeof(tLista_arreglo));
    l->maxSize = MAXSIZE;
    l->tam = 0;
    l->curr = 0;
    l->arreglo = (int*)malloc(sizeof(int)*MAXSIZE);
    return l;
}


void insert(tLista_arreglo* l, int elemento){
    int i;
    if (l->tam <= l->maxSize){
        for (i = l->tam; i > l->curr; --i){
            l->arreglo[i] = l->arreglo [i-1];
        }
        l->arreglo[i] = elemento;
        ++l->tam;
        l->curr = l->tam;
    }
}

void moveToEnd(tLista_arreglo* l){
    l->curr = l->tam;
}

void append(tLista_arreglo* l, int elemento){
    if (l->tam <= l->maxSize){
        moveToEnd(l);
        l->arreglo[l->tam] = elemento;
        ++l->tam;
    }
}

void moveToStar(tLista_arreglo* l){
    l->curr = 0;
}

void moveToPos(tLista_arreglo* l, int pos){
    if (l->curr!= pos && pos<= l->tam){
        l->curr = pos;
    }
}

void prev(tLista_arreglo* l){
    int a;
    if (l->curr != 0){
        a = l->curr--;
        l->curr = a;
    }
}

void next(tLista_arreglo* l){
    int a;
    if (l->curr != l->tam){
        a = l->curr++;
        l->curr = a;
    }
}

int currPos(tLista_arreglo* l){
    return l->curr;
}

int length(tLista_arreglo* l){
    return l->tam;
}

void destructor (tLista_arreglo* l){
    free (l);
}

void clear (tLista_arreglo* l){
    free(l->arreglo);
    l->arreglo = NULL;
    l->tam = l->curr = 0;
}

int select1(tLista_arreglo* l, int i){
    int elemento;
    elemento = l->arreglo[i];
    return elemento;
}

int rank(tLista_arreglo* l, int x){
    int i;
    for (i=0; i<l->tam; ++i){
        moveToPos(l,i);
        if (l->arreglo[l->curr] == x){
            return i;
        }
    }
    return -1;
}

tLista_arreglo* intTolist ( int n){
    tLista_arreglo* l;
    l = constructor();
    int resto;
    while (n != 0){

        resto = n%10;
        moveToStar(l);
        insert(l,resto);
        n = n/10;

        if ( n < 10){
            moveToStar(l);
            insert(l,n);
            n = 0;
        }
    }
    return l
}



int main(){

    tLista_arreglo* lista;
    int a;
    lista = constructor();

    a = 8273344 ;
    intTolist (lista,a);

    printf ("%d\n",lista->arreglo[0]);
    printf ("%d\n",lista->arreglo[1]);
    printf ("%d\n",lista->arreglo[2]);
    printf ("%d\n",lista->arreglo[3]);
    printf ("%d\n",lista->arreglo[4]);
    printf ("%d\n",lista->arreglo[5]);
    printf ("%d\n",lista->arreglo[6]);


    clear(lista);
    destructor(lista);

    return 0;
}
