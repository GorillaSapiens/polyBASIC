####
# autotranslation for the "arabic" language
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

END <= نهاية                  # the end statement

# from ECMA-55 §9

ABS <= قيمهمطلقه              # the absolute value function
ATN <= عكسالظل                # the trigonomic arctangent function
COS <= جيبالتمام              # the trigonomic cosine function
EXP <= متسارع                 # the exponential / power function
INT <= عددصحيح                # the integer / floor function
LOG <= لوغاريتم               # the natural log function
RND <= لفافة                  # generate random number
SGN <= لافتة                  # determine the sign
SIN <= جيب                    # the trigonomic sine function
SQR <= الجذرالتربيعي          # the square root function
TAN <= الظل                   # the trigonomic tangent function
DBL <= مزدوج                  # convert to double
STR <= نص                     # convert to string
RAT <= عاقل                   # convert to rational

# from ECMA-55 §10

DEF <= يعرف                   # for user defined functions

# from ECMA-55 §11

LET <= يترك                   # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= يذهب                    # part of the GOTO and GOSUB
GOSUB <= يتصل                 # formed from GO and SUB if no direct translation exists
GOTO <= القفز                 # formed from GO and TO if no direct translation exists
TO <= ل                       # part of for/to/step/next constructs
IF <= لو                      # part of if/then constructs
THEN <= ثم                    # part of if/then constructs
SUB <= الفرعية                # beware, used as part of "go sub"
ON <= يحول                    # a sort of a switch statement
RETURN <= يعود                # used to exit a subroutine
STOP <= تمالانتهاءمن          # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= من                     # part of for/to/step/next constructs
STEP <= خطوة                  # part of for/to/step/next constructs
NEXT <= التالي                # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= مطبعة                # to print things out

# from ECMA-55 §15

INPUT <= مدخل                 # the input statement

# from ECMA-55 §16

READ <= يقرأ                  # part of read / restore
RESTORE <= إعادةالقراءة       # part of read / restore

# from ECMA-55 §17

DATA <= معلومة                # to embed data in the program

# from ECMA-55 §18

