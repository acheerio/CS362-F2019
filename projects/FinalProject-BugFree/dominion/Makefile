CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittests: unittest-bug1.c unittest-bug2.c unittest-bug3.c unittest-bug4.c unittest-bug5.c unittest-bug6.c unittest-bug7.c dominion.o rngs.o interface.o
	gcc -o unittest-bug1 unittest-bug1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unittest-bug2 unittest-bug2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unittest-bug3 unittest-bug3.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unittest-bug4 unittest-bug4.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unittest-bug5 unittest-bug5.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o unittest-bug6 unittest-bug6.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o unittest-bug7 unittest-bug7.c -g dominion.o rngs.o $(CFLAGS)

unittestresults: unittests
	./unittest-bug1 >> unittestresults.out
	./unittest-bug2 >> unittestresults.out
	./unittest-bug3 >> unittestresults.out
	./unittest-bug4 >> unittestresults.out
	./unittest-bug5 >> unittestresults.out
	./unittest-bug6 >> unittestresults.out
	./unittest-bug7 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o unittest-bug1 unittest-bug1.exe unittest-bug2 unittest-bug2.exe unittest-bug3 unittest-bug3.exe playdom.exe unittest-bug4 unittest-bug4.exe unittest-bug5 unittest-bug7 playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
