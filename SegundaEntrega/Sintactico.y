%{
    
#include "lista.h"
#include "listaPolaca.h"
#include <stdio.h>
#include <stdlib.h>

#include "y.tab.h"

#define STR_LIMITE 30
#define ID_LIMITE 30
#define ENT_LIMITE 5
#define TABLA_SIMBOLOS_TXT "ts.txt"

#define COTA_INFERIOR_ENT -32768
#define COTA_SUPERIOR_ENT 32767

#define COTA_SUPERIOR_REAL 3.4028235E+38
#define COTA_INFERIOR_REAL -3.4028235E+38

int yystopparser=0;
//FILE  *yyin;
//int yylex();
//int yyparse();
//extern int yyerror();


typedef struct
{
    char nombre[200];
    char tipo[30];
    char valor[200];
    int longitud;   

}tablaSimbolos;

tablaSimbolos tb[2000];
int cantReg=0;
FILE  *yyin;
FILE * fpTabla;
//int yylval;
extern int yylex();
//int yyparse();
extern char * yyerror();


void cargarTipoDato(tStack* pilaTipoVariables, tStack* pilaVariables);
char* validarRangoString( char *text );
char* validarRangoEntero( char *text );
char* validarRangoID( char *text );
char* validarRangoReal( char *text );
void escribirTablaSimbolos();
void cargarVecTablaString(char * text, char * tipo);
void cargarVecTablaID(char * text);
void cargarVecTablaNumero(char * text, char * tipo);
int abrirTablaDeSimbolos();

/// segunda entrega
t_lista listaPolaca;
tStack pilaNumCelda;
tStack pilaVariables;
tStack pilaTipoVariables;
int cont=1;


%}
%union{
    char* strVal;
}

%start programa 
%right OP_ASIG 
%left OP_SUMA OP_RESTA
%left OP_MULT OP_DIV
%right MENOS_UNARIO

%token <strVal> OP_ASIG
%token <strVal> OP_SUMA
%token <strVal>  OP_RESTA
%token <strVal> OP_DIV
%token <strVal> OP_MULT
%token  OP_MAY 
%token  OP_MAYIGU 
%token  OP_MEN 
%token  OP_MENIGU
%token  OP_IGUAL
%token  OP_DIF
%token WHILE IF 
%token <strVal> INTEGER 
%token <strVal> FLOAT 
%token <strVal> STRING 
%token ELSE THEN DECVAR ENDDEC IN 
%token <strVal> AND
%token <strVal> OR
%token <strVal> NOT 
%token LONG BETWEEN INLIST
%token WRITE COMA ENDIF ENDWHILE DO READ PAR_A PAR_C COR_A COR_C PYC DP

%token <strVal> ID
%token <strVal> CTE_INTEGER
%token <strVal> CTE_FLOAT    
%token <strVal> CTE_STRING

%%
programa:
    declaracion bloque          {printf("\nREGLA 1: <programa> --> <declaracion> <bloque>\n");} 
bloque:
    sentencia                       {printf("\nREGLA 1: <bloque> --> <sentencia>\n");}       
    | bloque sentencia            {printf("\nREGLA 2: <bloque> --> <bloque> <sentencia>\n");};              
    
sentencia:
     asignacion                      {printf("\nREGLA 4: <sentencia> --> <asignacion>\n");}   
    |ciclo                           {printf("\nREGLA 5: <sentencia> --> <ciclo>\n");}   
    |seleccion                       {printf("\nREGLA 6: <sentencia> --> <seleccion>\n");}   
    |salida                          {printf("\nREGLA 7: <sentencia> --> <salida>\n");}   
    |entrada                         {printf("\nREGLA 8: <sentencia> --> <entrada>\n");};



declaracion:
    DECVAR listaDeclaraciones  ENDDEC   {  
                                            
                                            printf("\nREGLA 11: <declaracion> --> DECVAR <listaDeclaraciones> ENDDEC\n");
                                        };    
listaDeclaraciones:
    listavar DP tipodato                        {
                                                    cargarTipoDato(&pilaTipoVariables,&pilaVariables);
                                                    printf("\nREGLA 11: <listaDeclaraciones> --> <listavar> DP <tipodato> \n");}   
    |listaDeclaraciones listavar DP tipodato    {
                                                    cargarTipoDato(&pilaTipoVariables,&pilaVariables);
                                                    printf("\nREGLA 11: <listaDeclaraciones> --> <listaDeclaraciones> <listavar> DP <tipodato> \n");
                                                };    
