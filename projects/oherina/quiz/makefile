CC=gcc
CFLAGS= -fprofile-arcs -ftest-coverage

all: testme

testme:
	$(CC) $(CFLAGS) testme.c -o testme

.PHONY: clean

clean :
	rm testme *.gcno *.gcda *.gcov