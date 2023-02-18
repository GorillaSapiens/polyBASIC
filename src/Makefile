.PHONY: all
all: reflex polybasic verify tests

.PHONY: reflex
reflex:
	(cd reflex && make)

.PHONY: polybasic
polybasic:
	(cd polybasic && make)

.PHONY: verify
verify:
	(cd verify && make)

.PHONY: tests
tests:
	(cd tests && make)

.PHONY: clean
clean:
	(cd polybasic && make clean)

.PHONY: squeaky
squeaky: clean
	(cd RE-flex && make clean)