listavar:
    ID                              {
                                        pushStack(&pilaVariables,$1);
                                        printf("\nREGLA 12: <listavar> --> ID \n");
                                    }
    | listavar COMA ID              {
                                        pushStack(&pilaVariables,$3);
                                        printf("\nREGLA 13: <listavar> --> <listavar> COMA ID\n");
                                    };

tipodato:
    INTEGER                         {
                                        pushStack(&pilaTipoVariables,$1);
                                        printf("\nREGLA 14: <tipodato> --> INTEGER  \n");
                                    }
    | FLOAT                         {
                                        pushStack(&pilaTipoVariables,$1);
                                        printf("\nREGLA 15: <tipodato> --> FLOAT \n");}
    | STRING                        {
                                        pushStack(&pilaTipoVariables,$1);
                                        printf("\nREGLA 16: <tipodato> --> STRING \n");
                                    };

seleccion:
    IF condicion THEN bloque ELSE bloque ENDIF      {printf("\nREGLA 17: <seleccion> --> IF <condicion> THEN <bloque> ELSE <bloque> ENDIF\n");}
    | IF condicion THEN bloque ENDIF                  {printf("\nREGLA 18: <seleccion> --> IF <condicion> THEN <bloque> ENDIF \n");};

ciclo:
    WHILE ID IN COR_A lista COR_C DO bloque ENDWHILE         {printf("\nREGLA 19: <ciclo> --> WHILE ID IN COR_A <lista> COR_C DO <sentencia> ENDWHILE\n");};

entrada:
    READ ID                                          {printf("\nREGLA 20: <entrada> --> READ ID\n");};

salida:
    WRITE CTE_STRING                                   {printf("\nREGLA 21: <salida> -->  WRITE CTE_STRING  \n");};

asignacion:
    ID OP_ASIG expresion                                {
                                                             insertar_en_polaca(&listaPolaca,$1,cont++);
                                                             insertar_en_polaca(&listaPolaca,$2,cont++);
                                                             printf("\nREGLA 22: <asignacion> --> ID OP_ASIG <expresion> \n");
                                                        }
    | ID OP_ASIG CTE_STRING                             {
                                                             insertar_en_polaca(&listaPolaca,$1,cont++);                  insertar_en_polaca(&listaPolaca,$1,cont++);
                                                             insertar_en_polaca(&listaPolaca,$3,cont++);
                                                             insertar_en_polaca(&listaPolaca,$2,cont++);
                                                             printf("\nREGLA 22: <asignacion> --> ID OP_ASIG CTE_STRING \n");
                                                        };

condicion:
    comparacion                                         {printf("\nREGLA 23: <condicion> --> <comparacion> \n");}
    | condicion AND comparacion                         {printf("\nREGLA 24: <condicion> --> <comparacion> AND <comparacion>\n");}
    | condicion OR comparacion                          {printf("\nREGLA 25: <condicion> --> <comparacion> OR <comparacion>\n");}
    | PAR_A NOT condicion PAR_C AND comparacion         {printf("\nREGLA 26: <condicion> --> PAR_A NOT <condicion> PAR_C <comparacion> \n");}
    | PAR_A  NOT condicion PAR_C OR comparacion         {printf("\nREGLA 27: <condicion> --> PAR_A NOT <condicion> PAR_C <comparacion> \n");}
    | between                         {printf("\nREGLA 9: <condicion> --> <between>\n");}
    |inlist                          {printf("\nREGLA 10: <condicion> --> <inlist>\n");};

comparacion:
    expresion comparador expresion                     {printf("\nREGLA 28: <comparacion> --> <expresion><comparador><expresion> \n");};

expresion:
    expresion OP_SUMA termino                           {   
                                                            insertar_en_polaca(&listaPolaca,$2,cont++);
                                                            printf("\nREGLA 29: <expresion> --> <expresion><OP_SUMA><termino> \n");
                                                        }
    | expresion OP_RESTA termino                        {
                                                             insertar_en_polaca(&listaPolaca,$2,cont++);
                                                             printf("\nREGLA 30: <expresion> --> <expresion><OP_RESTA><termino> \n");
                                                        }
    | termino                                           {printf("\nREGLA 31: <expresion> --> <termino> \n");}
    |OP_RESTA expresion %prec MENOS_UNARIO              {printf("\nREGLA 32: <expresion> --> OP_RESTA <expresion> \n");}                               ;

termino:
    termino OP_MULT factor          {
                                        insertar_en_polaca(&listaPolaca,$2,cont++);
                                        printf("\nREGLA 33: <termino> --> <termino> OP_MULT <factor> \n");
                                    }
    | termino OP_DIV factor         {
                                        insertar_en_polaca(&listaPolaca,$2,cont++);
                                        printf("\nREGLA 34: <termino> --> <termino> OP_DIV <factor> \n");
                                    }
    | factor                       {
                                        printf("\nREGLA 35: <termino> --> <factor> \n");
                                   };

