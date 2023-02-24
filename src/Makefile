.PHONY: all
all: reflex polybasic verify tests

.PHONY: reflex
reflex:
	@echo =========================
	@echo ===== MAKE $@
	@echo =========================
	(cd reflex && make)

.PHONY: polybasic
polybasic:
	@echo =========================
	@echo ===== MAKE $@
	@echo =========================
	(cd polybasic && make)

.PHONY: verify
verify:
	@echo =========================
	@echo ===== MAKE $@
	@echo =========================
	(cd verify && make)

.PHONY: tests
tests:
	@echo =========================
	@echo ===== MAKE $@
	@echo =========================
	(cd tests && make)

.PHONY: clean
clean:
	@echo =========================
	@echo ===== MAKE $@
	@echo =========================
	(cd polybasic && make clean)

.PHONY: squeaky
squeaky: clean
	@echo =========================
	@echo ===== MAKE $@
	@echo =========================
	(cd reflex && make clean)
