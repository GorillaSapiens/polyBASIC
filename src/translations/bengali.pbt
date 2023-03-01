####
# autotranslation for the "bengali" language
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

END <= শষ                   # the end statement

# from ECMA-55 §9

ABS <= পরমমন                # the absolute value function
ATN <= বপরতসপরশকতর          # the trigonomic arctangent function
COS <= কসইন                 # the trigonomic cosine function
EXP <= ততপরযপরণ             # the exponential / power function
INT <= পরণসখয               # the integer / floor function
LOG <= লগরদম                # the natural log function
RND <= রল                   # generate random number
SGN <= চহন                  # determine the sign
SIN <= সইন                  # the trigonomic sine function
SQR <= বরগমল                # the square root function
TAN <= সপরশকতর              # the trigonomic tangent function
DBL <= দবগণ                 # convert to double
STR <= পঠয                  # convert to string
RAT <= যকতসঙগত              # convert to rational

# from ECMA-55 §10

DEF <= সজঞযত                # for user defined functions

# from ECMA-55 §11

LET <= দন                   # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= যওয                   # part of the GOTO and GOSUB
GOSUB <= কল                 # formed from GO and SUB if no direct translation exists
GOTO <= লফ                  # formed from GO and TO if no direct translation exists
TO <= পরত                   # part of for/to/step/next constructs
IF <= যদ                    # part of if/then constructs
THEN <= তরপর                # part of if/then constructs
SUB <= সব                   # beware, used as part of "go sub"
ON <= সযইচ                  # a sort of a switch statement
RETURN <= পরতযবরতন          # used to exit a subroutine
STOP <= সমপত                # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= থক                   # part of for/to/step/next constructs
STEP <= পদকষপ               # part of for/to/step/next constructs
NEXT <= পরবরত               # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= ছপ                 # to print things out

# from ECMA-55 §15

INPUT <= ইনপট               # the input statement

# from ECMA-55 §16

READ <= পডন                 # part of read / restore
RESTORE <= পনরযপডন          # part of read / restore

# from ECMA-55 §17

DATA <= তথয                 # to embed data in the program

# from ECMA-55 §18

