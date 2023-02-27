####
# ECMA-55 BASIC translations for the Korean language
#
# ECMA-55 can be found at the "Download this standard" button
# at the bottom of
# https://www.ecma-international.org/publications-and-standards/standards/ecma-55/
#
# please forgive me for any errors. i am not
# a native Korean speaker.  these translations
# came from a third party database.
#
# i am certain some of these are embarrassingly wrong,
# and i apologize.
#
# i am also certain some of the longer ones can
# probably be shortened.
#
# this is not the final release file.  this file
# was simply used for testing, because i needed a
# non Latin based script.
#
####
# this file should be utf8
# entries on the left are the actual BASIC keywords
# entries on the right are the native versions of those keywords
# blank lines are allowed

# from ECMA-55 §3.8

# The keywords in Minimal BASIC are: BASE, DATA, DEF, DIM, END,
# FOR, GO, GOSUB, GOTO, IF, INPUT, LET, NEXT, ON, OPTION, PRINT,
# RANDOMIZE, READ, REM, RESTORE, RETURN, STEP, STOP, SUB, THEN
# and TO.

[keywords]

# from ECMA-55 §5

END <= 끝           # the end of program instruction

# from ECMA-55 §9

ABS <= 절대값       # the absolute value function
ATN <= 아탄         # the trigonomic arctangent function
COS <= 코사인       # the trigonomic cosine function
EXP <= 멱지수       # the exponential / power function
INT <= 본질         # the integer / floor function
LOG <= 로그         # the natural log function
RND <= 랜드         # generate random number
SGN <= 징후         # determine the sign
SIN <= 사인         # the trigonomic sine function
SQR <= 제곱         # the square root function
TAN <= 접선         # the trigonomic tangent function
DBL <= 더블         # convert to double
RAT <= 파편         # convert to rational
STR <= 텍스         # convert to string

# from ECMA-55 §10

DEF <= 밝히다       # for user defined functions

# from ECMA-55 §11

LET <= 허용하다     # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= 가다          # possibly used in both "go to" and "go sub"
TO <= 에게          # part of for/to/step/next constructs
IF <= 만약          # part of if/then constructs
THEN <= 그          # part of if/then constructs
SUB <= 보결         # beware, used as part of "go sub"
ON <= 언제          # a sort of a switch statement
RETURN <= 돌아가다  # used to exit a subroutine
STOP <= 멈추다      # command to stop execution
GOTO <= 가다에게    # the GOTO statement
GOSUB <= 가다보결   # the GOSUB statement

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= 각           # part of for/to/step/next constructs
STEP <= 증가        # part of for/to/step/next constructs
NEXT <= 다음        # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= 인쇄       # to print things out

# from ECMA-55 §15

INPUT <= 입력       # the input statement

# from ECMA-55 §16

READ <= 읽다        # part of read / restore
RESTORE <= 복원하다 # part of read / restore

# from ECMA-55 §17

DATA <= 데이터      # to embed data in the program

# from ECMA-55 §18

DIM <= 크기         # dimension arrays
OPTION <= 옵션      # see ECMA-55 §18.1
BASE <= 베이스      # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= 메모          # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= 무작위화하다

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP

[errors]

# error messages

err0|오류: m파일 {0s} 선 {1i} 기둥 {2i}

