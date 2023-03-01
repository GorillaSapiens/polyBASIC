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
❮%0❯ at %1:%2 ->%b	❮%0❯ je%1:%2 ->%b
❮%0❯ at %1:%2%n	❮%0❯ je%1:%2%n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	Kaj neniu lingvo donita sur komandlinio. Elirante.%n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	Ne povas aliri dosierujon ❮%0❯.%n
ERROR: def ❮%0❯ multiply defined %1:%2 and %3:%4%n	Eraro: def ❮%0❯ multobligu difinitan%1:%2 kaj%3:%4%n
ERROR: DEFINITION CYCLE DISCOVERED%n	Eraro: Difina ciklo malkovrita%n
ERROR: for ❮%0❯ multiply defined %1:%2 and %3:%4%n	Eraro: Por ❮%0❯ multobligu difinitan%1:%2 kaj%3:%4%n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n	Eraro: Etikedo ❮%0❯ AT%1:%2 Jam difinita%3:%4%n
ERROR: line %0 column %1, ❮%2❯ has no value%n	Eraro: Line %0 Kolumno %1, ❮ %2❯ havas neniun valoron %n
ERROR: NO PARSE TREE FOR LINE %0%n	Eraro: Neniu parsearbo por linio %0 %n
-l requires a language.%n	-L postulas lingvon.%n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	Bonvolu kontroli la median variablon de 'POLYBASICPATH' kaj/aŭ lingvaj agordoj.%n
POLYBASICLANG' ENVIRONMENT VARIABLE NOT SET,	POLYBASICLANG 'media variablo ne agordita,
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	Fonto%0:%1, Array ❮%2❯ Jam difinita en linio%3%n
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	Fonto%0:%1, datuma eniga subfluo%n
SOURCE %0:%1, DATA READ UNDERFLOW%n	Fonto%0:%1, Datumoj Legu Subfluon%n
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	Fonto %0: %1, funkcio def ❮ %2❯ postulas %3 paramojn, sed nomataj kun %4 %n
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	Fonto%0:%1, Gosub Stack Overflow%n
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	Fonto%0:%1, Gosub Stack Underflow%n
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	Fonto %0: %1, indekso %2 ekster gamo %n
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	Fonto %0: %1, Maldekstra/Dekstra OP Malsaĝulo %2 %3 %n
SOURCE %0:%1, NEGATIVE INDEX %d%n	Fonto %0: %1, negativa indekso %d %n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	Fonto%0:%1, poste por buklo kun ĉena variablo%n
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	Fonto%0:%1, Operand -miskomparo ❮%2:%3❯ ❮%4:%5❯%n
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	Fonto%0:%1, ĉena matematika logika eraro%n
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	Fonto%0:%1, nedifinita etikedo ❮%2❯%n
SOURCE %0:%1, UNHANDLED OP %2%n	Fonto %0: %1, Unhandled OP %2 %n
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	Fonto%0:%1, nekonata se etikedo ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED DOUBLE MATH OP ❮%2❯%n	Fonto%0:%1, ne rekonita duobla matematiko op ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	Fonto%0:%1, ne rekonita funkcio def ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	Fonto%0:%1, ne rekonita GOSUB -etikedo ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	Fonto%0:%1, ne rekonita goto -etikedo ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED INTEGER MATH OP ❮%2❯%n	Fonto%0:%1, ne rekonita entjera matematiko op ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	Fonto %0: %1, ne rekonita meza op %2 %n
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	Fonto%0:%1, ne rekonita sekva variablo ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED RATIONAL MATH OP ❮%2❯%n	Fonto%0:%1, ne rekonita racia matematiko op ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	Fonto%0:%1, ne rekonita ŝanĝiĝema tipo ❮%2❯%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	Fonto%0:%1, variablo ❮%2❯ difinita kiel dim%3 (%4 ..%5,%6 ..%7) Array On Line%8%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	Fonto%0:%1, variablo ❮%2❯ difinita kiel DIM%3 (%4 ..%5) Array On Line%6%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	Fonto%0:%1, variablo ❮%2❯ difinita kiel dim%3 tabelo sur linio%4%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	Fonto%0:%1, variablo ❮%2❯ difinita kiel nearray On Line%3%n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	Fonto %0: %1, variablo ❮ %2❯ DIM1 kiel %3 ekster Bounds1 %4 .. %5 de linio %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	Fonto %0: %1, variablo ❮ %2❯ DIM1 kiel %3 ekster limoj %4 .. %5 de linio %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	Fonto %0: %1, variablo ❮ %2❯ DIM2 kiel %3 ekster limoj2 %4 .. %5 de linio %6 %n
UNABLE TO OPEN %0 FOR READING.%n	Ne eblas malfermi %0 por legado. %n
UNABLE TO OPEN FILE ❮%0❯%n	Ne eblas malfermi dosieron ❮%0❯%n
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	Unhandled Opcode Src: %0 OP %1 Line %2 Col %3 %n
UNRECOGNIZED INPUT ❮%0❯%n	Ne rekonita enigo ❮%0❯%n
