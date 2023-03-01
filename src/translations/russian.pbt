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
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.	И нет языка, не указанного в командной строке. Выход.
ARRAY ALREADY DEFINED	Массив уже определен
ARRAY INDEX OUTSIDE OF BOUNDS	Массив индекс за пределами
CANNOT ACCESS DIRECTORY	Не может получить доступ к каталогу
DATA INPUT UNDERFLOW	Вход данных в разделе
DATA READ UNDERFLOW	Данные прочитали недостаток
DEFINITION CYCLE DISCOVERED	Цикл определения обнаружено
ERROR	ОШИБКА
FOR VARIABLE MULTIPLY DEFINED	Для переменной умноженной определенной
FUNCTION DEFINITION MULTIPLY DEFINED	Определение функции умноженное определено
FUNCTION DEFINITION PARAMETER MISMATCH	Определение функции несоответствие параметров
GOSUB STACK OVERFLOW	Госуб стек переполнен
GOSUB STACK UNDERFLOW	Gosub Stack hoonflow
INDEX OUT OF RANGE	Указатель
LABEL ALREADY DEFINED	Метка уже определен
LEFT / RIGHT OPERATION MISMATCH	Несоответствие левой / правой операции
NEGATIVE INDEX	Отрицательный индекс
NEXT ON FOR LOOP WITH STRING VARIABLE	Далее для петли с переменной строки
OPERAND MISMATCH	Операнд несоответствие
OPTION REQUIRES A LANGUAGE	Вариант требует языка
PLEASE CHECK LANGUAGE SETTINGS OR ENVIRONMENT VARIABLE	Пожалуйста, проверьте настройки языка или переменную среды
STRING MATH LOGIC ERROR	Ошибка математической логики строки
UNABLE TO OPEN FILE	НЕВОЗМОЖНО ОТКРЫТЬ ФАЙЛ
UNABLE TO OPEN TO OPEN FILE FOR READING	Невозможно открыть для открытия файла для чтения
UNDEFINED LABEL	Неопределенная этикетка
UNHANDLED OPERATION	Неупомянутая операция
UNHANDLED OPERATION CODE	Код операции нездоровой
UNKNOWN IF LABEL	Неизвестно, если этикетка
UNRECOGNIZED DOUBLE MATH OPERATION	Нераспознанная двойная математическая операция
UNRECOGNIZED FUNCTION FUNCTION DEFINITION	Определение функции нерасположенной функции
UNRECOGNIZED GOSUB LABEL	Непознанный лейбл Госуба
UNRECOGNIZED GOTO LABEL	Непознанный лейбл Goto
UNRECOGNIZED INPUT	Непознанный вход
UNRECOGNIZED INTEGER MATH OPERATION	Непознанная целочисленная математическая операция
UNRECOGNIZED MATH TYPE	Непознанный математический тип
UNRECOGNIZED NEXT VARIABLE	Непознанная следующая переменная
UNRECOGNIZED OP IN PRINT	Непознанный OP в печати
UNRECOGNIZED RATIONAL MATH OPERATION	Нераспознанная рациональная математическая операция
UNRECOGNIZED VARIABLE TYPE	Непознанный тип переменной
UNSET ENVIRONMENT VARIABLE	Неоткрытая переменная среды
VARIABLE / ARRAY DEFINITION MISMATCH	Несоответствие определения переменной / массива
VARIABLE DEFINED AS ARRAY	Переменная, определенная как массив
VARIABLE DEFINED AS NONARRAY	Переменная, определяемая как nonArray
VARIABLE HAS NO VALUE	Переменная не имеет значения
VARIABLE IS NOT AN ARRAY	Переменная не массив
