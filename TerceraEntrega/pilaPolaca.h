#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_nodo
{
    struct  s_nodo *sig;
    int info;
}t_nodo;
typedef t_nodo* t_pila;

//PILA
void createStackPolish(t_pila *);
int push(t_pila*,int);
int pop(t_pila*);
void seeTop(const t_pila *p, int *d);
int emptyStackPolish(t_pila*);

int emptyStackPolish(t_pila *p){
    return !*p;
}

void seeTop(const t_pila *p, int *d)
{
    if(!*p)
        return;

    *d=(*p)->info;
}

void createStackPolish(t_pila *p)
{
    *p=NULL;
}

int push(t_pila *p,int posicion)
{
    t_nodo *nuevo=(t_nodo *)malloc(sizeof(t_nodo));
    if(nuevo==NULL)
        return 0;
    nuevo->sig=*p;
    nuevo->info=posicion;
    *p=nuevo;
    return 1;
}

int pop(t_pila *p)
{

    int valor_actual;
    t_nodo *viejo=*p;
    if(viejo==NULL)
        return 0;
    *p=viejo->sig;
    valor_actual = viejo->info;
    free(viejo);

    return valor_actual;
}
