####
# autotranslation for the "korean" language
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

END <= 끝             # the end statement

# from ECMA-55 §9

ABS <= 절대가치          # the absolute value function
ATN <= 역탄젠트          # the trigonomic arctangent function
COS <= 코사인           # the trigonomic cosine function
EXP <= 지수            # the exponential / power function
INT <= 정수            # the integer / floor function
LOG <= 로그            # the natural log function
RND <= 롤             # generate random number
SGN <= 징후            # determine the sign
SIN <= 사인            # the trigonomic sine function
SQR <= 제곱근           # the square root function
TAN <= 접선            # the trigonomic tangent function
DBL <= 더블            # convert to double
STR <= 텍스트           # convert to string
RAT <= 합리적인          # convert to rational

# from ECMA-55 §10

DEF <= 정의하다          # for user defined functions

# from ECMA-55 §11

LET <= 허락하다          # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= 가다             # part of the GOTO and GOSUB
GOSUB <= 부르다         # formed from GO and SUB if no direct translation exists
GOTO <= 도약           # formed from GO and TO if no direct translation exists
TO <= 에게             # part of for/to/step/next constructs
IF <= 만약에            # part of if/then constructs
THEN <= 그다음에         # part of if/then constructs
SUB <= 보결            # beware, used as part of "go sub"
ON <= 스위치            # a sort of a switch statement
RETURN <= 반품         # used to exit a subroutine
STOP <= 완성된          # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= 에서            # part of for/to/step/next constructs
STEP <= 단계           # part of for/to/step/next constructs
NEXT <= 다음           # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= 인쇄          # to print things out

# from ECMA-55 §15

INPUT <= 입력          # the input statement

# from ECMA-55 §16

READ <= 읽다           # part of read / restore
RESTORE <= 다시읽었습니다   # part of read / restore

# from ECMA-55 §17

DATA <= 정보           # to embed data in the program

# from ECMA-55 §18

DIM <= 치수            # dimension arrays
OPTION <= 옵션         # see ECMA-55 §18.1
BASE <= 베이스          # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= 주목            # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= 무작위화

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]
❮%0❯ at %1:%2 ->	❮%0%at%1 :%2->
❮%0❯ at %1:%2%n	❮%0%at%1 :%2%n
AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.%n	그리고 명령 줄에는 언어가 없습니다. 출구.%n
CANNOT ACCESS DIRECTORY ❮%0❯.%n	디렉토리에 액세스 할 수 없습니다
ERROR: DEFINITION CYCLE DISCOVERED%n	오류 : 정의주기 발견%n
ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n	오류 : 레이블 ❯%0❮ at%1 :%2 이미 정의 된%3 :%4%n
ERROR: line %0 column %1, ❮%2❯ has no value%n	오류 : line %0 열 %1, ❮ %2❯ 값이 없습니다.
ERROR: NO PARSE TREE FOR LINE %0%n	오류 : 라인 %0 %n에 대한 구문 분석 트리 없음
-l requires a language.%n	-L 언어가 필요합니다.%n
PLEASE CHECK 'POLYBASICPATH' ENVIRONMENT VARIABLE AND/OR LANGUAGE SETTINGS.%n	'POLYBASICPATH'환경 변수 및/또는 언어 설정을 확인하십시오.%n
POLYBASICLANG' ENVIRONMENT VARIABLE NOT SET,	Poly -Basiclang 'Environment 변수 설정되지 않음
SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n	Source%0 :%1, 배열 ❮%2 ❯ 이미 라인에 정의 된%3%n
SOURCE %0:%1, DATA INPUT UNDERFLOW%n	소스%0 :%1, 데이터 입력 언더 플로우%n
SOURCE %0:%1, DATA READ UNDERFLOW%n	소스%0 :%1, 데이터 읽기 언더 플로%n
SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n	Source %0 : %1, 기능 def ❮ %2❯는 %3 매개 변수를 필요로하지만 %4 %n으로 호출됩니다.
SOURCE %0:%1, GOSUB STACK OVERFLOW%n	소스%0 :%1, Gosub 스택 오버플로%n
SOURCE %0:%1, GOSUB STACK UNDERFLOW%n	소스%0 :%1, Gosub 스택 언더 플로%n
SOURCE %0:%1, INDEX %2 OUT OF RANGE%n	소스 %0 : %1, 색인 %2 범위 %n
SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n	소스 %0 : %1, 왼쪽/오른쪽 OP 불일치 %2 %3 %n
SOURCE %0:%1, NEGATIVE INDEX %d%n	소스 %0 : %1, 음의 지수 %d %n
SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n	Source%0 :%1, 문자열 변수%n을 가진 루프에 대한 다음 on
SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n	Source%0 :%1, 오페라 불일치 ❮%2 :%3❯%4 :%5 ❯%n
SOURCE %0:%1, STRING MATH LOGIC ERROR%n	소스%0 :%1, 문자열 수학 로직 오류%n
SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n	Source%0 :%1, 정의되지 않은 레이블 ❮%2❯%n
SOURCE %0:%1, UNHANDLED OP %2%n	Source %0 : %1, 취급되지 않은 OP %2 %n
SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n	Source%0 :%1, 알 수없는 레이블 ❮%2 ❯%n
SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n	Source%0 :%1, 인식되지 않은 기능 def ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n	Source%0 :%1, 인식되지 않은 Gosub 레이블 ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n	Source%0 :%1, 인식되지 않은 Goto 레이블 ❮%2 ❯%n
SOURCE %0:%1, UNRECOGNIZED MATH OP ❮%2❯%n	Source%0 :%1, 인식되지 않은 수학 OP ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED MID OP %2%n	Source %0 : %1, 인식되지 않은 중간 OP %2 %n
SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n	Source%0 :%1, 인식되지 않은 다음 변수 ❮%2❯%n
SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n	Source%0 :%1, 인식되지 않은 가변 유형 ❮%2❯%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n	소스%0 :%1, 변수 ❮%2❯ Dim%3 (%4 ..%5,%6 ..%7) 배열%8%n으로 정의됩니다.
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n	소스%0 :%1, 변수 ❮%2❯ Dim%3 (%4 ..%5) 라인에 대한 배열%6%n
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n	소스%0 :%1, 변수 ❮%2❯ 라인에서 Dim%3 어레이로 정의
SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n	소스%0 :%1, 변수 ❮%2❯ 라인에서 비 체류로 정의 된%3%n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n	소스 %0 : %1, 변수 ❮ %2 ❯ dim1 as %3 외부 경계 1 %4 .. %5 라인 %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n	소스 %0 : %1, 변수 ❮ %2 ❯ dim1 as %3 외부 경계 %4 .. %5 라인 %6 %n
SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n	소스 %0 : %1, 변수 ❮ %2 ❯ dim2 as %3 외부 경계 2 %4 .. %5 라인 %6 %n
UNABLE TO OPEN %0 FOR READING.%n	읽기를 위해 %0을 열 수 없습니다. %n
UNABLE TO OPEN FILE ❮%0❯%n	파일을 열 수 없음 file%0❯%n
UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n	처리되지 않은 OPCODE SRC : %0 OP %1 라인 %2 COL %3 %n
UNRECOGNIZED INPUT ❮%0❯%n	인식되지 않은 입력 ized%0 ❯%n
