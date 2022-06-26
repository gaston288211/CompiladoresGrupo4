#include "pilaPolaca.h"
#define SUCCESS 1
#define DUPLICATE 2
#define NO_MEMORY 0

typedef struct l_nodo
{
    struct l_nodo* sig;
    int nroPolaca;
    char elemento[200];

}l_nodo;
typedef l_nodo* t_lista;


//LISTA
void createListaPolaca(t_lista*);
int emptyListPolish(t_lista*);
int fullListPolish(t_lista* );

//POLACA
int insertar_en_polaca(t_lista* ,char*, int );
int vaciar_polaca(t_lista* l);
void rellenarPolaca2(t_lista*, int , char* );

void createListaPolaca(t_lista* l)
{
    *l=NULL;
}

int emptyListPolish(t_lista* l)
{
    return !*l;
}

int insertar_en_polaca(t_lista* l,char* d, int posicion)
{
    t_lista* nodoaux = l;
    l_nodo* nuevo = (l_nodo*)malloc(sizeof(l_nodo));
    if(!nuevo){
        printf("NO RESERVO MEMORIA\n");
        return 0;
    }

    nuevo->sig=NULL;
    strcpy(nuevo->elemento,d);
    nuevo->nroPolaca = posicion;
    if(!*l){
        *l = nuevo;
    }else{
        while((*nodoaux)->sig != NULL){
            nodoaux = &(*nodoaux)->sig;
        }
        (*nodoaux)->sig = nuevo;
    }
    return 1;
}

int fullListPolish(t_lista* l)
{
    l_nodo* aux=(l_nodo*)malloc(sizeof(l_nodo));
    return !aux;
}

int vaciar_polaca(t_lista* l)
{
    FILE* pf = fopen("intermedia.txt","w+");
    if(!pf){
        printf("No se pudo abrir el archivo;\n");
        return 0;
    }

    while(*l)
    {
        fprintf(pf,"%d\t%s\n",(*l)->nroPolaca, (*l)->elemento);
        l=&(*l)->sig;
    }
    fclose(pf);
    return 1;
}

void rellenarPolaca2(t_lista *l, int posicion, char* valor){

    t_lista* aux = l;
    char cadena[10];
    char etiqueta[10];
    while(*aux && (((*aux)->nroPolaca-posicion) != 0)  ){
        aux = &(*aux)->sig;
    }
    if(!*aux){
        printf("LISTA VACIA!\n");
    }
    if(((*aux)->nroPolaca-posicion) == 0){
        strcpy((*aux)->elemento, valor );
    }
}
