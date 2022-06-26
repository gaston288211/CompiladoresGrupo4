
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "Sintactico.y"

    
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

/// segunda entrega
t_lista listaPolaca;
tStack pilaNumCelda;
tStack pilaVariables;
tStack pilaTipoVariables;
tStack pilaCondiciones;
tStack pilaInList;
tList  symbolTable;
int cont=1;

char labelIfFin[30];
char labelIfTrue[30];
char labelIfFalse[20];
char labelBodyWhile[20];
char labelWhile[20];
char labelIF[20];
char auxBetween [100];
char auxInlist[100];


/* Line 189 of yacc.c  */
#line 154 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     OP_ASIG = 258,
     OP_RESTA = 259,
     OP_SUMA = 260,
     OP_DIV = 261,
     OP_MULT = 262,
     MENOS_UNARIO = 263,
     OP_MAY = 264,
     OP_MAYIGU = 265,
     OP_MEN = 266,
     OP_MENIGU = 267,
     OP_IGUAL = 268,
     OP_DIF = 269,
     WHILE = 270,
     IF = 271,
     INTEGER = 272,
     FLOAT = 273,
     STRING = 274,
     ELSE = 275,
     THEN = 276,
     DECVAR = 277,
     ENDDEC = 278,
     IN = 279,
     AND = 280,
     OR = 281,
     NOT = 282,
     LONG = 283,
     BETWEEN = 284,
     INLIST = 285,
     WRITE = 286,
     COMA = 287,
     ENDIF = 288,
     ENDWHILE = 289,
     DO = 290,
     READ = 291,
     PAR_A = 292,
     PAR_C = 293,
     COR_A = 294,
     COR_C = 295,
     PYC = 296,
     DP = 297,
     ID = 298,
     CTE_INTEGER = 299,
     CTE_FLOAT = 300,
     CTE_STRING = 301
   };
#endif
/* Tokens.  */
#define OP_ASIG 258
#define OP_RESTA 259
#define OP_SUMA 260
#define OP_DIV 261
#define OP_MULT 262
#define MENOS_UNARIO 263
#define OP_MAY 264
#define OP_MAYIGU 265
#define OP_MEN 266
#define OP_MENIGU 267
#define OP_IGUAL 268
#define OP_DIF 269
#define WHILE 270
#define IF 271
#define INTEGER 272
#define FLOAT 273
#define STRING 274
#define ELSE 275
#define THEN 276
#define DECVAR 277
#define ENDDEC 278
#define IN 279
#define AND 280
#define OR 281
#define NOT 282
#define LONG 283
#define BETWEEN 284
#define INLIST 285
#define WRITE 286
#define COMA 287
#define ENDIF 288
#define ENDWHILE 289
#define DO 290
#define READ 291
#define PAR_A 292
#define PAR_C 293
#define COR_A 294
#define COR_C 295
#define PYC 296
#define DP 297
#define ID 298
#define CTE_INTEGER 299
#define CTE_FLOAT 300
#define CTE_STRING 301




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 80 "Sintactico.y"

    char* strVal;



