####
# autotranslation for the "russian" language
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

END <= КОНЕЦ                        # the end statement

# from ECMA-55 §9

ABS <= АБСОЛЮТНАЯВЕЛИЧИНА           # the absolute value function
ATN <= ОБРАТНАЯКАСАТЕЛЬНАЯ          # the trigonomic arctangent function
COS <= КОСИНУС                      # the trigonomic cosine function
EXP <= ЭКСПОНЕНЦИАЛЬНЫЙ             # the exponential / power function
INT <= ЦЕЛОЕЧИСЛО                   # the integer / floor function
LOG <= ЛОГАРИФМ                     # the natural log function
RND <= РУЛОН                        # generate random number
SGN <= ЗНАК                         # determine the sign
SIN <= СИНУС                        # the trigonomic sine function
SQR <= КВАДРАТНЫЙКОРЕНЬ             # the square root function
TAN <= ТАНГЕНС                      # the trigonomic tangent function
DBL <= ДВОЙНОЙ                      # convert to double
STR <= ТЕКСТ                        # convert to string
RAT <= РАЦИОНАЛЬНЫЙ                 # convert to rational

# from ECMA-55 §10

DEF <= ОПРЕДЕЛЯТЬ                   # for user defined functions

# from ECMA-55 §11

LET <= ПОЗВОЛЯТЬ                    # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= ИДТИ                          # part of the GOTO and GOSUB
GOSUB <= ВЫЗОВ                      # formed from GO and SUB if no direct translation exists
GOTO <= ПРЫГАТЬ                     # formed from GO and TO if no direct translation exists
TO <= К                             # part of for/to/step/next constructs
IF <= ЕСЛИ                          # part of if/then constructs
THEN <= ЗАТЕМ                       # part of if/then constructs
SUB <= ПОДСТАВКА                    # beware, used as part of "go sub"
ON <= ВЫКЛЮЧАТЕЛЬ                   # a sort of a switch statement
RETURN <= ВОЗВРАЩАТЬСЯ              # used to exit a subroutine
STOP <= ЗАКОНЧЕННЫЙ                 # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= ОТ                           # part of for/to/step/next constructs
STEP <= ШАГ                         # part of for/to/step/next constructs
NEXT <= СЛЕДУЮЩИЙ                   # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= РАСПЕЧАТАТЬ                # to print things out

# from ECMA-55 §15

INPUT <= ВХОД                       # the input statement

# from ECMA-55 §16

READ <= ЧИТАТЬ                      # part of read / restore
RESTORE <= ПЕРЕЧИТЫВАТЬ             # part of read / restore

# from ECMA-55 §17

DATA <= ИНФОРМАЦИЯ                  # to embed data in the program

# from ECMA-55 §18

DIM <= ИЗМЕРЕНИЕ                    # dimension arrays
OPTION <= ВАРИАНТ                   # see ECMA-55 §18.1
BASE <= БАЗА                        # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= ПРИМЕЧАНИЕ                   # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= РАНДОМИЗИРОВАТЬ

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]
❮%0❯ at %1:%2 ->%b	❮%0❯ AT%1:%2 ->%b
❮%0❯ at %1:%2%n	❮%0❯ AT%1:%2%n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	И нет языка, не указанного в командной строке. Выход.%n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	Невозможно получить доступ к каталогу ❮%0❯.%n
ERROR: def ❮%0❯ multiply defined %1:%2 and %3:%4%n	Ошибка: def ❮%0❯ Умноженное определено%1:%2 и%3:%4%n
ERROR: DEFINITION CYCLE DISCOVERED%n	Ошибка: цикл определения обнаружена%n
ERROR: for ❮%0❯ multiply defined %1:%2 and %3:%4%n	Ошибка: для ❮%0❯ Умноженное определение%1:%2 и%3:%4%n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n	Ошибка: метка ❮%0❯%1:%2 уже определено%3:%4%n
ERROR: line %0 column %1, ❮%2❯ has no value%n	Ошибка: Line %0 Column %1, ❮ %2❯ не имеет значения %n
ERROR: NO PARSE TREE FOR LINE %0%n	Ошибка: нет дерева разбора для линии %0 %n
-l requires a language.%n	-l требует языка.%n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	Пожалуйста, проверьте переменную среды POLYBASICPATH и/или языковые настройки.%n
POLYBASICLANG' ENVIRONMENT VARIABLE NOT SET,	POLYBASICLANG 'переменная среды не установлена,
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	Источник%0:%1, массив ❮%2❯ уже определен на линии%3%n
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	Источник%0:%1, ввод данных под разделение потока%n
SOURCE %0:%1, DATA READ UNDERFLOW%n	Источник%0:%1, Data Read Underflow%n
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	Источник %0: %1, Функция def ❮ %2❯ требует %3 параметров, но вызовов с 4 %n
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	Источник%0:%1, gosub Stack Overflow%n
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	Источник%0:%1, gosub Stack inderflow%n
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	Источник %0: %1, индекс %2 из диапазона %n
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	Источник %0: %1, слева/правое несоответствие OP %2 %3 %n
SOURCE %0:%1, NEGATIVE INDEX %d%n	Источник %0: %1, отрицательный индекс %d %n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	Источник%0:%1, следующий для цикла с помощью строковой переменной%n
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	Источник%0:%1, несоответствие операнда ❮%2:%3❯%4:%5❯%n
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	Источник%0:%1, строка математическая логика ошибка%n
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	Источник%0:%1, неопределенная метка ❮%2❯%n
SOURCE %0:%1, UNHANDLED OP %2%n	Источник %0: %1, Unlended OP %2 %n
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	Источник%0:%1, неизвестно, если метка ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	Источник%0:%1, непризнанная функция def ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	Источник%0:%1, непризнанная метка Gosub ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	Источник%0:%1, непризнанная метка goto ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MATH OP ❮%2❯%n	Источник%0:%1, непризнанная математика op ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	Источник %0: %1, непризнанная середина OP %2 %n
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	Источник%0:%1, непризнанная следующая переменная ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	Источник%0:%1, непризнанный тип переменной ❮%2❯%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	Источник%0:%1, переменная ❮%2
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	Источник%0:%1, переменная ❮%2❯ определено как Dim%3 (%4 ..%5) массив на линию%6%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	Источник%0:%1, переменная ❮%2❯ определено как массив Dim%3 на линии%4%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	Источник%0:%1, переменная ❮%2
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	Источник %0: %1, переменная ❮ %2❯ Dim1 As %3 внешние границы1 %4 .. %5 от линии %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	Источник %0: %1, переменная ❮ %2❯ Dim1 As %3 внешние границы %4 .. %5 из линии %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	Источник %0: %1, переменная ❮ %2❯ Dim2 As %3 внешние границы 2 %4 .. %5 от линии %6 %n
UNABLE TO OPEN %0 FOR READING.%n	Невозможно открыть %0 для чтения. %n
UNABLE TO OPEN FILE ❮%0❯%n	Невозможно открыть файл ❮%0❯%n
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	Неупомянутый OpCode SRC: %0 OP %1 Line %2 COL %3 %n
UNRECOGNIZED INPUT ❮%0❯%n	Нераспознанный вход ❮%0❯%n
