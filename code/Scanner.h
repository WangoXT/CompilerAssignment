/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Author: Paulo Sousa
* Course: CST 8152 ? Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Jul 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
//#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	VID_T,		/*  1: Method name identifier token (start: &) */
	STR_T,		/*  2: String literal token */
	LPR_T,		/*  3: Left parenthesis token */
	RPR_T,		/*  4: Right parenthesis token */
	LBR_T,		/*  5: Left brace token */
	RBR_T,		/*  6: Right brace token */
	KW_T,		/*  7: Keyword token */
	EOS_T,		/*  8: End of statement (semicolon) */
	RTE_T,		/*  9: Run-time error token */
	INL_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	MID_T,  	/* 12: Variable name identifier token (underscore) */
	DTID_T,		/* 13: Data type token (dollar sign) */
	CID_T		/* 14: Class name identifier ('at' symbol)*/
};

/* TO_DO: Operators token attributes */
//typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
//typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
//typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	bab_intg codeType;      /* integer attributes accessor */
	EofOperator seofType;				/* source-end-of-file attribute code */
	bab_intg keywordIndex;					/* keyword index in the keyword table */
	bab_intg contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	bab_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	bab_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	bab_byte flags;			/* Flags information */
	union {
		bab_char* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	bab_intg code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '_'		/* Variable Prefix */
#define CHRCOL3 '&'		/* Method Suffix */
#define CHRCOL4 '$'		/* Datatype indentifier Prefix */
#define CHRCOL5 '"'		/* Quotations for String Literals */
#define CHRCOL6 '#'		/* Comment prefix/suffix */
#define CHRCOL7 '\''	/* new line */
#define CHRCOL8 ' '     /* whitespace */
#define CHRCOL9 '@'     /* Class token */

/* These constants will be used on VID / MID function */
#define MIDSUFFIX '&'	/* Method identifier */
#define VIDPREFIX '_'	/* Variable identifier */
#define DTIDPREFIX '$'  /* Datatype identifier */
#define CIDPREFIX '@'  /* Class identifier */

/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESWR	101		/* Error state with retract */
#define ESNR	102		/* Error state with no retract */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 11
static bab_intg transitionTable[][TABLE_COLUMNS] = {
/*	     [A-z] ,[0-9],    _,    &,    $,    ",    #,SEOF, other whitespace
	       L(0), D(1), V(2), M(3), D(4), Q(5), C(6), E(7), O(8), W(9), C(10) */
	/* s0  */{ 1, ESNR,    2, ESNR,    2,    5,    6, ESWR, ESNR, ESNR, 10  }, //  s0: NOAS
	/* s1  */{ 1,    1, ESNR,    3, ESNR, ESNR, ESWR, ESWR, ESNR,    4, ESNR}, //  s1: NOAS
	/* s2  */{ 2, ESNR, ESNR, ESNR, ESNR, ESNR, ESNR, ESWR, ESNR,    3, ESNR}, //  s2: NOAS
	/* s3  */{FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS, FS  }, //  s3: ASNR (MVDTCID)
	/* s4  */{FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS, FS  }, //  s4: ASWR (KEY)
	/* s5  */{ 5,    5,    5,    5,    5,    7,    5, ESWR,    5,    5, 5   }, //  s5: NOAS (String literal transit)ion
	/* s6  */{ 6,    6,    6,    6,    6,    6,    7, ESWR,    6,    6, 6   }, //  s6: NOAS (Comment transition)
	/* s7  */{FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS, FS  }, //  s7: ASNR (SL/Comment)
	/* s8  */{FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS, FS  }, //  s8: ASNR (ES)
	/* s9  */{FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS, FS  }, //  s9: ASWR (ER)
	/* s10 */{10, ESNR, ESNR, ESNR, ESNR, ESNR, ESNR, ESNR, ESNR,    3, ESNR}  // s10: NOAS
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static bab_intg stateType[] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	NOFS, /* 02 */
	FSNR, /* 03 (MDTVID) - Variables */
	FSWR, /* 04 (Keyword) */
	NOFS, /* 05 */
	NOFS, /* 06 */
	FSNR, /* 07 (SL) */
	FSNR, /* 08 (Err1 - no retract) */
	FSWR, /* 09 (Err2 - retract) */
	NOFS  /* 10 */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
bab_intg startScanner(ReaderPointer psc_buf);
static bab_intg nextClass(bab_char c);			/* character class function */
static bab_intg nextState(bab_intg, bab_char);		/* state machine function */

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(bab_char* lexeme);

/* Declare accepting states functions */
Token funcSL	(bab_char lexeme[]);
Token funcID	(bab_char lexeme[]);
Token funcKEY	(bab_char lexeme[]);
Token funcErr	(bab_char lexeme[]);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	NULL,		/* -    [02] */
	funcID,		/* VID	[03] */
	funcKEY,	/* KEY  [04] */
	NULL,		/* -    [05] */
	NULL,		/* -    [06] */
	funcSL,		/* SL   [07] */
	funcErr,	/* ERR1 [08] */
	funcErr, 	/* ERR2 [09] */
	NULL		/* -    [10] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 12

/* TO_DO: Define the list of keywords */
static bab_char* keywordTable[KWT_SIZE] = {
	"isA",			// generalization
	"hasA",			// composition
	"hasAn",		// aggregation
	"class",		// class variable
	"private",		// declare the field to be private
	"protected",	// declare the field to be protected
	"public",		// declare the field to be public
	"integer",		// declare the field to be an integer
	"String",		// declare the field to be a string
	"double",		// declare the field to be a double
	"startDiagram",	// start a uml diagram
	"endDiagram"	// end of the uml diagram
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	bab_char indentationCharType;
	bab_intg indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

#endif
