####
# autotranslation for the "hebrew" language
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

END <= סוף                 # the end statement

# from ECMA-55 §9

ABS <= ערךמוחלט            # the absolute value function
ATN <= משיקהפוך            # the trigonomic arctangent function
COS <= קוסינוס             # the trigonomic cosine function
EXP <= מעריכי              # the exponential / power function
INT <= מספרשלם             # the integer / floor function
LOG <= לוגריתם             # the natural log function
RND <= גליל                # generate random number
SGN <= סימן                # determine the sign
SIN <= סינוס               # the trigonomic sine function
SQR <= שורשריבועי          # the square root function
TAN <= משיק                # the trigonomic tangent function
DBL <= להכפיל              # convert to double
STR <= טקסט                # convert to string
RAT <= רציונלי             # convert to rational

# from ECMA-55 §10

DEF <= להגדיר              # for user defined functions

# from ECMA-55 §11

LET <= לתת                 # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= ללכת                 # part of the GOTO and GOSUB
GOSUB <= שיחה              # formed from GO and SUB if no direct translation exists
GOTO <= קפיצה              # formed from GO and TO if no direct translation exists
TO <= ל                    # part of for/to/step/next constructs
IF <= אם                   # part of if/then constructs
THEN <= לאחרמכן            # part of if/then constructs
SUB <= תת                  # beware, used as part of "go sub"
ON <= החלף                 # a sort of a switch statement
RETURN <= לחזור            # used to exit a subroutine
STOP <= גמור               # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= מ                   # part of for/to/step/next constructs
STEP <= שלב                # part of for/to/step/next constructs
NEXT <= הבא                # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= הדפס              # to print things out

# from ECMA-55 §15

INPUT <= קלט               # the input statement

# from ECMA-55 §16

READ <= לקרוא              # part of read / restore
RESTORE <= לקרואמחדש       # part of read / restore

# from ECMA-55 §17

DATA <= מידע               # to embed data in the program

# from ECMA-55 §18

DIM <= ממד                 # dimension arrays
OPTION <= אופציה           # see ECMA-55 §18.1
BASE <= בסיס               # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= הערה                # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= אקראי

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]
❮%0❯ at %1:%2 ->%b	❮%0❯ at%1:%2 ->%b
❮%0❯ at %1:%2%n	❮%0❯ ב%1:%2%n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	ושום שפה ניתנת בשורת הפקודה. יציאה.%n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	לא ניתן לגשת לספריה ❮%0❯.%n
ERROR: def ❮%0❯ multiply defined %1:%2 and %3:%4%n	שגיאה: def ❮%0❯ הכפל%מוגדר%1:%2 ו-%3:%4%n
ERROR: DEFINITION CYCLE DISCOVERED%n	שגיאה: מחזור ההגדרה התגלה%n
ERROR: for ❮%0❯ multiply defined %1:%2 and %3:%4%n	שגיאה: עבור ❮%0❯ הכפלת%מוגדרת%1:%2 ו-%3:%4%n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n	שגיאה: תווית ❮%0❯ at%1:%2 כבר מוגדר%3:%4%n
ERROR: line %0 column %1, ❮%2❯ has no value%n	שגיאה: קו %0 עמודה %1, ❮ %2❯ אין ערך %n
ERROR: NO PARSE TREE FOR LINE %0%n	שגיאה: אין עץ ניתוח עבור קו %0 %n
-l requires a language.%n	-ל דורש שפה.%n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	אנא בדוק משתנה סביבת 'POLYBASICPATH' ו/או הגדרות שפה.%n
POLYBASICLANG' ENVIRONMENT VARIABLE NOT SET,	משתנה הסביבה של POLYBASICLANG לא מוגדר,
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	מקור%0:%1, מערך ❮%2❯ כבר מוגדר על קו%3%n
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	מקור%0:%1, זרימת קלט נתונים%n
SOURCE %0:%1, DATA READ UNDERFLOW%n	מקור%0:%1, נתונים נקראו תחת זרימה%n
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	מקור %0: %1, פונקציה def ❮ %2❯ דורשת %3 פרמטרים, אך נקראת עם %4 %n
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	מקור%0:%1, Gosub Stack Goverflow%n
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	מקור%0:%1, Gosub Stack זרף%n
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	מקור %0: %1, אינדקס %2 מחוץ לטווח %n
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	מקור %0: %1, אי התאמה משמאל/ימין OP %2 %3 %n
SOURCE %0:%1, NEGATIVE INDEX %d%n	מקור %0: %1, אינדקס שלילי %d %n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	מקור%0:%1, הבא לולאה עם משתנה מחרוזת%n
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	מקור%0:%1, אי התאמה של אופרנד ❮%2:%3❯ ❮%4:%5❯%n
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	מקור%0:%1, שגיאת היגיון למתמטיקה של מחרוזת%n
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	מקור%0:%1, תווית לא מוגדרת ❮%2❯%n
SOURCE %0:%1, UNHANDLED OP %2%n	מקור %0: %1, OP %לא מטופלים 2 %n
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	מקור%0:%1, לא ידוע אם התווית ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	מקור%0:%1, פונקציה לא מוכרת def ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	מקור%0:%1, תווית Gosub לא מוכרת ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	מקור%0:%1, תווית GOTO לא מוכרת ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MATH OP ❮%2❯%n	מקור%0:%1, מתמטיקה לא מוכרת ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	מקור %0: %1, לא מוכר באמצע OP %2 %n
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	מקור%0:%1, משתנה הבא לא מוכר ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	מקור%0:%1, סוג משתנה לא מוכר ❮%2❯%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	מקור%0:%1, משתנה ❮%2❯ מוגדר כ- Dim%3 (%4 ..%5,%6 ..%7) מערך על קו%8%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	מקור%0:%1, משתנה ❮%2❯ מוגדר כ- Dim%3 (%4 ..%5) מערך על קו%6%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	מקור%0:%1, משתנה ❮%2❯ המוגדר כמערך dim%3 על קו%4%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	מקור%0:%1, משתנה ❮%2❯ המוגדר כלא מערך בקו%3%n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	מקור %0: %1, משתנה ❮ %2❯ dim1 AS %3 מחוץ לתחום 1 %4 .. %5 מ- LINE %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	מקור %0: %1, משתנה ❮ %2❯ dim1 AS %3 גבולות חיצוניים %4 .. %5 מ- LINE %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	מקור %0: %1, משתנה ❮ %2❯ dim2 AS %3 מחוץ לתחום 2 %4 .. %5 מ- LINE %6 %n
UNABLE TO OPEN %0 FOR READING.%n	לא ניתן לפתוח %0 לקריאה. %n
UNABLE TO OPEN FILE ❮%0❯%n	לא ניתן לפתוח את הקובץ ❮%0❯%n
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	OpCode SRC לא מטופל: %0 OP %1 קו %2 COL %3 %n
UNRECOGNIZED INPUT ❮%0❯%n	קלט לא מוכר ❮%0❯%n