/* Line 214 of yacc.c  */
#line 288 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 300 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   132

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNRULES -- Number of states.  */
#define YYNSTATES  123

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     8,    11,    13,    15,    17,    19,
      21,    25,    29,    34,    36,    40,    42,    44,    46,    47,
      54,    58,    62,    63,    64,    65,    74,    77,    80,    84,
      88,    90,    94,    95,   101,   102,   103,   109,   111,   113,
     117,   121,   125,   129,   133,   137,   141,   145,   147,   150,
     154,   158,   160,   164,   166,   168,   170,   171,   172,   173,
     187,   189,   193,   194
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    51,    49,    -1,    50,    -1,    49,    50,
      -1,    64,    -1,    58,    -1,    55,    -1,    63,    -1,    62,
      -1,    22,    52,    23,    -1,    53,    42,    54,    -1,    52,
      53,    42,    54,    -1,    43,    -1,    53,    32,    43,    -1,
      17,    -1,    18,    -1,    19,    -1,    -1,    57,    49,    20,
      56,    49,    33,    -1,    57,    49,    33,    -1,    16,    65,
      21,    -1,    -1,    -1,    -1,    15,    59,    65,    35,    60,
      49,    61,    34,    -1,    36,    43,    -1,    31,    46,    -1,
      43,     3,    70,    -1,    43,     3,    46,    -1,    69,    -1,
      65,    25,    69,    -1,    -1,    37,    27,    66,    69,    38,
      -1,    -1,    -1,    65,    67,    26,    68,    69,    -1,    73,
      -1,    78,    -1,    70,     9,    70,    -1,    70,    11,    70,
      -1,    70,    12,    70,    -1,    70,    10,    70,    -1,    70,
      13,    70,    -1,    70,    14,    70,    -1,    70,     5,    71,
      -1,    70,     4,    71,    -1,    71,    -1,     4,    70,    -1,
      71,     7,    72,    -1,    71,     6,    72,    -1,    72,    -1,
      37,    70,    38,    -1,    45,    -1,    43,    -1,    44,    -1,
      -1,    -1,    -1,    29,    37,    43,    74,    32,    39,    70,
      41,    75,    70,    40,    76,    38,    -1,    70,    -1,    77,
      41,    70,    -1,    -1,    30,    37,    43,    79,    41,    39,
      77,    40,    38,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   119,   119,   122,   123,   126,   127,   128,   129,   130,
     133,   139,   142,   148,   152,   158,   162,   165,   171,   171,
     219,   240,   249,   258,   264,   249,   297,   304,   312,   317,
     326,   327,   331,   331,   335,   358,   335,   367,   368,   371,
     392,   413,   434,   455,   477,   500,   504,   508,   509,   512,
     516,   520,   525,   526,   531,   535,   542,   546,   553,   542,
     562,   581,   602,   602
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OP_ASIG", "OP_RESTA", "OP_SUMA",
  "OP_DIV", "OP_MULT", "MENOS_UNARIO", "OP_MAY", "OP_MAYIGU", "OP_MEN",
  "OP_MENIGU", "OP_IGUAL", "OP_DIF", "WHILE", "IF", "INTEGER", "FLOAT",
  "STRING", "ELSE", "THEN", "DECVAR", "ENDDEC", "IN", "AND", "OR", "NOT",
  "LONG", "BETWEEN", "INLIST", "WRITE", "COMA", "ENDIF", "ENDWHILE", "DO",
  "READ", "PAR_A", "PAR_C", "COR_A", "COR_C", "PYC", "DP", "ID",
  "CTE_INTEGER", "CTE_FLOAT", "CTE_STRING", "$accept", "programa",
  "bloque", "sentencia", "declaracion", "listaDeclaraciones", "listavar",
  "tipodato", "seleccion", "$@1", "condicion_if", "ciclo", "$@2", "$@3",
  "$@4", "entrada", "salida", "asignacion", "condicion", "$@5", "$@6",
  "$@7", "comparacion", "expresion", "termino", "factor", "between", "$@8",
  "$@9", "$@10", "lista_expr", "inlist", "$@11", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    50,    50,    50,
      51,    52,    52,    53,    53,    54,    54,    54,    56,    55,
      55,    57,    59,    60,    61,    58,    62,    63,    64,    64,
      65,    65,    66,    65,    67,    68,    65,    65,    65,    69,
      69,    69,    69,    69,    69,    70,    70,    70,    70,    71,
      71,    71,    72,    72,    72,    72,    74,    75,    76,    73,
      77,    77,    79,    78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     2,     1,     1,     1,     1,     1,
       3,     3,     4,     1,     3,     1,     1,     1,     0,     6,
       3,     3,     0,     0,     0,     8,     2,     2,     3,     3,
       1,     3,     0,     5,     0,     0,     5,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     2,     3,
       3,     1,     3,     1,     1,     1,     0,     0,     0,    13,
       1,     3,     0,     9
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    13,     0,     0,     1,    22,     0,
       0,     0,     0,     2,     3,     7,     0,     6,     9,     8,
       5,    10,     0,     0,     0,     0,     0,     0,     0,     0,
      54,    55,    53,    34,    30,     0,    47,    51,    37,    38,
      27,    26,     0,     4,     0,     0,    14,    15,    16,    17,
      11,    34,     0,    48,     0,     0,    32,     0,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    29,    28,    18,    20,    12,    23,    56,    62,     0,
      52,    31,    35,    46,    45,    39,    42,    40,    41,    43,
      44,    50,    49,     0,     0,     0,     0,     0,     0,     0,
      24,     0,     0,    33,    36,    19,     0,     0,     0,    25,
       0,    60,     0,    57,     0,     0,     0,    63,    61,     0,
      58,     0,    59
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    13,    14,     3,     5,     6,    50,    15,    93,
      16,    17,    25,    94,   106,    18,    19,    20,    33,    79,
      60,    98,    34,    35,    36,    37,    38,    95,   116,   121,
     112,    39,    96
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -55
static const yytype_int8 yypact[] =
{
     -13,   -37,    19,    68,   -55,   -16,   -28,   -55,   -55,    16,
      48,    -9,    73,    68,   -55,   -55,    68,   -55,   -55,   -55,
     -55,   -55,   -24,    54,    51,    16,    11,    63,    66,    20,
     -55,   -55,   -55,    -8,   -55,   111,     5,   -55,   -55,   -55,
     -55,   -55,     6,   -55,    76,    51,   -55,   -55,   -55,   -55,
     -55,    -2,    11,   -55,    65,    67,   -55,    24,   -55,    11,
      80,    30,    30,    11,    11,    11,    11,    11,    11,    30,
      30,   -55,    31,   -55,   -55,   -55,   -55,   -55,   -55,    11,
     -55,   -55,   -55,     5,     5,    31,    31,    31,    31,    31,
      31,   -55,   -55,    68,    68,    81,    77,    79,    11,    62,
      68,    75,    87,   -55,   -55,   -55,    93,    11,    11,   -55,
      17,    31,    45,   -55,    90,    11,    11,   -55,    31,    26,
     -55,    91,   -55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -55,   -55,   -14,   -12,   -55,   -55,   125,    86,   -55,   -55,
     -55,   -55,   -55,   -55,   -55,   -55,   -55,   -55,   107,   -55,
     -55,   -55,   -54,   -26,    10,    32,   -55,   -55,   -55,   -55,
     -55,   -55,   -55
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      53,    43,    44,    57,    23,    81,     4,    21,    23,     1,
      26,    69,    70,    58,    24,    26,    72,    59,    45,     7,
      26,    61,    62,    59,    26,    97,    57,     4,    61,    62,
      61,    62,    43,    76,    41,    61,    62,    85,    86,    87,
      88,    89,    90,    52,   104,    27,    28,    56,    52,    30,
      31,    32,    71,    29,    30,    31,    32,    52,   113,    30,
      31,    32,    80,    30,    31,    32,   120,    52,    47,    48,
      49,    83,    84,    30,    31,    32,    42,     8,     9,    99,
     100,   110,   111,     8,     9,   114,   115,    43,    43,   118,
     119,     8,     9,    10,    40,   105,    73,    46,    11,    10,
      54,    91,    92,    55,    11,    12,    82,    10,    77,    74,
      78,    12,    11,   101,   107,    61,    62,   103,   102,    12,
      63,    64,    65,    66,    67,    68,   108,   109,   117,   122,
      22,    75,    51
};

