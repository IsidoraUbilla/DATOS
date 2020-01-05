#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct nodoABB { //struct de un nodo de ABB
    int info; //informacion del nodo
    int cant;//cantidad de numeros a la izquierda del nodo
    struct nodoABB *left;
    struct nodoABB *right;
} nodoABB;

typedef struct {   // struct de un arbol
    nodoABB *raiz;
    int nElems; //numero de elementos del arbol
} Abb;


/*****
*
TipoFunción NombreFunción : ConsTree
******
*
Resumen Función : funcion que construye un arbol inicializando vacio
******
*
Input: void

*
.......
******
*
Returns: Abb*
TipoRetorno, Descripción retorno : abb* ; retorna un puntero a un arbol vacio
*****/

Abb* ConsTree() {
    Abb* t;
    t = (Abb*)malloc(sizeof(Abb));
    t->raiz = NULL;
    t->nElems = 0;
    return t;
}

/*****
*
TipoFunción NombreFunción : DesTree
******
*
Resumen Función : funcion que destruye un arbol por medio de free
******
*
Input: puntero de tipo arbol
tipoParámetro NombreParámetro : Abb* t
*
.......
******
*
Returns: void

*****/

void DesTree(Abb *t){ // destruye un arbol
    free(t);
}

/*****
*
TipoFunción NombreFunción : clearHelp
******
*
Resumen Función : funcion auxiliar recursiva para eliminar nodos del arbol
******
*
Input: recibe un puntero al nodo raiz
tipoParámetro NombreParámetro : nodoABB *r
*
.......
******
*
Returns: void

*****/

void clearHelp (nodoABB *r){
    if (r == NULL){
        return;
    }
    clearHelp (r->left);
    clearHelp (r->right);
    free ((void *)r);
}

/*****
*
TipoFunción NombreFunción : clear
******
*
Resumen Función : funcion que borra todos los nodos del arbol reiniciandolo vacio
******
*
Input: recibe un puntero al arbol
tipoParámetro NombreParámetro : Abb *t
*
.......
******
*
Returns: void

*****/

void clear (Abb *t){
    clearHelp(t->raiz);
    t->raiz = NULL;
    t->nElems = 0;
}

/*****
*
TipoFunción NombreFunción : getValue
******
*
Resumen Función : funcion que retorna la informacion del nodo
******
*
Input: puntero al nodo a revisar
tipoParámetro NombreParámetro :  nodoABB *n
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno : int ; retorna un entero con la informacion del nodo
*****/

int getValue(nodoABB *n){
    int x;
    x = n->info;
    return x;
}

/*****
*
TipoFunción NombreFunción : getCant
******
*
Resumen Función : funcion que retorna la cantidad de nodos menor al nodo entregado
******
*
Input: puntero al nodo a revisar
tipoParámetro NombreParámetro :  nodoABB *n
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno : int ; retorna un entero con la cantidad de nodos menor al recibido como parametro
*****/

int getCant(nodoABB *n){
    int x;
    x = n->cant;
    return x;
}

/*****
*
TipoFunción NombreFunción : findHelp
******
*
Resumen Función : funcion auxiliar recursiva para encontrar un item en el arbol
******
*
Input: puntero al nodo a revisar ; entero con el item que se busca encontrar en los nodos
tipoParámetro NombreParámetro :  nodoABB *n ; int item
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno : int ; retorna 0 si el item no esta en el arbol, retorna 1 si el item esta en el arbol
*****/

int findHelp(nodoABB *n, int item){

    if (n == NULL){
        return 0; // item no esta en el ABB
    }

    if (getValue(n) == item){
        return 1; //item encontrado
    }

    if (item < getValue(n)){ //si el item es menor que el nodo, se recorre la parte izquierda
        return findHelp(n->left, item);
    }

    else{ //si el item es mayor que el nodo, se recorre la parte derecha
        return findHelp(n->right, item);
    }
}

