####
# autotranslation for the "zulu" language
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

END <= UKUGCINA                          # the end statement

# from ECMA-55 §9

ABS <= INANIELIPHELELE                   # the absolute value function
ATN <= IINVERSETANGENT                   # the trigonomic arctangent function
COS <= ICOSI                             # the trigonomic cosine function
EXP <= UKUVEZA                           # the exponential / power function
INT <= PHETHE                            # the integer / floor function
LOG <= ISILINGANISOSOGAZIDUZEMI          # the natural log function
RND <= QOQA                              # generate random number
SGN <= BHALA                             # determine the sign
SIN <= SINE                              # the trigonomic sine function
SQR <= ISQUAREROOT                       # the square root function
TAN <= INHLIZIYOYAKHONA                  # the trigonomic tangent function
DBL <= BILI                              # convert to double
STR <= UMBHALO                           # convert to string
RAT <= NENGQONDO                         # convert to rational

# from ECMA-55 §10

DEF <= CHASISELA                         # for user defined functions

# from ECMA-55 §11

LET <= VUMELA                            # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= HAMBANGEMOTO                       # part of the GOTO and GOSUB
GOSUB <= MEMEZA                          # formed from GO and SUB if no direct translation exists
GOTO <= GXUMA                            # formed from GO and TO if no direct translation exists
TO <= KWA                                # part of for/to/step/next constructs
IF <= NXA                                # part of if/then constructs
THEN <= KHONA                            # part of if/then constructs
SUB <= INDAWO                            # beware, used as part of "go sub"
ON <= SHINTSHA                           # a sort of a switch statement
RETURN <= BUYISELAEMUVA                  # used to exit a subroutine
STOP <= KUQEDIWE                         # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= UKUSUKA                           # part of for/to/step/next constructs
STEP <= GXATHA                           # part of for/to/step/next constructs
NEXT <= OLANDELAYO                       # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= CINDEZELA                       # to print things out

# from ECMA-55 §15

INPUT <= FAKA                            # the input statement

# from ECMA-55 §16

READ <= FUNDA                            # part of read / restore
RESTORE <= XWAYISA                       # part of read / restore

# from ECMA-55 §17

DATA <= ULWAZI                           # to embed data in the program

# from ECMA-55 §18

