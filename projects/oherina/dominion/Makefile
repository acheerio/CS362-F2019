CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

cardEffect.o: cardEffect.h cardEffect.c
	gcc -c cardEffect.c -g $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o cardEffect.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o cardEffect.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

randomhelper.o: randomhelper.c randomhelper.h
	gcc -c randomhelper.c -g $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o cardEffect.o randomhelper.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o cardEffect.o randomhelper.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o cardEffect.o randomhelper.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o cardEffect.o randomhelper.o rngs.o $(CFLAGS)

randomtestcard3: randomtestcard3.c dominion.o cardEffect.o randomhelper.o rngs.o
	gcc -o randomtestcard3 -g randomtestcard3.c dominion.o cardEffect.o randomhelper.o rngs.o $(CFLAGS)

run-tests: randomtestcard1 randomtestcard2 randomtestcard3
	./randomtestcard1 &> randomtestresults.out
	./randomtestcard2 &>> randomtestresults.out
	./randomtestcard3 &>> randomtestresults.out
	gcov -b -f cardEffect.c >> randomtestresults.out
	cat cardEffect.c.gcov >> randomtestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o cardEffect.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out

clean-tests:
	rm -f *.o *.gcov *.gcda *.gcno randomtestcard1 randomtestcard2 randomtestcard3
	rm -i randomtestresults.out