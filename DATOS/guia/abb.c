#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct nodoABB { //struct de un nodo de ABB
    int info; //informacion del nodo
    struct nodoABB *left;
    struct nodoABB *right;
} nodoABB;

typedef struct {   // struct de un arbol
    nodoABB *raiz;
    int nElems;
} Abb;

Abb* ConsTree() {  // Crear un arbol vacio
    Abb* t;
    t = (Abb*)malloc(sizeof(Abb));
    t->raiz = NULL;
    t->nElems = 0;
    return t;
}

void DesTree(Abb *t){ // destruye un arbol
    free(t);
}

void clearHelp (nodoABB *r){  //funcion auxiliar recursiva para eliminar nodos del arbol, recibe un puntero al nodo raiz
    if (r == NULL){
        return;
    }
    clearHelp (r->left);
    clearHelp (r->right);
    free ((void *)r);
}

void clear (Abb *t){  // funcion que borra todos los nodos
    clearHelp(t->raiz);
    t->raiz = NULL;
    t->nElems = 0;
}

int getValue(nodoABB *n){
    int x;
    x = n->info;
    return x;
}

int findHelp(nodoABB *n, int item){

    if (n == NULL){
        return 0; // item no esta en el ABB
    }

    if (getValue(n) == item){
        return 1; //item encontrado
    }

    if (item < getValue(n)){
        return findHelp(n->left, item);
    }

    else{
        return findHelp(n->right, item);
    }
}

int buscar(Abb *t, int item){

    int x;
    x = findHelp(t->raiz, item);
    return x;
}

nodoABB* nodo_insert_help(nodoABB* a, int item){


    if (item < getValue(a) && a->left == NULL){
        return a;
    }

    if(item > getValue(a) && a->right == NULL){
        return a;
    }

    if (a->left == NULL && a->right == NULL){
        return a;
    }

    if (item < getValue(a)){
        return nodo_insert_help(a->left, item);
    }

    else{
        return nodo_insert_help(a->right, item);
    }
}

nodoABB* nodo_insert(Abb* t, int item){
    nodoABB* here;
    here = nodo_insert_help(t->raiz, item);
    return here;
}

void insert(Abb* t, int item){

    int x;
    nodoABB* aux;
    nodoABB* aux1;

    x = buscar(t,item);

    if (x == 0){ // el item no esta entonces podemos hacer insert

        if(t->nElems == 0){// caso cuando es arbol vacio
            t->raiz = (nodoABB *)malloc(sizeof(nodoABB));
            t->raiz->info = item;
            t->nElems++;
            t->raiz->right = NULL;
            t->raiz->left = NULL;
        }

        else{
            aux = nodo_insert(t,item);
            if (getValue(aux) < item){ //derecha
                aux1 = (nodoABB *)malloc(sizeof(nodoABB));
                aux1->info = item;
                aux1->right = NULL;
                aux1->left = NULL;
                t->nElems++;
                aux->right = aux1;

            }


            else{ //izq
                aux1 = (nodoABB *)malloc(sizeof(nodoABB));
                aux1->info = item;
                aux1->right = NULL;
                aux1->left = NULL;
                t->nElems++;
                aux->left = aux1;

            }
        }

    }

}

/*int getGrado(nodoABB *n){

    if(n->left!=NULL && n->right!=NULL){
        return 2;
    }
    else if(n->left!=NULL && n->right==NULL){
        return 1;
    }
    else if( n->left==NULL && n->right!=NULL){
        return 1;
    }
    else{
        return 0;
    }
}

nodoABB* buscarHelp(nodoABB* n, int item){

    if (n == NULL){
        return n; // item no esta en el ABB
    }

    if (getValue(n) == item){
        return n; //item encontrado
    }

    if (item < getValue(n)){
        return buscarHelp(n->left, item);
    }

    else{
        return buscarHelp(n->right, item);
    }
}

nodoABB* buscar_eliminar(Abb* t, int item){

    nodoABB* aqui;
    aqui = buscarHelp(t->raiz, item);
    return aqui;
}

nodoABB* nodo_prev_help(nodoABB* a, int item){


    if (item < getValue(a) && a->left == item){
        return a;
    }

    if(item > getValue(a) && a->right == item){
        return a;
    }

    if (a->left == NULL && a->right == NULL){
        return a;
    }

    if (item < getValue(a)){
        return nodo_insert_help(a->left, item);
    }

    else{
        return nodo_insert_help(a->right, item);
    }
}

nodoABB* nodo_prev_eliminar(Abb* t, int item){
    nodoABB* this;
    this = nodo_prev_help(t->raiz, item);
    return this;
}

void remove(Abb* t, int eliminar){

    nodoABB* nodo_eliminar;
    nodoABB* nodo_prev_a_eliminar;
    int caso;

    nodo_eliminar = buscar_eliminar(t,eliminar);

    if (nodo_eliminar != NULL){  //significa que esta

        caso = getGrado(nodo_eliminar);

        if (caso == 0){ //cuando es hoja   CASO1
            nodo_prev_a_eliminar = nodo_prev_eliminar(t,eliminar);
        }
    }

}*/