/*****
*
TipoFunción NombreFunción : buscar
******
*
Resumen Función : funcion que busca si esta o no un nodo en el arbol, llama a la funcion recursiva findHelp
******
*
Input: puntero al arbol en el que se quiere buscar ; entero con el item a buscar en el arbol
tipoParámetro NombreParámetro :  Abb *t ; int item
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno :  int ; retorna 1 si esta y 0 si no se encuentra
*****/

int buscar(Abb *t, int item){

    int x;
    x = findHelp(t->raiz, item);
    return x;
}

/*****
*
TipoFunción NombreFunción : nodo_insert_help
******
*
Resumen Función : funcion auxiliar recursiva para encontrar el nodo previo a la insercion
******
*
Input: puntero al nodo raiz ; entero con el item a insertar en el arbol
tipoParámetro NombreParámetro :  nodoABB* a ; int item
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno :  nodoABB ; retorna el nodo previo a la insercion
*****/

nodoABB* nodo_insert_help(nodoABB* a, int item){


    if (item < getValue(a) && a->left == NULL){
        a->cant++;
        return a;
    }

    if(item > getValue(a) && a->right == NULL){
        return a;
    }

    if (a->left == NULL && a->right == NULL){
        return a;
    }

    if (item < getValue(a)){
        a->cant++;
        return nodo_insert_help(a->left, item);
    }

    else{
        return nodo_insert_help(a->right, item);
    }
}

/*****
*
TipoFunción NombreFunción : nodo_insert
******
*
Resumen Función : funcion para encontrar el nodo previo a la insercion, llama a la funcion recursiva nodo_insert
******
*
Input: puntero al arbol ; entero con el item a insertar en el arbol
tipoParámetro NombreParámetro :  Abb* t ; int item
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno :  nodoABB ; retorna el nodo previo a la insercion
*****/

nodoABB* nodo_insert(Abb* t, int item){
    nodoABB* here;
    here = nodo_insert_help(t->raiz, item);
    return here;
}

/*****
*
TipoFunción NombreFunción : insert
******
*
Resumen Función : funcion utilazada para insertar un nodo(item) en el arbol
******
*
Input: puntero al arbol donde se quiere insertar ; entero con el item a insertar en el arbol
tipoParámetro NombreParámetro :  Abb* t ; int item
*
.......
******
*
Returns: void
*****/

void insert(Abb* t, int item){

    int x;
    nodoABB* aux;
    nodoABB* aux1;

    x = buscar(t,item);

    if (x == 0){ // el item no esta entonces podemos hacer insert

        if(t->nElems == 0){// caso cuando es arbol vacio
            t->raiz = (nodoABB *)malloc(sizeof(nodoABB)); //se reserva espacio para el nodo raiz
            t->raiz->info = item;
            t->raiz->cant = 0;
            t->nElems++;
            t->raiz->right = NULL;
            t->raiz->left = NULL;
        }

        else{ //cuando el arbol ya tiene nodos
            aux = nodo_insert(t,item);
            if (getValue(aux) < item){ //derecha
                aux1 = (nodoABB *)malloc(sizeof(nodoABB));
                aux1->info = item;
                aux1->right = NULL;
                aux1->left = NULL;
                aux1->cant = 0;
                t->nElems++;
                aux->right = aux1;

            }


            else{ //izq
                aux1 = (nodoABB *)malloc(sizeof(nodoABB));
                aux1->info = item;
                aux1->right = NULL;
                aux1->left = NULL;
                aux1->cant = 0;
                t->nElems++;
                aux->left = aux1;

            }
        }

    }

}


/*****
*
TipoFunción NombreFunción : getGrado
******
*
Resumen Función : funcion que retorna el grado del nodo
******
*
Input: puntero al nodo a evaluar
tipoParámetro NombreParámetro :  nodoABB* n
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno :  int ; es grado 0 cuando es hoja, 1 con un solo hijo, 2 con ambos hijos
*****/

