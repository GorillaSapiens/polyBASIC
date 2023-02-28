####
# autotranslation for the "esperanto" language
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

END <= FINO                     # the end statement

# from ECMA-55 §9

ABS <= ABSOLUTAVALORO           # the absolute value function
ATN <= INVERSATANGENTO          # the trigonomic arctangent function
COS <= KOSINARO                 # the trigonomic cosine function
EXP <= EKSPONENTA               # the exponential / power function
INT <= ENTJERO                  # the integer / floor function
LOG <= LOGARITMO                # the natural log function
RND <= RULO                     # generate random number
SGN <= SIGNO                    # determine the sign
SIN <= SINUSO                   # the trigonomic sine function
SQR <= KVADRATARADIKO           # the square root function
TAN <= TANĜANTO                 # the trigonomic tangent function
DBL <= DUOBLA                   # convert to double
STR <= TEKSTO                   # convert to string
RAT <= RACIA                    # convert to rational

# from ECMA-55 §10

DEF <= DIFINI                   # for user defined functions

# from ECMA-55 §11

LET <= LASU                     # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= IRU                       # part of the GOTO and GOSUB
GOSUB <= VOKU                   # formed from GO and SUB if no direct translation exists
GOTO <= SALTU                   # formed from GO and TO if no direct translation exists
TO <= AL                        # part of for/to/step/next constructs
IF <= SE                        # part of if/then constructs
THEN <= TIAM                    # part of if/then constructs
SUB <= SUB                      # beware, used as part of "go sub"
ON <= ŜALTI                     # a sort of a switch statement
RETURN <= REVENU                # used to exit a subroutine
STOP <= FINITA                  # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= DE                       # part of for/to/step/next constructs
STEP <= PAŜO                    # part of for/to/step/next constructs
NEXT <= POSTE                   # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= PRESI                  # to print things out

# from ECMA-55 §15

INPUT <= ENIGO                  # the input statement

# from ECMA-55 §16

READ <= LEGU                    # part of read / restore
RESTORE <= RELEGI               # part of read / restore

# from ECMA-55 §17

DATA <= INFORMOJ                # to embed data in the program

# from ECMA-55 §18

DIM <= DIMENSIO                 # dimension arrays
OPTION <= OPCIO                 # see ECMA-55 §18.1
BASE <= BAZO                    # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= RIMARKO                  # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= HAZARDA

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]

# error messages

err0|ERARO: dosiero {0s}, linio {1i}, kolumno {2i}
