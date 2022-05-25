%{
#include <stdio.h>
#include <stdlib.h>

#include "y.tab.h"
int yystopparser=0;
FILE  *yyin;
int yylex();
int yyparse();
int yyerror();
%}

%start programa 
%right OP_ASIG 
%left OP_SUMA OP_RESTA
%left OP_MULT OP_DIV
%right MENOS_UNARIO

%token OP_MAY OP_MAYIGU OP_MEN OP_MENIGU OP_IGUAL OP_DIF
%token WHILE IF INTEGER FLOAT STRING ELSE THEN DECVAR ENDDEC IN AND OR NOT LONG BETWEEN INLIST
%token WRITE COMA ENDIF ENDWHILE DO READ PAR_A PAR_C COR_A COR_C PYC DP

%token ID CONST_ENT CONST_REAL CONST_STR


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
    |entrada                         {printf("\nREGLA 8: <sentencia> --> <entrada>\n");}  
    |between                         {printf("\nREGLA 9: <sentencia> --> <between>\n");}
    |inlist                          {printf("\nREGLA 10: <sentencia> --> <inlist>\n");};



declaracion:
    DECVAR listaDeclaraciones  ENDDEC    {printf("\nREGLA 11: <declaracion> --> DECVAR <listaDeclaraciones> ENDDEC\n");};    
listaDeclaraciones:
    listavar DP tipodato    {printf("\nREGLA 11: <listaDeclaraciones> --> <listavar> DP <tipodato> \n");}   
    |listaDeclaraciones listavar DP tipodato    {printf("\nREGLA 11: <listaDeclaraciones> --> <listaDeclaraciones> <listavar> DP <tipodato> \n");};    
listavar:
    ID                              {printf("\nREGLA 12: <listavar> --> ID \n");}
    | listavar COMA ID              {printf("\nREGLA 13: <listavar> --> <listavar> COMA ID\n");};

tipodato:
    INTEGER                         {printf("\nREGLA 14: <tipodato> --> INTEGER  \n");}
    | FLOAT                         {printf("\nREGLA 15: <tipodato> --> FLOAT \n");}
    | STRING                        {printf("\nREGLA 16: <tipodato> --> STRING \n");};

seleccion:
    IF condicion THEN bloque ELSE bloque ENDIF      {printf("\nREGLA 17: <seleccion> --> IF <condicion> THEN <bloque> ELSE <bloque> ENDIF\n");}
    | IF condicion THEN bloque ENDIF                  {printf("\nREGLA 18: <seleccion> --> IF <condicion> THEN <bloque> ENDIF \n");};

ciclo:
    WHILE ID IN COR_A lista COR_C DO bloque ENDWHILE         {printf("\nREGLA 19: <ciclo> --> WHILE ID IN COR_A <lista> COR_C DO <sentencia> ENDWHILE\n");};

entrada:
    READ ID                                          {printf("\nREGLA 20: <entrada> --> READ <factor>\n");};

salida:
    WRITE CONST_STR                                   {printf("\nREGLA 21: <salida> -->  WRITE CONST_STR  \n");};

asignacion:
    ID OP_ASIG expresion                                {printf("\nREGLA 22: <asignacion> --> <ID><OP_ASIG><expresion> \n");};

condicion:
    comparacion                                         {printf("\nREGLA 23: <condicion> --> <comparacion> \n");}
    | condicion AND comparacion                         {printf("\nREGLA 24: <condicion> --> <comparacion><AND><comparacion>\n");}
    | condicion OR comparacion                          {printf("\nREGLA 25: <condicion> --> <comparacion><OR><comparacion>\n");}
    | PAR_A NOT condicion PAR_C AND comparacion         {printf("\nREGLA 26: <condicion> --> <PAR_A><NOT><condicion><PAR_C><comparacion> \n");}
    | PAR_A  NOT condicion PAR_C OR comparacion         {printf("\nREGLA 27: <condicion> --> <PAR_A><NOT><condicion><PAR_C><comparacion> \n");};

comparacion:
    expresion comparador expresion                     {printf("\nREGLA 28: <comparacion> --> <expresion><comparador><expresion> \n");};

expresion:
    expresion OP_SUMA termino                           {printf("\nREGLA 29: <expresion> --> <expresion><OP_SUMA><termino> \n");}
    | expresion OP_RESTA termino                        {printf("\nREGLA 30: <expresion> --> <expresion><OP_RESTA><termino> \n");}
    | termino                                           {printf("\nREGLA 31: <expresion> --> <termino> \n");}
    |OP_RESTA expresion %prec MENOS_UNARIO              {printf("\nREGLA 32: <expresion> --> OP_RESTA <expresion> \n");}                               ;

termino:
    termino OP_MULT factor                              {printf("\nREGLA 33: <termino> --> <termino><OP_MULT><factor> \n");}
    | termino OP_DIV factor                             {printf("\nREGLA 34: <termino> --> <termino><OP_DIV><factor> \n");}
    | factor                                            {printf("\nREGLA 35: <termino> --> <factor> \n");};

lista:
    factor                                              {printf("\nREGLA 36: <lista> --> <factor> \n");}
    | lista COMA factor                                 {printf("\nREGLA 37: <lista> --> <lista><COMA><factor> \n");};

factor:
    PAR_A expresion PAR_C       {printf("\nREGLA 38: <factor> --> <PAR_A><expresion><PAR_C>\n");} 
    | CONST_REAL                {printf("\nREGLA 39: <factor> --> <CONST_REAL>\n");} 
    | ID                        {printf("\nREGLA 40: <factor> --> <ID>\n");} 
    | CONST_ENT                 {printf("\nREGLA 41: <factor> --> <CONST_ENT>\n");};

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
