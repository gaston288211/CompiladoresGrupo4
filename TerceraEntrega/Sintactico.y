%{
    
#include "lista.h"
#include "listaPolaca.h"
#include <stdio.h>
#include <stdlib.h>

#include "y.tab.h"
#define SUCCESS 1
#define DUPLICATE 2
#define NO_EXISTE 3

#define STR_LIMITE 30
#define ID_LIMITE 30
#define ENT_LIMITE 5
#define TABLA_SIMBOLOS_TXT "ts.txt"

#define COTA_INFERIOR_ENT -32768
#define COTA_SUPERIOR_ENT 32767

#define COTA_SUPERIOR_REAL 3.4028235E+38
#define COTA_INFERIOR_REAL -3.4028235E+38

#define LABELTRUE   "LABELTRUE"
#define LABELFALSE  "LABELFALSE"

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
char* listaComparacion[2000];
int indiceComparacion=0;

// Para assembler
	FILE * pfASM; // Final.asm

void cargarTipoDato(tList* symbolTable, tStack* pilaTipoVariables, tStack* pilaVariables);
char* validarRangoString( char *text );
char* validarRangoEntero( char *text );
char* validarRangoID( char *text );
char* validarRangoReal( char *text );
void escribirTablaSimbolos();
void cargarVecTablaString(char * text, char * tipo);
void cargarVecTablaID(char * text);
void cargarVecTablaNumero(char * text, char * tipo);
int abrirTablaDeSimbolos();
void insertarListaComp(char* lex) ;
void compararTiposAsig();
void compararTiposAsigSting();
void compararTiposComp();
/// segunda entrega
t_lista listaPolaca;
tStack pilaNumCelda;
tStack pilaVariables;
tStack pilaTipoVariables;
tStack pilaCondiciones;
tStack pilaInList;
tList  symbolTable;

int cont=1;
int contIF=0;

char labelIfFin[30];
char labelIfTrue[30];
char labelIfFalse[20];
char labelBodyWhile[20];
char labelWhile[20];
char labelIF[20];
char auxBetween [100];
char auxInlist[100];
%}
%union{
    char* strVal;
}

%start programa 
%right OP_ASIG 
%left OP_SUMA OP_RESTA
%left OP_MULT OP_DIV
%right MENOS_UNARIO

%token OP_MAY 
%token OP_MAYIGU 
%token OP_MEN 
%token OP_MENIGU
%token OP_IGUAL
%token OP_DIF
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
%token <strVal> OP_SUMA
%token <strVal> OP_RESTA
%token <strVal> OP_ASIG
%token <strVal> OP_DIV
%token <strVal> OP_MULT

%%
programa:
    declaracion bloque				{printf("\nREGLA 1: <programa> --> <declaracion> <bloque>\n");} 
	
bloque:
    sentencia                       {printf("\nREGLA 2: <bloque> --> <sentencia>\n");}       
    |bloque sentencia            	{printf("\nREGLA 3: <bloque> --> <bloque> <sentencia>\n");};              
    
sentencia:
    asignacion                    	{printf("\nREGLA 4: <sentencia> --> <asignacion>\n");}   
    |ciclo                          {printf("\nREGLA 5: <sentencia> --> <ciclo>\n");}   
    |seleccion                      {printf("\nREGLA 6: <sentencia> --> <seleccion>\n");}   
    |salida                         {printf("\nREGLA 7: <sentencia> --> <salida>\n");}   
    |entrada                        {printf("\nREGLA 8: <sentencia> --> <entrada>\n");};

declaracion:
    DECVAR listaDeclaraciones  ENDDEC	{  
                                            
                                            printf("\nREGLA 9: <declaracion> --> DECVAR <listaDeclaraciones> ENDDEC\n");
                                        };
										
listaDeclaraciones:
    listavar DP tipodato                        {
                                                    cargarTipoDato(&symbolTable, &pilaTipoVariables,&pilaVariables);
                                                    printf("\nREGLA 10: <listaDeclaraciones> --> <listavar> DP <tipodato> \n");}   
    |listaDeclaraciones listavar DP tipodato    {
                                                    cargarTipoDato(&symbolTable, &pilaTipoVariables,&pilaVariables);
                                                    printf("\nREGLA 11: <listaDeclaraciones> --> <listaDeclaraciones> <listavar> DP <tipodato> \n");
                                                };    
												
listavar:
    ID                              {
                                        pushStack(&pilaVariables,$1);
                                        printf("\nREGLA 12: <listavar> --> ID \n");
                                    }
    |listavar COMA ID               {
                                        pushStack(&pilaVariables,$3);
                                        printf("\nREGLA 13: <listavar> --> <listavar> COMA ID\n");
                                    };
									
tipodato:
    INTEGER                         {
                                        pushStack(&pilaTipoVariables,"INTEGER");
                                        printf("\nREGLA 14: <tipodato> --> INTEGER  \n");
                                    }
    |FLOAT                          {
                                        pushStack(&pilaTipoVariables,"FLOAT");
                                        printf("\nREGLA 15: <tipodato> --> FLOAT \n");}
    |STRING                         {
                                        pushStack(&pilaTipoVariables,"STRING");
                                        printf("\nREGLA 16: <tipodato> --> STRING \n");
                                    };
									
