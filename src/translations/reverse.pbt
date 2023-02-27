####
# translations for a fictional "reverse" language
####
# this file should be utf8
# entries on the left are the actual BASIC keywords
# entries on the right are the native versions of those keywords
# blank lines are allowed

[keywords]

# from ECMA-55 §5.2

END <= DNE          # the end statement

# from ECMA-55 §9

ABS <= SBA          # the absolute value function
ATN <= NTA          # the trigonomic arctangent function
COS <= SOC          # the trigonomic cosine function
EXP <= PXE          # the exponential / power function
INT <= TNI          # the integer / floor function
LOG <= GOL          # the natural log function
RND <= DNR          # generate random number
SGN <= NGS          # determine the sign
SIN <= NIS          # the trigonomic sine function
SQR <= RQS          # the square root function
TAN <= NAT          # the trigonomic tangent function
DBL <= LBD          # convert to double
RAT <= TAR          # convert to rational
STR <= RTS          # convert to string

# from ECMA-55 §10

DEF <= FED          # for user defined functions

# from ECMA-55 §11

LET <= TEL          # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= OG
GOSUB <= BUSOG
GOTO <= OTOG
TO <= OT            # part of for/to/step/next constructs
IF <= FI            # part of if/then constructs
THEN <= NEHT        # part of if/then constructs
SUB <= BUS          # beware, used as part of "go sub"
ON <= NO            # a sort of a switch statement
RETURN <= NRUTER    # used to exit a subroutine
STOP <= POTS        # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= ROF          # part of for/to/step/next constructs
STEP <= PETS        # part of for/to/step/next constructs
NEXT <= TXEN        # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= TNIRP      # to print things out

# from ECMA-55 §15

INPUT <= TUPNI      # the input statement

# from ECMA-55 §16

READ <= DAER        # part of read / restore
RESTORE <= EROTSER  # part of read / restore

# from ECMA-55 §17

DATA <= ATAD        # to embed data in the program

# from ECMA-55 §18

DIM <= MID          # dimension arrays
OPTION <= NOITPO    # see ECMA-55 §18.1
BASE <= ESAB        # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= MER          # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= EZIMODNAR

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP
# END
#

# LOOP <= POOL  # designed to evoke an error for testing
# END <= DNE    # designed to evoke an error for testing

[errors]

# error messages

err0|RORRE: mnuloc {2i}, enil {1i}, elif {0s}

