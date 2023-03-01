####
# autotranslation for the "urdu" language
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

END <= آخر                 # the end statement

# from ECMA-55 §9

ABS <= مطلققیمت            # the absolute value function
ATN <= الٹاٹینجنٹ          # the trigonomic arctangent function
COS <= کوسائن              # the trigonomic cosine function
EXP <= کفایتشعاری          # the exponential / power function
INT <= انٹیجر              # the integer / floor function
LOG <= لوگرتھم             # the natural log function
RND <= رول                 # generate random number
SGN <= دستخطکریں           # determine the sign
SIN <= SINE                # the trigonomic sine function
SQR <= مربعجڑ              # the square root function
TAN <= ٹینجینٹ             # the trigonomic tangent function
DBL <= دگنا                # convert to double
STR <= متن                 # convert to string
RAT <= عقلی                # convert to rational

# from ECMA-55 §10

DEF <= وضاحتکریں           # for user defined functions

# from ECMA-55 §11

LET <= دو                  # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= جاؤ                  # part of the GOTO and GOSUB
GOSUB <= کالکریں           # formed from GO and SUB if no direct translation exists
GOTO <= چھلانگ             # formed from GO and TO if no direct translation exists
TO <= TO                   # part of for/to/step/next constructs
IF <= اگر                  # part of if/then constructs
THEN <= پھر                # part of if/then constructs
SUB <= سب                  # beware, used as part of "go sub"
ON <= سوئچ                 # a sort of a switch statement
RETURN <= واپس             # used to exit a subroutine
STOP <= ختم                # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= سے                  # part of for/to/step/next constructs
STEP <= مرحلہ              # part of for/to/step/next constructs
NEXT <= اگلے               # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= پرنٹکریں          # to print things out

# from ECMA-55 §15

INPUT <= انپٹ              # the input statement

# from ECMA-55 §16

READ <= پڑھیں              # part of read / restore
RESTORE <= دوبارہپڑھیں     # part of read / restore

# from ECMA-55 §17

DATA <= معلومات            # to embed data in the program

# from ECMA-55 §18

