.PHONY: test
test:
	for each in `ls -d */`; do (cd $$each && make); done

.PHONY: clean
clean:
	for each in `ls -d */`; do (cd $$each && make clean); done