DIM <= البعد                  # dimension arrays
OPTION <= خيار                # see ECMA-55 §18.1
BASE <= قاعدة                 # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= ملاحظة                 # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= عشوائي

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]
❮%0❯ at %1:%2 ->	❮ ٪ 0❯ في ٪ 1: ٪ 2 ->
❮%0❯ at %1:%2%n	❮ ٪ 0❯ في ٪ 1: ٪ 2 ٪ n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	ولا توجد لغة ممنوحة على سطر الأوامر. الخروج. ٪ ن
CANNOT ACCESS DIRECTORY ❮%0❯.%n	لا يمكن الوصول إلى دليل ❮ ٪ 0❯. ٪ n
ERROR: DEFINITION CYCLE DISCOVERED%n	خطأ: دورة التعريف المكتشفة ٪ n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4	خطأ: التسمية ❮ ٪ 0❯ في ٪ 1: ٪ 2 محددة بالفعل ٪ 3: ٪ 4
ERROR: line %0 column %1, ❮%2❯ has no value%n	خطأ: السطر ٪ 0 العمود ٪ 1 ، ❮ ٪ 2❯ ليس له قيمة ٪ n
ERROR: NO PARSE TREE FOR LINE %0%n	خطأ: لا توجد شجرة تحليل للخط ٪ 0 ٪ n
-l requires a language.%n	-L يتطلب لغة. ٪ ن
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	يرجى التحقق من "POLYBASICPATH" المتغير و/أو إعدادات اللغة. ٪ N
POLYBASICLANG' ENVIRONMENT VARIABLE NOT SET,	متغير البيئة POLYBASICLANG غير محدد ،
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	المصدر ٪ 0: ٪ 1 ، صفيف ❮ ٪ 2❯ محدد بالفعل على الخط ٪ 3 ٪ n
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	المصدر ٪ 0: ٪ 1 ، إدخال البيانات underflow ٪ n
SOURCE %0:%1, DATA READ UNDERFLOW%n	المصدر ٪ 0: ٪ 1 ، قراءة البيانات underflow ٪ n
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	المصدر ٪ 0: ٪ 1 ، الدالة def ❮ ٪ 2❯ تتطلب ٪ 3 params ، ولكن دعا مع ٪ 4 ٪ n
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	المصدر ٪ 0: ٪ 1 ، Gosub Stack Overflow ٪ n
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	المصدر ٪ 0: ٪ 1 ، Gosub Stack Underflow ٪ n
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	المصدر ٪ 0: ٪ 1 ، فهرس ٪ 2 من النطاق ٪ ن
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	المصدر ٪ 0: ٪ 1 ، اليسار/اليمين OP عدم التطابق ٪ 2 ٪ 3 ٪ N
SOURCE %0:%1, NEGATIVE INDEX %d%n	المصدر ٪ 0: ٪ 1 ، المؤشر السلبي ٪ d ٪ n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	المصدر ٪ 0: ٪ 1 ، التالي على حلقة مع متغير السلسلة ٪ n
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	المصدر ٪ 0: ٪ 1 ، عدم تطابق المعامل ❮ ٪ 2: ٪ 3❯ ❮ ٪ 4: ٪ 5❯ ٪ n
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	المصدر ٪ 0: ٪ 1 ، خطأ في منطق الرياضيات ٪ n
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	المصدر ٪ 0: ٪ 1 ، التسمية غير المحددة ❮ ٪ 2❯ ٪ n
SOURCE %0:%1, UNHANDLED OP %2%n	المصدر ٪ 0: ٪ 1 ، OP ٪ 2 ٪ N
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	المصدر ٪ 0: ٪ 1 ، غير معروف إذا كان التسمية ❮ ٪ 2❯ ٪ n
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	المصدر ٪ 0: ٪ 1 ، وظيفة غير معروفة def ❮ ٪ 2❯ ٪ n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	المصدر ٪ 0: ٪ 1 ، علامة Gosub غير المعترف بها ❮ ٪ 2❯ ٪ N
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	المصدر ٪ 0: ٪ 1 ، ملصق GOTO غير المعترف به ❮ ٪ 2❯ ٪ N
SOURCE %0:%1, UNRECOGNIZED MATH OP ❮%2❯%n	المصدر ٪ 0: ٪ 1 ، الرياضيات غير المعترف بها OP ❮ ٪ 2❯ ٪ N
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	المصدر ٪ 0: ٪ 1 ، Mid Op ٪ 2 ٪ N غير المعترف به
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	المصدر ٪ 0: ٪ 1 ، المتغير التالي غير المعترف به ❮ ٪ 2❯ ٪ n
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	المصدر ٪ 0: ٪ 1 ، النوع المتغير غير المعترف به ❮ ٪ 2❯ ٪ n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	المصدر ٪ 0: ٪ 1 ، المتغير ❮ ٪ 2❯ محدد على أنه dim ٪ 3 (٪ 4 .. ٪ 5 ، ٪ 6 .. ٪ 7) صفيف في الخط ٪ 8 ٪ n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	المصدر ٪ 0: ٪ 1 ، المتغير ❮ ٪ 2❯ محدد على أنه DIM ٪ 3 (٪ 4 .. ٪ 5) صفيف في الخط ٪ 6 ٪ n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	المصدر ٪ 0: ٪ 1 ، المتغير ❮ ٪ 2❯ محدد على أنه dim ٪ 3 صفيف في الخط ٪ 4 ٪ n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	المصدر ٪ 0: ٪ 1 ، المتغير ❮ ٪ 2❯ المعرّف بأنه غير محدد على الخط ٪ 3 ٪ n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	المصدر ٪ 0: ٪ 1 ، المتغير ❮ ٪ 2❯ DIM1 AS ٪ 3 خارج الحدود 1 ٪ 4 .. ٪ 5 من الخط ٪ 6 ٪ n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	المصدر ٪ 0: ٪ 1 ، المتغير ❮ ٪ 2❯ DIM1 AS ٪ 3 خارج الحدود ٪ 4 .. ٪ 5 من الخط ٪ 6 ٪ n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	المصدر ٪ 0: ٪ 1 ، المتغير ❮ ٪ 2❯ DIM2 AS ٪ 3 خارج الحدود 2 ٪ 4 .. ٪ 5 من الخط ٪ 6 ٪ n
UNABLE TO OPEN %0 FOR READING.%n	غير قادر على فتح ٪ 0 للقراءة. ٪ ن
UNABLE TO OPEN FILE ❮%0❯%n	غير قادر على فتح ملف ❮ ٪ 0❯ ٪ n
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	OPCODE UNHEDLED SRC: ٪ 0 OP ٪ 1 LINE ٪ 2 COL ٪ 3 ٪ N
UNRECOGNIZED INPUT ❮%0❯%n	المدخلات غير المعترف بها ❮ ٪ 0❯ ٪ n
