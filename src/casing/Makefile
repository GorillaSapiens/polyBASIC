ucd = https://www.unicode.org/Public/UCD/latest/ucd/

all: lowercase.h

lowercase.h: lowercase.pl UnicodeData.txt SpecialCasing.txt
	./lowercase.pl > lowercase.h

# see https://www.unicode.org/L2/L1999/UnicodeData.html for an explanation
# of this file format
UnicodeData.txt:
	wget $(ucd)UnicodeData.txt

SpecialCasing.txt:
	wget $(ucd)SpecialCasing.txt

.PHONY: clean
clean:
	rm -f UnicodeData.txt SpecialCasing.txt lowercase.h
