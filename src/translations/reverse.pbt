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
❮%0❯ at %1:%2 ->	❮%0❯ ta %1:%2 ->
❮%0❯ at %1:%2%n	❮%0❯ ta %1:%2%n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	DNA ON EGAUGNAL NEVIG NO DNAMMOC ENIL.  GNITIXE.%n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	TONNAC SSECCA YROTCERID ❮%0❯.%n
ERROR: DEFINITION CYCLE DISCOVERED%n	RORRE: NOITINIFED ELCYC DEREVOCSID%n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4	RORRE: lebal ❮%0❯ ta %1:%2 ydaerla denifed %3:%4
ERROR: line %0 column %1, ❮%2❯ has no value%n	RORRE: enil %0 nmuloc %1, ❮%2❯ sah on eulav%n
ERROR: NO PARSE TREE FOR LINE %0%n	RORRE: ON ESRAP EERT ROF ENIL %0%n
-l requires a language.%n	-l seriuqer a egaugnal.%n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	ESAELP KCEHC 'HTAPCISABYLOP' TNEMNORIVNE ELBAIRAV DNA/RO EGAUGNAL SGNITTES.%n
POLYBASICLANG' ENVIRONMENT VARIABLE NOT SET,	GNALCISABYLOP' TNEMNORIVNE ELBAIRAV TON TES,
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	ECRUOS %0:%1, YARRA ❮%2❯ YDAERLA DENIFED NO ENIL %3%n
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	ECRUOS %0:%1, ATAD TUPNI WOLFREDNU%n
SOURCE %0:%1, DATA READ UNDERFLOW%n	ECRUOS %0:%1, ATAD DAER WOLFREDNU%n
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	ECRUOS %0:%1, NOITCNUF FED ❮%2❯ SERIUQER %3 SMARAP, TUB DELLAC HTIW %4%n
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	ECRUOS %0:%1, BUSOG KCATS WOLFREVO%n
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	ECRUOS %0:%1, BUSOG KCATS WOLFREDNU%n
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	ECRUOS %0:%1, XEDNI %2 TUO FO EGNAR%n
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	ECRUOS %0:%1, TFEL/THGIR PO HCTAMSIM %2 %3%n
SOURCE %0:%1, NEGATIVE INDEX %d%n	ECRUOS %0:%1, EVITAGEN XEDNI %d%n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	ECRUOS %0:%1, TXEN NO ROF POOL HTIW GNIRTS ELBAIRAV%n
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	ECRUOS %0:%1, DNAREPO HCTAMSIM ❮%2:%3❯ ❮%4:%5❯%n
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	ECRUOS %0:%1, GNIRTS HTAM CIGOL RORRE%n
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	ECRUOS %0:%1, DENIFEDNU LEBAL ❮%2❯%n
SOURCE %0:%1, UNHANDLED OP %2%n	ECRUOS %0:%1, DELDNAHNU PO %2%n
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	ECRUOS %0:%1, NWONKNU FI LEBAL ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	ECRUOS %0:%1, DEZINGOCERNU NOITCNUF FED ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	ECRUOS %0:%1, DEZINGOCERNU BUSOG LEBAL ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	ECRUOS %0:%1, DEZINGOCERNU OTOG LEBAL ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MATH OP ❮%2❯%n	ECRUOS %0:%1, DEZINGOCERNU HTAM PO ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	ECRUOS %0:%1, DEZINGOCERNU DIM PO %2%n
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	ECRUOS %0:%1, DEZINGOCERNU TXEN ELBAIRAV ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	ECRUOS %0:%1, DEZINGOCERNU ELBAIRAV EPYT ❮%2❯%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	ECRUOS %0:%1, ELBAIRAV ❮%2❯ DENIFED SA MID%3(%4..%5, %6..%7) YARRA NO ENIL %8%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	ECRUOS %0:%1, ELBAIRAV ❮%2❯ DENIFED SA MID%3(%4..%5) YARRA NO ENIL %6%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	ECRUOS %0:%1, ELBAIRAV ❮%2❯ DENIFED SA MID%3 YARRA NO ENIL %4%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	ECRUOS %0:%1, ELBAIRAV ❮%2❯ DENIFED SA YARRANON NO ENIL %3%n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	ECRUOS %0:%1, ELBAIRAV ❮%2❯ MID1 SA %3 EDISTUO SDNUOB1 %4..%5 MORF ENIL %6%n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	ECRUOS %0:%1, ELBAIRAV ❮%2❯ MID1 SA %3 EDISTUO SDNUOB %4..%5 MORF ENIL %6%n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	ECRUOS %0:%1, ELBAIRAV ❮%2❯ MID2 SA %3 EDISTUO SDNUOB2 %4..%5 MORF ENIL %6%n
UNABLE TO OPEN %0 FOR READING.%n	ELBANU OT NEPO %0 ROF GNIDAER.%n
UNABLE TO OPEN FILE ❮%0❯%n	ELBANU OT NEPO ELIF ❮%0❯%n
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	DELDNAHNU EDOCPO crs:%0 po %1 enil %2 loc %3%n
UNRECOGNIZED INPUT ❮%0❯%n	DEZINGOCERNU TUPNI ❮%0❯%n
