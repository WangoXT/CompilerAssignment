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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

ReaderPointer readerCreate(boa_intg size, boa_intg increment, boa_intg mode) {
	ReaderPointer readerPointer;
	/* TO_DO: Defensive programming */
	if ((size < 0) || (increment < 0))
		return NULL;
	/* TO_DO: Adjust the values according to parameters */

	size = READER_DEFAULT_SIZE;
	increment = READER_DEFAULT_INCREMENT;
	mode = MODE_FIXED;
	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));

	/* TO_DO: Defensive programming */
	if (readerPointer) {
		readerPointer->content = (boa_char*)malloc(size);
	readerPointer->size = size;
	}

	/* TO_DO: Defensive programming */
	
	/* TO_DO: Initialize the histogram */
	readerPointer->histogram;

	readerPointer->increment = increment;
	readerPointer->mode = mode;


	/* TO_DO: Initialize flags */
	readerPointer->flags;

	/* TO_DO: The created flag must be signalized as EMP */
	readerPointer->flags |= SET_EMP;
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, boa_char ch) {
	boa_char* tempReader = NULL;
	boa_intg newSize = 0;
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;
	if (ch < 31 || ch > 127)
		return NULL;

	if (readerPointer->histogram[ch]++)

		/* TO_DO: Reset Realocation */
		readerPointer->flags = readerPointer->flags & RESET_REL;
	/* TO_DO: Test the inclusion of chars */
	if(ch<0){
		return NULL;
	}
	if (readerPointer->position.wrte * (boa_intg)sizeof(boa_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */

	} else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags &= RESET_FUL;
		switch (readerPointer->mode) {

		case MODE_FIXED:
			return NULL;

		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size + readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < 0)
				return NULL;
			tempReader = realloc(readerPointer->content, newSize);
			if (!tempReader)
				return NULL;
			if (tempReader != readerPointer->content)
				readerPointer->flags |= SET_REL;
			readerPointer->content = tempReader;
			readerPointer->size = newSize;
			break;

		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size * readerPointer->size;
			/* TO_DO: Defensive programming */
			if (newSize < 0)
				return READER_ERROR;
			tempReader = realloc(readerPointer->content, newSize);
			if (!tempReader)
				return NULL;
			if (tempReader != readerPointer->content)
				readerPointer->flags |= SET_REL;
			readerPointer->content = tempReader;
			readerPointer->size = newSize;
			break;
		default:
			return NULL;
		}
		/* TO_DO: New reader allocation */
		tempReader = realloc(readerPointer->content, newSize);
			/* TO_DO: Defensive programming */
			if (!tempReader)
				return NULL;
			readerPointer->size = tempReader;
			readerPointer->content = tempReader;
		/* TO_DO: Check Relocation */
		if (readerPointer->content != tempReader)
			readerPointer->flags |= CHECK_REL; 
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/* TO_DO: Updates histogram */
	readerPointer->histogram[ch]++;
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_boln readerClear(ReaderPointer const readerPointer) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BOA_FALSE;
	/* TO_DO: Adjust flags original */
	readerPointer->position.read = readerPointer->position.wrte = readerPointer->position.mark = 0;

	readerPointer->flags = readerPointer->flags & RESET_EMP;
	readerPointer->flags = readerPointer->flags & RESET_END;
	readerPointer->flags = readerPointer->flags & RESET_FUL;
	readerPointer->flags = readerPointer->flags & RESET_REL;
	return BOA_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_boln readerFree(ReaderPointer const readerPointer) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BOA_FALSE;
	/* TO_DO: Free pointers */
	free(readerPointer->content);
	free(readerPointer);
	return BOA_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_boln readerIsFull(ReaderPointer const readerPointer) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BOA_FALSE;

	/* TO_DO: Check flag if buffer is FUL */
	if ((readerPointer->flags & CHECK_FUL) == 1)
		return BOA_TRUE;

	return BOA_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_boln readerIsEmpty(ReaderPointer const readerPointer) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BOA_FALSE;
	/* TO_DO: Check flag if buffer is EMP */
	if ((readerPointer->flags & CHECK_EMP) == 1)
		return BOA_TRUE;
	
	return BOA_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_boln readerSetMark(ReaderPointer const readerPointer, boa_intg mark) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer || mark < 0 || mark > readerPointer -> position.wrte)
		return BOA_FALSE;
	/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;
	return BOA_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_intg readerPrint(ReaderPointer const readerPointer) {
	/*DONE*/
	boa_intg cont = 0;
	boa_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	if (!readerPointer)
		return READER_ERROR;
	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	if (!c)
		return READER_ERROR;

	while (cont < readerPointer->position.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_intg readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	/*DONE*/
	boa_intg size = 0;
	boa_char c;
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	c = (boa_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/* TO_DO: Defensive programming */
	if (readerPointer->size < 0)
		return READER_ERROR;

	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_boln readerRecover(ReaderPointer const readerPointer) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BOA_FALSE;
	/* TO_DO: Recover positions */
	readerPointer->position.read = readerPointer->position.mark = 0;
	return BOA_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_boln readerRetract(ReaderPointer const readerPointer) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BOA_FALSE;
	/* TO_DO: Retract (return 1 pos read) */
	readerPointer->position.read--;
	return BOA_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_boln readerRestore(ReaderPointer const readerPointer) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BOA_FALSE;
	/* TO_DO: Restore positions (read/mark) */
	readerPointer->position.read = readerPointer->position.mark;
	return BOA_TRUE;
}

/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_char readerGetChar(ReaderPointer const readerPointer) {
	/*DONE??*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;
	/* TO_DO: Check condition to read/wrte */
	if (readerPointer->position.read == readerPointer->position.wrte) {
		/* TO_DO: Set EOB flag */
		readerPointer->flags | SET_END;
		return READER_TERMINATOR;
	}
	else {
		/* TO_DO: Reset EOB flag */
		readerPointer->flags & RESET_END;
		return readerPointer->content[readerPointer->position.read++];
	}
}
	
/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_char* readerGetContent(ReaderPointer const readerPointer, boa_intg pos) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer || !readerPointer->content)
		return NULL;
	/* TO_DO: Return content (string) */
	return readerPointer -> content + pos;
}

/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_intg readerGetPosRead(ReaderPointer const readerPointer) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return read */
	return readerPointer -> position.read;
}

/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_intg readerGetPosWrte(ReaderPointer const readerPointer) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return wrte */
	return readerPointer -> position.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_intg readerGetPosMark(ReaderPointer const readerPointer) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return mark */
	return readerPointer -> position.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_intg readerGetSize(ReaderPointer const readerPointer) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return size */
	return readerPointer -> size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_intg readerGetInc(ReaderPointer const readerPointer) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return increment */
	return readerPointer -> increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_intg readerGetMode(ReaderPointer const readerPointer) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return mode */
	return readerPointer -> mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_byte readerGetFlags(ReaderPointer const readerPointer) {
	/*DONE*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return flags */
	return readerPointer -> flags;
}


/*
***********************************************************
* Function name: readerShowStat
* Purpose: Returns the number of chars used.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
boa_intg readerShowStat(ReaderPointer const readerPointer) {
	/*DONE???*/
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Updates the histogram */
	return readerPointer -> histogram[NCHAR];
}