lista:
    factor                                              {printf("\nREGLA 36: <lista> --> <factor> \n");}
    | lista COMA factor                                 {printf("\nREGLA 37: <lista> --> <lista> COMA <factor> \n");};

factor:
    PAR_A expresion PAR_C       {printf("\nREGLA 38: <factor> --> PAR_A<expresion><PAR_C>\n");} 
    | CTE_FLOAT                 {
                                    insertar_en_polaca(&listaPolaca,$1,cont++);
                                    printf("\nREGLA 39: <factor> --> CTE_FLOAT\n");
                                } 
    | ID                        {   
                                    insertar_en_polaca(&listaPolaca,$1,cont++);
                                    printf("\nREGLA 40: <factor> --> ID\n");
                                    
                                } 
    | CTE_INTEGER               {
                                    insertar_en_polaca(&listaPolaca,$1,cont++);
                                    printf("\nREGLA 41: <factor> --> <CTE_INTEGER>\n");
                                };

comparador:
    OP_MAY          {printf("\nREGLA 42: <comparador> --> <OP_MAY>\n");} 
    | OP_MEN        {printf("\nREGLA 43: <comparador> --> <OP_MEN>\n");} 
    | OP_MENIGU     {printf("\nREGLA 44: <bloque> --> <OP_MENIGU>\n");} 
    | OP_MAYIGU     {printf("\nREGLA 45: <bloque> --> <OP_MAYIGU>\n");} 
    | OP_IGUAL      {printf("\nREGLA 46: <bloque> --> <OP_IGUAL>\n");} 
    | OP_DIF        {printf("\nREGLA 47: <bloque> --> <OP_DIF>\n");};

between:
    BETWEEN PAR_A ID COMA COR_A expresion PYC expresion COR_C PAR_C	{printf("\nREGLA 48: <between> --> <BETWEEN><PAR_A><ID><COMA><COR_A><expresion><PYC><expresion><COR_C><PAR_C>\n");}; 

lista_expr:
    expresion                                              {printf("\nREGLA 49: <lista_expr> --> <expresion> \n");}
    | lista_expr PYC expresion                             {printf("\nREGLA 50: <lista_expr> --> <lista_expr><PYC><expresion> \n");};
   
inlist:
    INLIST PAR_A ID PYC COR_A lista_expr COR_C PAR_C	{printf("\nREGLA 51: <inlist> --> <INLIST><PAR_A><ID><PYC><COR_A><lista_expr><COR_C><PAR_C>\n");}; 


%%



int main(int argc,char *argv[])
{
    
    abrirTablaDeSimbolos();
    
    createListaPolaca(&listaPolaca);
    createStack(&pilaNumCelda);
    createStack(&pilaVariables);
    createStack(&pilaTipoVariables);

if ((yyin = fopen(argv[1], "rt")) == NULL)
    {
        printf("\nNo se puede abrir el archivo: %s\n", argv[1]);
    }
else
    {
        yyparse();
    }
    escribirTablaSimbolos();
    
    vaciar_polaca(&listaPolaca);
    fclose(fpTabla);
    fclose(yyin);
    return 1;
}




char* validarRangoString( char *text ){
    char * tipo ="CTE_STRING";
    if(strlen(text)>STR_LIMITE)
{
            printf("Eror String: %s - ",text);
            return yyerror();
        }
else{
            cargarVecTablaString(text,tipo);
          return text;
}
}


char* validarRangoID( char *text ){
    if(strlen(text)>ID_LIMITE)
{
        printf("Eror ID: %s - ",text);
        return yyerror();
}
else{

        cargarVecTablaID(text);
          return text;
    } 
}


char* validarRangoEntero( char *text ){
    char* tipo ="CTE_INTEGER";
printf("Valor del entero : %s\n",text+1 );
    if(*text == '-') 
    {
        if( strlen( text+1 ) > ENT_LIMITE || atoi(text) < COTA_INFERIOR_ENT )
        {
           printf("Eror constante entera fuera del limite: %s - ",text);
            return yyerror();
        }


    }else
    {
        if( strlen( text ) > ENT_LIMITE || atoi(text)> COTA_SUPERIOR_ENT )
        {
             printf("Eror constante entera fuera del limite: %s - ",text);
            return yyerror();
        }
   
    }
 cargarVecTablaNumero(text, tipo);
 return text;
}


