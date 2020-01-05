#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define VACIO -1 //para cuando una ranura esta vacia

///////////////////STRUCTS//////////////////////////////////////////

typedef struct {
    int cod_producto; //clave
    char nombre_producto[31]; //info
    int precio; //info
} producto;

typedef struct {
    int cod_producto; //clave
    int cantidad_descuento; //info
    int descuento; //info
} oferta;

typedef struct {
    int cod_producto; //clave
    int cantidad; //info
} cliente;


/////////////////////////INICIALIZADORES//////////////////////////////////////////


/*****
*
producto** InicializarP
*
******
*
Inicializa una tabla hash de tamaño m (arreglo tamaño m), con punteros del tipo producto.
En una primera instancia con productos de codigo VACIO
******
*
Input:
int m: tamaño de la tabla de hash calculado previamente (cantidad de "casillas")
*
******
*
Returns:
*
producto ** :retorna una tabla de hash con punteros del tipo producto
*****/

producto** InicializarP (int m){
    producto** TabP;
    int i;
    TabP = (producto**)malloc(sizeof(producto*)*m);
    for (i=0; i < m; ++i){
        TabP[i] = (producto*)malloc(sizeof(producto));
        TabP[i]->cod_producto = VACIO;
    }
    return TabP;

}

/*****
*
producto** InicializarO
*
******
*
Inicializa una tabla hash de tamaño m (arreglo tamaño m), con punteros del tipo oferta.
CAda puntero de tipo oferta es inicializado con codigos de producto igual a VACIO
******
*
Input:
int m: tamaño de la tabla de hash calculado previamente (cantidad de "casillas")
*
******
*
Returns:
*
oferta ** :retorna una tabla de hash con punteros del tipo oferta
*****/

oferta** InicializarO(int m){
    oferta** TabO;
    int i;
    TabO = (oferta**)malloc(sizeof(oferta*)*m);
    for (i=0; i < m; ++i){
        TabO[i] = (oferta*)malloc(sizeof(oferta));
        TabO[i]->cod_producto = VACIO;
    }
    return TabO;
}

/*****
*
producto** InicializarC
*
******
*
Inicializa una tabla hash de tamaño n (arreglo tamaño n), con punteros del tipo cliente.
Cada puntero de tipo cliente se inicializan con codigos de producto igual a VACIO
******
*
Input:
int n: tamaño de la tabla de hash calculado previamente (cantidad de "casillas")
*
******
*
Returns:
*
clientes ** :retorna una tabla de hash con punteros del tipo cliente
*****/

cliente** InicializarC(int n){
    cliente** TabC;
    int i;
    TabC = (cliente**)malloc(sizeof(cliente*)*n);
    for (i=0; i < n; ++i){
        TabC[i] = (cliente*)malloc(sizeof(cliente));
        TabC[i]->cod_producto = VACIO;
    }
    return TabC;
}

/////////////////////DESTRUCTORES//////////////////////////////////////////////

/*****
*
void DestruirP
******
*
Libera el espacio en memoria utilizado por la tabla de hash **p de tipo producto y todos sus punteros tambien del tipo producto
******
*
Input:
*
producto** p: tabla de hash (arreglo) que almacena punteros de structs producto
******
*
Returns:
*
void ,no retorna nada
*****/

void DestruirP (producto** p, int m){
    int i;
    for (i=0; i<m; ++i){
        free(p[i]);
    }

    free(p);
}

/*****
*
void DestruirO
******
*
Libera el espacio en memoria utilizado por la tabla de hash **o de tipo oferta y todos sus punteros tambien del mismo tipo
******
*
Input:
*
oferta** o: tabla de hash (arreglo) que almacena punteros de structs oferta
******
*
Returns:
*
void ,no retorna nada
*****/

void DestruirO (oferta** o, int m){
    int i;
    for (i=0; i<m; ++i){
        free(o[i]);
    }

    free(o);
}

/*****
*
void DestruirC
******
*
Libera el espacio en memoria utilizado por la tabla de hash **c de tipo cliente y todos sus punteros tambien del tipo cliente
******
*
Input:
*
cliente** c: tabla de hash (arreglo) que almacena punteros de structs cliente
******
*
Returns:
*
void ,no retorna nada
*****/

