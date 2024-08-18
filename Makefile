link: move
	echo "Linking foo"
	gcc -Werror -Wfatal-errors -Wpedantic -Wall -Wextra -o test main.c -lfoo -fanalyzer -Wanalyzer-too-complex -ggdb --coverage

move: libfoo.so
	echo "Moving libfoo.so to /usr/lib"
	sudo mv libfoo.so /usr/lib
	sudo chmod 755 /usr/lib/libfoo.so
	sudo ldconfig
	ldconfig -p | grep libfoo

libfoo.so: foo.o
	echo "Building shared library"
	gcc -Werror -Wfatal-errors -Wpedantic -Wall -Wextra -shared -o libfoo.so foo.o

compile: foo.c
	echo "Compiling foo.c"
	cc -c -Werror -Wfatal-errors -Wpedantic -Wall -Wextra -fanalyzer -Wanalyzer-too-complex -ggdb --coverage -fpic foo.c

clean:
	echo "Cleaning up"
	rm -f foo.o foo.gcda foo.gcno foo.gcov foo.c.* foo.i.* foo.s.* foo.s foo.o foo.gcda *.gcno foo.gcov libfoo.so test

.PHONY: clean compile foo link move