char* validarRangoReal( char *text ){
    char * tipo ="CTE_FLOAT";
    if(atof(text) > COTA_SUPERIOR_REAL|| atof(text) <  COTA_INFERIOR_REAL) 
        {
            printf("Eror Real: %s - ",text);
            return yyerror();
        }
        else{
            
        cargarVecTablaNumero(text, tipo );
          return text;
        }
   
}

int abrirTablaDeSimbolos()
{
    fpTabla = fopen(TABLA_SIMBOLOS_TXT,"wt");
    if(!fpTabla)
    {
        printf("Error de apertura del archivo de la tabla de simbolos");
        return 0;
    }
    return 1;
}

void escribirTablaSimbolos()
{ 
    int i;
    fprintf(fpTabla,"NOMBRE\t\t\t\tTIPO\t\t\t\tVALOR\t\t\t\tLONGITUD\n");
    for(i = 0 ; i < cantReg; i++)
    {
        fprintf(fpTabla,"%-s\t\t\t\t%-s\t\t\t\t%-s\t\t\t\t%-d\n",tb[i].nombre ,tb[i].tipo ,tb[i].valor,tb[i].longitud);
    }
}

void cargarVecTablaNumero(char * text, char * tipo)
{
   int duplicados = 0,j;
    for ( j=0 ;j< cantReg; j++)
    {
        if(strcmp(text,(tb[j].nombre)+1)==0)
            duplicados = 1;      
    }

    if(!duplicados){
        int tamanio=strlen(text),i;
        char aux[tamanio+2];
        aux[0]='_';
        for (i=1; i<= tamanio ; i++ )
        {
            aux[i]=*(text+i-1);

        }
        aux[i]='\0';
        strcpy(tb[cantReg].nombre,aux);
        strcpy(tb[cantReg].valor,text);
        strcpy(tb[cantReg].tipo,tipo);
         
        tb[cantReg].longitud = 0;
        //printf("\nNombre : %s   -   Valor : %s -   longitud :    %d\n",tb[cantReg].nombre , tb[cantReg].valor,tb[cantReg].longitud);

        cantReg++;
    }



}

void cargarVecTablaID(char * text)
{
    
    int duplicados = 0,j;
    for ( j=0 ;j< cantReg; j++)
    {
        if(strcmp(text,(tb[j].nombre)+1)==0)
            duplicados = 1;      
    }
    if(!duplicados)
    {
        int tamanio=strlen(text),i;
        char aux[tamanio+2];
        aux[0]='_';
        for (i=1; i<= tamanio ; i++ )
        {
            aux[i]=*(text+i-1);
        }
        aux[tamanio+1]='\0';
        strcpy(tb[cantReg].nombre,aux);
        strcpy(tb[cantReg].valor,"-\0");
        tb[cantReg].longitud = 0;
        //printf("\nNombre : %s   -   Valor : %s -   longitud :    %d\n",tb[cantReg].nombre,tb[cantReg].valor,tb[cantReg].longitud);
        cantReg++;
    }
  
}


void cargarVecTablaString(char * text, char* tipo)
{  

        int duplicados = 0,j;
        int i=0 ;
        char aux [strlen(text)+1];
        strcpy(aux,text);
        aux[0] = '_';
        for (i=0; i<= strlen(text) ; i++ )
        {
            if(aux[i] == ' ')
                aux[i]= '_';
        }
        aux[i-2]='\0';
        for ( j=0 ;j< cantReg; j++)
        {
            if(strcmp(aux,tb[j].nombre)==0)
            duplicados = 1;      
        }
        if(!duplicados){
            strcpy(tb[cantReg].nombre,aux);
            strcpy(tb[cantReg].valor,text);
            strcpy(tb[cantReg].tipo,tipo);
            tb[cantReg].longitud = strlen(text)-2;
            cantReg++;
        }
   // printf("\nNombre : %s   -   Valor : %s -   longitud :    %d\n",tb[cantReg].nombre , tb[cantReg].valor,tb[cantReg].longitud);

    
}
void cargarTipoDato(tStack* pilaTipoVariables, tStack* pilaVariables)
{
        int j;
    char * variableaux;
    char * tipo;
    if (emptyStack(pilaTipoVariables))
        popStack(pilaTipoVariables,tipo);
    while(emptyStack(pilaVariables))
    {
        popStack(pilaVariables, variableaux);
        for ( j=0 ;j< cantReg; j++)
        {
            if(strcmp(variableaux,tb[j].nombre)==0)
            {
                strcpy(tb[j].tipo,tipo);
            }
             strcpy(tb[j].tipo,"testt");
        }
    }
}