void DestruirC (cliente** c, int n){
    int i;
    for (i=0; i<n; ++i){
        free(c[i]);
    }

    free(c);
}

///////////////////////FUNCIONES HASH////////////////////////////////////////////

/*****
*
int hash1
******
*
Algoritmo de hashing para insertar elementos en las tablas hash
******
*
Input:
*
int llave : codigo del producto
*
int m : tamaño de la tabla de hash
******
*
Returns:
*
int x, retorna un entero que sera utilizado para insertar de forma random en la tabla hash
*****/

int hash1(int llave, int m) {

    int x;
    x = fabs((llave*(llave-5)) % m);

    return x;
}

/*****
*
int hash2
******
*
Segundo algoritmo de hashing para insertar elementos en la tabla de hash, se utiliza en caso de que hash1 genere colision
******
*
Input:
*
int llave : codigo del producto
*
int m: tamaño de la tabla de hash
******
*
Returns:
*
int y; retorna un entero y que sera utilizado como llave de busqueda en la tabla hash
*****/

int hash2(int llave, int m) {
    int y;
    y = 1+(llave%(m-1));
    return y;
}

/*****
*
int p
******
*
Funcion que se utiliza en caso de colision generada por hash1, esta llama a hash2 para buscar una casilla en VACIO para hacer insert
******
*
Input:
*
int k : codigo del producto
*
int i : contador externo que se usa para aumentar la posicion anterior en el resultado de hash2
*
int m: tamaño de la tabla de hash
******
*
Returns:
*
int, retorna un entero que sera utilizado como llave de busqueda en las tablas hash
*****/

int p(int k, int i, int m){
    return i+hash2(k,m);
}

///////////////////////INSERT////////////////////////////////////////////

/*****
*
void hashInsert_producto
******
*
Insercion de un elemento de tipo producto en la tabla de hashing htp
******
*
Input:
*
producto** htp : tabla de hash productos donde se insertara un elemento de tipo producto (que los punteros apunten al producto que se quiere insertar)
*
producto aux : struct de tipo producto a insertar
*
int m : tamaño de la tabla de hash
******
*
Returns:
*
void , no retorna nada
*****/

void hashInsert_producto (producto** htp, producto aux, int m){
    int inicio;
    int i1;
    int pos;


    inicio = hash1(aux.cod_producto, m);

    pos = inicio;

    for (i1 = 1; htp[pos]->cod_producto !=  VACIO && htp[pos]->cod_producto != aux.cod_producto; ++i1){

        pos = (inicio + p(aux.cod_producto,i1,m)) % m;

    }


    if (htp[pos]->cod_producto == aux.cod_producto){
        printf("INSERCION NO EXITOSA\n"); // insercion no exitosa -> clave repetida
    }

    else{

        htp[pos]->cod_producto = aux.cod_producto;
        htp[pos]->precio = aux.precio;
        strcpy (htp[pos]->nombre_producto, aux.nombre_producto);

    }

    return ;
}


/*****
*
void hashInsert_oferta
******
*
Insercion de un elemento de tipo oferta en la tabla de hashing hto
******
*
Input:
*
oferta** hto : tabla de hash oferta donde se insertara un elemento de tipo oferta (que el puntero apunte a la oferta que se quiere insertar)
*
oferta aux : struct de tipo oferta a insertar
*
int m : tamaño de la tabla de hash
******
*
Returns:
*
void , no retorna nada
*****/

void hashInsert_oferta (oferta** hto, oferta aux, int m){

    int inicio, pos, i1;

    pos = inicio = hash1(aux.cod_producto, m);

    for (i1 = 1; hto[pos]->cod_producto !=  VACIO && hto[pos]->cod_producto != aux.cod_producto; ++i1){

        pos = (inicio + p(aux.cod_producto,i1,m)) % m;

    }

    if (hto[pos]->cod_producto == aux.cod_producto){
        printf("INSERCION NO EXITOSA\n"); // insercion no exitosa -> clave repetida
    }

    else{
        hto[pos]->cod_producto = aux.cod_producto;
        hto[pos]->cantidad_descuento = aux.cantidad_descuento;
        hto[pos]->descuento = aux.descuento;

    }

    return ;
}