seleccion:
    condicion_if  bloque ELSE    {
									int numCell;
									int cmp;
									char label[20];
                                    strcpy(label,"Ini");
											
									while(!emptyStack(&pilaNumCelda) && strcmpi(label, "IF_ANIDADO")!=0)
									{
										popStack2(&pilaNumCelda, label, &numCell);
										cmp=strcmpi(label, LABELFALSE);
										if (cmp==0) {
											char NumBiOutOfTheWhile[20];
											//strcpy(labelIfFalse,"ET_FALSE_IF_");
											itoa(cont+2, NumBiOutOfTheWhile, 10);
											strcpy(labelIfFalse, NumBiOutOfTheWhile);
											rellenarPolaca2(&listaPolaca, numCell, labelIfFalse);
										} 
										else 
										{   
											cmp=strcmpi(label, LABELTRUE);
											if (cmp==0){
													//VER SI ES NECESARIO
												rellenarPolaca2(&listaPolaca, numCell, labelIfTrue);
											}
										}
									}
									strcpy(labelIfFin,"ET_END_IF_");
									insertar_en_polaca(&listaPolaca,"BI",cont++);
									pushStack2(&pilaNumCelda,labelIfFin,cont);//guardar en pila posicion actual
									insertar_en_polaca(&listaPolaca,labelIfFin,cont++);
                                    insertar_en_polaca(&listaPolaca,"ET_FALSE_IF",cont++);
								}
     
    bloque ENDIF	{
						int numCell;
						int cmp;
						char label[20];
                        strcpy(label,"Ini");
                        while(!emptyStack(&pilaNumCelda) && strcmpi(label, "IF_ANIDADO")!=0)
						{
							popStack2(&pilaNumCelda, label, &numCell);
							cmp=strcmpi(label, labelIfFin);
							if (cmp==0) 
							{
								char NumBiOutOfTheWhile[20];
								itoa(cont, NumBiOutOfTheWhile, 10);
								strcpy(label, NumBiOutOfTheWhile);
								rellenarPolaca2(&listaPolaca, numCell, label);
							}
						}
                        insertar_en_polaca(&listaPolaca,"ET_END_IF",cont++);
                        printf("\nREGLA 17: <seleccion> --> IF <condicion> THEN <bloque> ELSE <bloque> ENDIF\n");
					}
	|condicion_if bloque ENDIF	{
									int numCell;
									int cmp;
									char label[20];
                                    strcpy(label,"Ini");
									while(!emptyStack(&pilaNumCelda) && strcmpi(label, "IF_ANIDADO")!=0)
									{
										popStack2(&pilaNumCelda, label, &numCell);
										cmp=strcmpi(label, LABELFALSE);
										if (cmp==0) 
										{
											char NumBiOutOfTheWhile[20];
											//strcpy(labelIfFin,"ET_END_IF_");
											itoa(cont, NumBiOutOfTheWhile, 10);
											strcpy(labelIfFin, NumBiOutOfTheWhile);
											rellenarPolaca2(&listaPolaca, numCell, labelIfFin);
										}
									}		
                                    insertar_en_polaca(&listaPolaca,"ET_END_IF",cont++);
									printf("\nREGLA 18: <seleccion> --> IF <condicion> THEN <bloque> ELSE <bloque> ENDIF\n");
								};
								
condicion_if:
    IF                  {   
                            contIF++;
                            pushStack2(&pilaNumCelda,"IF_ANIDADO",contIF);
                        }
        condicion THEN	{
							char num[20];
							strcpy(labelIfTrue,"ET_TRUE_IF");
							itoa(cont, num, 10);
							strcat(labelIfTrue, num);
                            printf("\nREGLA 48: <seleccion> --> IF <condicion> THEN \n");
						};
						
ciclo:  
	WHILE   {
				char numCell[10];
				char labelInitWhile[20];
				itoa(cont, numCell, 10);
				strcpy(labelInitWhile, "ET_WHILE_");
				strcat(labelInitWhile, numCell);
				strcpy(labelWhile, labelInitWhile);
				insertar_en_polaca(&listaPolaca, "ET_INICIO_WHILE", cont++);
			}
	condicion DO 	{
						char NumBiOutOfTheWhile[20];
						strcpy(labelBodyWhile,"ET_INIT_WHILE_");
						itoa(cont, NumBiOutOfTheWhile, 10);
						strcat(labelBodyWhile, NumBiOutOfTheWhile);
					}
	bloque  {
				insertar_en_polaca(&listaPolaca,"BI",cont++);
				insertar_en_polaca(&listaPolaca,labelWhile,cont++);
			}
	ENDWHILE 	{
					int numCell;
					int cmp;
					char label[20];
					while(!emptyStack(&pilaNumCelda))
					{
						popStack2(&pilaNumCelda, label, &numCell);
						cmp=strcmpi(label, LABELFALSE);
						if (cmp==0) 
						{
							char NumBiOutOfTheWhile[20];
							char labelBi[20];
							strcpy(labelBi,"ET_END_WHILE_");
							itoa(cont, NumBiOutOfTheWhile, 10);
							rellenarPolaca2(&listaPolaca, numCell, NumBiOutOfTheWhile);
							strcat(labelBi, NumBiOutOfTheWhile);
                            insertar_en_polaca(&listaPolaca,labelBi,cont++);
						} 
						else 
						{   
							cmp=strcmpi(label, LABELTRUE);
							if (cmp==0){
									//VER SI ES NECESARIO
								rellenarPolaca2(&listaPolaca, numCell, labelBodyWhile);
							}
						}
					}
				};
				
entrada:
    READ ID {
				insertar_en_polaca(&listaPolaca,"READ",cont++);
				insertar_en_polaca(&listaPolaca,$2,cont++);
				printf("\nREGLA 19: <entrada> --> READ ID\n");
			};
			
salida:
    WRITE CTE_STRING    {
							insertar_en_polaca(&listaPolaca,$2,cont++);
                            insertar_en_polaca(&listaPolaca,"WRITE",cont++);
							insertarString(&symbolTable, $2);
							printf("\nREGLA 20: <salida> -->  WRITE CTE_STRING  \n");
						};
						
asignacion:
ID                          
    OP_ASIG expresion    {
                                listaComparacion[0]=$1;
								insertar_en_polaca(&listaPolaca,$1,cont++);
								insertar_en_polaca(&listaPolaca,$2,cont++);
                                compararTiposAsig();
								printf("\nREGLA 21: <asignacion> --> ID OP_ASIG <expresion> \n");
							}
    |ID OP_ASIG CTE_STRING  {
                                insertarListaComp($1);
                                insertarListaComp($3);
                                compararTiposAsigSting();
								insertar_en_polaca(&listaPolaca,$3,cont++);
								insertar_en_polaca(&listaPolaca,$1,cont++);                  
								insertar_en_polaca(&listaPolaca,$2,cont++);
								insertarString(&symbolTable, $3);
								printf("\nREGLA 22: <asignacion> --> ID OP_ASIG CTE_STRING \n");
							};

