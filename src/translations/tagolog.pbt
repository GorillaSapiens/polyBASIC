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
STR <= TEKSTO                       # convert to string
RAT <= MAKATUWIRAN                  # convert to rational

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

DATA <= IMPORMASYON                 # to embed data in the program

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
❮%0❯ at %1:%2 ->%b	❮%0❯ sa%1:%2 ->%B
❮%0❯ at %1:%2%n	❮%0❯ sa%1:%2%n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	At walang wikang ibinigay sa linya ng utos. Paglabas.%n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	Hindi ma -access ang direktoryo ❮%0❯.%n
ENVIRONMENT VARIABLE 'POLYBASICLANG' NOT SET,	Hindi nakatakda ang variable na 'POLYBASICLANG',
ERROR: def ❮%0❯ multiply defined %1:%2 and %3:%4%n	Error: def ❮%0❯ Multiply tinukoy%1:%2 at%3:%4%n
ERROR: DEFINITION CYCLE DISCOVERED%n	ERROR: Napag -alaman ng Cycle ng Kahulugan%n
ERROR: for ❮%0❯ multiply defined %1:%2 and %3:%4%n	ERROR: Para sa ❮%0❯ Multiply na tinukoy%1:%2 at%3:%4%n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n	Error: Label ❮%0❯ sa%1:%2 Natukoy na%3:%4%n
ERROR: line %0 column %1, ❮%2❯ has no value%n	Error: linya %0 haligi %1, ❮ %2❯ ay walang halaga %n
ERROR: NO PARSE TREE FOR LINE %0%n	Error: walang puno ng parse para sa linya %0 %n
-l requires a language.%n	-l ay nangangailangan ng isang wika.%n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	Mangyaring suriin ang 'POLYBASICPATH' variable at/o mga setting ng wika.%n
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	Pinagmulan%0:%1, array ❮%2❯ Natukoy na sa linya%3%n
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	Pinagmulan%0:%1, Data Input underflow%n
SOURCE %0:%1, DATA READ UNDERFLOW%n	Pinagmulan%0:%1, nabasa ng data ang underflow%n
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	Pinagmulan %0: %1, function def ❮ %2❯ ay nangangailangan ng %3 mga param, ngunit tinawag na may %4 %n
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	Pinagmulan%0:%1, Gosub stack overflow%n
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	Pinagmulan%0:%1, gosub stack underflow%n
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	Pinagmulan %0: %1, index %2 sa saklaw %n
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	Pinagmulan %0: %1, kaliwa/kanang op mismatch %2 %3 %n
SOURCE %0:%1, NEGATIVE INDEX %d%n	Pinagmulan %0: %1, negatibong index %d %n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	Pinagmulan%0:%1, Susunod sa para sa loop na may String variable%n
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	Pinagmulan%0:%1, operand mismatch ❮%2:%3❯ ❮%4:%5❯%n
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	Pinagmulan%0:%1, String Math Logic Error%n
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	Pinagmulan%0:%1, hindi natukoy na label ❮%2❯%n
SOURCE %0:%1, UNHANDLED OP %2%n	Pinagmulan %0: %1, Unhandled op %2 %n
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	Pinagmulan%0:%1, hindi kilala kung label ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED DOUBLE MATH OP ❮%2❯%n	Pinagmulan%0:%1, hindi nakikilalang dobleng matematika op ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	Pinagmulan%0:%1, hindi nakikilalang function def ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	Pinagmulan%0:%1, hindi nakikilalang label ng gosub ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	Pinagmulan%0:%1, hindi nakikilalang label ng goto ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED INTEGER MATH OP ❮%2❯%n	Pinagmulan%0:%1, hindi nakikilalang integer math op ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	Pinagmulan %0: %1, hindi nakikilala mid op %2 %n
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	Pinagmulan%0:%1, hindi nakikilalang susunod na variable ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED RATIONAL MATH OP ❮%2❯%n	Pinagmulan%0:%1, hindi nakikilalang Rational Math Op ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	Pinagmulan%0:%1, hindi nakikilalang uri ng variable ❮%2❯%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	Pinagmulan%0:%1, variable ❮%2❯ tinukoy bilang dim%3 (%4 ..%5,%6 ..%7) array sa linya%8%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	Pinagmulan%0:%1, variable ❮%2❯ tinukoy bilang dim%3 (%4 ..%5) array sa linya%6%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	Pinagmulan%0:%1, variable ❮%2❯ tinukoy bilang dim%3 array sa linya%4%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	Pinagmulan%0:%1, variable ❮%2❯ tinukoy bilang nonarray sa linya%3%n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	Pinagmulan %0: %1, variable ❮ %2❯ dim1 bilang %3 sa labas ng hangganan1 %4 .. %5 mula sa linya %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	Pinagmulan %0: %1, variable ❮ %2❯ dim1 bilang %3 sa labas ng hangganan %4 .. %5 mula sa linya %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	Pinagmulan %0: %1, variable ❮ %2❯ dim2 bilang %3 sa labas ng hangganan2 %4 .. %5 mula sa linya %6 %n
UNABLE TO OPEN %0 FOR READING.%n	Hindi mabuksan ang %0 para sa pagbabasa. %n
UNABLE TO OPEN FILE ❮%0❯%n	Hindi mabuksan ang file ❮%0❯%n
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	UNHANDLED OPCODE SRC: %0 OP %1 LINE %2 Col %3 %n
UNRECOGNIZED INPUT ❮%0❯%n	Hindi nakikilalang input ❮%0❯%n
