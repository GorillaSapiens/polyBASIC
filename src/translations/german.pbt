####
# autotranslation for the "german" language
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

END <= ENDE                     # the end statement

# from ECMA-55 §9

ABS <= ABSOLUTERWERT            # the absolute value function
ATN <= INVERSETANGENTE          # the trigonomic arctangent function
COS <= KOSINUS                  # the trigonomic cosine function
EXP <= EXPONENTIELL             # the exponential / power function
INT <= GANZEZAHL                # the integer / floor function
LOG <= LOGARITHMUS              # the natural log function
RND <= ROLLEN                   # generate random number
SGN <= ZEICHEN                  # determine the sign
SIN <= SINUS                    # the trigonomic sine function
SQR <= QUADRATWURZEL            # the square root function
TAN <= TANGENTE                 # the trigonomic tangent function
DBL <= DOPPELT                  # convert to double

# from ECMA-55 §10

DEF <= DEFINIEREN               # for user defined functions

# from ECMA-55 §11

LET <= LASSEN                   # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= GEHEN                     # part of the GOTO and GOSUB
GOSUB <= FORDERUNG              # formed from GO and SUB if no direct translation exists
GOTO <= SPRINGEN                # formed from GO and TO if no direct translation exists
TO <= ZU                        # part of for/to/step/next constructs
IF <= WENN                      # part of if/then constructs
THEN <= DANN                    # part of if/then constructs
SUB <= SUB                      # beware, used as part of "go sub"
ON <= SCHALTEN                  # a sort of a switch statement
RETURN <= ZURÜCKKEHREN          # used to exit a subroutine
STOP <= FERTIG                  # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= AUS                      # part of for/to/step/next constructs
STEP <= SCHRITT                 # part of for/to/step/next constructs
NEXT <= NÄCHSTE                 # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= DRUCKEN                # to print things out

# from ECMA-55 §15

INPUT <= EINGANG                # the input statement

# from ECMA-55 §16

READ <= LESEN                   # part of read / restore
RESTORE <= NEULESEN             # part of read / restore

# from ECMA-55 §17

DATA <= DATEN                   # to embed data in the program

# from ECMA-55 §18

DIM <= ABMESSUNGEN              # dimension arrays
OPTION <= MÖGLICHKEIT           # see ECMA-55 §18.1
BASE <= BASE                    # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= ANMERKUNG                # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= RANDOMISIEREN

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]

# error messages

err0|FEHLER: datei {0s}, linie {1i}, spalte {2i}