condicion:
    comparacion				{printf("\nREGLA 23: <condicion> --> <comparacion> \n");}
    |condicion 
    AND comparacion         {   //queda igual porque si una es neg salta
								printf("\nREGLA 24: <condicion> --> <comparacion> AND <comparacion>\n");
							}
	|PAR_A NOT      		{   //meto en la pila el not, y cuando leo las condiciones inserto el neg
								pushStack(&pilaCondiciones,$2);
							}
    comparacion PAR_C
    |condicion          	{//SI es neg deberia preguntar por la segunda
								int numCell;
								int contaux;
								char label[20];
								char NumBiOutOfTheWhile[20];
								while(!emptyStack(&pilaNumCelda))
								{
									popStack2(&pilaNumCelda, label, &numCell);
									//printf("%s - %d --------------\n",label, numCell);
									int cmp =  strcmpi(label, "LABELFALSE");
									if (cmp==0) 
									{
										strcpy(label,"OR_SIG_COND_");
										contaux=cont+2;//por el salto de BI y etiqueta true
										itoa(contaux, NumBiOutOfTheWhile, 10);
										strcat(label, NumBiOutOfTheWhile);
										rellenarPolaca2(&listaPolaca, numCell, label);
									}
                                }
                                insertar_en_polaca(&listaPolaca,"BI",cont++);
                                pushStack2(&pilaNumCelda,LABELTRUE,cont);//guardar en pila posicion actual
                                insertar_en_polaca(&listaPolaca,LABELTRUE,cont++);
                            }
    OR                      {
								char label[20];
								strcpy(label,"OR_SIG_COND");
								insertar_en_polaca(&listaPolaca,label,cont++);
								//printf("despues de or");
                            }
    comparacion             {
                                printf("\nREGLA 25: <condicion> --> <comparacion> OR <comparacion>\n");
							}
    |between                {printf("\nREGLA 26: <condicion> --> <between>\n");}
    |inlist                 {printf("\nREGLA 27: <condicion> --> <inlist>\n");};

comparacion:
    expresion OP_MAY expresion                     		
                        {	
							char label[20];
                            if(!emptyStack(&pilaCondiciones))
							{
								popStack(&pilaCondiciones, label);
                                if (strcmp(label,"NOT")==0)
                                {
                                    insertar_en_polaca(&listaPolaca,"CMP",cont++);
                                    insertar_en_polaca(&listaPolaca,"BGT",cont++);
                                }
                            }	
                            else
							{						
								insertar_en_polaca(&listaPolaca,"CMP",cont++);
								insertar_en_polaca(&listaPolaca,"BLE",cont++);
                            }
                            pushStack2(&pilaNumCelda,LABELFALSE,cont);//guardar en pila posicion actual
                            insertar_en_polaca(&listaPolaca,LABELFALSE,cont++);//Avanzar
                            printf("\nREGLA 28: <comparacion> --> <expresion> OP_MAY <expresion> \n");							
					    } 
    |expresion OP_MEN expresion          	
						{
						    char label[20];
                            if(!emptyStack(&pilaCondiciones))
							{
                                popStack(&pilaCondiciones, label );
                                if (strcmp(label,"NOT")==0)
                                {
                                    insertar_en_polaca(&listaPolaca,"CMP",cont++);
                                    insertar_en_polaca(&listaPolaca,"BLT",cont++);
                                }
                            }	
                            else
							{
                                insertar_en_polaca(&listaPolaca,"CMP",cont++);
						        insertar_en_polaca(&listaPolaca,"BGE",cont++);
                            }
							pushStack2(&pilaNumCelda,LABELFALSE,cont);//guardar en pila posicion actual
							insertar_en_polaca(&listaPolaca,LABELFALSE,cont++);//Avanzar
							printf("\nREGLA 29: <comparacion> --> <expresion> OP_MEN <expresion> \n");
						} 
    |expresion OP_MENIGU expresion      	
						{
                            char label[20];
                            if(!emptyStack(&pilaCondiciones))
							{
                                popStack(&pilaCondiciones, label);
                                if (strcmp(label,"NOT")==0)
                                {
                                    insertar_en_polaca(&listaPolaca,"CMP",cont++);
                                    insertar_en_polaca(&listaPolaca,"BLE",cont++);
                                }
                            }	
                            else
							{
								insertar_en_polaca(&listaPolaca,"CMP",cont++);
								insertar_en_polaca(&listaPolaca,"BGT",cont++);
                            }
							pushStack2(&pilaNumCelda,LABELFALSE,cont);//guardar en pila posicion actual
							insertar_en_polaca(&listaPolaca,LABELFALSE,cont++);//Avanzar
							printf("\nREGLA 30: <comparacion> --> <expresion> OP_MENIGU <expresion> \n");
						} 
    |expresion OP_MAYIGU expresion      	
						{
							char label[20];
							if(!emptyStack(&pilaCondiciones))
							{
                                popStack(&pilaCondiciones, label);
                                if (strcmp(label,"NOT")==0)
                                {
                                    insertar_en_polaca(&listaPolaca,"CMP",cont++);
                                    insertar_en_polaca(&listaPolaca,"BGE",cont++);
                                }
                            }	
                            else
							{
								insertar_en_polaca(&listaPolaca,"CMP",cont++);
								insertar_en_polaca(&listaPolaca,"BLT",cont++);
                            }
							pushStack2(&pilaNumCelda,LABELFALSE,cont);//guardar en pila posicion actual
							insertar_en_polaca(&listaPolaca,LABELFALSE,cont++);//Avanzar
							printf("\nREGLA 31: <comparacion> --> <expresion> OP_MAYIGU <expresion> \n");
						} 
    |expresion OP_IGUAL expresion       	
						{
							char label[20];
                            if(!emptyStack(&pilaCondiciones))
							{
                                popStack(&pilaCondiciones, label );
                                //printf("%s-test",label);
                                if (strcmp(label,"NOT")==0)
                                {
                                    insertar_en_polaca(&listaPolaca,"CMP",cont++);
                                    insertar_en_polaca(&listaPolaca,"BET",cont++);
                                }
                            }	
                            else
							{
								insertar_en_polaca(&listaPolaca,"CMP",cont++);
								insertar_en_polaca(&listaPolaca,"BNE",cont++);
                            }
							pushStack2(&pilaNumCelda,LABELFALSE,cont);//guardar en pila posicion actual
							insertar_en_polaca(&listaPolaca,LABELFALSE,cont++);//Avanzar
							printf("\nREGLA 32: <comparacion> --> <expresion> OP_IGUAL <expresion> \n");
						} 
    |expresion OP_DIF expresion         	
						{	
							char label[20];
                            if(!emptyStack(&pilaCondiciones))
							{
                                popStack(&pilaCondiciones, label);
                                if (strcmp(label,"NOT")==0)
                                {
                                    insertar_en_polaca(&listaPolaca,"CMP",cont++);
                                    insertar_en_polaca(&listaPolaca,"BNE",cont++);
                                }
                            }	
                            else
							{
								insertar_en_polaca(&listaPolaca,"CMP",cont++);
								insertar_en_polaca(&listaPolaca,"BET",cont++);
                            }
							pushStack2(&pilaNumCelda,LABELFALSE,cont);//guardar en pila posicion actual
							insertar_en_polaca(&listaPolaca,LABELFALSE,cont++);//Avanzar
							printf("\nREGLA 33: <comparacion> --> <expresion> OP_DIF <expresion> \n");
						};
					
