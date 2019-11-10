#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffect.h"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>
// unittest1

void testBaron() {
	int seed = 1; // need some constant here that's deterministic (vs seeding by time)
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	printf("Baron - choose to discard estate, estate is first card.");
	// set up state - currentPlayer 0 with hand: estate, baron
	G.whoseTurn = 0;
	G.coins = 2;
	int coinsExpected = G.coins + 4;
	G.handCount[G.whoseTurn] = 2;
	G.hand[G.whoseTurn][0] = estate;
	G.hand[G.whoseTurn][1] = baron;
	
	int card = baron;
	int choice1 = 1; // choose to discard estate
	int handPos = 1; // baron card in position 1
	
	int result = baronEffect(card, choice1, &G, handPos);
	
	printf("Function successful.\n");
	assert("Function returns 0 (Success)\n", result, 0);
	
	printf("Baron card moved out of player's hand.\n");
	assert("Baron removed from hand.\n", hasCard(G.whoseTurn, baron, G), FALSE);
	assert("Baron placed at top of played cards.\n", G.playedCards[G.playedCardCount], baron);
	
	printf("Estate card discarded.\n");
	assert("Estate card removed from hand.\n", hasCard(G.whoseTurn, estate, G), FALSE);
	assert("Estate card discarded.\n", G.discard[G.whoseTurn][G.discardCount[G.whoseTurn]], estate);
	
	printf("Four coins gained.\n");
	assert("+4 Coins", G.coins, coinsExpected);
}

int main() {
	testBaron();
	return 0;
}
