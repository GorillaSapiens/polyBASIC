.PHONY: all
all: reflex polybasic autotranslate verify tests

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

.PHONY: autotranslate
autotranslate:
	@echo =========================
	@echo ===== MAKE $@
	@echo =========================
	(cd autotranslate && make)

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
	(cd autotranslate && make clean)
	(cd tests && make clean)

.PHONY: squeaky
squeaky: clean
	@echo =========================
	@echo ===== MAKE $@
	@echo =========================
	(cd reflex && make clean)
	(cd polybasic && make squeaky)
