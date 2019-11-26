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

    printf("Begin Bug #7 unit test: Tribute card effect\n");

    int card = tribute;
    int handPos = 0;
    int currentPlayer = 0;
    G.handCount[currentPlayer] = 1;
    G.hand[currentPlayer][handPos] = card;
    G.deckCount[currentPlayer] = 6;
    int i;
    for (i = 0; i < G.deckCount[currentPlayer]; i++) {
    	G.deck[currentPlayer][i] = copper;
    }

    int nextPlayer = 1;
    G.deckCount[nextPlayer] = 2;
    G.deck[nextPlayer][0] = estate;
    G.deck[nextPlayer][1] = estate;

    G.coins = 0;
    int bonus = 0;
    G.numActions = 0;

    int result = cardEffect(tribute, -1, -1, -1, &G, handPos, &bonus);

    assertPrint("Function was successful.", result, 0);
    assertPrint("Current player has 4 cards in hand.", G.handCount[currentPlayer], 4);
    assertPrint("Current player drew 4 cards from deck.", G.deckCount[currentPlayer], 2);
    assertPrint("Coins unchanged (bonus).", bonus, 0);
    assertPrint("Coins unchanged (state->coins).", G.coins, 0);
    assertPrint("Actions unchanged.", G.numActions, 0);

    return 0;
}