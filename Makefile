compile: foo.c
	echo "Compiling foo.c"
	cc -c -Werror -Wfatal-errors -Wpedantic -Wall -Wextra -fanalyzer -Wanalyzer-too-complex -fdump-analyzer-callgraph -fdump-analyzer-exploded-graph -fdump-analyzer-supergraph -ggdb --coverage -fpic foo.c

clean:
	echo "Cleaning up"
	rm -f foo.o foo.gcda foo.gcno foo.gcov foo.c.* foo.i.* foo.s.* foo.s

.PHONY: clean compile