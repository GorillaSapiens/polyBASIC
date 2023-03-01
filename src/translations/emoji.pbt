####
# ECMA-55 BASIC translations for the 👻👽👾🤖😺🦓 language
#
# ECMA-55 can be found at the "Download this standard" button
# at the bottom of
# https://www.ecma-international.org/publications-and-standards/standards/ecma-55/
#
####
# this file should be utf8
# entries on the left are the actual BASIC keywords
# entries on the right are the native versions of those keywords
# blank lines are allowed

# from ECMA-55 §3.8

# The keywords in Minimal BASIC are: BASE, DATA, DEF, DIM, END,
# FOR, GO, GOSUB, GOTO, IF, INPUT, LET, NEXT, ON, OPTION, PRINT,
# RANDOMIZE, READ, REM, RESTORE, RETURN, STEP, STOP, SUB, THEN
# and TO.

[keywords]

# from ECMA-55 §5

END <= 👻👻           # the end of program instruction

# from ECMA-55 §9

ABS <= 👻👽         # the absolute value function
ATN <= 👻👾         # the trigonomic arctangent function
COS <= 👻🤖         # the trigonomic cosine function
EXP <= 👻😺         # the exponential / power function
INT <= 👻🦓         # the integer / floor function
LOG <= 👽👻         # the natural log function
RND <= 👽👽         # generate random number
SGN <= 👽👾         # determine the sign
SIN <= 👽🤖         # the trigonomic sine function
SQR <= 👽😺         # the square root function
TAN <= 👽🦓         # the trigonomic tangent function
DBL <= 🦓🦓         # to convert a type to double
RAT <= 🐀           # convert to type rational
STR <= 🧵           # convert to type string

# from ECMA-55 §10

DEF <= 👾👻         # for user defined functions

# from ECMA-55 §11

LET <= 👾👽         # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GOTO <= 👾👾👾🤖
GOSUB <= 👾👾🤖👻

GO <= 👾👾          # possibly used in both "go to" and "go sub"
TO <= 👾🤖          # part of for/to/step/next constructs
IF <= 👾😺          # part of if/then constructs
THEN <= 👾🦓        # part of if/then constructs
SUB <= 🤖👻         # beware, used as part of "go sub"
ON <= 🤖👽          # a sort of a switch statement
RETURN <= 🤖👾      # used to exit a subroutine
STOP <= 🤖🤖        # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= 🤖😺         # part of for/to/step/next constructs
STEP <= 🤖🦓        # part of for/to/step/next constructs
NEXT <= 😺👻        # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= 😺👽       # to print things out

# from ECMA-55 §15

INPUT <= 😺👾       # the input statement

# from ECMA-55 §16

READ <= 😺🤖        # part of read / restore
RESTORE <= 😺😺 # part of read / restore

# from ECMA-55 §17

DATA <= 😺🦓        # to embed data in the program

# from ECMA-55 §18

DIM <= 🦓👻         # dimension arrays
OPTION <= 🦓👽      # see ECMA-55 §18.1
BASE <= 🦓👾        # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= 🦓🤖         # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= 🦓😺

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP
#

[errors]
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.	AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.
ARRAY ALREADY DEFINED	ARRAY ALREADY DEFINED
ARRAY INDEX OUTSIDE OF BOUNDS	ARRAY INDEX OUTSIDE OF BOUNDS
CANNOT ACCESS DIRECTORY	CANNOT ACCESS DIRECTORY
DATA INPUT UNDERFLOW	DATA INPUT UNDERFLOW
DATA READ UNDERFLOW	DATA READ UNDERFLOW
DEFINITION CYCLE DISCOVERED	DEFINITION CYCLE DISCOVERED
ERROR	ERROR
FOR VARIABLE MULTIPLY DEFINED	FOR VARIABLE MULTIPLY DEFINED
FUNCTION DEFINITION MULTIPLY DEFINED	FUNCTION DEFINITION MULTIPLY DEFINED
FUNCTION DEFINITION PARAMETER MISMATCH	FUNCTION DEFINITION PARAMETER MISMATCH
GOSUB STACK OVERFLOW	GOSUB STACK OVERFLOW
GOSUB STACK UNDERFLOW	GOSUB STACK UNDERFLOW
INDEX OUT OF RANGE	INDEX OUT OF RANGE
LABEL ALREADY DEFINED	LABEL ALREADY DEFINED
LEFT / RIGHT OPERATION MISMATCH	LEFT / RIGHT OPERATION MISMATCH
NEGATIVE INDEX	NEGATIVE INDEX
NEXT ON FOR LOOP WITH STRING VARIABLE	NEXT ON FOR LOOP WITH STRING VARIABLE
OPERAND MISMATCH	OPERAND MISMATCH
OPTION REQUIRES A LANGUAGE	OPTION REQUIRES A LANGUAGE
PLEASE CHECK LANGUAGE SETTINGS OR ENVIRONMENT VARIABLE	PLEASE CHECK LANGUAGE SETTINGS OR ENVIRONMENT VARIABLE
STRING MATH LOGIC ERROR	STRING MATH LOGIC ERROR
UNABLE TO OPEN FILE	UNABLE TO OPEN FILE
UNABLE TO OPEN TO OPEN FILE FOR READING	UNABLE TO OPEN TO OPEN FILE FOR READING
UNDEFINED LABEL	UNDEFINED LABEL
UNHANDLED OPERATION	UNHANDLED OPERATION
UNHANDLED OPERATION CODE	UNHANDLED OPERATION CODE
UNKNOWN IF LABEL	UNKNOWN IF LABEL
UNRECOGNIZED DOUBLE MATH OPERATION	UNRECOGNIZED DOUBLE MATH OPERATION
UNRECOGNIZED FUNCTION FUNCTION DEFINITION	UNRECOGNIZED FUNCTION FUNCTION DEFINITION
UNRECOGNIZED GOSUB LABEL	UNRECOGNIZED GOSUB LABEL
UNRECOGNIZED GOTO LABEL	UNRECOGNIZED GOTO LABEL
UNRECOGNIZED INPUT	UNRECOGNIZED INPUT
UNRECOGNIZED INTEGER MATH OPERATION	UNRECOGNIZED INTEGER MATH OPERATION
UNRECOGNIZED MATH TYPE	UNRECOGNIZED MATH TYPE
UNRECOGNIZED NEXT VARIABLE	UNRECOGNIZED NEXT VARIABLE
UNRECOGNIZED OP IN PRINT	UNRECOGNIZED OP IN PRINT
UNRECOGNIZED RATIONAL MATH OPERATION	UNRECOGNIZED RATIONAL MATH OPERATION
UNRECOGNIZED VARIABLE TYPE	UNRECOGNIZED VARIABLE TYPE
UNSET ENVIRONMENT VARIABLE	UNSET ENVIRONMENT VARIABLE
VARIABLE / ARRAY DEFINITION MISMATCH	VARIABLE / ARRAY DEFINITION MISMATCH
VARIABLE DEFINED AS ARRAY	VARIABLE DEFINED AS ARRAY
VARIABLE DEFINED AS NONARRAY	VARIABLE DEFINED AS NONARRAY
VARIABLE HAS NO VALUE	VARIABLE HAS NO VALUE
VARIABLE IS NOT AN ARRAY	VARIABLE IS NOT AN ARRAY
