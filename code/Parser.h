/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
 _________________________________
|                                 |
| ........ BOA LANGUAGE ......... |
|     __    __    __    __        |
|    /  \  /  \  /  \  /  \       |
| __/  __\/  __\/  __\/  __\__    |
| _/  /__/  /__/  /__/  /_____|   |
|  \_/ \   / \   / \   / \  \___  |
|       \_/   \_/   \_/   \___o_> |
|                                 |
| .. ALGONQUIN COLLEGE - 2022F .. |
|_________________________________|

*/

/*
************************************************************
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferReader* stringLiteralTable;
extern bab_intg line;
extern Token tokenizer();
extern bab_char* keywordTable[];
bab_intg syntaxErrorNumber = 0;

#define STR_LANGNAME	"Bab"
#define LANG_WRTE		"print&"
#define LANG_READ		"input&"
#define LANG_MAIN		"main&"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_isA,
	KW_hasA,
	KW_hasAn,
	KW_class,
	KW_private,
	KW_protected,
	KW_public,
	KW_integer,
	KW_String,
	KW_double,
	startDiagram,
	endDiagram
};

/* Function definitions */
bab_void startParser();
bab_void matchToken(bab_intg, bab_intg);
bab_void syncErrorHandler(bab_intg);
bab_void printError();

/* TO_DO: Place ALL non-terminal function declarations */
bab_void codeSession();
bab_void dataSession();
bab_void optVarListDeclarations();
bab_void optionalStatements();
bab_void outputStatement();
bab_void outputVariableList();
bab_void program();
bab_void statement();
bab_void statements();
bab_void statementsPrime();

#endif
