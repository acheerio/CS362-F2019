#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "unittest_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>

int main () {

    int k[10] = { adventurer, treasure_map, sea_hag, gardens, mine, remodel, ambassador, tribute, baron, minion };
    // declare the game state
    struct gameState G;

    printf("Begin Bug #4 unit test:\n");
    
    memset(&G, 23, sizeof(struct gameState)); // set the game state
    initializeGame(2, k, 123, &G); // initialize a new game

    // Game should not be over initially
    int isGameOverInitial = isGameOver(&G);

    // Set three card supply piles to be empty
    G.supplyCount[treasure_map] = 0;
    G.supplyCount[sea_hag] = 0;
    G.supplyCount[mine] = 0;

    int isGameOverFinal = isGameOver(&G);

    // Assert that game is over after setting three supply piles to be 0
    if (assertIntEquals(isGameOverInitial, 0) && assertIntEquals(isGameOverFinal, 1)) {
        printf("   PASSED: Bug #4 (incorrect logic in isGameOver function) test.\n");
    } else {
        printf("   FAILED: Bug #4 (incorrect logic in isGameOver function) test.\n");
    }

    printf("\n");

    return 0;
}
