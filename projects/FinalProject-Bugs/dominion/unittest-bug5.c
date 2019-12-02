#include "dominion.h"
#include "dominion_helpers.h"
#include "unittest_helpers.h"
#include <string.h>
#include <stdio.h>

void test1(struct gameState state) {
    printf("Begin Bug #5 (incorrect deck count in scoreFor) unit test 1: deckCount > discardCount\n");
    int currentPlayer = 0;
    state.handCount[currentPlayer] = 0;
    state.discardCount[currentPlayer] = 0;
    state.deckCount[currentPlayer] = 2;
    state.deck[currentPlayer][0] = estate;
    state.deck[currentPlayer][1] = estate;

    int score = scoreFor(0, &state);
    assertPrint("The current player should have a score of 2.", score, 2);
    printf("\n");
}

void test2(struct gameState state) {
    printf("Begin Bug #5 (incorrect deck count in scoreFor) unit test 2: deckCount < discardCount\n");
    int currentPlayer = 0;
    state.handCount[currentPlayer] = 0;
    state.discardCount[currentPlayer] = 2;
    state.discard[currentPlayer][0] = silver;
    state.discard[currentPlayer][1] = silver;
    state.deckCount[currentPlayer] = 0;
    state.deck[currentPlayer][0] = estate;
    state.deck[currentPlayer][1] = estate;

    int score = scoreFor(0, &state);
    assertPrint("The current player should have a score of 0.", score, 0);
    printf("\n");
}

int main () {

    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, ambassador, tribute, baron, minion };
    // declare the game state
    int numPlayers = 2;
    int seed = 1;
    struct gameState G;
    memset(&G, 23, sizeof(struct gameState)); // set the game state
    initializeGame(numPlayers, k, seed, &G); // initialize a new game

    test1(G);
    test2(G);
    
    return 0;
}