DIM <= طولوعرض             # dimension arrays
OPTION <= آپشن             # see ECMA-55 §18.1
BASE <= بنیاد              # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= تبصرہ               # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= بےترتیب

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]
❮%0❯ at %1:%2 ->	❮ ٪ 0❯ at 1: ٪ 2 ->
❮%0❯ at %1:%2%n	❮ ٪ 0❯ at 1: ٪ 2 ٪ n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	اور کمانڈ لائن پر کوئی زبان نہیں دی گئی۔ باہر نکلنا۔ ٪ n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	ڈائریکٹری تک رسائی حاصل نہیں کرسکتی ❮ ٪ 0❯. ٪ n
ERROR: DEFINITION CYCLE DISCOVERED%n	غلطی: تعریف سائیکل دریافت ٪ n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n	غلطی: لیبل ❮ ٪ 0❯ at 1: ٪ 2 پہلے ہی وضاحت شدہ ٪ 3: ٪ 4 ٪ n
ERROR: line %0 column %1, ❮%2❯ has no value%n	خرابی: لائن ٪ 0 کالم ٪ 1 ، ❮ ٪ 2❯ کی کوئی قیمت نہیں ہے ٪ n
ERROR: NO PARSE TREE FOR LINE %0%n	غلطی: لائن ٪ 0 ٪ N کے لئے کوئی پارس درخت نہیں
-l requires a language.%n	-l کو ایک زبان کی ضرورت ہے۔ ٪ n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	براہ کرم 'پولی بیسک پاتھ' ماحولیاتی متغیر اور/یا زبان کی ترتیبات کو چیک کریں۔ ٪ N
POLYBASICLANG' ENVIRONMENT VARIABLE NOT SET,	POLYBASICLANG 'ماحولیاتی متغیر مقرر نہیں ،
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	ماخذ ٪ 0: ٪ 1 ، سرنی ❮ ٪ 2❯ لائن پر پہلے ہی بیان کردہ ٪ 3 ٪ n
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	ماخذ ٪ 0: ٪ 1 ، ڈیٹا ان پٹ انڈر فلو ٪ n
SOURCE %0:%1, DATA READ UNDERFLOW%n	ماخذ ٪ 0: ٪ 1 ، ڈیٹا انڈر فلو ٪ N پڑھا
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	ماخذ ٪ 0: ٪ 1 ، فنکشن ڈیف ❮ ٪ 2❯ میں ٪ 3 پیرام کی ضرورت ہوتی ہے ، لیکن ٪ 4 ٪ N کے ساتھ کہا جاتا ہے
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	ماخذ ٪ 0: ٪ 1 ، گوسب اسٹیک اوور فلو ٪ n
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	ماخذ ٪ 0: ٪ 1 ، گوسب اسٹیک انڈر فلو ٪ n
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	ماخذ ٪ 0: ٪ 1 ، انڈیکس ٪ 2 سے باہر کی حد ٪ n
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	ماخذ ٪ 0: ٪ 1 ، بائیں/دائیں اوپی مماثل ٪ 2 ٪ 3 ٪ n
SOURCE %0:%1, NEGATIVE INDEX %d%n	ماخذ ٪ 0: ٪ 1 ، منفی انڈیکس ٪ d ٪ n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	ماخذ ٪ 0: ٪ 1 ، سٹرنگ متغیر ٪ n کے ساتھ لوپ کے لئے اگلا ،
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	ماخذ ٪ 0: ٪ 1 ، اوپیرینڈ مماثل ❮ ٪ 2: ٪ 3❯ ❮ ٪ 4: ٪ 5❯ ٪ n
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	ماخذ ٪ 0: ٪ 1 ، سٹرنگ ریاضی کی منطق کی خرابی ٪ n
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	ماخذ ٪ 0: ٪ 1 ، غیر متعینہ لیبل ❮ ٪ 2❯ ٪ n
SOURCE %0:%1, UNHANDLED OP %2%n	ماخذ ٪ 0: ٪ 1 ، غیر منقولہ اوپی ٪ 2 ٪ n
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	ماخذ ٪ 0: ٪ 1 ، نامعلوم اگر لیبل ❮ ٪ 2❯ ٪ N
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	ماخذ ٪ 0: ٪ 1 ، غیر تسلیم شدہ فنکشن ڈیف ❮ ٪ 2❯ ٪ n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	ماخذ ٪ 0: ٪ 1 ، غیر تسلیم شدہ گوسوب لیبل ❮ ٪ 2❯ ٪ n
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	ماخذ ٪ 0: ٪ 1 ، غیر تسلیم شدہ گوٹو لیبل ❮ ٪ 2❯ ٪ n
SOURCE %0:%1, UNRECOGNIZED MATH OP ❮%2❯%n	ماخذ ٪ 0: ٪ 1 ، غیر تسلیم شدہ ریاضی op ❮ ٪ 2❯ ٪ n
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	ماخذ ٪ 0: ٪ 1 ، غیر تسلیم شدہ وسط او پی ٪ 2 ٪ N
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	ماخذ ٪ 0: ٪ 1 ، غیر تسلیم شدہ اگلی متغیر ❮ ٪ 2❯ ٪ n
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	ماخذ ٪ 0: ٪ 1 ، غیر تسلیم شدہ متغیر قسم ❮ ٪ 2❯ ٪ n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	ماخذ ٪ 0: ٪ 1 ، متغیر ❮ ٪ 2❯ DIM ٪ 3 (٪ 4 .. ٪ 5 ، ٪ 6 .. ٪ 7) کے طور پر بیان کیا گیا ہے
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	ماخذ ٪ 0: ٪ 1 ، متغیر ❮ ٪ 2❯ DIM ٪ 3 (٪ 4 .. ٪ 5) کے طور پر بیان کردہ لائن پر لائن ٪ 6 ٪ N
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	ماخذ ٪ 0: ٪ 1 ، متغیر ❮ ٪ 2❯ لائن پر DIM ٪ 3 سرنی کے طور پر بیان کردہ 4 ٪ N
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	ماخذ ٪ 0: ٪ 1 ، متغیر ❮ ٪ 2❯ لائن پر نانری کے طور پر بیان کردہ ٪ 3 ٪ n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	ماخذ ٪ 0: ٪ 1 ، متغیر ❮ ٪ 2❯ dim1 as ٪ 3 سے باہر کی حد 1 ٪ 4 .. ٪ 5 لائن ٪ 6 ٪ n سے ٪ 5
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	ماخذ ٪ 0: ٪ 1 ، متغیر ❮ ٪ 2❯ Dim1 as ٪ 3 سے باہر ٪ 4 .. ٪ 5 لائن ٪ 6 ٪ N سے ٪ 5
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	ماخذ ٪ 0: ٪ 1 ، متغیر ❮ ٪ 2❯ Dim2 as ٪ 3 سے باہر کی حد 2 ٪ 4 .. ٪ 5 لائن ٪ 6 ٪ N سے ٪ 5
UNABLE TO OPEN %0 FOR READING.%n	پڑھنے کے لئے ٪ 0 کھولنے سے قاصر۔ ٪ n
UNABLE TO OPEN FILE ❮%0❯%n	فائل کھولنے سے قاصر ❮ ٪ 0❯ ٪ n
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	غیر منقولہ اوپکوڈ ایس آر سی: ٪ 0 آپٹ ٪ 1 لائن ٪ 2 کرنل ٪ 3 ٪ n
UNRECOGNIZED INPUT ❮%0❯%n	غیر تسلیم شدہ ان پٹ ❮ ٪ 0❯ ٪ n
