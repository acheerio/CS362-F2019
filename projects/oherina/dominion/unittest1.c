#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffect.h"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>

void baronTest1(struct gameState state) {
	printf("Baron - choose to discard estate, estate is first card.\n");
	// set up state - currentPlayer 0 with hand: estate, baron
	state.whoseTurn = 0;
	state.coins = 2;
	int coinsExpected = state.coins + 4;
	state.handCount[state.whoseTurn] = 2;
	state.hand[state.whoseTurn][0] = estate;
	state.hand[state.whoseTurn][1] = baron;
	
	int card = baron;
	int choice1 = 1; // choose to discard estate
	int handPos = 1; // baron card in position 1
	
	int result = baronEffect(card, choice1, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns 0 (Success)", result, 0);
	
	printf("2) Baron card moved out of player's hand.\n");
	assert("Baron removed from hand.", hasCard(state.whoseTurn, baron, state), FALSE);
	assert("Baron placed at top of played cards.", state.playedCards[state.playedCardCount], baron);
	
	printf("3) Estate card discarded.\n");
	assert("Estate card removed from hand.", hasCard(state.whoseTurn, estate, state), FALSE);
	assert("Estate card at top of discard pile.", state.discard[state.whoseTurn][state.discardCount[state.whoseTurn]], estate);
	
	printf("4) Four coins gained.\n");
	assert("+4 Coins", state.coins, coinsExpected);
}

void testBaron() {
	int seed = 1; // need some constant here that's deterministic (vs seeding by time)
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	// calling tests and passing by value since we want gameState unchanged
	baronTest1(G);
}

int main() {
	testBaron();
	return 0;
}
