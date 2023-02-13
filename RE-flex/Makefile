.PHONY: all
all: source configure build

.PHONY: source
source: RE-flex

RE-flex:
	git clone https://github.com/Genivia/RE-flex.git

.PHONY: configure
configure: RE-flex/Makefile

RE-flex/Makefile:
	(cd RE-flex ; ./configure)

.PHONY: build
build: RE-flex/src/reflex

RE-flex/src/reflex:
	(cd RE-flex ; make)