expresion:
    expresion OP_SUMA termino               {   
												insertar_en_polaca(&listaPolaca,$2,cont++);
												printf("\nREGLA 34: <expresion> --> <expresion><OP_SUMA><termino> \n");
											}
    | expresion OP_RESTA termino            {
												 insertar_en_polaca(&listaPolaca,$2,cont++);
												 printf("\nREGLA 35: <expresion> --> <expresion><OP_RESTA><termino> \n");
											}
    | termino                              	{printf("\nREGLA 36: <expresion> --> <termino> \n");}
    |OP_RESTA expresion %prec MENOS_UNARIO	{printf("\nREGLA 37: <expresion> --> OP_RESTA <expresion> \n");};

termino:
    termino OP_MULT factor          {
										insertar_en_polaca(&listaPolaca,$2,cont++);
										printf("\nREGLA 38: <termino> --> <termino> OP_MULT <factor> \n");
                                    }
    |termino OP_DIV factor          {
										insertar_en_polaca(&listaPolaca,$2,cont++);
										printf("\nREGLA 39: <termino> --> <termino> OP_DIV <factor> \n");
                                    }
    |factor                         {
										printf("\nREGLA 40: <termino> --> <factor> \n");
                                    };

factor:
    PAR_A expresion PAR_C       {printf("\nREGLA 41: <factor> --> PAR_A<expresion><PAR_C>\n");} 
    |CTE_FLOAT                  {
                                    insertar_en_polaca(&listaPolaca,$1,cont++);
                                    insertarNumero(&symbolTable,$1,"CTE_FLOAT");
                                    insertarListaComp($1);
                                    printf("\nREGLA 42: <factor> --> CTE_FLOAT\n");
                                } 
    |ID                         {   
									insertar_en_polaca(&listaPolaca,$1,cont++);
                                    insertarListaComp($1);
									printf("\nREGLA 43: <factor> --> ID\n");
                                } 
    |CTE_INTEGER                {
									insertar_en_polaca(&listaPolaca,$1,cont++);
									insertarNumero(&symbolTable,$1,"CTE_INTEGER");
                                    insertarListaComp($1);
									printf("\nREGLA 44: <factor> --> <CTE_INTEGER>\n");
								};

between:
    BETWEEN PAR_A ID			{	
									strcpy(auxBetween,$3);
									insertar_en_polaca(&listaPolaca,$3,cont++);
								}
	COMA COR_A expresion PYC	{
									insertar_en_polaca(&listaPolaca,"CMP",cont++);
                                    insertar_en_polaca(&listaPolaca,"BLT",cont++);
									pushStack2(&pilaNumCelda,LABELFALSE,cont);//guardar en pila posicion actual
									insertar_en_polaca(&listaPolaca,LABELFALSE,cont++);//Avanzar
									insertar_en_polaca(&listaPolaca,auxBetween,cont++);
								}
	expresion COR_C				{
									insertar_en_polaca(&listaPolaca,"CMP",cont++);
                                    insertar_en_polaca(&listaPolaca,"BGT",cont++);
									pushStack2(&pilaNumCelda,LABELFALSE,cont);//guardar en pila posicion actual
									insertar_en_polaca(&listaPolaca,LABELFALSE,cont++);//Avanzar
								}
	PAR_C						{printf("\nREGLA 45: <between> --> <BETWEEN><PAR_A><ID><COMA><COR_A><expresion><PYC><expresion><COR_C><PAR_C>\n");};

