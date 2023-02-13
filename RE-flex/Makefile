all: source

source: RE-flex RE-flex-configure

RE-flex:
	git clone https://github.com/Genivia/RE-flex.git

RE-flex-configure: RE-flex/Makefile

RE-flex/Makefile:
	(cd RE-flex ; ./configure)