DIM <= UBUKHULU                          # dimension arrays
OPTION <= UKUKHETHA                      # see ECMA-55 §18.1
BASE <= ISIZINDA                         # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= PHAWULA                           # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= PHUNGULA

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]
❮%0❯ at %1:%2 ->%b	❮ %0❯ ku %1: %2 -> %B
❮%0❯ at %1:%2%n	❮ %0❯ ku- %1: %2 %n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	Futhi alukho ulimi olunikezwe kulayini womyalo. Ukuphuma. %n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	Ayikwazi ukufinyelela umkhombandlela ❮ %0❯. %n
ERROR: def ❮%0❯ multiply defined %1:%2 and %3:%4%n	I-ERROR: def ❮ %0❯ ichaze i- %1: %2 no %3: %4 %n
ERROR: DEFINITION CYCLE DISCOVERED%n	Iphutha: Ukuchazwa komjikelezo kutholakele %n
ERROR: for ❮%0❯ multiply defined %1:%2 and %3:%4%n	I-ERROR: ye-❮ %0❯ ichaze kaningi %1: %2 no %3: %4 %n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n	Iphutha: Ilebula ❮ %0❯ ku- %1: %2 isivele ichaziwe %3: %4 %n
ERROR: line %0 column %1, ❮%2❯ has no value%n	Iphutha: umugqa %0 ikholomu %1, ❮ %2❯ ayinanzuzo %n
ERROR: NO PARSE TREE FOR LINE %0%n	I-ERROR: Akukho Tree Parse for Line %0 %n
-l requires a language.%n	-L kudinga ulimi. %n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	Sicela ubheke i- 'POLYBASICPATH' imvelo eguquguqukayo kanye / noma izilungiselelo zolimi. %n
POLYBASICLANG' ENVIRONMENT VARIABLE NOT SET,	Ukuguquguquka kwemvelo kwePOLYBASICLANG 'akusethiwe,
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	Umthombo %0: %1, u-Array ❮ %2❯ ochaziwe kulayini %3 %n
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	Umthombo %0: %1, Ukufakwa kwedatha okuvinjelwe %n
SOURCE %0:%1, DATA READ UNDERFLOW%n	Umthombo %0: %1, idatha ifundwe underflow %n
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	Umthombo %0: %1, I-Function Def ❮ %2❯ idinga %3 amapharamu, kepha ibizwa nge- %4 %n
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	Umthombo %0: %1, GoSub Stack Overflow %n
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	Umthombo %0: %1, GoSub Stack Underflow %n
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	Umthombo %0: %1, Index %2 Out of Range %n
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	Umthombo %0: %1, kwesokunxele / kwesokudla op mismatch %2 %3 %n
SOURCE %0:%1, NEGATIVE INDEX %d%n	Umthombo %0: %1, inkomba emibi %d %n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	Umthombo %0: %1, olandelayo on loop nge-string freaff %n
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	Umthombo %0: %1, i-operand mismatch ❮ %2: %3❯ ❮ %4: %5❯ %n
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	Umthombo %0: %1, I-String Math Logic Iphutha %n
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	Umthombo %0: %1, ilebula elingachazwanga ❮ %2❯ %n
SOURCE %0:%1, UNHANDLED OP %2%n	Umthombo %0: %1, ungajabuli i-OP %2 %n
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	Umthombo %0: %1, Akaziwa Uma ilebula ❮ %2❯ %n
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	Umthombo %0: %1, I-def engaziwa ye-def ❮ %2❯ %n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	Umthombo %0: %1, Ilebula engaziwa ye-GOSUB ❮ %2❯ %n
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	Umthombo %0: %1, ilebula le-goto elingaziwa ❮ %2❯ %n
SOURCE %0:%1, UNRECOGNIZED MATH OP ❮%2❯%n	Umthombo %0: %1, ongaziwa nge-Math Op %2❯ %n
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	Umthombo %0: %1, engaziwa maphakathi ne-OP %2 %n
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	Umthombo %0: %1, engaziwa ngokulandelana okulandelayo ❮ %2❯ %n
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	Umthombo %0: %1, Uhlobo olungaziwa oluguquguqukayo ❮ %2❯ %n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	Umthombo %0: %1, uguquguqukayo ❮ %2❯ ochazwe njenge-Dim %3 ( %4 .. %5, %6 .. %7) Uhlu kulayini %8 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	Umthombo %0: %1, uguquguqukayo ❮ %2❯ uchazwe njenge-Dim %3 ( %4 .. %5) uhlu lwamalungu ku- %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	Umthombo %0: %1, uguquguqukayo ❮ %2❯ ochazwe njenge-Dim %3 Array kulayini %4 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	Umthombo %0: %1, uguquguqukayo ❮ %2❯ ochazwe njenge-nonnarray kulayini %3 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	Umthombo %0: %1, uguquguqukayo ❮ %2❯ dim1 njengoba %3 ngaphandle kwe-Bounds1 %4 .. %5 kusuka kulayini %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	Umthombo %0: %1, uguquguqukayo ❮ %2❯ dim1 njengoba %3 ngaphandle kwemingcele %4 .. %5 kusuka kulayini %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	Umthombo %0: %1, aguquguqukayo ❮ %2❯ Dim2 njengoba %3 ngaphandle kwe-Sourts2 %4 .. %5 kusuka kulayini %6 %n
UNABLE TO OPEN %0 FOR READING.%n	Ayikwazi ukuvula i- %0 yokufunda. %n
UNABLE TO OPEN FILE ❮%0❯%n	Ayikwazi ukuvula ifayela ❮ %0❯ %n
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	I-Opcode Src edidanisiwe: %0 op %1 umugqa %2 Col %3 %n
UNRECOGNIZED INPUT ❮%0❯%n	Okokufaka okungaziwa ❮ %0❯ %n
