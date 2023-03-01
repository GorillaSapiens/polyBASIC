####
# autotranslation for the "portuguese" language
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

END <= FIM                      # the end statement

# from ECMA-55 §9

ABS <= VALORABSOLUTO            # the absolute value function
ATN <= TANGENTEINVERSA          # the trigonomic arctangent function
COS <= COSSENO                  # the trigonomic cosine function
EXP <= EXPONENCIAL              # the exponential / power function
INT <= INTEIRO                  # the integer / floor function
LOG <= LOGARITMO                # the natural log function
RND <= ROLAR                    # generate random number
SGN <= SINAL                    # determine the sign
SIN <= SENO                     # the trigonomic sine function
SQR <= RAIZQUADRADA             # the square root function
TAN <= TANGENTE                 # the trigonomic tangent function
DBL <= DOBRO                    # convert to double
STR <= TEXTO                    # convert to string
RAT <= RACIONAL                 # convert to rational

# from ECMA-55 §10

DEF <= DEFINIR                  # for user defined functions

# from ECMA-55 §11

LET <= DEIXAR                   # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= IR                        # part of the GOTO and GOSUB
GOSUB <= CHAMAR                 # formed from GO and SUB if no direct translation exists
GOTO <= PULAR                   # formed from GO and TO if no direct translation exists
TO <= PARA                      # part of for/to/step/next constructs
IF <= SE                        # part of if/then constructs
THEN <= ENTÃO                   # part of if/then constructs
SUB <= SUB                      # beware, used as part of "go sub"
ON <= TROCAR                    # a sort of a switch statement
RETURN <= RETORNAR              # used to exit a subroutine
STOP <= FINALIZADO              # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= DE                       # part of for/to/step/next constructs
STEP <= ETAPA                   # part of for/to/step/next constructs
NEXT <= PRÓXIMO                 # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= IMPRIMIR               # to print things out

# from ECMA-55 §15

INPUT <= ENTRADA                # the input statement

# from ECMA-55 §16

READ <= LER                     # part of read / restore
RESTORE <= RELER                # part of read / restore

# from ECMA-55 §17

DATA <= INFORMAÇÃO              # to embed data in the program

# from ECMA-55 §18

DIM <= DIMENSÃO                 # dimension arrays
OPTION <= OPÇÃO                 # see ECMA-55 §18.1
BASE <= BASE                    # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= OBSERVAÇÃO               # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= ALEATÓRIA

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]
❮%0❯ at %1:%2 ->	❮%0❯ em%1:%2 ->
❮%0❯ at %1:%2%n	❮%0❯ em%1:%2%n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	E nenhum idioma dado na linha de comando. Saindo.%n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	Não é possível acessar o diretório ❮%0❯.%n
ERROR: DEFINITION CYCLE DISCOVERED%n	Erro: ciclo de definição descoberta%n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4	Erro: Rótulo ❮%0❯ em%1:%2 já definido%3:%4
ERROR: line %0 column %1, ❮%2❯ has no value%n	Erro: linha %0 coluna %1, ❮ %2❯ não tem valor %n
ERROR: NO PARSE TREE FOR LINE %0%n	Erro: nenhuma árvore de análise para linha %0 %n
-l requires a language.%n	-l requer um idioma.%n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	Verifique a variável de ambiente 'POLYBASICPATH' e/ou configurações de idioma.%n
POLYBASICLANG' ENVIRONMENT VARIABLE NOT SET,	Variável de ambiente PoliBasiclang não definida,
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	Fonte%0:%1, matriz ❮%2❯ já definido na linha%3%n
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	Fonte%0:%1, entrada de dados subfluente%n
SOURCE %0:%1, DATA READ UNDERFLOW%n	Fonte%0:%1, dados Leia o subflow%n
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	Fonte %0: %1, função def ❮ %2❯ requer %3 params, mas chamado com %4 %n
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	Fonte%0:%1, Gosub Stack Overflow%n
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	Fonte%0:%1, Gosub Stack Subflow%n
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	Fonte %0: %1, índice %2 fora da faixa %n
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	Fonte %0: %1, esquerda/direita OP incompatível %2 %3 %n
SOURCE %0:%1, NEGATIVE INDEX %d%n	Fonte %0: %1, índice negativo %d %n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	Fonte%0:%1, a seguir para loop com variável de string%n
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	Fonte%0:%1, incompatibilidade de operando ❮%2:%3❯ ❮%4:%5❯%n
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	Fonte%0:%1, erro de lógica matemática de cordas%n
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	Fonte%0:%1, etiqueta indefinida ❮%2❯%n
SOURCE %0:%1, UNHANDLED OP %2%n	Fonte %0: %1, OP não atribuído %2 %n
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	Fonte%0:%1, desconhecido se rótulo ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	Fonte%0:%1, função não reconhecida def ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	Fonte%0:%1, etiqueta Gosub não reconhecida ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	Fonte%0:%1, rótulo Goto não reconhecido ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MATH OP ❮%2❯%n	Fonte%0:%1, matemática não reconhecida ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	Fonte %0: %1, não reconhecido Op %2 %n
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	Fonte%0:%1, não reconhecida a próxima variável ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	Fonte%0:%1, Tipo de variável não reconhecido ❮%2❯%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	Fonte%0:%1, variável ❮%2❯ Definido como Dim%3 (%4 ..%5,%6 ..%7) Matriz na linha%8%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	Fonte%0:%1, variável ❮%2❯ Definido como Dim%3 (%4 ..%5) Matriz on -line%6%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	Fonte%0:%1, variável ❮%2❯ Definido como Dim%3 Array na linha%4%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	Fonte%0:%1, variável ❮%2❯ Definido como não -marge on -line%3%n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	Fonte %0: %1, variável ❮ %2❯ DIM1 como %3 limites externos1 %4 .. %5 da linha %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	Fonte %0: %1, variável ❮ %2❯ DIM1 como %3 Limites externos %4 .. %5 da linha %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	Fonte %0: %1, variável ❮ %2❯ Dim2 como %3 Limites externos2 %4 .. %5 da linha %6 %n
UNABLE TO OPEN %0 FOR READING.%n	Incapaz de abrir %0 para leitura. %n
UNABLE TO OPEN FILE ❮%0❯%n	Incapaz de abrir o arquivo ❮%0❯%n
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	Opcode não atendido SRC: %0 OP %1 linha %2 col %3 %n
UNRECOGNIZED INPUT ❮%0❯%n	Entrada não reconhecida ❮%0❯%n
