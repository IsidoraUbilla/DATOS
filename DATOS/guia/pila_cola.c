#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10000

// pila implementada con arreglos
typedef struct{
    int maxSize; //tam max
    int top; //tam actual
    char *arreglo;
} Pila;

/* pila implementada con punteros
typedef struct nodo{
    int info;
    struct nodo *sig;
} tnodo;

typedef struct {
    int tam;
    int top;
    tnodo *cabeza;
} pila; */

Pila* constructorP(){
    Pila* p;
    p = (Pila*)malloc(sizeof(Pila));
    p->maxSize = MAXSIZE;
    p->top = 0;
    p->arreglo = (char*)malloc(sizeof(char)*MAXSIZE);
    return p;
}

void push(Pila* p, char elemento){
    int a;
    if (p->top <= p->maxSize){
        a = ++p->top;
        p->arreglo[a-1] = elemento;
        p->top = a;
    }
}

void pop(Pila* p){
    int x;
    if (p->top != 0){
        x = --p->top;
        p->top = x;
    }
}

char topValue(Pila* p){
    char a;
    int x;
    x = p->top-1;
    a = p->arreglo[x];
    return a;
}

int size(Pila* p){
    int a;
    a = p->top;
    return a;
}

void destructorP(Pila* p){
    free (p);
}

void clear(Pila* p){
    free(p->arreglo);
    p->arreglo = NULL;
    p->top = 0;
}


//cola circular

typedef struct {
    int tam_max;
    int tam;
    int inicio;
    char* arr;
} cola_cir;

cola_cir* constructorC (){
    cola_cir* c;
    c = (cola_cir*)malloc(sizeof(cola_cir));
    c->tam_max = MAXSIZE;
    c->tam = 0;
    c->inicio = 0;
    c->arr = (char*)malloc(sizeof(char)*MAXSIZE);
    return c;
}

void enqueue(cola_cir* c, char e){
    int i;
    if (c->tam <= c->tam_max){
        i = (c->inicio+c->tam)%c->tam_max;
        c->arr[i] = e;
        ++c->tam;
    }
}

void dequeue(cola_cir* c){
    if (c->tam !=0){
        c->inicio = (1+c->inicio)%c->tam_max;
        c->tam--;
    }
}

char frontValue(cola_cir* c){
    char a;
    int x;
    x = c->inicio;
    a = c->arr[x];
    return a;
}

int size_cola(cola_cir* c){
    int x;
    x = c->tam;
    return x;
}

void destructorC(cola_cir* c){
    free (c);
}

void clearC(cola_cir* c){
    free(c->arr);
    c->arr = NULL;
    c->tam = 0;
    c->inicio = 0;
}


int palin(char* palabra, int n){

    Pila* p;
    cola_cir* c;
    int i;
    char z,z1;

    p = constructorP();
    c = constructorC();

    for (i=0; i<n ; ++i){
        push (p, palabra[i]);
        enqueue (c, palabra[i]);
    }

    for (i=0; i<n; ++i){
        z = topValue(p);
        z1 = frontValue(c);
        if (z!=z1){
            clearC(c);
            clear(p);

            destructorC(c);
            destructorP(p);
            return -1;
        }
        pop(p);
        dequeue(c);

    }

    clearC(c);
    clear(p);

    destructorC(c);
    destructorP(p);

    return 0;
}

Pila* remover(Pila* p, char x){
    Pila* p2 = constructorP();

    while (topValue(p) != 0){
        if (topValue(p) == x){
            pop(p);
        }
        push(p2,topValue(p));
        pop(p);
    }

    while (topValue(p2) != 0){
        push(p,topValue(p2));
        pop(p2);
    }

    return p;
}




int main(){
    int i;
    Pila* palabra2;
    Pila* Palabra = constructorP();
    char a,b,c,d;
    a = 'h';
    b = 'o';
    c = 'l';
    d = 'a';
    push (Palabra, a);
    push (Palabra, b);
    push (Palabra, c);
    push (Palabra, d);

    palabra2 = remover(Palabra,'l');

    for (i=0; i < size(palabra2); i++){
        printf("%c\n",palabra2->arreglo[i] );
    }

    return 0;
}
