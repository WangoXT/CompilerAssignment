﻿/*
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

ReaderPointer readerCreate(bab_intg size, bab_intg increment, bab_intg mode) {
	ReaderPointer readerPointer;
	bab_intg counter;
	/* TO_DO: Defensive programming */
	if (size < 0 || increment < 0)   //|| mode != MODE_ADDIT && mode != MODE_MULTI && mode != MODE_FIXED
		return NULL;
	/* TO_DO: Adjust the values according to parameters */
	if (!size) {
		size = READER_DEFAULT_SIZE;
		increment = READER_DEFAULT_INCREMENT;
	}
	if (!increment)
		mode = MODE_FIXED;
	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;

	readerPointer->content = (bab_char*)malloc(size);
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;
	/* TO_DO: Initialize the histogram */
	for (counter = 0; counter < NCHAR; counter++)
		readerPointer->histogram[counter] = 0;

	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;
	/* TO_DO: Initialize flags */
	readerPointer->flags |= READER_DEFAULT_FLAG;

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

ReaderPointer readerAddChar(ReaderPointer const readerPointer, bab_char ch) {
	bab_char* tempReader;
	bab_intg newSize = 0;
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;
	else {
		/* TO_DO: Reset Realocation */
		readerPointer->flags &= RESET_REL;
		/* TO_DO: Test the inclusion of chars */
		if (readerPointer->position.wrte * (bab_intg)sizeof(bab_char) >= READER_MAX_SIZE) {
			return NULL;
			/* TO_DO: This buffer is NOT full  */
		}
		/* TO_DO: Reset Full flag */
		//readerPointer->flags &= READER_RESET_FUL;
		if (readerIsFull(readerPointer)) {

			switch (readerPointer->mode) {
			case MODE_FIXED:       // ENTERS THIS, MODE DOESN'T CHANGE TO ADDIT OR MULTI
				return NULL;
			case MODE_ADDIT:
				/* TO_DO: Adjust new size */
				newSize = readerPointer->size + readerPointer->increment;
				/* TO_DO: Defensive programming */
				if (newSize < 0 || newSize <= readerPointer->size)
					return NULL;

				break;
			case MODE_MULTI:
				/* TO_DO: Adjust new size */
				newSize = readerPointer->size * readerPointer->increment;
				/* TO_DO: Defensive programming */
				if (newSize < 0 || newSize <= readerPointer->size)
					return NULL;
				break;
			default:
				return NULL;
			}
			/* TO_DO: New reader allocation */
			tempReader = (char*)realloc(readerPointer->content, newSize);
			/* TO_DO: Defensive programming */
			if (!tempReader)
				return NULL;
			/* TO_DO: Check Relocation */
			readerPointer->flags &= RESET_FUL;
			readerPointer->flags |= SET_REL;
			readerPointer->content = tempReader;
			readerPointer->size = newSize;
		}
		/* TO_DO: Add the char */
		readerPointer->content[readerPointer->position.wrte++] = ch;
		if (readerPointer->position.wrte == readerPointer->size)
			readerPointer->flags |= SET_FUL;
		if (ch == READER_TERMINATOR)
			readerPointer->flags |= SET_END;
		/* TO_DO: Updates histogram */
		readerPointer->histogram[ch]++;
		return readerPointer;
	}
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
bab_boln readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BAB_FALSE;
	/* TO_DO: Adjust flags original */
	readerPointer->position.mark = 0;
	readerPointer->position.wrte = 0;
	readerPointer->position.read = 0;
	readerPointer->flags &= RESET_EMP;
	readerPointer->flags &= RESET_FUL;
	readerPointer->flags &= RESET_REL;
	readerPointer->flags &= RESET_END;

	return BAB_TRUE;
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
bab_boln readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BAB_FALSE;
	/* TO_DO: Free pointers */
	free(readerPointer->content);
	free(readerPointer);
	return BAB_TRUE;
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
bab_boln readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BAB_FALSE;
	/* TO_DO: Check flag if buffer is FUL */
	if ((readerPointer->flags & CHECK_FUL) == CHECK_FUL)
		return BAB_TRUE;
	else
		return BAB_FALSE;
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
bab_boln readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BAB_FALSE;

	/* TO_DO: Check flag if buffer is EMP */
	if ((readerPointer->flags & CHECK_EMP) != BAB_FALSE)
		return BAB_TRUE;
	// if readerPointer->position.wrte == 0, if write position is 0 there is nothing in reader, its empty
	return BAB_FALSE;
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
bab_boln readerSetMark(ReaderPointer const readerPointer, bab_intg mark) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BAB_FALSE;
	//	if (mark < 0 || mark > readerPointer->position.wrte)
		//	return DUB_FALSE;
		/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;
	return BAB_TRUE;
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
bab_intg readerPrint(ReaderPointer const readerPointer) {
	bab_intg cont = 0;
	bab_char c;
	if (!readerPointer) {
		return READER_ERROR;
	}

	c = readerGetChar(readerPointer);
	if (c < 0) {
		return READER_ERROR;
	}
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
bab_intg readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	bab_intg size = 0;
	bab_char c;
	/* TO_DO: Defensive programming */
	if (!readerPointer || !fileDescriptor)
		return READER_ERROR;
	c = (bab_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/* TO_DO: Defensive programming */
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
bab_boln readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BAB_FALSE;
	/* TO_DO: Recover positions */
	readerPointer->position.mark = 0;
	readerPointer->position.read = 0;
	return BAB_TRUE;
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
bab_boln readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BAB_FALSE;
	/* TO_DO: Retract (return 1 pos read) */
	if (readerPointer->position.read > 0)
		readerPointer->position.read--;

	return BAB_TRUE;
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
bab_boln readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return BAB_FALSE;
	/* TO_DO: Restore positions (read/mark) */
	readerPointer->position.read = readerPointer->position.mark;
	return BAB_TRUE;
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
bab_char readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Check condition to read/wrte */
	if (readerPointer->position.read == readerPointer->position.wrte) {
		//readerPointer->content[readerPointer->position.read] = READER_TERMINATOR;
		/* TO_DO: Set EOB flag */
		readerPointer->flags |= SET_END;
		return READER_TERMINATOR;
	}
	/* TO_DO: Reset EOB flag */
	else {
		readerPointer->flags &= RESET_END;
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
bab_char* readerGetContent(ReaderPointer const readerPointer, bab_intg pos) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;
	//if (pos < 0 || pos > readerPointer->position.wrte)
	//	return NULL;
	/* TO_DO: Return content (string) */
	return readerPointer->content + pos;

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
bab_intg readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return read */
	return readerPointer->position.read;

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
bab_intg readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return wrte */
	return readerPointer->position.wrte;

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
bab_intg readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return mark */
	return readerPointer->position.mark;
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
bab_intg readerGetSize(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return size */
	return readerPointer->size;
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
bab_intg readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return increment */
	return readerPointer->increment;
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
bab_intg readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	//|| readerPointer->mode != MODE_ADDIT && readerPointer->mode != MODE_MULTI && readerPointer->mode != MODE_FIXED
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return mode */
	return readerPointer->mode;
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
bab_byte readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return READER_ERROR;
	/* TO_DO: Return flags */
	return readerPointer->flags;
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
bab_intg readerShowStat(ReaderPointer const readerPointer) {
	bab_intg counter;
	bab_intg distinctChars = 0;
	/* TO_DO: Defensive programming */
	if (!readerPointer || !readerPointer->histogram)
		return 0;
	/* TO_DO: Updates the histogram */
	for (counter = 0; counter < NCHAR; counter++) {
		if (readerPointer->histogram[counter] != 0)
			distinctChars++;
	}
	return distinctChars;
}

