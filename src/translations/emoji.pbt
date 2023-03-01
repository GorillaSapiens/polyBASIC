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
❮%0❯ at %1:%2 ->%b	❮%0❯ at %1:%2 ->%b
❮%0❯ at %1:%2%n	❮%0❯ at %1:%2%n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	CANNOT ACCESS DIRECTORY ❮%0❯.%n
ENVIRONMENT VARIABLE 'POLYBASICLANG' NOT SET,	ENVIRONMENT VARIABLE 'POLYBASICLANG' NOT SET,
ERROR: def ❮%0❯ multiply defined %1:%2 and %3:%4%n	ERROR: def ❮%0❯ multiply defined %1:%2 and %3:%4%n
ERROR: DEFINITION CYCLE DISCOVERED%n	ERROR: DEFINITION CYCLE DISCOVERED%n
ERROR: for ❮%0❯ multiply defined %1:%2 and %3:%4%n	ERROR: for ❮%0❯ multiply defined %1:%2 and %3:%4%n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n	ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n
ERROR: line %0 column %1, ❮%2❯ has no value%n	ERROR: line %0 column %1, ❮%2❯ has no value%n
ERROR: NO PARSE TREE FOR LINE %0%n	ERROR: NO PARSE TREE FOR LINE %0%n
-l requires a language.%n	-l requires a language.%n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	SOURCE %0:%1, DATA INPUT UNDERFLOW%n
SOURCE %0:%1, DATA READ UNDERFLOW%n	SOURCE %0:%1, DATA READ UNDERFLOW%n
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	SOURCE %0:%1, GOSUB STACK OVERFLOW%n
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	SOURCE %0:%1, GOSUB STACK UNDERFLOW%n
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	SOURCE %0:%1, INDEX %2 OUT OF RANGE%n
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n
SOURCE %0:%1, NEGATIVE INDEX %d%n	SOURCE %0:%1, NEGATIVE INDEX %d%n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	SOURCE %0:%1, STRING MATH LOGIC ERROR%n
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n
SOURCE %0:%1, UNHANDLED OP %2%n	SOURCE %0:%1, UNHANDLED OP %2%n
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED DOUBLE MATH OP ❮%2❯%n	SOURCE %0:%1, UNRECOGNIZED DOUBLE MATH OP ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED INTEGER MATH OP ❮%2❯%n	SOURCE %0:%1, UNRECOGNIZED INTEGER MATH OP ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	SOURCE %0:%1, UNRECOGNIZED MID OP %2%n
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED RATIONAL MATH OP ❮%2❯%n	SOURCE %0:%1, UNRECOGNIZED RATIONAL MATH OP ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n
UNABLE TO OPEN %0 FOR READING.%n	UNABLE TO OPEN %0 FOR READING.%n
UNABLE TO OPEN FILE ❮%0❯%n	UNABLE TO OPEN FILE ❮%0❯%n
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n
UNRECOGNIZED INPUT ❮%0❯%n	UNRECOGNIZED INPUT ❮%0❯%n
