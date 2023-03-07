.PHONY:step1
step1:
	./makeinput.pl > input.tsv
	@echo import "input.tsv" into google sheets
	@echo specify TAB delimiters when importing
	@echo WAIT FOR EVERYTHING TO LOAD
	@echo then download as polybasic.tsv
	@echo then \"make step2\"

.PHONY:step2
step2:
	./polypoly.pl
	./reverse.pl > reverse.utf8
	./emoji.pl > emoji.utf8
	./dotransfer.pl
	(cd ../verify && make)

.PHONY:clean
clean:
	git clean -f .