DIM <= মতর                  # dimension arrays
OPTION <= বকলপ              # see ECMA-55 §18.1
BASE <= বস                  # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= মনতবয                # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= এলমলভব

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]
❮%0❯ at %1:%2 ->%b	%1 0❯%1:%2 ->%বি এ
❮%0❯ at %1:%2%n	%1 0❯%1:%2%এন
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	এবং কমান্ড লাইনে কোনও ভাষা দেওয়া হয়নি। প্রস্থান।%n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	ডিরেক্টরি অ্যাক্সেস করতে পারে না ❮%0❯।%n
ENVIRONMENT VARIABLE 'POLYBASICLANG' NOT SET,	পরিবেশ পরিবর্তনশীল 'পলিবাসিক্ল্যাং' সেট করা হয়নি,
ERROR: def ❮%0❯ multiply defined %1:%2 and %3:%4%n	ত্রুটি: ডিএফ ❮%0❯ গুণিত সংজ্ঞায়িত%1:%2 এবং%3:%4%এন
ERROR: DEFINITION CYCLE DISCOVERED%n	ত্রুটি: সংজ্ঞা চক্র%n আবিষ্কার করেছে
ERROR: for ❮%0❯ multiply defined %1:%2 and %3:%4%n	ত্রুটি: ❮%0 ❯ গুণিত সংজ্ঞায়িত%1:%2 এবং%3:%4%এন
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n	ত্রুটি:%1 এ লেবেল ❮%0❯:%2 ইতিমধ্যে সংজ্ঞায়িত%3:%4%এন
ERROR: line %0 column %1, ❮%2❯ has no value%n	ত্রুটি: লাইন %0 কলাম %1, ❮ %2❯ এর কোনও মান %এন নেই
ERROR: NO PARSE TREE FOR LINE %0%n	ত্রুটি: লাইন %0 %এন এর জন্য পার্স ট্রি নেই
-l requires a language.%n	-এল একটি ভাষা প্রয়োজন।%n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	দয়া করে 'পলিবাসিকপথ' পরিবেশের পরিবর্তনশীল এবং/অথবা ভাষার সেটিংস পরীক্ষা করুন।%n
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	উত্স%0:%1, অ্যারে ❮%2❯ ইতিমধ্যে লাইন%3%এন এ সংজ্ঞায়িত
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	উত্স%0:%1, ডেটা ইনপুট আন্ডারফ্লো%এন
SOURCE %0:%1, DATA READ UNDERFLOW%n	উত্স%0:%1, ডেটা রিড আন্ডারফ্লো%এন
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	উত্স %0: %1, ফাংশন ডিএফ ❮ %2❯ এর জন্য %3 প্যারাম প্রয়োজন, তবে %4 %এন দিয়ে কল করা হয়
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	উত্স%0:%1, গোসব স্ট্যাক ওভারফ্লো%এন
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	উত্স%0:%1, গোসব স্ট্যাক আন্ডারফ্লো%এন
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	উত্স %0: %1, সূচক %2 রেঞ্জের বাইরে %এন
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	উত্স %0: %1, বাম/ডান ওপি মেলে  %%2 %3 %এন
SOURCE %0:%1, NEGATIVE INDEX %d%n	উত্স %0: %1, নেতিবাচক সূচক %d %n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	উত্স%0:%1, স্ট্রিং ভেরিয়েবল%এন সহ লুপের জন্য পরবর্তী
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	উত্স%0:%1, অপারেন্ড অমিল ❮%2:%3❯ ❮%4:%5❯%এন
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	উত্স%0:%1, স্ট্রিং ম্যাথ লজিক ত্রুটি%এন
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	উত্স%0:%1, অপরিজ্ঞাত লেবেল ❮%2❯%এন
SOURCE %0:%1, UNHANDLED OP %2%n	উত্স %0: %1, আনহ্যান্ডড ওপি %2 %এন
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	উত্স%0:%1, অজানা যদি লেবেল ❮%2❯%এন
SOURCE %0:%1, UNRECOGNIZED DOUBLE MATH OP ❮%2❯%n	উত্স%0:%1, অচেনা ডাবল ম্যাথ অপ ❮%2❯%এন
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	উত্স%0:%1, অচেনা ফাংশন ডিএফ ❮%2❯%এন
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	উত্স%0:%1, অচেনা গোসব লেবেল ❮%2❯%এন
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	উত্স%0:%1, অচেনা গোটো লেবেল ❮%2❯%এন
SOURCE %0:%1, UNRECOGNIZED INTEGER MATH OP ❮%2❯%n	উত্স%0:%1, অচেনা পূর্ণসংখ্যা গণিত অপ ❮%2❯%এন
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	উত্স %0: %1, অচেনা মিড ওপ %2 %এন
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	উত্স%0:%1, স্বীকৃত পরবর্তী পরিবর্তনশীল ❮%2❯%এন
SOURCE %0:%1, UNRECOGNIZED RATIONAL MATH OP ❮%2❯%n	উত্স%0:%1, অচেনা যুক্তিযুক্ত গণিত অপ ❮%2❯%এন
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	উত্স%0:%1, অচেনা পরিবর্তনশীল প্রকার ❮%2❯%এন
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	উত্স%0:%1, ভেরিয়েবল ❮%2❯ ম্লান%3 (%4 ..%5,%6 ..%7) হিসাবে সংজ্ঞায়িত
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	উত্স%0:%1, ভেরিয়েবল ❮%2❯ ডিম%3 (%4 ..%5) লাইন অন লাইন%6%এন হিসাবে সংজ্ঞায়িত
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	উত্স%0:%1, পরিবর্তনশীল ❮%2❯ লাইন%4%এন এ ডিম%3 অ্যারে হিসাবে সংজ্ঞায়িত
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	উত্স%0:%1, ভেরিয়েবল ❮%2❯ লাইনে ননআরে হিসাবে সংজ্ঞায়িত%3%এন
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	উত্স %0: %1, পরিবর্তনশীল ❮ %2❯ DIM1 হিসাবে %3 এর বাইরে সীমা 1 %4 .. %5 লাইন থেকে %6 %এন
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	উত্স %0: %1, পরিবর্তনশীল ❮ %2❯ DIM1 হিসাবে %3 এর বাইরে %3 %4 .. %5 লাইন থেকে %6 %এন
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	উত্স %0: %1, পরিবর্তনশীল ❮ %2❯ DIM2 হিসাবে %3 এর বাইরে 2 %4 .. %5 লাইন থেকে %6 %এন
UNABLE TO OPEN %0 FOR READING.%n	পড়ার জন্য %0 খুলতে অক্ষম। %n
UNABLE TO OPEN FILE ❮%0❯%n	ফাইল খুলতে অক্ষম ❮%0❯%এন
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	Unhandled opcode src: %0 op %1 লাইন %2 কল %3 %n
UNRECOGNIZED INPUT ❮%0❯%n	অচেনা ইনপুট ❮%0❯%n
