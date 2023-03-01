####
# autotranslation for the "latin" language
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

END <= FINIS                      # the end statement

# from ECMA-55 §9

ABS <= ABSOLUTUS                  # the absolute value function
ATN <= INVERSUMTANGENTEM          # the trigonomic arctangent function
COS <= COSINUS                    # the trigonomic cosine function
EXP <= EXPONENTIALIS              # the exponential / power function
INT <= INTEGER                    # the integer / floor function
LOG <= LOGARITHMUS                # the natural log function
RND <= VOLUMEN                    # generate random number
SGN <= SIGNUM                     # determine the sign
SIN <= SINUS                      # the trigonomic sine function
SQR <= QUADRATUS                  # the square root function
TAN <= TANGENS                    # the trigonomic tangent function
DBL <= DUPLEX                     # convert to double
STR <= TEXT                       # convert to string
RAT <= RATIONALIS                 # convert to rational

# from ECMA-55 §10

DEF <= DEFINIRE                   # for user defined functions

# from ECMA-55 §11

LET <= FIAT                       # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= PEREO                       # part of the GOTO and GOSUB
GOSUB <= VOCO                     # formed from GO and SUB if no direct translation exists
GOTO <= JUMP                      # formed from GO and TO if no direct translation exists
TO <= UT                          # part of for/to/step/next constructs
IF <= SI                          # part of if/then constructs
THEN <= TUM                       # part of if/then constructs
SUB <= SUB                        # beware, used as part of "go sub"
ON <= SWITCH                      # a sort of a switch statement
RETURN <= REDITUS                 # used to exit a subroutine
STOP <= COMPLEXUS                 # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= EX                         # part of for/to/step/next constructs
STEP <= GRADUS                    # part of for/to/step/next constructs
NEXT <= DEINDE                    # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= PRINT                    # to print things out

# from ECMA-55 §15

INPUT <= INPUT                    # the input statement

# from ECMA-55 §16

READ <= LEGERE                    # part of read / restore
RESTORE <= RELIGIO                # part of read / restore

# from ECMA-55 §17

DATA <= NOTITIA                   # to embed data in the program

# from ECMA-55 §18

DIM <= DIMENSIO                   # dimension arrays
OPTION <= OPTIO                   # see ECMA-55 §18.1
BASE <= BASIS                     # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= ADNOTATIO                  # see ECMA-55 §18.1

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
❮%0❯ at %1:%2 ->%b	❮ %0 ❯ %1, %2 -> %B
❮%0❯ at %1:%2%n	❮ %0❯ ad %1, %2 %n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	Et non linguam dedit in order versus. Exivit. %n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	Potest accedere Directory ❮ %0❯. %n
ENVIRONMENT VARIABLE 'POLYBASICLANG' NOT SET,	Environment variabilis 'POLYBASICLANG' non posuit:
ERROR: def ❮%0❯ multiply defined %1:%2 and %3:%4%n	Error: DEF ❮ %0❯ multiplicare defined %1: %2 %3, %4 %n
ERROR: DEFINITION CYCLE DISCOVERED%n	Error: Definitio exolvuntur inventa %n
ERROR: for ❮%0❯ multiply defined %1:%2 and %3:%4%n	Error: nam ❮ %0 ❯ multiplicare defined %1: %2 et %3, %4 %n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n	Error: Label ❮ %0❯ ad %1: %2 iam defined %3, %4 %n
ERROR: line %0 column %1, ❮%2❯ has no value%n	Error: linea %0 columna %1, ❮ %2❯ habet valorem %n
ERROR: NO PARSE TREE FOR LINE %0%n	Error: Non parse in linea %0 %n
-l requires a language.%n	-L postulat lingua. %n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	Placere reprehendo 'POLYBASICPATH, environment variabilis et / vel lingua occasus. %n
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	Fontem %0: %1, ordinata ❮ %2❯ iam defined in line %3 %n
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	Source %0: %1, data initus underflow %n
SOURCE %0:%1, DATA READ UNDERFLOW%n	Fonte %0: %1, data Read underflow %n
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	Fontem %0: %1, function def ❮ %2❯ requirit %3 params, sed vocavit %4 %n
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	Source %0: %1, Gosumb Stack redundantiam %n
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	Fontem %0: %1, Gosub Stack underflow %n
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	Fonte %0: %1, Index %2 de range %n
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	Fonte %0: %1, reliquit / ius op mismatch %2 %3 %n
SOURCE %0:%1, NEGATIVE INDEX %d%n	Fontem %0: %1, index %d %n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	Source %0: %1, deinde ad loop cum filum variabilis %n
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	Fonte %0: %1, Operand mismatch ❮ %2, %3❯ ❮ %4: %5 ^ N
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	Fonte %0: %1, linea Math Logica Error %n
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	Source %0: %1, Undefined Label ❮ %2 ❯ %n
SOURCE %0:%1, UNHANDLED OP %2%n	Source %0: %1, Unhandled op %2 %n
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	Fontem %0: %1, ignotum si titulus ❮ %2 ^ n
SOURCE %0:%1, UNRECOGNIZED DOUBLE MATH OP ❮%2❯%n	Fontem %0: %1, latuit duplex math op ❮ %2 ^ n
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	Fontem %0: %1, latuit functio def ❮ %2 ❯ %n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	Fontem %0: %1, cognognized Gosub Label ❮ %2❯ %n
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	Source %0: %1, latuit gata Label ❮ %2❯ %n
SOURCE %0:%1, UNRECOGNIZED INTEGER MATH OP ❮%2❯%n	Fontem %0: %1, intelligitur integer math op ❮ %2 ❯ %n
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	Fonte %0: %1, latuit medium op %2 %n
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	Fontem %0: %1, latuit Next variabilis ❮ %2 ^ n
SOURCE %0:%1, UNRECOGNIZED RATIONAL MATH OP ❮%2❯%n	Fontem %0: %1, latuit rationalis math op ❮ %2❯ %n
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	Fonte %0: %1, latuit variabilis generis ❮ %2 ❯ %n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	Fonte %0: %1, variabilis ❮ %2❯ defined Dim %3 ( %4 .. %5, %6 .. %7) ordinata in linea %8 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	Fontem %0: %1, variabilis ❮ %2❯ defined Dim %3 ( %4 .. %5) ordinata in line %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	Fontem %0: %1, variabilis ❮ %2❯ defined Dim %3 ordinata in linea %4 N
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	Fontem %0: %1, variabilis ❮ %2❯ defined as nonarray in line %3 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	Fontem %0: %1, variabilis ❮ %2 ❯ dim1 sicut %3 extra terminari1 %4 .. %5 ex linea %6 %6
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	Fontem %0: %1, variabilis ❮ %2 ❯ Dim1 sicut %3 extra terminis %4 .. %5 ex linea %6 %6
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	Fontem %0: %1, variabilis ❮ %2 ❯ Dim2 sicut %3 extra terminos2 %4 .. %5 ex linea %6 %6
UNABLE TO OPEN %0 FOR READING.%n	'Non aperire %0 ad Lectio. %n
UNABLE TO OPEN FILE ❮%0❯%n	Non aperire file ❮ %0 ❯ %n
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	Unhandled OPCODE SRC: %0 op %1 line %2 Col %3 %n
UNRECOGNIZED INPUT ❮%0❯%n	❮ %0 ❮ initus ❮ (0 ❯
