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

    printf("Begin Bug #2 (incorrect cost calculations in mine card) unit test 1:\n");
    
    memset(&G, 23, sizeof(struct gameState)); // set the game state
    initializeGame(2, k, 123, &G); // initialize a new game

    // Set up player 0's hand
    G.handCount[0] = 2;
    G.hand[0][0] = mine; 
    G.hand[0][1] = copper;
    int coinBonus;

    // Call cardEffect function
    cardEffect(mine, 1, gold, 0, &G, 0, &coinBonus);

    // Neither of the cards in the player's hand should be gold
    if (!assertIntEquals(G.hand[0][0], gold) && !assertIntEquals(G.hand[0][1], gold)) {
        printf("   PASSED: Cannot trash copper to gain gold.\n");
    } else {
        printf("   FAILED: Cannot trash copper to gain gold.\n");
    }

    printf("\n");

    printf("Begin Bug #2 (incorrect cost calculations in mine card) unit test 2:\n");

    memset(&G, 23, sizeof(struct gameState)); // set the game state
    initializeGame(2, k, 123, &G); // initialize a new game

    // Set up player 0's hand
    G.handCount[0] = 2;
    G.hand[0][0] = mine; 
    G.hand[0][1] = silver;

    // Call cardEffect function
    cardEffect(mine, 1, copper, 0, &G, 0, &coinBonus);

    // One of the cards in the player's hand should be copper
    if (assertIntEquals(G.hand[0][0], copper) || assertIntEquals(G.hand[0][1], copper)) {
        printf("   PASSED: Able to trash silver to gain copper.\n");
    } else {
        printf("   FAILED: Able to trash silver to gain copper.\n");
    }
    printf("\n");

    return 0;
}
