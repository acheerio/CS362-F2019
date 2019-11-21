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

unittest1: unittest1.c dominion.o testhelper.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o testhelper.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o testhelper.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o testhelper.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o testhelper.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o testhelper.o rngs.o $(CFLAGS)
	
unittest4: unittest4.c dominion.o testhelper.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o testhelper.o rngs.o $(CFLAGS)
	
unittest5: unittest5.c dominion.o testhelper.o rngs.o
	gcc -o unittest5 -g unittest5.c dominion.o testhelper.o rngs.o $(CFLAGS)

testhelper.o: testhelper.c testhelper.h
	gcc -c testhelper.c -g $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o testhelper.o interface.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o testhelper.o interface.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o testhelper.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o testhelper.o interface.o rngs.o $(CFLAGS)

randomtestcard3: randomtestcard3.c dominion.o testhelper.o rngs.o
	gcc -o randomtestcard3 -g randomtestcard3.c dominion.o testhelper.o interface.o rngs.o $(CFLAGS)

run-tests: unittest1 unittest2 unittest3 unittest4 unittest5 randomtestcard1 randomtestcard2 randomtestcard3
	./unittest1 &> assign5-results.out
	./unittest2 &>> assign5-results.out
	./unittest3 &>> assign5-results.out
	./unittest4 &>> assign5-results.out
	./unittest5 &>> assign5-results.out
	./randomtestcard1 &>> assign5-results.out
	./randomtestcard2 &>> assign5-results.out
	./randomtestcard3 &>> assign5-results.out
	gcov -b -f dominion.c >> assign5-results.out
	cat dominion.c.gcov >> assign5-results.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

clean-tests:
	rm -f *.o *.gcov *.gcda *.gcno unittest1 unittest2 unittest3 unittest4 unittest5 randomtestcard1 randomtestcard2 randomtestcard3
	rm -i assign5-results.out