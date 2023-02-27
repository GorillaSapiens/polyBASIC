####
# autotranslation for the "japanese" language
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

END <= 終わり            # the end statement

# from ECMA-55 §9

ABS <= 絶対値            # the absolute value function
ATN <= 逆の接線           # the trigonomic arctangent function
COS <= 余弦             # the trigonomic cosine function
EXP <= 指数             # the exponential / power function
INT <= 整数             # the integer / floor function
LOG <= 対数             # the natural log function
RND <= ロール            # generate random number
SGN <= サイン            # determine the sign
SIN <= 正弦             # the trigonomic sine function
SQR <= 平方根            # the square root function
TAN <= 正接             # the trigonomic tangent function
DBL <= ダブル            # convert to double
STR <= 文章             # convert to string
RAT <= 合理的な           # convert to rational

# from ECMA-55 §10

DEF <= 定義             # for user defined functions

# from ECMA-55 §11

LET <= させて            # for variable assignment

# from ECMA-55 §12
# NB: ECMA-55 has no ELSE statement

GO <= 行く              # part of the GOTO and GOSUB
GOSUB <= 電話           # formed from GO and SUB if no direct translation exists
GOTO <= ジャンプ          # formed from GO and TO if no direct translation exists
TO <= に               # part of for/to/step/next constructs
IF <= もしも             # part of if/then constructs
THEN <= それから          # part of if/then constructs
SUB <= サブ             # beware, used as part of "go sub"
ON <= スイッチ            # a sort of a switch statement
RETURN <= 戻る          # used to exit a subroutine
STOP <= 終了した          # command to stop execution

# from ECMA-55 §13
# NB: translation for TO is in §12

FOR <= から             # part of for/to/step/next constructs
STEP <= ステップ          # part of for/to/step/next constructs
NEXT <= 次             # part of for/to/step/next constructs

# from ECMA-55 §14

PRINT <= 印刷           # to print things out

# from ECMA-55 §15

INPUT <= 入力           # the input statement

# from ECMA-55 §16

READ <= 読む            # part of read / restore
RESTORE <= 読み直します     # part of read / restore

# from ECMA-55 §17

DATA <= 情報            # to embed data in the program

# from ECMA-55 §18

DIM <= 寸法             # dimension arrays
OPTION <= オプション       # see ECMA-55 §18.1
BASE <= ベース           # see ECMA-55 §18.1

# from ECMA-55 §19

REM <= 述べる            # see ECMA-55 §18.1

# from ECMA-55 §20

RANDOMIZE <= ランダム化

#### end of ECMA-55 defined constants
#
# it is worth noting that the following constants,
# while they may appear in other versions of BASIC,
# do NOT appear in ECMA-55:
#
# LOOP <= LOOP  # designed to evoke an error for testing

[errors]

# error messages

err0|エラー: ファイル {0s}, ライン {1i}, 桁 {2i}

