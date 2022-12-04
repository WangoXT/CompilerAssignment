:: COMPILERS COURSE - SCRIPT ---------------------------------------------
:: SCRIPT A32 - CST8152 - Fall 2022

CLS
SET COMPILER=BabCompiler.exe

SET FILE1=Test

SET ASSIGNMENT=A32
SET EXTENSION=bab
SET OUTPUT=out
SET ERROR=err

SET PARAM=P

:: ---------------------------------------------------------------------
:: Begin of Tests (A32 - F22) ------------------------------------------
:: ---------------------------------------------------------------------

@echo off
ECHO " _________________________________ "
ECHO "|                                 |"
ECHO "| ....... 'BOA' LANGUAGE ........ |"
ECHO "|     __    __    __    __        |"
ECHO "|    /  \  /  \  /  \  /  \       |"
ECHO "| __/  __\/  __\/  __\/  __\__    |"
ECHO "| _/  /__/  /__/  /__/  /_____|   |"
ECHO "|  \_/ \   / \   / \   / \  \___  |"
ECHO "|       \_/   \_/   \_/   \___o_> |"
ECHO "|                                 |"
ECHO "| .. ALGONQUIN COLLEGE - 2022F .. |"
ECHO "|_________________________________|"
ECHO "                                   "
ECHO "[PARSER SCRIPT ...................]"
ECHO "                                   "

ren *.exe %COMPILER%

::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A32 - W22) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% %PARAM% %FILE1%.%EXTENSION%	> %FILE1%-%ASSIGNMENT%.%OUTPUT%	2> %FILE1%-%ASSIGNMENT%.%ERROR%

:: SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -
DIR *.OUT
DIR *.ERR

:: ---------------------------------------------------------------------
:: End of Tests (A32 - F22) --------------------------------------------
:: ---------------------------------------------------------------------
