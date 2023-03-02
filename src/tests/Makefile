.PHONY: test
test:
	for each in `ls -d */`; do if ! (cd $$each && make); then exit 1; fi; done

.PHONY: clean
clean:
	for each in `ls -d */`; do (cd $$each && make clean); done
