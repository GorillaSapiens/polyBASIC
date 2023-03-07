a = 100+6/2
print "100+6/2=",a

a = 100/5/2
print "100/5/2=",a

a = abs(-5)
print "abs(-5)=",a

a = atn(0)
print "atn(0)=",a

a = chr(65)
print "chr(65)=",a

a = chr(129421)
print "chr(129421)=",a

a = cos(0)
print "cos(0)=",a

a = dbl(#4'2/3)
print "dbl(#4'2/3)=",a

a = exp(1.0)
print "exp(1.0)=",a

a = int(#-4'2/3)
print "int(#-4'2/3)=",a

a = rat(1.333333333)
print "rat(1.333333333)=",a

a = rat(4.4623655914)
print "rat(4.4623655914)=#4'43/93=",a

a = rat(1.0625)
print "rat(2.0625)=#2'1/16=",a

a = "|" & str(22) & "|"
print "str(22)=",a

a = log(exp(1))
print "log(exp(1))=",a

a = rnd(4.5)
print "rnd(4.5)=",a

REM a = randomize
REM print "randomize=",a
REM a = rnd(4.5)
REM print "rnd(4.5)=",a

a = sgn(-12)
print "sgn(-12)=",a

a = sgn(#0)
print "sgn(#0)=",a

a = sgn(15.2)
print "sgn(15.2)=",a

a = sin(3.14159265358/2)
print "sin(3.14159265358/2)=",a

a = sqr(#2)
print "sqr(#2)=",a

print "tab(20)",tab(20),"hello!"

PRINT VAL("A1"):REM Screen: 0
PRINT VAL("- 1 2 3 . 2 3 4 e + 23"):REM Screen: -1.23234e+25
PRINT VAL("1051 E-3 -1.051 C") :REM Screen: 1.051

a = rat(12.077007956766618999456941283075070802675777989896810511198410528)
print "rat(whatever)=",a
