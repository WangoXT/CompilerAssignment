/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
 _____________________________________
|                                     |
|........... BABEL LANGUAGE ..........|
|__________       ___.          .__   |
|\______   \_____ \_ |__   ____ |  |  |
| |    |  _/\__  \ | __ \_/ __ \|  |  |
| |    |   \ / __ \| \_\ \  ___/|  |__|
| |______  /(____  /___  /\___  >____/|
|		 \/      \/    \/     \/      |
|             _   _   _               |
|            |;|_|;|_|;|              |
|            \\.    .  /              |
|             \\:  .  /               |
|              ||:   |                |
|              ||:.  |                |
|              ||:  .|                |
|              ||:   |                |
|              ||: , |                |
|              ||:   |                |
|              ||: . |                |
|              ||_   |                |
| .. ALGONQUIN COLLEGE - 2022F .......|
|_____________________________________|

*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR (-1)						/* General error message */
#define READER_TERMINATOR '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */

/* TO_DO: BIT 3: FUL = Full */
#define SET_FUL 0x08	/*0000.1000 OR Operator*/
#define RESET_FUL 0xF7	/*1111.0111 - AND Operator*/
#define CHECK_FUL SET_FUL 	

/* TO_DO: BIT 2: EMP: Empty */
#define SET_EMP 0x04	/*0000.0100 - OR Operator*/
#define RESET_EMP 0xFB	/*1111.1011 - AND Operator*/
#define CHECK_EMP SET_EMP	

/* TO_DO: BIT 1: REL = Relocation */
#define SET_REL 0x02	/*0000.0010 - OR Operator*/
#define RESET_REL 0xFD	/*1111.1101 - AND Operator*/
#define CHECK_REL SET_REL	

/* TO_DO: BIT 0: END = EndOfBuffer */
#define SET_END 0x01	/* 0000.0001 - OR Operator*/
#define RESET_END 0xFE	/* 1111.1110 - AND Operator*/
#define CHECK_END SET_END	

#define NCHAR 128			/* Chars from 0 to 127 */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	bab_intg mark;			/* the offset to the mark position (in chars) */
	bab_intg read;			/* the offset to the get a char position (in chars) */
	bab_intg wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	bab_char*	content;			/* pointer to the beginning of character array (character buffer) */
	bab_intg	size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	bab_intg	increment;			/* character array increment factor */
	bab_intg	mode;				/* operational mode indicator */
	bab_byte	flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position	position;			/* Offset / position field */
	bab_intg	histogram[NCHAR];	/* Statistics of chars */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate		(bab_intg, bab_intg, bab_intg);
ReaderPointer	readerAddChar		(ReaderPointer const, bab_char);
bab_boln		readerClear		    (ReaderPointer const);
bab_boln		readerFree		    (ReaderPointer const);
bab_boln		readerIsFull		(ReaderPointer const);
bab_boln		readerIsEmpty		(ReaderPointer const);
bab_boln		readerSetMark		(ReaderPointer const, bab_intg);
bab_intg		readerPrint		    (ReaderPointer const);
bab_intg		readerLoad			(ReaderPointer const, FILE* const);
bab_boln		readerRecover		(ReaderPointer const);
bab_boln		readerRetract		(ReaderPointer const);
bab_boln		readerRestore		(ReaderPointer const);
/* Getters */
bab_char		readerGetChar		(ReaderPointer const);
bab_char*		readerGetContent	(ReaderPointer const, bab_intg);
bab_intg		readerGetPosRead	(ReaderPointer const);
bab_intg		readerGetPosWrte	(ReaderPointer const);
bab_intg		readerGetPosMark	(ReaderPointer const);
bab_intg		readerGetSize		(ReaderPointer const);
bab_intg		readerGetInc		(ReaderPointer const);
bab_intg		readerGetMode		(ReaderPointer const);
bab_byte		readerGetFlags		(ReaderPointer const);
bab_intg		readerShowStat		(ReaderPointer const);

#endif
