#include "pila.h"
#define SUCCESS 1
#define DUPLICATE 2
#define NO_MEMORY 0

typedef struct sNode
{
    char name[50];
    char dataType[50];
    char value[50];
    int  length;
    struct sNode* next;
}tNode;

typedef tNode* tList;

void crearLista(tList *p);
int insertarEnOrden(tList *p, char* name, char* dataType, char* value, int length);
int insertarVariable(tList *p, char* name, char* dataType); 
int insertarString(tList *p, char* name);
int insertarNumero(tList *p, char* lex);
void escribirTabla(tList *p);
char* formatoString(char* lex);


void crearLista(tList *p)
{
    *p = NULL;
}

int insertarEnOrden(tList *p, char* name, char* dataType, char* value, int length)
{
    int result = -1;
    tNode* nue = (tNode*)malloc(sizeof(tNode));
    
    if(!nue)
        return NO_MEMORY;

    while(*p && ((result = (strcmp((*p)->name, name))) < 0))
        p = &(*p)->next;

    if(result == 0)
        return DUPLICATE;
    strcpy(nue->name, name);
    strcpy(nue->dataType, dataType);
    strcpy(nue->value, value);
    
    nue->length = length;

    nue->next = *p;

    *p = nue;

    return SUCCESS;
}

int insertarNumero(tList *p, char* lex) 
{
    int result = -1;
    char name[100];

    strcpy(name, "_");
    strcat(name, lex); 

    result = insertarEnOrden(p, name, " ", lex, 0);

    if(result == DUPLICATE){
        //printf("Lexema %s ya se ingreso en la tabla de simbolos\n",lex);
        return DUPLICATE;
    }

    return SUCCESS;
}

int insertarString(tList *p, char* lex)
{
    int result = -1;
    char name[100];

    char* newName = formatoString(lex);

    strcpy(name, "_");
    strcat(name, newName);

    result = insertarEnOrden(p, name, " ", newName, strlen(newName));

    if(result == DUPLICATE){
        // printf("Lexema %s ya se ingreso en la tabla de simbolos\n",lex);
        return DUPLICATE;
    }

    return SUCCESS;
}

char* formatoString(char* lex)
{
    char* cad = lex;
    char* cadIni = cad;
    while(*lex)
    {
        if(*lex != '"')
        {
            (*cad) = (*lex);
            cad++;
        }
        lex++;
    }
    *cad = '\0';
    return cadIni;
}

int insertarVariable(tList *p, char* lex, char* dataType)
{
    int result = -1;

    result = insertarEnOrden(p, lex, dataType, " ", 0);
    if(result == DUPLICATE){
        //printf("Lexema %s ya se ingreso en la tabla de simbolos\n",lex);
        return DUPLICATE;
    }

    return SUCCESS;
}

void escribirTabla(tList *p)
{
    FILE *pTable = fopen("ts.txt", "w+");
    if(!pTable) {
        //printf("No se pudo abrir el archivo ts.txt \n");
        return;
    }

    printf("\n_______________________________TABLA DE SIMBOLOS______________________________\n");

    printf("_______________________________________________________________________________\n");
    printf("|%-25s|%-14s|%-25s|%-10s|\n", "NOMBRE", "TIPODATO", "VALOR", "LONGITUD");
    printf("_______________________________________________________________________________\n");

    fprintf(pTable,"\n______________________________TABLA DE SIMBOLOS_______________________________\n");
    fprintf(pTable, "_______________________________________________________________________________\n");
    fprintf(pTable, "|%-25s|%-14s|%-25s|%-10s|\n", "NOMBRE", "TIPODATO", "VALOR", "LONGITUD");
    fprintf(pTable, "_______________________________________________________________________________\n");

    while(*p)
    {
        printf("|%-25s|%-14s|%-25s|%-10d|\n", (*p)->name, (*p)->dataType, (*p)->value, (*p)->length);
        fprintf(pTable, "|%-25s|%-14s|%-25s|%-10d|\n", (*p)->name, (*p)->dataType, (*p)->value, (*p)->length);
        p = &(*p)->next;
    }

    printf("_______________________________________________________________________________\n");
    fprintf(pTable, "_______________________________________________________________________________\n");
    fclose(pTable);
}
