#include<stdio.h>
#include<stdlib.h>

typedef struct nodoABB { //struct de un nodo de ABB
    int info; //informacion del nodo
    //int cant;//numeros a la izquierda del nodo
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

/*int getCant(nodoABB *n){
    int x;
    x = n->cant;
    return x;
}*/

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
        //a->cant++;
        return a;
    }

    if(item > getValue(a) && a->right == NULL){
        return a;
    }

    if (a->left == NULL && a->right == NULL){
        return a;
    }

    if (item < getValue(a)){
        //a->cant++;
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

void insert(Abb* t, int item, FILE *fp){

    int x;
    nodoABB* aux;
    nodoABB* aux1;

    x = buscar(t,item);

    if (x == 0){ // el item no esta entonces podemos hacer insert

        if(t->nElems == 0){// caso cuando es arbol vacio
            t->raiz = (nodoABB *)malloc(sizeof(nodoABB));
            t->raiz->info = item;
            //t->raiz->cant = 0;
            t->nElems++;
            t->raiz->right = NULL;
            t->raiz->left = NULL;
            fprintf(fp,"%d\n",t->raiz->info);
        }

        else{
            aux = nodo_insert(t,item);
            if (getValue(aux) < item){ //derecha
                aux1 = (nodoABB *)malloc(sizeof(nodoABB));
                aux1->info = item;
                aux1->right = NULL;
                aux1->left = NULL;
                //aux1->cant = 0;
                t->nElems++;
                aux->right = aux1;

                fprintf(fp,"%d\n",aux1->info);

            }


            else{ //izq
                aux1 = (nodoABB *)malloc(sizeof(nodoABB));
                aux1->info = item;
                aux1->right = NULL;
                aux1->left = NULL;
                //aux1->cant = 0;
                t->nElems++;
                aux->left = aux1;
                fprintf(fp,"%d\n",aux1->info);


            }
        }

    }

}

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

int rank_help(nodoABB *n, int num, int i){

    if (n==NULL){
		return 0;
	}

	else if(getGrado(n) == 2){
		if(getValue(n) <= num){
			i++;
			i=rank_help(n->left,num,i); // i=3
			return rank_help(n->right,num,i);
		}
		else{
			return rank_help(n->left,num,i);
		}
	}
	else if(getGrado(n)==1){
		if(getValue(n)<=num){
			i++;
			if(n->left!=NULL){
				return rank_help(n->left,num,i);
			}
			else{
				return rank_help(n->right,num,i);
			}
		}
		else{ //n>num
			if(n->left!=NULL){
				return rank_help(n->left,num,i);
			}
			else{
				return rank_help(n->right,num,i);
			}
		}
	}

	else if (getGrado(n) == 0){
		if(getValue(n)<=num){
		   i++;
		   return i;
		}

		else{
		return i;
        }
   }
   return 0;
}

int rank(Abb *t, int num){

    int x;
    int i = 0;
    x = rank_help(t->raiz, num, i);
    return x;
}

int main(){

    Abb *tree;
    FILE *fp;
    int r;

    fp=fopen("prueba.txt","w");
    tree = ConsTree();

    /*insert(tree,5,fp);
    insert(tree,12,fp);
    insert(tree,4,fp);
    printf("cantidad de menores que el 5: %d\n", tree->raiz->cant);
    printf("\n");
    printf("                            %d           \n", tree->raiz->info);
    printf("                %d                    %d \n ", tree->raiz->left->info,tree->raiz->right->info);
    printf("\n");
    insert(tree,6,fp);
    printf("cantidad de menores que el 12: %d\n", tree->raiz->right->cant);
    printf("\n");
    printf("                            %d           \n", tree->raiz->info);
    printf("                %d                    %d \n ", tree->raiz->left->info,tree->raiz->right->info);
    printf("          null       null         %d      null\n ", tree->raiz->right->left->info);
    printf("\n");
    insert(tree,3,fp);
    printf("cantidad de menores que el 5: %d\n", tree->raiz->cant);
    printf("cantidad de menores que el 4: %d\n", tree->raiz->left->cant);
    printf("\n");
    printf("                            %d           \n", tree->raiz->info);
    printf("                %d                    %d \n ", tree->raiz->left->info,tree->raiz->right->info);
    printf("           %d       null          %d      null\n ", tree->raiz->left->left->info, tree->raiz->right->left->info);
    printf("\n");
    insert(tree,8,fp);
    printf("cantidad de menores que el 12: %d\n", tree->raiz->right->cant);
    printf("                            %d           \n", tree->raiz->info);
    printf("                %d                    %d \n ", tree->raiz->left->info,tree->raiz->right->info);
    printf("           %d       null          %d      null\n ", tree->raiz->left->left->info, tree->raiz->right->left->info);
    printf("      null   null            null     %d          \n",tree->raiz->right->left->right->info);*/

    /*insert(tree,0,fp);
    insert(tree,1,fp);
    insert(tree,2,fp);
    insert(tree,4,fp);
    insert(tree,3,fp);

    printf("                              %d           \n", tree->raiz->info);
    printf("                 null                       %d \n ",tree->raiz->right->info);
    printf("                                      null        %d\n ", tree->raiz->right->right->info);
    printf("                                             null     %d\n",tree->raiz->right->right->right->info);
    printf("                                                    %d\n",tree->raiz->right->right->right->left->info);

    r = rank(tree, 5);
    printf ("rank de 5: %d\n", r);
    r = rank(tree, 4);
    printf ("rank de 4: %d\n", r);*/


    fclose(fp);

    return 0;

}