lista_expr:
    expresion                   {
									int auxcont;
									char label[20];
									char numCell[20];
									insertar_en_polaca(&listaPolaca,auxInlist,cont++);
									insertar_en_polaca(&listaPolaca,"CMP",cont++);
									insertar_en_polaca(&listaPolaca,"BNE",cont++);
									//pushStack2(&pilaNumCelda,LABELFALSE,cont);//guardar en pila posicion actual
									auxcont=cont+3;
									strcpy(label,"SIG_COND_");
									itoa(auxcont,numCell,10);
									strcat(label,numCell);
									pushStack2(&pilaInList,"_",cont);
									insertar_en_polaca(&listaPolaca,label,cont++);//Avanzar
									insertar_en_polaca(&listaPolaca,"BI",cont++);//Avanzar
									pushStack2(&pilaNumCelda,LABELTRUE,cont);//guardar en pila posicion actual
									insertar_en_polaca(&listaPolaca,LABELTRUE,cont++);//Avanzar
									printf("\nREGLA 46: <lista_expr> --> <expresion> \n");
								}
    |lista_expr PYC expresion   {	
									int auxcont;
									char label[20];
									char numCell[20];
									insertar_en_polaca(&listaPolaca,auxInlist,cont++);
									insertar_en_polaca(&listaPolaca,"CMP",cont++);
									insertar_en_polaca(&listaPolaca,"BNE",cont++);
									//pushStack2(&pilaNumCelda,LABELFALSE,cont);//guardar en pila posicion actual
									auxcont=cont+3;
									strcpy(label,"SIG_COND_");
									itoa(auxcont,numCell,10);
									strcat(label,numCell);
									pushStack2(&pilaInList,"_",cont);
									insertar_en_polaca(&listaPolaca,label,cont++);//Avanzar
									insertar_en_polaca(&listaPolaca,"BI",cont++);//Avanzar
									pushStack2(&pilaNumCelda,LABELTRUE,cont);//guardar en pila posicion actual
									insertar_en_polaca(&listaPolaca,LABELTRUE,cont++);//Avanzar
									printf("\nREGLA 47: <lista_expr> --> <lista_expr><PYC><expresion> \n");
								};
   
inlist:
    INLIST PAR_A ID 					{	
											strcpy(auxInlist,$3);
										}
	PYC COR_A lista_expr COR_C PAR_C	{
											char label[20];
											int numCell;
											if(!emptyStack(&pilaInList))
											{
												popStack2(&pilaInList,label,&numCell);
												rellenarPolaca2(&listaPolaca,numCell,LABELFALSE);
												pushStack2(&pilaNumCelda,LABELFALSE,numCell);//guardar en pila posicion actual
                                            }
											printf("\nREGLA 48: <inlist> --> <INLIST><PAR_A><ID><PYC><COR_A><lista_expr><COR_C><PAR_C>\n");
											}; 

%%


int main(int argc,char *argv[])
{
    
    //abrirTablaDeSimbolos();
    
    createListaPolaca(&listaPolaca);
    createStack(&pilaNumCelda);
    createStack(&pilaVariables);
    createStack(&pilaTipoVariables);
    crearLista(&symbolTable);

if ((yyin = fopen(argv[1], "rt")) == NULL)
    {
        printf("\nNo se puede abrir el archivo: %s\n", argv[1]);
    }
else
    {
        yyparse();
    }
    //escribirTablaSimbolos();
    vaciar_polaca(&listaPolaca);
	escribirTabla(&symbolTable);
    fclose(fpTabla);
    fclose(yyin);
    return 1;
}




