.PHONY: all
all: reflex polybasic

.PHONY: reflex
reflex:
	(cd reflex && make)

.PHONY: polybasic
polybasic:
	(cd polybasic && make)

.PHONY: clean
clean:
	(cd polybasic && make clean)

.PHONY: squeaky
squeaky: clean
	(cd RE-flex && make clean)