static const yytype_uint8 yycheck[] =
{
      26,    13,    16,    29,    32,    59,    43,    23,    32,    22,
       4,     6,     7,    21,    42,     4,    42,    25,    42,     0,
       4,     4,     5,    25,     4,    79,    52,    43,     4,     5,
       4,     5,    44,    35,    43,     4,     5,    63,    64,    65,
      66,    67,    68,    37,    98,    29,    30,    27,    37,    43,
      44,    45,    46,    37,    43,    44,    45,    37,    41,    43,
      44,    45,    38,    43,    44,    45,    40,    37,    17,    18,
      19,    61,    62,    43,    44,    45,     3,    15,    16,    93,
      94,   107,   108,    15,    16,    40,    41,    99,   100,   115,
     116,    15,    16,    31,    46,    33,    20,    43,    36,    31,
      37,    69,    70,    37,    36,    43,    26,    31,    43,    33,
      43,    43,    36,    32,    39,     4,     5,    38,    41,    43,
       9,    10,    11,    12,    13,    14,    39,    34,    38,    38,
       5,    45,    25
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    22,    48,    51,    43,    52,    53,     0,    15,    16,
      31,    36,    43,    49,    50,    55,    57,    58,    62,    63,
      64,    23,    53,    32,    42,    59,     4,    29,    30,    37,
      43,    44,    45,    65,    69,    70,    71,    72,    73,    78,
      46,    43,     3,    50,    49,    42,    43,    17,    18,    19,
      54,    65,    37,    70,    37,    37,    27,    70,    21,    25,
      67,     4,     5,     9,    10,    11,    12,    13,    14,     6,
       7,    46,    70,    20,    33,    54,    35,    43,    43,    66,
      38,    69,    26,    71,    71,    70,    70,    70,    70,    70,
      70,    72,    72,    56,    60,    74,    79,    69,    68,    49,
      49,    32,    41,    38,    69,    33,    61,    39,    39,    34,
      70,    70,    77,    41,    40,    41,    75,    38,    70,    70,
      40,    76,    38
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 119 "Sintactico.y"
    {printf("\nREGLA 1: <programa> --> <declaracion> <bloque>\n");}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 122 "Sintactico.y"
    {printf("\nREGLA 2: <bloque> --> <sentencia>\n");}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 123 "Sintactico.y"
    {printf("\nREGLA 3: <bloque> --> <bloque> <sentencia>\n");}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 126 "Sintactico.y"
    {printf("\nREGLA 4: <sentencia> --> <asignacion>\n");}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 127 "Sintactico.y"
    {printf("\nREGLA 5: <sentencia> --> <ciclo>\n");}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 128 "Sintactico.y"
    {printf("\nREGLA 6: <sentencia> --> <seleccion>\n");}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 129 "Sintactico.y"
    {printf("\nREGLA 7: <sentencia> --> <salida>\n");}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 130 "Sintactico.y"
    {printf("\nREGLA 8: <sentencia> --> <entrada>\n");}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 133 "Sintactico.y"
    {  
                                            
                                            printf("\nREGLA 9: <declaracion> --> DECVAR <listaDeclaraciones> ENDDEC\n");
                                        }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 139 "Sintactico.y"
    {
                                                    cargarTipoDato(&symbolTable, &pilaTipoVariables,&pilaVariables);
                                                    printf("\nREGLA 10: <listaDeclaraciones> --> <listavar> DP <tipodato> \n");}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 142 "Sintactico.y"
    {
                                                    cargarTipoDato(&symbolTable, &pilaTipoVariables,&pilaVariables);
                                                    printf("\nREGLA 11: <listaDeclaraciones> --> <listaDeclaraciones> <listavar> DP <tipodato> \n");
                                                }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 148 "Sintactico.y"
    {
                                        pushStack(&pilaVariables,(yyvsp[(1) - (1)].strVal));
                                        printf("\nREGLA 12: <listavar> --> ID \n");
                                    }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 152 "Sintactico.y"
    {
                                        pushStack(&pilaVariables,(yyvsp[(3) - (3)].strVal));
                                        printf("\nREGLA 13: <listavar> --> <listavar> COMA ID\n");
                                    }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 158 "Sintactico.y"
    {
                                        pushStack(&pilaTipoVariables,(yyvsp[(1) - (1)].strVal));
                                        printf("\nREGLA 14: <tipodato> --> INTEGER  \n");
                                    }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 162 "Sintactico.y"
    {
                                        pushStack(&pilaTipoVariables,(yyvsp[(1) - (1)].strVal));
                                        printf("\nREGLA 15: <tipodato> --> FLOAT \n");}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 165 "Sintactico.y"
    {
                                        pushStack(&pilaTipoVariables,(yyvsp[(1) - (1)].strVal));
                                        printf("\nREGLA 16: <tipodato> --> STRING \n");
                                    }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 171 "Sintactico.y"
    {
									int numCell;
									int cmp;
									char label[20];
									while(!emptyStack(&pilaNumCelda))
									{
										popStack2(&pilaNumCelda, label, &numCell);
										cmp=strcmpi(label, LABELFALSE);
										if (cmp==0) {
											char NumBiOutOfTheWhile[20];
											strcpy(labelIfFalse,"ET_FALSE_IF");
											itoa(cont, NumBiOutOfTheWhile, 10);
											strcat(labelIfFalse, NumBiOutOfTheWhile);
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
								}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 201 "Sintactico.y"
    {
						int numCell;
						int cmp;
						char label[20];
						while(!emptyStack(&pilaNumCelda))
						{
							popStack2(&pilaNumCelda, label, &numCell);
							cmp=strcmpi(label, labelIfFin);
							if (cmp==0) 
							{
								char NumBiOutOfTheWhile[20];
								itoa(cont, NumBiOutOfTheWhile, 10);
								strcat(labelIfFin, NumBiOutOfTheWhile);
								rellenarPolaca2(&listaPolaca, numCell, labelIfFin);
							}
						}
                        printf("\nREGLA 17: <seleccion> --> IF <condicion> THEN <bloque> ELSE <bloque> ENDIF\n");
					}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 219 "Sintactico.y"
    {
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
											strcpy(labelIfFin,"ET_END_IF_");
											itoa(cont, NumBiOutOfTheWhile, 10);
											strcat(labelIfFin, NumBiOutOfTheWhile);
											rellenarPolaca2(&listaPolaca, numCell, labelIfFin);
										}
									}		
									printf("\nREGLA 18: <seleccion> --> IF <condicion> THEN <bloque> ELSE <bloque> ENDIF\n");
								}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 240 "Sintactico.y"
    {
							char num[20];
							strcpy(labelIfTrue,"ET_TRUE_IF");
							itoa(cont, num, 10);
							strcat(labelIfTrue, num);
                            printf("\nREGLA 48: <seleccion> --> IF <condicion> THEN \n");
						}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 249 "Sintactico.y"
    {
				char numCell[10];
				char labelInitWhile[20];
				itoa(cont, numCell, 10);
				strcpy(labelInitWhile, "ET_WHILE_");
				strcat(labelInitWhile, numCell);
				strcpy(labelWhile, labelInitWhile);
				insertar_en_polaca(&listaPolaca, labelInitWhile, cont++);
			}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 258 "Sintactico.y"
    {
						char NumBiOutOfTheWhile[20];
						strcpy(labelBodyWhile,"ET_INIT_WHILE_");
						itoa(cont, NumBiOutOfTheWhile, 10);
						strcat(labelBodyWhile, NumBiOutOfTheWhile);
					}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 264 "Sintactico.y"
    {
				insertar_en_polaca(&listaPolaca,"BI",cont++);
				insertar_en_polaca(&listaPolaca,labelWhile,cont++);
			}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 268 "Sintactico.y"
    {
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
							strcpy(labelBi,"ET_END_WHILE");
							itoa(cont, NumBiOutOfTheWhile, 10);
							strcat(labelBi, NumBiOutOfTheWhile);
							rellenarPolaca2(&listaPolaca, numCell, labelBi);
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
				}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 297 "Sintactico.y"
    {
				insertar_en_polaca(&listaPolaca,"READ",cont++);
				insertar_en_polaca(&listaPolaca,(yyvsp[(2) - (2)].strVal),cont++);
				printf("\nREGLA 19: <entrada> --> READ ID\n");
			}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 304 "Sintactico.y"
    {
							insertar_en_polaca(&listaPolaca,(yyvsp[(2) - (2)].strVal),cont++);
                            insertar_en_polaca(&listaPolaca,"WRITE",cont++);
							insertarString(&symbolTable, (yyvsp[(2) - (2)].strVal));
							printf("\nREGLA 20: <salida> -->  WRITE CTE_STRING  \n");
						}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 312 "Sintactico.y"
    {
								insertar_en_polaca(&listaPolaca,(yyvsp[(1) - (3)].strVal),cont++);
								insertar_en_polaca(&listaPolaca,(yyvsp[(2) - (3)].strVal),cont++);
								printf("\nREGLA 21: <asignacion> --> ID OP_ASIG <expresion> \n");
							}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 317 "Sintactico.y"
    {
								insertar_en_polaca(&listaPolaca,(yyvsp[(3) - (3)].strVal),cont++);
								insertar_en_polaca(&listaPolaca,(yyvsp[(1) - (3)].strVal),cont++);                  
								insertar_en_polaca(&listaPolaca,(yyvsp[(2) - (3)].strVal),cont++);
								insertarString(&symbolTable, (yyvsp[(3) - (3)].strVal));
								printf("\nREGLA 22: <asignacion> --> ID OP_ASIG CTE_STRING \n");
							}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 326 "Sintactico.y"
    {printf("\nREGLA 23: <condicion> --> <comparacion> \n");}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 328 "Sintactico.y"
    {   //queda igual porque si una es neg salta
								printf("\nREGLA 24: <condicion> --> <comparacion> AND <comparacion>\n");
							}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 331 "Sintactico.y"
    {   //meto en la pila el not, y cuando leo las condiciones inserto el neg
								pushStack(&pilaCondiciones,(yyvsp[(2) - (2)].strVal));
							}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 335 "Sintactico.y"
    {//SI es neg deberia preguntar por la segunda
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
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 358 "Sintactico.y"
    {
								char label[20];
								strcpy(label,"OR_SIG_COND");
								insertar_en_polaca(&listaPolaca,label,cont++);
								//printf("despues de or");
                            }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 364 "Sintactico.y"
    {
                                printf("\nREGLA 25: <condicion> --> <comparacion> OR <comparacion>\n");
							}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 367 "Sintactico.y"
    {printf("\nREGLA 26: <condicion> --> <between>\n");}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 368 "Sintactico.y"
    {printf("\nREGLA 27: <condicion> --> <inlist>\n");}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 372 "Sintactico.y"
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
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 393 "Sintactico.y"
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
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 414 "Sintactico.y"
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
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 435 "Sintactico.y"
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
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 456 "Sintactico.y"
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
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 478 "Sintactico.y"
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
						}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 500 "Sintactico.y"
    {   
												insertar_en_polaca(&listaPolaca,(yyvsp[(2) - (3)].strVal),cont++);
												printf("\nREGLA 34: <expresion> --> <expresion><OP_SUMA><termino> \n");
											}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 504 "Sintactico.y"
    {
												 insertar_en_polaca(&listaPolaca,(yyvsp[(2) - (3)].strVal),cont++);
												 printf("\nREGLA 35: <expresion> --> <expresion><OP_RESTA><termino> \n");
											}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 508 "Sintactico.y"
    {printf("\nREGLA 36: <expresion> --> <termino> \n");}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 509 "Sintactico.y"
    {printf("\nREGLA 37: <expresion> --> OP_RESTA <expresion> \n");}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 512 "Sintactico.y"
    {
										insertar_en_polaca(&listaPolaca,(yyvsp[(2) - (3)].strVal),cont++);
										printf("\nREGLA 38: <termino> --> <termino> OP_MULT <factor> \n");
                                    }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 516 "Sintactico.y"
    {
										insertar_en_polaca(&listaPolaca,(yyvsp[(2) - (3)].strVal),cont++);
										printf("\nREGLA 39: <termino> --> <termino> OP_DIV <factor> \n");
                                    }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 520 "Sintactico.y"
    {
										printf("\nREGLA 40: <termino> --> <factor> \n");
                                    }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 525 "Sintactico.y"
    {printf("\nREGLA 41: <factor> --> PAR_A<expresion><PAR_C>\n");}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 526 "Sintactico.y"
    {
                                    insertar_en_polaca(&listaPolaca,(yyvsp[(1) - (1)].strVal),cont++);
                                    insertarNumero(&symbolTable,(yyvsp[(1) - (1)].strVal));
                                    printf("\nREGLA 42: <factor> --> CTE_FLOAT\n");
                                }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 531 "Sintactico.y"
    {   
									insertar_en_polaca(&listaPolaca,(yyvsp[(1) - (1)].strVal),cont++);
									printf("\nREGLA 43: <factor> --> ID\n");
                                }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 535 "Sintactico.y"
    {
									insertar_en_polaca(&listaPolaca,(yyvsp[(1) - (1)].strVal),cont++);
									insertarNumero(&symbolTable,(yyvsp[(1) - (1)].strVal));
									printf("\nREGLA 44: <factor> --> <CTE_INTEGER>\n");
								}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 542 "Sintactico.y"
    {	
									strcpy(auxBetween,(yyvsp[(3) - (3)].strVal));
									insertar_en_polaca(&listaPolaca,(yyvsp[(3) - (3)].strVal),cont++);
								}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 546 "Sintactico.y"
    {
									insertar_en_polaca(&listaPolaca,"CMP",cont++);
                                    insertar_en_polaca(&listaPolaca,"BLT",cont++);
									pushStack2(&pilaNumCelda,LABELFALSE,cont);//guardar en pila posicion actual
									insertar_en_polaca(&listaPolaca,LABELFALSE,cont++);//Avanzar
									insertar_en_polaca(&listaPolaca,auxBetween,cont++);
								}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 553 "Sintactico.y"
    {
									insertar_en_polaca(&listaPolaca,"CMP",cont++);
                                    insertar_en_polaca(&listaPolaca,"BGT",cont++);
									pushStack2(&pilaNumCelda,LABELFALSE,cont);//guardar en pila posicion actual
									insertar_en_polaca(&listaPolaca,LABELFALSE,cont++);//Avanzar
								}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 559 "Sintactico.y"
    {printf("\nREGLA 45: <between> --> <BETWEEN><PAR_A><ID><COMA><COR_A><expresion><PYC><expresion><COR_C><PAR_C>\n");}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 562 "Sintactico.y"
    {
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
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 581 "Sintactico.y"
    {	
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
								}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 602 "Sintactico.y"
    {	
											strcpy(auxInlist,(yyvsp[(3) - (3)].strVal));
										}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 605 "Sintactico.y"
    {
											char label[20];
											int numCell;
											if(!emptyStack(&pilaInList))
											{
												popStack2(&pilaInList,label,&numCell);
												rellenarPolaca2(&listaPolaca,numCell,LABELFALSE);
												pushStack2(&pilaNumCelda,LABELFALSE,numCell);//guardar en pila posicion actual
                                            }
											printf("\nREGLA 48: <inlist> --> <INLIST><PAR_A><ID><PYC><COR_A><lista_expr><COR_C><PAR_C>\n");
											}
    break;



/* Line 1455 of yacc.c  */
#line 2422 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 617 "Sintactico.y"



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
    char variableaux[100];
    char tipo[100];
    if (!emptyStack(pilaTipoVariables)){
        printf("test1");
        j=popStack(pilaTipoVariables,tipo);
    }
    printf("%s",tipo);
    while(!emptyStack(pilaVariables))
    {
        printf("test");
       j=popStack(pilaVariables, variableaux);
        insertarVariable(symbolTable, variableaux, tipo);  
    }
}

