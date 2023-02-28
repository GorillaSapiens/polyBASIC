####
# autotranslation for the "bengali" language
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

END <= শষ                   # the end statement

# from ECMA-55 §9

ABS <= পরমমন                # the absolute value function
ATN <= বপরতসপরশকতর          # the trigonomic arctangent function
COS <= কসইন                 # the trigonomic cosine function
EXP <= ততপরযপরণ             # the exponential / power function
INT <= পরণসখয               # the integer / floor function
LOG <= লগরদম                # the natural log function
RND <= রল                   # generate random number
SGN <= চহন                  # determine the sign
SIN <= সইন                  # the trigonomic sine function
SQR <= বরগমল                # the square root function
TAN <= সপরশকতর              # the trigonomic tangent function
DBL <= দবগণ                 # convert to double
STR <= পঠয                  # convert to string
RAT <= যকতসঙগত              # convert to rational

# from ECMA-55 §10

DEF <= সজঞযত                # for user defined functions

# from ECMA-55 §11

LET <= দন                   # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= যওয                   # part of the GOTO and GOSUB
GOSUB <= কল                 # formed from GO and SUB if no direct translation exists
GOTO <= লফ                  # formed from GO and TO if no direct translation exists
TO <= পরত                   # part of for/to/step/next constructs
IF <= যদ                    # part of if/then constructs
THEN <= তরপর                # part of if/then constructs
SUB <= সব                   # beware, used as part of "go sub"
ON <= সযইচ                  # a sort of a switch statement
RETURN <= পরতযবরতন          # used to exit a subroutine
STOP <= সমপত                # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= থক                   # part of for/to/step/next constructs
STEP <= পদকষপ               # part of for/to/step/next constructs
NEXT <= পরবরত               # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= ছপ                 # to print things out

# from ECMA-55 §15

INPUT <= ইনপট               # the input statement

# from ECMA-55 §16

READ <= পডন                 # part of read / restore
RESTORE <= পনরযপডন          # part of read / restore

# from ECMA-55 §17

DATA <= তথয                 # to embed data in the program

# from ECMA-55 §18

DIM <= মতর                  # dimension arrays
OPTION <= বকলপ              # see ECMA-55 §18.1
BASE <= বস                  # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= মনতবয                # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= এলমলভব

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]

# error messages

err0|তরট: ফইল {0s}, লইন {1i}, কলম {2i}