/*****
*
int* hashInsert_clientes
******
*
Insercion de un elemento de tipo clientes en la tabla de hashing htc
******
*
Input:
*
cliente** htc : tabla de hash clientes donde se insertara un elemento de tipo cliente (que el puntero apunte al cliente que se quiere insertar)
*
int codigo1 : codigo del producto que se quiere guardar en el struct cliente que se insertara
*
int a : tamaño de la tabla hash hashInsert_clientes
*
int w : posicion en la que se guardara las llaves(codigos de productos) en el arreglo_llaves
*
int* arreglo_llaves : puntero al arreglo_llaves que almacena los codigos de los productos que son las llaves para la tabla htc
******
*
Returns:
*
int* arreglo_llaves , retorna un puntero al arreglo que almacena las llaves (codigos de productos)
*****/

int* hashInsert_clientes (cliente** htc, int codigo1, int a, int w, int* arreglo_llaves){  //a=modulo , w=posicion a guardar en el arreglo

    int inicio, pos, i1;

    inicio = hash1(codigo1, a);
    pos = inicio;

    for (i1 = 1; htc[pos]->cod_producto !=  VACIO && htc[pos]->cod_producto != codigo1; ++i1){

        pos = (inicio + p(codigo1,i1,a)) % a;

    }


    if (htc[pos]->cod_producto == codigo1){ //si la clave es repetida
        htc[pos]->cantidad = htc[pos]->cantidad+1;
    }

    else{
        htc[pos]->cod_producto = codigo1;
        htc[pos]->cantidad = 1;
        arreglo_llaves[w] = codigo1;

    }
    return arreglo_llaves;
}

/////////////////////////SEARCH//////////////////////////////////////////


/*****
*
int hashSearchP
******
*
Busca dentro de la tabla hash htp un producto con la llave product entregada como parametro
******
*
Input:
*
producto** htp : Tabla de hash con punteros de tipo producto, donde se buscará un producto especifico
*
int product : llave del producto a buscar en la tabla htp representada por un numero entero
*
int m : tamaño de la tabla de hash
******
*
Returns:
*
int , retorna el precio del producto buscado, en caso de que la busqueda sea invalida retorna 0
*****/

int hashSearchP (producto** htp, int product, int m){

    int inicio, count;
    int pos = inicio = hash1(product,m);

    for (count = 1; htp[pos]->cod_producto !=  VACIO && htp[pos]->cod_producto != product; count++){
        pos = (inicio + p(product,count,m)) % m;
    }
    if (htp[pos]->cod_producto == product){
        return htp[pos]->precio;
    }

    else{
        return 0; //busqueda invalida
    }

}

/*****
*
oferta* hashSearchO
******
*
Busca dentro de la tabla hash hto una oferta con la llave product ingresada como parametro
******
*
Input:
*
oferta* hto: Tabla de hash con punteros de tipo oferta, donde se buscará si existe oferta para un producto en especifico
*
int product : llave de la oferta a buscar representada por un numero entero
*
int m : tamaño de la tabla de hash
******
*
Returns:
*
oferta , si el producto en cuestion tiene oferta, entonces retorna el struct oferta
en caso  contrario retorna NULLL
*****/

oferta* hashSearchO (oferta** hto, int product, int m){

    int inicio, count;
    int pos = inicio = hash1(product,m);

    for (count = 1; hto[pos]->cod_producto !=  VACIO && hto[pos]->cod_producto != product; count++){
        pos = (inicio + p(product,count,m)) % m;
        if(pos >= m){
        }
    }

    if (hto[pos]->cod_producto == product){
        return hto[pos];
    }

    else{
        return NULL ; //busqueda invalida, no existe la oferta
    }

}

/*****
*
int hashSearchC
******
*
Busca dentro de la tabla hash htc un cliente  con la llave product ingresada como entero en los paramentros
******
*
Input:
*
cliente** htc : Tabla Hash de clientes con punteros de tipo cliente, donde se buscará un cliente en especifico
*
int product : llave del cliente a buscar representada por un numero entero
*
int m : tamaño de la tabla de hash
******
*
Returns:
*
int , retorna la cantidad del producto que desea comprar el cliente, si no encuentra el
producto buscado retorna 0
*****/

