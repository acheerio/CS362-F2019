#include "dominion.h"
#include "dominion_helpers.h"
#include "unittest_helpers.h"
#include <string.h>
#include <stdio.h>

int main () {

    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, ambassador, tribute, baron, minion };
    // declare the game state
    int numPlayers = 2;
    int seed = 1;
    struct gameState G;
    memset(&G, 23, sizeof(struct gameState)); // set the game state
    initializeGame(numPlayers, k, seed, &G); // initialize a new game

    printf("Begin Bug #6 unit test: Play feast to gain gold (cost = 6)\n");

    int currentPlayer = 0;
    G.handCount[currentPlayer] = 2;
    G.hand[currentPlayer][0] = feast;
    G.hand[currentPlayer][1] = silver; // +2 coins
    G.discardCount[currentPlayer] = 0;
    int bonus = 0;

    int result = cardEffect(feast, gold, -1, -1, &G, 0, &bonus);

    assertPrint("Function unsuccessful.", result, -1);
    assertPrint("Gold not taken from supply.", G.supplyCount[gold], 30);
    assertPrint("Gold not gained to discard.", G.discardCount[currentPlayer], 0);
    printf("\n");

    return 0;
}