int getGrado(nodoABB *n){

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


/*****
*
TipoFunción NombreFunción : rank_help
******
*
Resumen Función : funcion auxiliar recursiva que encuentra los nodos menores a un numero dado por parametro, lleva la cuenta con el entero i
******
*
Input: puntero al nodo a revisar, al comienzo es el nodo raiz ; entero con el numero respecto al cual se buscan los nodos menores o iguales ; entero contador
tipoParámetro NombreParámetro :  nodoABB* n ; int num ; int i
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno :  int ; retorna 0 si es un arbol vacio, de otra forma retorna i que es el contador
*****/

int rank_help(nodoABB *n, int num, int i){

	if (n==NULL){ //si es un arbol vacio, retorna 0
		return 0;
	}
	else if(getGrado(n)==2){ //si el nodo es de grado dos y es menor que num, suma al contador la cantidad de nodos menores +1
		if(getValue(n)<=num){
			i++;
			i=i+n->cant;
			return rank_help(n->right,num,i); //va directamente a la derecha
		}
		else{ //si el nodo es mayor que num, recorre la izquierda, ya que la derecha va a ser si o si mayor que num
			return rank_help(n->left,num,i);
		}
	}
	else if(getGrado(n)==1){ //si el nodo es de grado 1 y es menor que num, suma la cantidad de nodos menores +1
		if(getValue(n)<=num){
			i++;
			i=i+n->cant;
			if(n->right==NULL){ //como la parte izquierda ya esta vista, verifica si existen nodos a la derecha, si no es asi retorna i
				return i;
			}
			else{ //si hay mas nodos, va hacia la derecha
				return rank_help(n->right,num,i);
			}
		}
		else{ //si el nodo es mayor que num, se verifica si hay mas nodos a la izquierda o derecha y se va para alla
			if(n->left!=NULL){
				return rank_help(n->left,num,i);
			}
			else{
				return rank_help(n->right,num,i);
			}
		}
	}
	else{ //cuando el grado del nodo es 0 (hoja) se suma 1 si es menor que num y se retorna i
		if(getValue(n)<=num){
			i++;
			return i;
		}
		else{
			return i;
		}

	}


}

/*****
*
TipoFunción NombreFunción : rank
******
*
Resumen Función : funcion rank que recibe un arbol y un numero al cual buscar los nodos menores o iguales, llama a la funcion rank_help
******
*
Input: puntero al arbol a revisar ; entero con el numero respecto al cual se buscan los nodos menores o iguales ; entero contador
tipoParámetro NombreParámetro :  Abb* t ; int num
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno :  int ; retorna la cantidad de nodos menores a num
*****/


int rank(Abb *t, int num){

    int x;
    int i = 0;
    x = rank_help(t->raiz, num, i);
    return x;
}

/*****
*
TipoFunción NombreFunción : main
******
*
Resumen Función : funcion principal que lee el input y actua segun el comando rank o insert
******
*
Input: void
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno :  int ; retorna un 0 si la funcion no tiene problemas al ser ejecutada, ademas retorna un archivo output2.txt con los resultados de la funcion rank
*****/

int main(){

    Abb *tree;
	FILE *fp;
    FILE *fp_out;
	char ir[10],i[10],r[10];
	int j;

    tree = ConsTree();

	fp = fopen("input2.dat","r");
    fp_out = fopen("output2.txt", "w");

	strcpy(i,"Insert");
	strcpy(r,"Rank");

	while(!feof(fp)){
		fscanf(fp,"%s %d", ir, &j);

		if (strcmp(ir,i) == 0){
			insert(tree, j);
		}

		else{
            fprintf(fp_out,"%d\n",rank(tree,j));
		}
        printf("\n");
	}

    clear(tree);
    DesTree(tree);

    fclose(fp);
    fclose(fp_out);

	return 0;
}
