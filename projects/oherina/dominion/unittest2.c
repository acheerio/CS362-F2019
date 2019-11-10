#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffect.h"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>

void minionTest1(struct gameState state) {
	printf("Minion - gain 2 coins.\n");
	// state
	state.whoseTurn = 0;
	state.coins = 2;
	int coinsExpected = state.coins + 2;
	state.playedCardCount = 0;
	int playedCardCountExpected = 1;
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn]; 
	
	// current player's hand = minion
	state.handCount[state.whoseTurn] = 1;
	int expectedHandCount = state.handCount[state.whoseTurn] - 1;
	state.hand[state.whoseTurn][0] = minion;
	int handPos = 0; // minion card in position 1
	
	int card = minion;
	int choice1 = 1; // chose to gain coins
	int choice2 = 0;
	
	int result = minionEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);
	
	printf("2) Minion card played.\n");
	assert("Minion removed from hand.", hasCard(state.whoseTurn, minion, state), FALSE);
	assert("Played cards incremented.", state.playedCardCount, playedCardCountExpected);
	assert("Minion placed at top of played cards.", state.playedCards[state.playedCardCount - 1], minion);
	
	printf("3) No cards discarded.\n");
	// assert("Estate card removed from hand.", hasCard(state.whoseTurn, estate, state), FALSE);
	assert("Number of cards in discard unchanged.", state.discardCount[state.whoseTurn], discardCountExpected);
	// assert("Estate card at top of discard pile.", state.discard[state.whoseTurn][state.discardCount[state.whoseTurn]], estate);
	
	printf("4) Two coins gained.\n");
	assert("+2 Coins", state.coins, coinsExpected);
	
	printf("5) Correct number of cards in hand.\n");
	assert("No cards in hand.", state.handCount[state.whoseTurn], expectedHandCount);
	printf("\n\n");
}
void minionTest2(struct gameState state) {
}
void minionTest3(struct gameState state) {}
void minionTest4(struct gameState state) {}
void minionTest5(struct gameState state) {}
void minionTest6(struct gameState state) {}

void testMinion() {
	int seed = 1; // need some constant here that's deterministic (vs seeding by time)
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, minion, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	// calling tests and passing by value since we want gameState unchanged
	minionTest1(G);
	minionTest2(G);
	minionTest3(G);
	minionTest4(G);
	minionTest5(G);
	minionTest6(G);	
}

int main() {
	testMinion();
	return 0;
}
