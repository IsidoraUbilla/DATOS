int main(){

    int j; //listsizeeee
    int w; //para getvalue
    int t; //para ver si funciona insert
    int i;
    tLista *lista1;

    lista1 = constructor();
    printf("\n");

    j = append1(lista1, 10,0); //agrego el 10   pos 0
    printf("curr: %d tail: %d head: %d tamano: %d\n", lista1->curr->info1,lista1->tail->info1,lista1->head->info1,lista1->listSize);
    printf("\n");

    j = append1(lista1,20,0); //agrego el 20    pos 1
    printf("curr: %d tail: %d head: %d tamano: %d   pos: %d\n", lista1->curr->info1,lista1->tail->info1,lista1->head->info1,lista1->listSize, lista1->pos);

    printf("\n");

    moveToEnd(lista1);
    insert1(lista1, 25,0);
    printf("curr: %d head: %d tail: %d tamano: %d boi\n", lista1->curr->info1,lista1->head->info1,lista1->tail->info1,lista1->listSize);




    j = append1(lista1,30,0);
    printf("%d\n",j);
    printf("curr: %d tail: %d head: %d tamano: %d\n", lista1->curr->info1,lista1->tail->info1,lista1->head->info1,lista1->listSize);


    j = append1(lista1,40,0);
    printf("curr: %d tail: %d head: %d tamano: %d\n", lista1->curr->info1,lista1->tail->info1,lista1->head->info1,lista1->listSize);


    moveToEnd(lista1); //deberia devolverme el 40 , head
    printf("PRUEBA MOVETOEND curr: %d tail: %d head: %d tamano: %d\n", lista1->curr->info1,lista1->tail->info1,lista1->head->info1,lista1->listSize); //para probar el movetoend

    moveToStar(lista1); //deberia devolver el 10, tail
    printf("MOVETOSTAR curr: %d tail: %d head: %d tamano: %d\n", lista1->curr->info1,lista1->tail->info1,lista1->head->info1,lista1->listSize); // para probar el movetostar


    insert1(lista1,5,0);
    printf("INSERT curr: %d head: %d tail: %d tamano: %d jujuju\n", lista1->curr->info1,lista1->head->info1,lista1->tail->info1,lista1->listSize);

    printf("\n");
    insert1(lista1,7,0);

    moveToStar(lista1);
    for (i=lista1->pos; i<lista1->listSize; i++){
        moveToPos(lista1, i);
        printf ("curr %d\n", lista1->curr->info1);

    }
    moveToStar(lista1);
    remove1(lista1);
    printf("REMOVE curr: %d head: %d tail: %d tamano: %d jujuju\n", lista1->curr->info1,lista1->head->info1,lista1->tail->info1,lista1->listSize);
    printf("\n");

    clear(lista1);

    destructor(lista1);

    return 0;
}
