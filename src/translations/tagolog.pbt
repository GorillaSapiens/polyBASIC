####
# autotranslation for the "tagolog" language
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

END <= MAGTAPOS                     # the end statement

# from ECMA-55 §9

ABS <= GANAPNAHALAGA                # the absolute value function
ATN <= KABALIGTARANTANGENT          # the trigonomic arctangent function
COS <= COSINE                       # the trigonomic cosine function
EXP <= EXPONENTIAL                  # the exponential / power function
INT <= INTEGER                      # the integer / floor function
LOG <= LOGARITHM                    # the natural log function
RND <= ROLL                         # generate random number
SGN <= TANDA                        # determine the sign
SIN <= SINE                         # the trigonomic sine function
SQR <= PARISUKATNAUGAT              # the square root function
TAN <= TANGENT                      # the trigonomic tangent function
DBL <= DOBLE                        # convert to double
STR <= STR                          # convert to string
RAT <= RAT                          # convert to rational

# from ECMA-55 §10

DEF <= TUKUYIN                      # for user defined functions

# from ECMA-55 §11

LET <= HAYAAN                       # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= PUMUNTAKANA                   # part of the GOTO and GOSUB
GOSUB <= TUMAWAG                    # formed from GO and SUB if no direct translation exists
GOTO <= TUMALON                     # formed from GO and TO if no direct translation exists
TO <= SA                            # part of for/to/step/next constructs
IF <= KUNG                          # part of if/then constructs
THEN <= PAGKATAPOS                  # part of if/then constructs
SUB <= SUB                          # beware, used as part of "go sub"
ON <= LUMIPAT                       # a sort of a switch statement
RETURN <= BUMALIK                   # used to exit a subroutine
STOP <= TAPOSNA                     # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= MULASA                       # part of for/to/step/next constructs
STEP <= HAKBANG                     # part of for/to/step/next constructs
NEXT <= SUSUNOD                     # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= IPRINT                     # to print things out

# from ECMA-55 §15

INPUT <= INPUT                      # the input statement

# from ECMA-55 §16

READ <= BASAHIN                     # part of read / restore
RESTORE <= BASAHINMULI              # part of read / restore

# from ECMA-55 §17

DATA <= DATA                        # to embed data in the program

# from ECMA-55 §18

DIM <= SUKAT                        # dimension arrays
OPTION <= PAGPIPILIAN               # see ECMA-55 §18.1
BASE <= BASE                        # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= PANSININ                     # see ECMA-55 §18.1

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

err0|ERROR: file {0s}, linya {1i}, haligi {2i}

