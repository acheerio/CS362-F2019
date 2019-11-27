#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "unittest_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>

int main () {

    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, ambassador, tribute, baron, minion };
    // declare the game state
    struct gameState G;

    printf("Begin Bug #3 unit test:\n");
    
    memset(&G, 23, sizeof(struct gameState)); // set the game state
    initializeGame(2, k, 123, &G); // initialize a new game

    // Set up player 0's hand
    G.hand[0][0] = remodel;
    G.hand[0][1] = estate;
    G.handCount[0] = 2;
    // Set player 0's discard pile to be empty
    G.discard[0][1] = -1;
    G.discard[0][0] = -1;
    G.discardCount[0] = 0;
    int coinBonus;

    // Call cardEffect function
    cardEffect(remodel, 1, silver, 0, &G, 0, &coinBonus);

    // Assert that one of the cards in the discard pile is a silver.
    if (assertIntEquals(G.discard[0][0], silver) || assertIntEquals(G.discard[0][1], silver)) {
        printf("   PASSED: Bug #3 (incorrect cost calculations in remodel card) test.\n");
    } else {
        printf("   FAILED: Bug #3 (incorrect cost calculations in remodel card) test.\n");
    }

    printf("\n");

    return 0;
}
