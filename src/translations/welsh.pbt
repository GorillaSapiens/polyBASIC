####
# autotranslation for the "welsh" language
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

END <= TERFYNA                  # the end statement

# from ECMA-55 §9

ABS <= GWERTHABSOLIWT           # the absolute value function
ATN <= TANGIADGWRTHDRO          # the trigonomic arctangent function
COS <= NGHOSIN                  # the trigonomic cosine function
EXP <= ESBONYDDOL               # the exponential / power function
INT <= GYFANRIF                 # the integer / floor function
LOG <= LOGARITHM                # the natural log function
RND <= TREIGLECH                # generate random number
SGN <= ARWYDDEN                 # determine the sign
SIN <= SEIN                     # the trigonomic sine function
SQR <= AILISRADD                # the square root function
TAN <= TANGIAD                  # the trigonomic tangent function
DBL <= DYBLWCH                  # convert to double
STR <= TECSTIO                  # convert to string
RAT <= RHESYMOL                 # convert to rational

# from ECMA-55 §10

DEF <= DDIFFINIA                # for user defined functions

# from ECMA-55 §11

LET <= GADAWN                   # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= AETHANT                   # part of the GOTO and GOSUB
GOSUB <= ALWA                   # formed from GO and SUB if no direct translation exists
GOTO <= BEICASID                # formed from GO and TO if no direct translation exists
TO <= I                         # part of for/to/step/next constructs
IF <= OS                        # part of if/then constructs
THEN <= YNA                     # part of if/then constructs
SUB <= HWB                      # beware, used as part of "go sub"
ON <= SWITSITH                  # a sort of a switch statement
RETURN <= DDYCHWELO             # used to exit a subroutine
STOP <= GORFFENEDIG             # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= ODDIWRTH                 # part of for/to/step/next constructs
STEP <= CAMOCH                  # part of for/to/step/next constructs
NEXT <= NESAF                   # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= BRINTIWYD              # to print things out

# from ECMA-55 §15

INPUT <= MEWNBYNNER             # the input statement

# from ECMA-55 §16

READ <= DARLLENEST              # part of read / restore
RESTORE <= AILDDARLLENWCH       # part of read / restore

# from ECMA-55 §17

DATA <= NGWYBODAETH             # to embed data in the program

# from ECMA-55 §18

