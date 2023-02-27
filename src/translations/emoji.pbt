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

# error messages

err0|⚠️ 😠 ━ 📁 {0s} ┕ {1i} ━ {2i} ❗

