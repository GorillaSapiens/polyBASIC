####
# autotranslation for the "hindi" language
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

END <= अत                 # the end statement

# from ECMA-55 §9

ABS <= नरपकषमलय           # the absolute value function
ATN <= उलटसपरशरख          # the trigonomic arctangent function
COS <= कजय                # the trigonomic cosine function
EXP <= घतय                # the exponential / power function
INT <= परणक               # the integer / floor function
LOG <= लगरतम              # the natural log function
RND <= लढकन               # generate random number
SGN <= सकत                # determine the sign
SIN <= जय                 # the trigonomic sine function
SQR <= वरगमल              # the square root function
TAN <= सपरशरख             # the trigonomic tangent function
DBL <= दहर                # convert to double
STR <= मलपठ               # convert to string
RAT <= तरकसगत             # convert to rational

# from ECMA-55 §10

DEF <= परभषतकरन           # for user defined functions

# from ECMA-55 §11

LET <= हनदन               # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= जन                  # part of the GOTO and GOSUB
GOSUB <= पकरन             # formed from GO and SUB if no direct translation exists
GOTO <= कदन               # formed from GO and TO if no direct translation exists
TO <= क                   # part of for/to/step/next constructs
IF <= अगर                 # part of if/then constructs
THEN <= तब                # part of if/then constructs
SUB <= वषय                # beware, used as part of "go sub"
ON <= बदलन                # a sort of a switch statement
RETURN <= वपसकरन          # used to exit a subroutine
STOP <= खतम               # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= स                  # part of for/to/step/next constructs
STEP <= कदम               # part of for/to/step/next constructs
NEXT <= अगल               # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= परट              # to print things out

# from ECMA-55 §15

INPUT <= इनपट             # the input statement

# from ECMA-55 §16

READ <= पढन               # part of read / restore
RESTORE <= कफरसपढ         # part of read / restore

# from ECMA-55 §17

DATA <= जनकर              # to embed data in the program

# from ECMA-55 §18

DIM <= आयम                # dimension arrays
OPTION <= वकलप            # see ECMA-55 §18.1
BASE <= आधर               # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= टपपण               # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= अनयमत

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]
❮%0❯ at %1:%2 ->	❮%0 ❮%1:%2 -> पर
❮%0❯ at %1:%2%n	❮%0 ❮%1 पर:%2%n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	और कमांड लाइन पर कोई भाषा नहीं दी गई है। बाहर निकलना।%n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	निर्देशिका ❮%0❯ तक पहुंच नहीं सकते।%n
ERROR: DEFINITION CYCLE DISCOVERED%n	त्रुटि: परिभाषा चक्र की खोज%n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4	त्रुटि: लेबल ❮%0❯%1 पर:%2 पहले से ही परिभाषित%3:%4
ERROR: line %0 column %1, ❮%2❯ has no value%n	त्रुटि: लाइन %0 कॉलम %1, ❮ %2❯ का कोई मूल्य %n नहीं है
ERROR: NO PARSE TREE FOR LINE %0%n	त्रुटि: लाइन %0 %n के लिए कोई पार्स पेड़ नहीं
-l requires a language.%n	-एल को एक भाषा की आवश्यकता होती है।%n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	कृपया 'पॉलीबैसिकपाथ' पर्यावरण चर और/या भाषा सेटिंग्स की जाँच करें।%n
POLYBASICLANG' ENVIRONMENT VARIABLE NOT SET,	POLYBASICLANG 'पर्यावरण चर सेट नहीं,
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	स्रोत%0:%1, सरणी ❮%2❯ पहले से ही लाइन%3%एन पर परिभाषित किया गया है
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	स्रोत%0:%1, डेटा इनपुट अंडरफ्लो%n
SOURCE %0:%1, DATA READ UNDERFLOW%n	स्रोत%0:%1, डेटा पढ़ा गया%n%n
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	स्रोत %0: %1, फ़ंक्शन def ❮ %2, के लिए %3 params की आवश्यकता होती है, लेकिन %4 %n के साथ कहा जाता है
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	स्रोत%0:%1, गोसुब स्टैक ओवरफ्लो%n
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	स्रोत%0:%1, गोसुब स्टैक अंडरफ्लो%एन
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	स्रोत %0: %1, सूचकांक %2 रेंज %n से बाहर
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	स्रोत %0: %1, बाएं/दाएं ओपी बेमेल %2 %3 %एन
SOURCE %0:%1, NEGATIVE INDEX %d%n	स्रोत %0: %1, नकारात्मक सूचकांक %d %n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	स्रोत%0:%1, स्ट्रिंग चर%n के साथ लूप के लिए आगे
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	स्रोत%0:%1, ऑपरेंड बेमेल ❮%2:%3 ❮%%4:%5❯%n
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	स्रोत%0:%1, स्ट्रिंग गणित तर्क त्रुटि%n
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	स्रोत%0:%1, अपरिभाषित लेबल ❮%2❯%n
SOURCE %0:%1, UNHANDLED OP %2%n	स्रोत %0: %1, अनहेल्दी ओपी %2 %एन
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	स्रोत%0:%1, अज्ञात यदि लेबल ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	स्रोत%0:%1, अपरिचित फ़ंक्शन def ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	स्रोत%0:%1, बिना मान्यता प्राप्त गोसुब लेबल ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	स्रोत%0:%1, गैर -मान्यता प्राप्त गोटो लेबल ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MATH OP ❮%2❯%n	स्रोत%0:%1, अपरिचित गणित ओपी of%2❯%एन
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	स्रोत %0: %1, अपरिचित मध्य op %2 %n
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	स्रोत%0:%1, बिना मान्यता प्राप्त अगला चर ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	स्रोत%0:%1, अपरिचित चर प्रकार ❮%2 of%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	स्रोत%0:%1, चर ❮%2❯ को मंद%3 (%4 ..%5,%6 ..%7) के रूप में परिभाषित किया गया
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	स्रोत%0:%1, चर ❮%2❯ को DIM%3 (%4 ..%5) के रूप में परिभाषित किया गया
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	स्रोत%0:%1, चर ❮%2❯ लाइन%4%एन पर dim%3 सरणी के रूप में परिभाषित किया गया
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	स्रोत%0:%1, चर ❮%2❯ लाइन%3%एन पर nonarray के रूप में परिभाषित किया गया
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	स्रोत %0: %1, चर ❮ %2❯ डिम 1 के रूप में %3 के बाहर सीमा 1 %4 .. %5 लाइन %6 %n से
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	स्रोत %0: %1, चर ❮ %2❯ डिम 1 के रूप में %3 के बाहर सीमा %4 .. %5 लाइन %6 %n से
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	स्रोत %0: %1, चर ❮ %2❯ डिम 2 के रूप में %3 के बाहर सीमा 2 %4 .. %5 लाइन %6 %एन से
UNABLE TO OPEN %0 FOR READING.%n	पढ़ने के लिए %0 खोलने में असमर्थ। %n
UNABLE TO OPEN FILE ❮%0❯%n	फ़ाइल को खोलने में असमर्थ ❮%0❯%n
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	Unhandled opcode src: %0 op %1 लाइन %2 col %3 %n
UNRECOGNIZED INPUT ❮%0❯%n	गैर -मान्यता प्राप्त इनपुट ❮%0❯%n