DIM <= DIMENSIWN                # dimension arrays
OPTION <= OPSIWN                # see ECMA-55 §18.1
BASE <= SEILIANT                # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= SYLW                     # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= ARHAP

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]
❮%0❯ at %1:%2 ->%b	❮%0❯ ar%1:%2 ->%b
❮%0❯ at %1:%2%n	❮%0❯ ar%1:%2%n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	A dim iaith a roddir ar linell orchymyn. Gadael.%n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	Methu cyrchu cyfeiriadur ❮%0❯.%n
ERROR: def ❮%0❯ multiply defined %1:%2 and %3:%4%n	Gwall: def ❮%0❯ Lluoswch wedi'i ddiffinio%1:%2 a%3:%4%n
ERROR: DEFINITION CYCLE DISCOVERED%n	Gwall: Cylch diffiniad wedi'i ddarganfod%n
ERROR: for ❮%0❯ multiply defined %1:%2 and %3:%4%n	Gwall: ar gyfer ❮%0❯ Lluoswch wedi'i ddiffinio%1:%2 a%3:%4%n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n	Gwall: Label ❮%0❯ ar%1:%2 eisoes wedi'i ddiffinio%3:%4%n
ERROR: line %0 column %1, ❮%2❯ has no value%n	Gwall: llinell %0 colofn %1, ❮ %2❯ nid oes gan unrhyw werth %n
ERROR: NO PARSE TREE FOR LINE %0%n	Gwall: dim coeden ddosrannu ar gyfer llinell %0 %n
-l requires a language.%n	-L yn gofyn am iaith.%n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	Gwiriwch newidyn amgylchedd a/neu osodiadau iaith 'POLYBASICPATH'.%n
POLYBASICLANG' ENVIRONMENT VARIABLE NOT SET,	Newidyn amgylchedd POLYBASICLANG 'heb ei osod,
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	Ffynhonnell%0:%1, arae ❮%2❯ wedi'i diffinio eisoes ar linell%3%n
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	Ffynhonnell%0:%1, tan -lif mewnbwn data%n
SOURCE %0:%1, DATA READ UNDERFLOW%n	Ffynhonnell%0:%1, data yn darllen tan -lif%n
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	Ffynhonnell %0: %1, swyddogaeth def ❮ %2❯ yn gofyn am %3 params, ond a elwir gyda %4 %n
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	Ffynhonnell%0:%1, gorlif pentwr gosub%n
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	Ffynhonnell%0:%1, is -lif pentwr gosub%n
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	Ffynhonnell %0: %1, mynegai %2 allan o ystod %n
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	Ffynhonnell %0: %1, Op Camgymhariad chwith/dde %2 %3 %n
SOURCE %0:%1, NEGATIVE INDEX %d%n	Ffynhonnell %0: %1, mynegai negyddol %d %n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	Ffynhonnell%0:%1, nesaf ymlaen ar gyfer dolen gyda newidyn llinyn%n
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	Ffynhonnell%0:%1, Camgymhariad Operand ❮%2:%3❯ ❮%4:%5❯%n
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	Ffynhonnell%0:%1, gwall rhesymeg mathemateg llinyn%n
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	Ffynhonnell%0:%1, label heb ei ddiffinio ❮%2❯%n
SOURCE %0:%1, UNHANDLED OP %2%n	Ffynhonnell %0: %1, OP heb ei drin %2 %n
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	Ffynhonnell%0:%1, anhysbys os yw label ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED DOUBLE MATH OP ❮%2❯%n	Ffynhonnell%0:%1, Math Dwbl heb ei gydnabod Op ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	Ffynhonnell%0:%1, swyddogaeth heb ei chydnabod def ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	Ffynhonnell%0:%1, label gosub heb ei gydnabod ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	Ffynhonnell%0:%1, label goto heb ei gydnabod ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED INTEGER MATH OP ❮%2❯%n	Ffynhonnell%0:%1, Math cyfanrif heb ei gydnabod Op ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	Ffynhonnell %0: %1, heb ei gydnabod canol op %2 %n
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	Ffynhonnell%0:%1, heb ei gydnabod y newidyn nesaf ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED RATIONAL MATH OP ❮%2❯%n	Ffynhonnell%0:%1, Math rhesymegol heb ei gydnabod Op ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	Ffynhonnell%0:%1, math newidiol heb ei gydnabod ❮%2❯%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	Ffynhonnell%0:%1, newidyn ❮%2❯ wedi'i ddiffinio fel dim%3 (%4 ..%5,%6 ..%7) arae ar linell%8%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	Ffynhonnell%0:%1, newidyn ❮%2❯ wedi'i ddiffinio fel dim%3 (%4 ..%5) arae ar linell%6%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	Ffynhonnell%0:%1, newidyn ❮%2❯ wedi'i ddiffinio fel dim%3 arae ar linell%4%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	Ffynhonnell%0:%1, newidyn ❮%2❯ wedi'i ddiffinio fel nonarray ar linell%3%n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	Ffynhonnell %0: %1, newidyn ❮ %2❯ dim1 fel %3 y tu allan ffin1 %4 .. %5 o'r llinell %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	Ffynhonnell %0: %1, newidyn ❮ %2❯ dim1 fel %3 ffin y tu allan %4 .. %5 o'r llinell %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	Ffynhonnell %0: %1, newidyn ❮ %2❯ dim2 fel %3 y tu allan ffin2 %4 .. %5 o'r llinell %6 %n
UNABLE TO OPEN %0 FOR READING.%n	Methu agor %0 ar gyfer darllen. %n
UNABLE TO OPEN FILE ❮%0❯%n	Methu agor ffeil ❮%0❯%n
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	Src Cod Opcode heb ei drin: %0 op %1 llinell %2 col %3 %n
UNRECOGNIZED INPUT ❮%0❯%n	Mewnbwn heb ei gydnabod ❮%0❯%n
