
INCLUDE macros2.asm		 ;incluye macros
INCLUDE number.asm		 ;incluye el asm para impresion de numeros

.MODEL LARGE		 ; tipo del modelo de memoria usado.
.386
.387
.STACK 200h		 ; bytes en el stack
	
.DATA		 ; comienzo de la zona de datos.
	TRUE equ 1
	FALSE equ 0
	MAXTEXTSIZE equ 30
	_12 dd 12

	_4 dd 4

	_7 dd 7

	_FALSO db "FALSO", '$', 25 dup(?)

	_fin db "fin", '$', 27 dup(?)

	_verdadero db "verdadero", '$', 21 dup(?)

	a dd 0

	a1 dd 0.0

	b dd 0

	b1 dd 0.0

	c dd 0

	d dd 0

	p1 dd 0.0

	p2 dd 0.0

	p3 dd 0.0

	var1 db MAXTEXTSIZE dup(?), '$'

	var2 db MAXTEXTSIZE dup(?), '$'

	variable1 db MAXTEXTSIZE dup(?), '$'

	z dd 0.0





.CODE
;comienzo de la zona de codigo


start:
mov AX,@DATA
mov DS,AX
mov es,ax


	FLD _4
	FLD _7
	FADD
	FSTP a1
	FLD _12
	FLD a1
	FCOM
	FSTSW AX
	SAHF
	JNE  ET_FALSE_IF_15
mov dx,OFFSET  _verdadero
mov ah,9
int 21h
newLine 1
	JMP  ET_END_IF_18
ET_FALSE_IF_15:
mov dx,OFFSET  _FALSO
mov ah,9
int 21h
newLine 1
ET_END_IF_18:
GetFloat a1
mov dx,OFFSET  _fin
mov ah,9
int 21h
newLine 1

mov AX, 4c00h  ; termina la ejecucion
int 21h
END start;
;