char* validarRangoString( char *text ){
    char * tipo ="CTE_STRING";
    if(strlen(text)>STR_LIMITE)
{
            printf("Error String: %s - ",text);
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
        printf("Error ID: %s - ",text);
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
           printf("Error constante entera fuera del limite: %s - ",text);
            return yyerror();
        }


    }else
    {
        if( strlen( text ) > ENT_LIMITE || atoi(text)> COTA_SUPERIOR_ENT )
        {
             printf("Error constante entera fuera del limite: %s - ",text);
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
            printf("Error Real: %s - ",text);
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
void cargarTipoDato(tList* symbolTable,tStack* pilaTipoVariables, tStack* pilaVariables)
{
    int j;
    int resultado;
    char variableaux[100];
    char tipo[100];
    if (!emptyStack(pilaTipoVariables)){
        //printf("test1");
        j=popStack(pilaTipoVariables,tipo);
    }
    printf("%s",tipo);
    while(!emptyStack(pilaVariables))
    {
        //printf("test");
       j=popStack(pilaVariables, variableaux);
        resultado=insertarVariable(symbolTable, variableaux, tipo);  
        if (resultado==DUPLICATE)
        {
            printf("\nError la variable %s ya fue declarada\n",variableaux);
            yyerror();
        }
    }
}

void insertarListaComp(char* lex) 
{
    indiceComparacion++;
    printf("\n%d\n",indiceComparacion);
    listaComparacion[indiceComparacion]=lex;
    
}
void compararTiposAsigSting()
{
    int result=0;
    int length , cmp;
    char  tipodato[50],  valor[50];
    result=obtenerDatos(&symbolTable,listaComparacion[0],tipodato, valor ,&length);
    if(result==0)
    {   
        cmp=strcmpi(tipodato,"STRING");
        if(cmp!=0)
        {
            
            printf("\nError se esta asingando una cosntante a un ID declarado como %s\n",tipodato);
            yyerror();
        }
    }else
    {
        printf("\nError %s no fue declarado\n",listaComparacion[0]);
        yyerror();
    }
}
void compararTiposAsig()
{
    char auxbaseNombre[50], auxbaseTipo[50],  auxbaseValor[50];
    char auxcompNombre[50], auxcompTipo[50],  auxcompValor[50];
    int lengthbase, lengthcomp, result;
    
    strcpy(auxbaseNombre, listaComparacion[0]);
    result=obtenerDatos(&symbolTable,auxbaseNombre,auxbaseTipo, auxbaseValor ,&lengthbase);
    if(result==0)
    { 
        printf("primerif\n %d",indiceComparacion);
        while(indiceComparacion>0)
        {
            printf("while %d",indiceComparacion);
            result=obtenerDatos(&symbolTable,listaComparacion[indiceComparacion],auxcompTipo, auxcompValor ,&lengthcomp);
            //si son iguales Salgo directamente
            if(result==0)
                { 
                    printf("\ncompara base: %s --- tipo compara: %s-%s", auxbaseTipo, auxcompTipo,listaComparacion[indiceComparacion]);
                    if (strcmp(auxbaseTipo, auxcompTipo)!=0)
                    {       
                        if(strcmp(auxbaseTipo,"INTEGER")==0 && (strcmp(auxbaseTipo,"CTE_FLOAT") || strcmp(auxbaseTipo,"FLOAT")))
                        {
                            printf("\nSe esta asignando una expresion tipo float a un entero\n");
                            yyerror();
                        }
                        if(strcmp(auxbaseTipo,"INTEGER")==0 && (strcmp(auxbaseTipo,"CTE_STRING") || strcmp(auxbaseTipo,"STRING")))
                        {
                            printf("\nSe esta asignando una expresion tipo string a un entero\n");
                            yyerror();
                        }
                        if(strcmp(auxbaseTipo,"FLOAT")==0 && (strcmp(auxbaseTipo,"CTE_STRING") || strcmp(auxbaseTipo,"STRING")))
                        {
                            printf("\nSe esta asignando una expresion tipo string a un float\n");
                            yyerror();
                        }

                    }
                }
            indiceComparacion--;
        }
    }
    indiceComparacion=0;
}
void compararTiposComp()
{
    char auxbaseNombre[50], auxbaseTipo[50],  auxbaseValor[50];
    char auxcompNombre[50], auxcompTipo[50],  auxcompValor[50];
    int lengthbase, lengthcomp;
    
    strcpy(auxbaseNombre, listaComparacion[0]);
    obtenerDatos(&symbolTable,auxbaseNombre,auxbaseTipo, auxbaseValor ,&lengthbase);

    while(indiceComparacion>0)
    {
        obtenerDatos(&symbolTable,auxcompNombre,auxcompTipo, auxcompValor ,&lengthcomp);
        //si son iguales Salgo directamente
        if (strcmp(auxbaseTipo, auxcompTipo)!=0)
        {       
            if(strcmp(auxbaseTipo,"CTE_INTEGER")==0 && strcmp(auxbaseTipo,"CTE_FLOAT"))
            {
                printf("\nSe esta asignando una expresion tipo float a un entero\n");
                yyerror();
            }
            if(strcmp(auxbaseTipo,"CTE_INTEGER")==0 && strcmp(auxbaseTipo,"CTE_STRING"))
            {
                printf("\nSe esta asignando una expresion tipo string a un entero\n");
                yyerror();
            }
            if(strcmp(auxbaseTipo,"CTE_FLOAT")==0 && strcmp(auxbaseTipo,"CTE_STRING"))
            {
                printf("\nSe esta asignando una expresion tipo string a un float\n");
                yyerror();
            }

        }
        indiceComparacion--;

    }
    indiceComparacion=0;
}

//////// ASSEMBLER 
//Funcion que se encarga de generar el archivo y completarlo
void generarAssembler(){
	pfASM = fopen("asm/Final.asm", "w");
    // Creo pilas para tercetos.
    crear_pila(&pVariables);
    generarEncabezado();
    generarDatos();
    generarCodigo();
    generarFin();
    fclose(pfASM);
}

void generarEncabezado(){
    fprintf(pfASM, "\nINCLUDE macros2.asm\t\t ;incluye macros\n");
    fprintf(pfASM, "INCLUDE number.asm\t\t ;incluye el asm para impresion de numeros\n");
    fprintf(pfASM, "\n.MODEL LARGE\t\t ; tipo del modelo de memoria usado.\n");
    fprintf(pfASM, ".386\n");
	fprintf(pfASM, ".387\n");
    fprintf(pfASM, ".STACK 200h\t\t ; bytes en el stack\n");
}

void generarDatos(){
    fprintf(pfASM, "\t\n.DATA\t\t ; comienzo de la zona de datos.\n");
    fprintf(pfASM, "\tTRUE equ 1\n");
    fprintf(pfASM, "\tFALSE equ 0\n");
    fprintf(pfASM, "\tMAXTEXTSIZE equ %d\n",COTA_STR);

    tList* auxSimbolos = symbTable;
	int i;
	//int tamTS = obtenerTamTS();
	//for(i=0; i<tamTS; i++)
	while(*auxSimbolos)
    {
		if(strcmp((*auxSimbolos)->dataType, "INTEGER") == 0 )
		{
			fprintf(pfASM, "\t%s dd 0\n",(*auxSimbolos)->name);
		}
		if(strcmp((*auxSimbolos)->dataType, "FLOAT") == 0 )
		{
			fprintf(pfASM, "\t%s dd 0.0\n",(*auxSimbolos)->name);
		}
		if(strcmp((*auxSimbolos)->dataType, "STRING") == 0 )
		{
			fprintf(pfASM, "\t%s db MAXTEXTSIZE dup(?), '$'\n",(*auxSimbolos)->name);
		}
		if(strcmp((*auxSimbolos)->dataType, "CTE_INTEGER") == 0 || strcmp((*auxSimbolos)->dataType, "CTE_FLOAT") == 0 )
		{
            fprintf(pfASM, "\t%s dd %s\n",(*auxSimbolos)->name, (*auxSimbolos)->value);
		}
		if(strcmp((*auxSimbolos)->dataType, "CTE_STRING") == 0)
		{
			int longitud = (*auxSimbolos)->length;
			int size = STR_LIMITE - longitud;
			fprintf(pfASM, "\t%s db %s, '$', %d dup(?)\n", (*auxSimbolos)->name, (*auxSimbolos)->value, size);
		}
	}
	
}

void imprimirFuncString(){
    int c;
    FILE *file;
    file = fopen("string.asm", "r");
    if (file) {
        fprintf(pfASM,"\n");
        while ((c = getc(file)) != EOF)
        fprintf(pfASM,"%c",c);
        fprintf(pfASM,"\n\n");
        fclose(file);
    }
}
//adaptar a polaca----------------------------
void generarCodigo(){
    fprintf(pfASM, "\n.CODE ;Comienza sector de codigo\n");

    imprimirFuncString();

    //Comienza codigo usuario
    fprintf(pfASM, "START: \t\t;Codigo assembler resultante.\n");
    fprintf(pfASM, "\tmov AX,@DATA \t\t;Comienza sector de datos\n");
    fprintf(pfASM, "\tmov DS,AX\n");
    fprintf(pfASM, "\tfinit\n\n");

	int i;
	int tamTercetos = obtenerIndiceActual();

	char aux1[50];
	char aux2[50];
	char auxEtiqueta[50];

	int flag;
	for(i=0; i<tamTercetos; i++)
	{
		char operador[50];
		strcpy(operador,tercetos[i].operador);
		flag = 0;

		if(strcmp(operador, "=") == 0)
		{
			flag = 1;
			fprintf(pfASM,"\t;ASIGNACIÓN\n");
			sacar_de_pila(&pVariables,&aux2);
			sacar_de_pila(&pVariables,&aux1);

			char * tipo = recuperarTipoTS(aux1);
    		char auxTipo[50] = "";
			strcpy(auxTipo, tipo);

			if(strcmp(tipo,"CONST_STR") == 0 || strcmp(tipo,"STRING") == 0)
			{
				fprintf(pfASM, "\tmov ax,@DATA\n");
                fprintf(pfASM, "\tmov es,ax\n");
                fprintf(pfASM, "\tmov si,OFFSET %s ;apunta el origen al auxiliar\n",aux1);
                fprintf(pfASM, "\tmov di,OFFSET %s ;apunta el destino a la cadena\n",aux2);
				fprintf(pfASM, "\tcall COPIAR ;copia los string\n\n");
			}
			else
			{
				fprintf(pfASM, "\tfld %s\n",aux1);
                fprintf(pfASM, "\tfstp %s\n\n",aux2);
			}
		}

		if(strcmp(operador, "CMP") == 0)
		{
			flag = 1;
			fprintf(pfASM,"\t;CMP\n");
			sacar_de_pila(&pVariables,&aux2);
			sacar_de_pila(&pVariables,&aux1);

			// fprintf(pfASM,"\t%s\n",auxEtiqueta);
			fprintf(pfASM, "\tfld %s\n",aux1);
            fprintf(pfASM, "\tfld %s\n",aux2);
            fprintf(pfASM, "\tfcomp\n");
            fprintf(pfASM, "\tfstsw ax\n");
            fprintf(pfASM, "\tfwait\n");
            fprintf(pfASM, "\tsahf\n\n");
		}

		if(strstr(operador, "ETIQ") != NULL)
		{
			flag = 1;
			fprintf(pfASM,"\n\n%s:\n",operador);
		}

		if(strcmp(operador, "JMP") == 0)
		{
			flag = 1;
			int indiceIzquierdo = desarmarIndice(tercetos[i].operandoIzq);
			char* etiqueta = obtenerTerceto(indiceIzquierdo, 1);
            fprintf(pfASM, "\tjmp %s\n",etiqueta);
		}

		if(strcmp(operador, "JE") == 0)
		{
			flag = 1;
			int indiceIzquierdo = desarmarIndice(tercetos[i].operandoIzq);
			char* etiqueta = obtenerTerceto(indiceIzquierdo, 1);
            fprintf(pfASM, "\tje %s\n",etiqueta);
		}

		if(strcmp(operador, "JNE") == 0)
		{
			flag = 1;
			int indiceIzquierdo = desarmarIndice(tercetos[i].operandoIzq);
			char* etiqueta = obtenerTerceto(indiceIzquierdo, 1);
            fprintf(pfASM, "\tjne %s\n", etiqueta);
		}

		if(strcmp(operador, "JB") == 0)
		{
			flag = 1;
			int indiceIzquierdo = desarmarIndice(tercetos[i].operandoIzq);
			char* etiqueta = obtenerTerceto(indiceIzquierdo, 1);
            fprintf(pfASM, "\tjb %s\n", etiqueta);
		}

		if(strcmp(operador, "JBE") == 0)
		{
			flag = 1;
			int indiceIzquierdo = desarmarIndice(tercetos[i].operandoIzq);
			char* etiqueta = obtenerTerceto(indiceIzquierdo, 1);
            fprintf(pfASM, "\tjbe %s\n", etiqueta);
		}

		if(strcmp(operador, "JA") == 0)
		{
			flag = 1;
			int indiceIzquierdo = desarmarIndice(tercetos[i].operandoIzq);
			char* etiqueta = obtenerTerceto(indiceIzquierdo, 1);
            fprintf(pfASM, "\tja %s\n", etiqueta);
		}

		if(strcmp(operador, "JAE") == 0)
		{
			flag = 1;
			int indiceIzquierdo = desarmarIndice(tercetos[i].operandoIzq);
			char* etiqueta = obtenerTerceto(indiceIzquierdo, 1);
            fprintf(pfASM, "\tjae %s\n", etiqueta);
		}

		if(strcmp(operador, "-") == 0)
		{
			flag = 1;
			fprintf(pfASM,"\t;RESTA\n");
			sacar_de_pila(&pVariables,&aux2);
			sacar_de_pila(&pVariables,&aux1);

            fprintf(pfASM, "\tfld %s\n",aux1);
            fprintf(pfASM, "\tfld %s\n",aux2);
            fprintf(pfASM, "\tfsub\n");

			char auxStr[50] = "";
			sprintf(auxStr, "@aux%d",i);
			fprintf(pfASM, "\tfstp %s\n\n",auxStr);
			insertarTokenEnTS("",auxStr);
			poner_en_pila(&pVariables,&auxStr);
		}

		if(strcmp(operador, "+") == 0)
		{
			flag = 1;
			fprintf(pfASM,"\t;SUMA\n");
			sacar_de_pila(&pVariables,&aux2);
			sacar_de_pila(&pVariables,&aux1);

			// fprintf(pfASM,"\t%s\n",auxEtiqueta);
			fprintf(pfASM, "\tfld %s\n",aux1);
            fprintf(pfASM, "\tfld %s\n",aux2);
            fprintf(pfASM, "\tfadd\n");

			char auxStr[50] = "";
			sprintf(auxStr, "@aux%d",i);
			fprintf(pfASM, "\tfstp %s\n\n",auxStr);
			insertarTokenEnTS("",auxStr);
			poner_en_pila(&pVariables,&auxStr);
		}

		if(strcmp(operador, "*") == 0)
		{
			flag = 1;
			fprintf(pfASM,"\t;MULTIPLICACION\n");
			sacar_de_pila(&pVariables,&aux2);
			sacar_de_pila(&pVariables,&aux1);

			fprintf(pfASM, "\tfld %s\n",aux1);
            fprintf(pfASM, "\tfld %s\n",aux2);
            fprintf(pfASM, "\tfmul\n");

			char auxStr[50] = "";
			sprintf(auxStr, "@aux%d",i);
			fprintf(pfASM, "\tfstp %s\n\n",auxStr);
			insertarTokenEnTS("",auxStr);
			poner_en_pila(&pVariables,&auxStr);
		}

		if(strcmp(operador, "/") == 0)
		{
			flag = 1;
			fprintf(pfASM,"\t;DIVISION\n");
			sacar_de_pila(&pVariables,&aux2);
			sacar_de_pila(&pVariables,&aux1);

			fprintf(pfASM, "\tfld %s\n",aux1);
            fprintf(pfASM, "\tfld %s\n",aux2);
            fprintf(pfASM, "\tfdiv\n");

			char auxStr[50] = "";
			sprintf(auxStr, "@aux%d",i);
			fprintf(pfASM, "\tfstp %s\n\n",auxStr);
			insertarTokenEnTS("",auxStr);
			poner_en_pila(&pVariables,&auxStr);
		}

		if(strcmp(operador, "MOD") == 0)
		{
			flag = 1;
			fprintf(pfASM,"\t;MOD\n");
			sacar_de_pila(&pVariables,&aux2);
			sacar_de_pila(&pVariables,&aux1);
			
			fprintf(pfASM, "\tfld %s\n",aux1);
			fprintf(pfASM, "\tfld %s\n",aux2);
			fprintf(pfASM, "\tfdiv\n");

			char auxStr[50] = "";
			sprintf(auxStr, "@aux%d",i);
			fprintf(pfASM, "\tfstp %s\n\n",auxStr);
			insertarTokenEnTS("",auxStr);
			poner_en_pila(&pVariables,&auxStr);
		}


		if(strcmp(operador, "DIV") == 0)
		{
			flag = 1;
			fprintf(pfASM,"\t;DIV\n");
			sacar_de_pila(&pVariables,&aux2);
			sacar_de_pila(&pVariables,&aux1);

			fprintf(pfASM, "\tfild %s\n",aux1);
			fprintf(pfASM, "\tfild %s\n",aux2);
			fprintf(pfASM, "\tfdiv\n");

			char auxStr[50] = "";
			sprintf(auxStr, "@aux%d",i);
			fprintf(pfASM, "\tfstp %s\n\n",auxStr);
			insertarTokenEnTS("",auxStr);
			poner_en_pila(&pVariables,&auxStr);
		}

		if(strcmp(operador, "READ") == 0)
		{
			flag = 1;
			fprintf(pfASM,"\t;READ\n");
			sacar_de_pila(&pVariables,&aux1);

			char * tipo = recuperarTipoTS(aux1);
    		char auxTipo[50] = "";
			strcpy(auxTipo, tipo);

			if(strcmp(tipo,"CONST_STR") == 0 || strcmp(tipo,"STRING") == 0)
			{
				fprintf(pfASM,"\tdisplayString %s\n",aux1);
                fprintf(pfASM, "\tnewLine 1\n\n");
			}
			if(strcmp(tipo,"CONST_INT") == 0 || strcmp(tipo,"INTEGER") == 0)
			{
   				fprintf(pfASM,"\tDisplayInteger %s 2\n",aux1);
                fprintf(pfASM, "\tnewLine 1\n\n");
			}
			if(strcmp(tipo,"CONST_REAL") == 0 || strcmp(tipo,"REAL") == 0)
			{
				fprintf(pfASM,"\tDisplayFloat %s 2\n",aux1);
                fprintf(pfASM, "\tnewLine 1\n\n");
			}
		}

		if(strcmp(operador, "PRINT") == 0)
		{
			flag = 1;
			fprintf(pfASM,"\t;PRINT\n");
			sacar_de_pila(&pVariables,&aux1);

			char * tipo = recuperarTipoTS(aux1);
    		char auxTipo[50] = "";
			strcpy(auxTipo, tipo);

			if(strcmp(tipo,"CONST_STR") == 0 || strcmp(tipo,"STRING") == 0)
			{
				fprintf(pfASM,"\tgetString %s\n\n",aux1);
			}
			else
			{
				fprintf(pfASM,"\tGetFloat %s\n\n",aux1);
			}
		}

		if(flag == 0)
		{
			char * nombre = recuperarNombreTS(operador);
			char auxNombre[50] = "";
			strcpy(auxNombre, nombre);
      poner_en_pila(&pVariables,&auxNombre);
		}
	}

	while(pila_vacia(&pVariables) != PILA_VACIA)
	{
		char varApilada[50] = "";
		sacar_de_pila(&pVariables, &varApilada);
	}
}

void generarFin(){
    fprintf(pfASM, "\nTERMINAR: ;Fin de ejecución.\n");
    fprintf(pfASM, "\tmov ax, 4C00h ;termina la ejecución.\n");
    fprintf(pfASM, "\tint 21h ;syscall\n");
    fprintf(pfASM, "\nEND START ;final del archivo.");
}
