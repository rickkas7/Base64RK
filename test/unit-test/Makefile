

all : unit-test
	./unit-test

unit-test : unit-test.cpp ../../src/Base64RK.cpp ../../src/Base64RK.h libwiringgcc
	gcc unit-test.cpp ../../src/Base64RK.cpp gcclib/libwiringgcc.a -std=c++11 -lc++ -Igcclib -I../../src -o unit-test

check : unit-test.cpp ../../src/Base64RK.cpp ../../src/Base64RK.h libwiringgcc
	gcc unit-test.cpp ../../src/Base64RK.cpp gcclib/libwiringgcc.a -g -O0 -std=c++11 -lc++ -Igcclib -I../../src -o unit-test && valgrind --leak-check=yes ./unit-test 

libwiringgcc :
	cd gcclib && make libwiringgcc.a 	
	
.PHONY: libwiringgcc