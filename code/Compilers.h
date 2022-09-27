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
* File name: compilers.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12, A22, A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */
 
/* Logical constants - adapt for your language */
#define BAB_TRUE  1
#define BAB_FALSE 0

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
		but they can be necessary for conversions.
------------------------------------------------------------
*/
/* TO_DO: Define your typedefs */
typedef char			bab_char;
typedef int				bab_intg;
typedef float			bab_real;
typedef void			bab_void;

typedef unsigned char	bab_boln;
typedef unsigned char	bab_byte;

typedef long			bab_long;
typedef double			bab_doub;

/*
------------------------------------------------------------
Programs:
1: Reader - invokes MainReader code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_READER	= 'R',
	PGM_SCANNER = 'S',
	PGM_PARSER	= 'P'
};

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/
bab_intg mainReader  (bab_intg argc, bab_char** argv);
/*
boa_intg mainScanner (boa_intg argc, boa_char** argv);
boa_intg mainParser  (boa_intg argc, boa_char** argv);
*/
bab_void printLogo();

#endif