int hashSearchC (cliente** htc, int product, int m){

    int inicio, count;
    int pos = inicio = hash1(product,m);



    for (count = 1; htc[pos]->cod_producto !=  VACIO && htc[pos]->cod_producto != product; count++){
        pos = (inicio + p(product,count,m)) % m;

    }

    if (htc[pos]->cod_producto == product){
        return htc[pos]->cantidad;
    }

    else{
        return 0; //busqueda invalida
    }

}

///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////


int main (){
    // VARIABLES
    FILE *archiP; FILE *archiO; FILE *compras; FILE *boletas;
    int productos_totales, ofertas_totales, clientes_totales, productito;
    int mP, mO, mC; int count,count1,count2;
    int* arreglo; int* llaves;
    producto **htp; producto aux;
    oferta **hto; oferta aux1; oferta* aux2;
    cliente **htc;
    int z;

    //
    // Apertura de archivos a usar
    boletas = fopen("boletas.txt", "w");
    archiP = fopen("productos.dat", "r");
    archiO = fopen("ofertas.dat", "r");
    compras = fopen("compras.txt","r");

    //
    // obtener cantidad de structs
    fread(&productos_totales,sizeof(int),1,archiP); //cantidad de structs productos
    mP =  productos_totales/0.7; // mp : tamaño de la tabla hash de productos

    fread(&ofertas_totales,sizeof(int),1,archiO); //cantidad de structs ofertas
    mO =  ofertas_totales/0.7; // mo : tamaño de tabla hash de ofertas

    //
    // Inicializar tabla hash productos y ofertas
    htp = InicializarP(mP);
    hto = InicializarO(mO);

    //
    // Insercion hash productos
    for (count = 0; count<productos_totales; ++count){
        fread(&aux,sizeof(producto),1,archiP);
        hashInsert_producto (htp,aux,mP);
    }
    //
    //insercion hash oferta
    for (count = 0; count<ofertas_totales; ++count){

        fread(&aux1,sizeof(oferta),1,archiO);

        hashInsert_oferta (hto,aux1,mO);
    }
    //
    //lectura del primer numero en compras.txt (cantidad de clientes totales a atender)
    fscanf(compras,"%d",&clientes_totales);
    fprintf(boletas,"%d\n",clientes_totales);

    for (count = 0; count < clientes_totales; ++count){ //carrito de cada clientes


        fscanf(compras,"%d", &mC); // mC = cantidad de productos a comprar por cliente

        htc = InicializarC(mC); //tabla de productos y cantidad a llevar

        arreglo = (int*)malloc(sizeof(int)*mC);  // arreglo de llaves(codigos de productos)
        //
        for (z=0;z<mC;++z){
            arreglo[z]=VACIO;
        }

        for (count1 = 0; count1 < mC; count1++){  //hash clientes
            fscanf(compras,"%d", &productito);
            llaves = hashInsert_clientes (htc,productito,mC,count1,arreglo);

        }

        int total=0;
        int procesados=0;
        int cantidad_productos_comprados, cociente, preciO;
        int f;

        for (count2 = 0; count2<mC; count2++){ //recorre el arreglo de llaves

            f = llaves[count2];
            if (f!= VACIO){
                cantidad_productos_comprados = hashSearchC (htc,f,mC);


                procesados = procesados+cantidad_productos_comprados;

                aux2 = hashSearchO (hto,f,mO);
                preciO = hashSearchP (htp,f,mP);

                if (aux2!=NULL){ //producto en listado de oferta
                    cociente = cantidad_productos_comprados/aux2->cantidad_descuento;


                    if (cantidad_productos_comprados>=aux2->cantidad_descuento){ //descuentos aplicables
                        total = total + cantidad_productos_comprados*preciO - cociente*aux2->descuento;
                    }

                    else  { //no se aplican descuentos
                        total = total + cantidad_productos_comprados*preciO;
                    }
                }

                else { //productos que no registran oferta
                    total = total + cantidad_productos_comprados*preciO;
                }

                if (procesados == mC){ //si se proceso el carrito entonces break
                    fprintf(boletas,"%d\n",total);
                    total = 0;
                    break;
                }

            }
        }

        free((void*)arreglo);


        DestruirC(htc,mC);
    }


    fclose(archiO);
    fclose(compras);
    fclose(boletas);
    fclose(archiP);

    //
    // Destruir


    DestruirP(htp,mP);
    DestruirO(hto,mO);


    return 0;
}
