
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 80 "Sintactico.y"

    char* strVal;



/* Line 1676 of yacc.c  */
#line 150 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


