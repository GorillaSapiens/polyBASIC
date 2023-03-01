####
# autotranslation for the "english" language
####
#
# THIS FILE WAS AUTOMATICALLY GENERATED
#
# this file was autogenerated from google translate there are bound to
# be problems, mistranslations, and cultural problems
#
# it is our sincerest hope that these will be corrected by the community
# over time
#
# we kindly ask for your patience, and any contributions you may wish
# to make
#
# the dev team is not fluent in these languages, and no actual offense
# is intended
#
# obviously, many of these can be shortened.  to do so properly would
# take a fluent language speaker who is also familiar with the BASIC
# programming language
#
# this file should be utf8
#
# entries on the left are the actual BASIC keywords
#
# entries on the right are the native versions of those keywords
#
# blank lines are allowed

[keywords]

# from ECMA-55 §5.2

END <= END          # the end statement

# from ECMA-55 §9

ABS <= ABS          # the absolute value function
ATN <= ATN          # the trigonomic arctangent function
COS <= COS          # the trigonomic cosine function
EXP <= EXP          # the exponential / power function
INT <= INT          # the integer / floor function
LOG <= LOG          # the natural log function
RND <= RND          # generate random number
SGN <= SGN          # determine the sign
SIN <= SIN          # the trigonomic sine function
SQR <= SQR          # the square root function
TAN <= TAN          # the trigonomic tangent function
DBL <= DBL          # convert to double
STR <= STR          # convert to string
RAT <= RAT          # convert to rational

# from ECMA-55 §10

DEF <= DEF          # for user defined functions

# from ECMA-55 §11

LET <= LET          # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= GO            # part of the GOTO and GOSUB
GOSUB <= GOSUB      # formed from GO and SUB if no direct translation exists
GOTO <= GOTO        # formed from GO and TO if no direct translation exists
TO <= TO            # part of for/to/step/next constructs
IF <= IF            # part of if/then constructs
THEN <= THEN        # part of if/then constructs
SUB <= SUB          # beware, used as part of "go sub"
ON <= ON            # a sort of a switch statement
RETURN <= RETURN    # used to exit a subroutine
STOP <= STOP        # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= FOR          # part of for/to/step/next constructs
STEP <= STEP        # part of for/to/step/next constructs
NEXT <= NEXT        # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= PRINT      # to print things out

# from ECMA-55 §15

INPUT <= INPUT      # the input statement

# from ECMA-55 §16

READ <= READ        # part of read / restore
RESTORE <= RESTORE  # part of read / restore

# from ECMA-55 §17

DATA <= DATA        # to embed data in the program

# from ECMA-55 §18

DIM <= DIM          # dimension arrays
OPTION <= OPTION    # see ECMA-55 §18.1
BASE <= BASE        # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= REM          # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= RANDOMIZE

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]
❮%0❯ at %1:%2 ->%b	❮%0❯ at %1:%2 ->%b
❮%0❯ at %1:%2%n	❮%0❯ at %1:%2%n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	CANNOT ACCESS DIRECTORY ❮%0❯.%n
ERROR: def ❮%0❯ multiply defined %1:%2 and %3:%4%n	ERROR: def ❮%0❯ multiply defined %1:%2 and %3:%4%n
ERROR: DEFINITION CYCLE DISCOVERED%n	ERROR: DEFINITION CYCLE DISCOVERED%n
ERROR: for ❮%0❯ multiply defined %1:%2 and %3:%4%n	ERROR: for ❮%0❯ multiply defined %1:%2 and %3:%4%n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n	ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n
ERROR: line %0 column %1, ❮%2❯ has no value%n	ERROR: line %0 column %1, ❮%2❯ has no value%n
ERROR: NO PARSE TREE FOR LINE %0%n	ERROR: NO PARSE TREE FOR LINE %0%n
-l requires a language.%n	-l requires a language.%n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n
POLYBASICLANG' ENVIRONMENT VARIABLE NOT SET,	POLYBASICLANG' ENVIRONMENT VARIABLE NOT SET,
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
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MATH OP ❮%2❯%n	SOURCE %0:%1, UNRECOGNIZED MATH OP ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	SOURCE %0:%1, UNRECOGNIZED MID OP %2%n
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n
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
