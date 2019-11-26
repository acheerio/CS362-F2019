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

    return 0;
}