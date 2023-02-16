# Makefile to build the reflex lexical parser

# top level target
.PHONY: all
all: source configure build

.PHONY: clean
clean:
	rm -rf RE-flex

# make sure the source code has been downloaded
.PHONY: source
source: RE-flex

# make sure it has been configured
.PHONY: configure
configure: RE-flex/Makefile

# make sure it has been built
.PHONY: build
build: RE-flex/src/reflex

# now the dirty work

RE-flex:
	git clone https://github.com/Genivia/RE-flex.git

RE-flex/Makefile:
	(cd RE-flex ; ./configure)

RE-flex/src/reflex:
	(cd RE-flex ; make)
