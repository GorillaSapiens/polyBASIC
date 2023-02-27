####
# translations for the "english" language
####
# this file should be utf8
# entries on the left are the actual BASIC keywords
# entries on the right are the native versions of those keywords
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
RAT <= RAT          # convert to rational
STR <= STR          # convert to string

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

# error messages

err0|ERROR: file {0s}, line {1i}, column {2i}

