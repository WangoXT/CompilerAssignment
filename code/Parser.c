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
* File name: mainBuffer.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

bab_void startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
bab_void matchToken(bab_intg tokenCode, bab_intg tokenAttribute) {
	bab_intg matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
bab_void syncErrorHandler(bab_intg syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
bab_void printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case VID_T:
		printf("VID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case MID_T:
		printf("MID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case CID_T:
		printf("CID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case DTID_T:
		printf("DTID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {MNID_T (main&)}.
 ***********************************************************
 */
bab_void program() {
	
	switch (lookahead.code) {
	case KW_T:
		if(KW_startDiagram){
			matchToken(KW_T, KW_startDiagram);
			propertiesSession();
			relationSession();
			matchToken(KW_T, KW_endDiagram);
			break;
		}
		else {
			printError();
		}
	case SEOF_T:
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}
/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> data { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (KW_data)}.
 ***********************************************************
 */
bab_void relationSession() {
	//matchToken(CID_T, NO_ATTR);
	optRelationStatements();

	if (lookahead.code == CID_T)
		relationSession();

	printf("%s%s\n", STR_LANGNAME, ": Relation Session parsed");
}

/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
bab_void optRelationStatements() {
	switch (lookahead.code) {
	case CID_T:
		relationStatements();
		break;
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Relation Statement parsed");
}

bab_void relationStatements() {
	relationStatement();
	relationStatementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

bab_void relationStatementsPrime() {
	switch (lookahead.code) {
	case CID_T:
		relationStatements();
		break;
	default:
		; //empty string
	}
}

bab_void relationStatement() {
	switch (lookahead.code)
	{
		case CID_T:
			matchToken(CID_T, NO_ATTR);
			switch (lookahead.attribute.codeType)
			{
			case KW_isA:
				matchToken(KW_T, KW_isA);
				matchToken(CID_T, NO_ATTR);
				break;
			case KW_hasA:
				matchToken(KW_T, KW_hasA);
				matchToken(CID_T, NO_ATTR);
				break;
			case KW_hasAn:
				matchToken(KW_T, KW_hasAn);
				matchToken(CID_T, NO_ATTR);
				break;
		default:
			printError();
		}
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
bab_void propertiesSession() {
	matchToken(KW_T, KW_class);
	matchToken(CID_T, NO_ATTR);
	matchToken(LBR_T, NO_ATTR);
	optionalStatements();
	matchToken(RBR_T, NO_ATTR);

	if (lookahead.attribute.codeType == KW_class)
		propertiesSession();

	printf("%s%s\n", STR_LANGNAME, ": Properties Session parsed");
}
/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
bab_void optionalStatements() {
	switch (lookahead.code) {
	case KW_T:
		statements();
		break;
	case STR_T:
		statements();
		break;
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
bab_void statements() {
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T,
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
bab_void statementsPrime() {
	switch (lookahead.code) {
		case KW_T:
				statements();
				break;
		case STR_T:
			statements();
			break;
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
bab_void statement() {
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case KW_private:
			matchToken(KW_T, KW_private);
			switch (lookahead.code)
			{
			case DTID_T:
				privateVariableStatement();
				break;
			case MID_T:
				privateMethodStatement();
				break;
			}
			break;
		case KW_public:
			matchToken(KW_T, KW_public);
			switch (lookahead.code)
			{
			case DTID_T:
				publicVariableStatement();
				break;
			case MID_T:
				publicMethodStatement();
				break;
			}
			break;
		case KW_protected:
			matchToken(KW_T, KW_protected);
			switch (lookahead.code)
			{
			case DTID_T:
				privateVariableStatement();
				break;
			case MID_T:
				privateMethodStatement();
				break;
			}
			break;
		default:
			printError();
		}
		break;
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */

bab_void privateVariableStatement() {
	matchToken(DTID_T, NO_ATTR);
	matchToken(VID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Private Variable statement parsed");
}
bab_void publicVariableStatement() {
	matchToken(DTID_T, NO_ATTR);
	matchToken(VID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Public Variable statement parsed");
}
bab_void protectedVariableStatement() {
	matchToken(DTID_T, NO_ATTR);
	matchToken(VID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Protected Variable statement parsed");
}

bab_void privateMethodStatement() {
	matchToken(MID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Private Method statement parsed");
}
bab_void publicMethodStatement() {
	matchToken(MID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Public Method statement parsed");
}
bab_void protectedMethodStatement() {
	matchToken(MID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Protected Method statement parsed");
}

