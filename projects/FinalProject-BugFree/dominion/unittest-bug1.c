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

    printf("Begin Bug #1 (incorrect discardCard function parameters in mine card) unit test:\n");
    
    memset(&G, 23, sizeof(struct gameState)); // set the game state
    initializeGame(2, k, 123, &G); // initialize a new game

    // Get initial played card count 
    int initialPlayedCardCount = G.playedCardCount;
    // Add silver to player 0's hand
    G.hand[0][4] = silver;
    int coinBonus;

    // Call cardEffect function
    cardEffect(mine, 4, gold, 0, &G, 0, &coinBonus);

    // verify that your asserts pass, for the bugs your asserts may fail
    // playedCardCount should only go up by 1, which is the mine card being played
    if (assertIntEquals(initialPlayedCardCount + 1, G.playedCardCount)) {
        printf("   PASSED: Played cards increases by exactly 1 (silver is trashed, not played).\n");
    } else {
        printf("   FAILED: Played cards increases by exactly 1 (silver is trashed, not played).\n");
    }

    printf("\n");

    return 0;
}
