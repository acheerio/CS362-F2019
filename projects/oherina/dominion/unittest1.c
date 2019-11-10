#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffect.h"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>

void baronTest1(struct gameState state) {
	printf("Baron - choose to discard estate, estate is first card in hand.\n");
	// set up state - currentPlayer 0 with hand: estate, baron
	state.whoseTurn = 0;
	state.coins = 2;
	int coinsExpected = state.coins + 4;
	state.playedCardCount = 0;
	int playedCardCountExpected = 1;
	state.handCount[state.whoseTurn] = 2;
	int expectedHandCount = state.handCount[state.whoseTurn] - 2;
	state.hand[state.whoseTurn][0] = estate;
	state.hand[state.whoseTurn][1] = baron;
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn] + 1; 
	
	int card = baron;
	int choice1 = 1; // choose to discard estate
	int handPos = 1; // baron card in position 1
	
	int result = baronEffect(card, choice1, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, 0);
	
	printf("2) Baron card moved out of player's hand.\n");
	assert("Baron removed from hand.", hasCard(state.whoseTurn, baron, state), FALSE);
	assert("Played cards incremented.", state.playedCardCount, playedCardCountExpected);
	assert("Baron placed at top of played cards.", state.playedCards[state.playedCardCount], baron);
	
	printf("3) Estate card discarded.\n");
	assert("Estate card removed from hand.", hasCard(state.whoseTurn, estate, state), FALSE);
	assert("Number of cards in discard incremented.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Estate card at top of discard pile.", state.discard[state.whoseTurn][state.discardCount[state.whoseTurn]], estate);
	assert("Hand is empty. (also #2)", state.handCount[state.whoseTurn], expectedHandCount);
	
	printf("4) Four coins gained.\n");
	assert("+4 Coins", state.coins, coinsExpected);
	printf("\n\n");
}

void baronTest2(struct gameState state) {
	printf("Baron - choose to discard estate, estate is last card in hand.\n");
	// set up state - currentPlayer 0 with hand: baron, estate
	state.whoseTurn = 0;
	state.coins = 2;
	int coinsExpected = state.coins + 4;
	state.playedCardCount = 0;
	int playedCardCountExpected = 1;
	state.handCount[state.whoseTurn] = 2;
	int expectedHandCount = state.handCount[state.whoseTurn] - 2;
	state.hand[state.whoseTurn][0] = baron;
	state.hand[state.whoseTurn][1] = estate;
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn] + 1; 
	int card = baron;
	int choice1 = 1; // choose to discard estate
	int handPos = 0; // baron card in position 1
	
	int result = baronEffect(card, choice1, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);
	
	printf("2) Baron card moved out of player's hand.\n");
	assert("Baron removed from hand.", hasCard(state.whoseTurn, baron, state), FALSE);
	assert("Played cards incremented.", state.playedCardCount, playedCardCountExpected);
	assert("Baron placed at top of played cards.", state.playedCards[state.playedCardCount], baron);
	
	printf("3) Estate card discarded.\n");
	assert("Estate card removed from hand.", hasCard(state.whoseTurn, estate, state), FALSE);
	assert("Number of cards in discard incremented.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Estate card at top of discard pile.", state.discard[state.whoseTurn][state.discardCount[state.whoseTurn]], estate);
	assert("Hand is empty. (also #2)", state.handCount[state.whoseTurn], expectedHandCount);
	
	printf("4) Four coins gained.\n");
	assert("+4 Coins", state.coins, coinsExpected);
	printf("\n\n");
}

void baronTest3(struct gameState state) {
	printf("Baron - choose to discard estate, no estate in hand, estate in supply > 1.\n");
	// set up state - currentPlayer 0 with hand: baron
	// supplyCount[estate] set to 8 by default in initializeGame for 2 players
	state.supplyCount[estate] = 8; // declare explicitly for clarity/readability
	int expectedEstateCount = state.supplyCount[estate] - 1;
	state.whoseTurn = 0;
	state.coins = 2;
	int coinsExpected = state.coins;
	state.playedCardCount = 0;
	int playedCardCountExpected = 1;
	state.handCount[state.whoseTurn] = 1;
	int expectedHandCount = state.handCount[state.whoseTurn] - 1;
	state.hand[state.whoseTurn][0] = baron;
	state.discardCount[state.whoseTurn] = 1;
	int discardCountExpected = state.discardCount[state.whoseTurn] + 1;
	int card = baron;
	int choice1 = 1; // choose to discard estate
	int handPos = 0; // baron card in position 1
	
	int result = baronEffect(card, choice1, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);
	
	printf("2) Baron card moved out of player's hand.\n");
	assert("Baron removed from hand.", hasCard(state.whoseTurn, baron, state), FALSE);
	assert("Played cards incremented.", state.playedCardCount, playedCardCountExpected);
	assert("Baron placed at top of played cards.", state.playedCards[state.playedCardCount], baron);
	
	printf("3) Estate card gained to discard.\n");
	assert("Number of estates in supply decreased 1.", state.supplyCount[estate], expectedEstateCount);
	assert("Correct number of discards.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Estate at top of discard.", state.discard[state.whoseTurn][state.discardCount[state.whoseTurn] - 1], estate);
	
	printf("4) No coins gained.\n");
	assert("+0 Coins", state.coins, coinsExpected);
	
	printf("5) Correct number of cards in hand.\n");
	assert("No cards in hand.", state.handCount[state.whoseTurn], expectedHandCount);
	printf("\n\n");
}

void baronTest4(struct gameState state) {
	
}

void baronTest6(struct gameState state) {
	void baronTest3(struct gameState state) {
	printf("Baron - choose not to discard estate, estate in supply > 1.\n");
	// set up state - currentPlayer 0 with hand: baron
	// supplyCount[estate] set to 8 by default in initializeGame for 2 players
	state.supplyCount[estate] = 8; // declare explicitly for clarity/readability
	int expectedEstateCount = state.supplyCount[estate] - 1;
	state.whoseTurn = 0;
	state.coins = 2;
	int coinsExpected = state.coins;
	state.playedCardCount = 0;
	int playedCardCountExpected = 1;
	state.handCount[state.whoseTurn] = 1;
	int expectedHandCount = state.handCount[state.whoseTurn] - 1;
	state.hand[state.whoseTurn][0] = baron;
	state.discardCount[state.whoseTurn] = 1;
	int discardCountExpected = state.discardCount[state.whoseTurn] + 1;
	int card = baron;
	int choice1 = 0; // choose not to discard estate
	int handPos = 0; // baron card in position 1
	
	int result = baronEffect(card, choice1, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);
	
	printf("2) Baron card moved out of player's hand.\n");
	assert("Baron removed from hand.", hasCard(state.whoseTurn, baron, state), FALSE);
	assert("Played cards incremented.", state.playedCardCount, playedCardCountExpected);
	assert("Baron placed at top of played cards.", state.playedCards[state.playedCardCount], baron);
	
	printf("3) Estate card gained to discard.\n");
	assert("Number of estates in supply decreased 1.", state.supplyCount[estate], expectedEstateCount);
	assert("Correct number of discards.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Estate at top of discard.", state.discard[state.whoseTurn][state.discardCount[state.whoseTurn] - 1], estate);
	
	printf("4) No coins gained.\n");
	assert("+0 Coins", state.coins, coinsExpected);
	
	printf("5) Correct number of cards in hand.\n");
	assert("No cards in hand.", state.handCount[state.whoseTurn], expectedHandCount);
	printf("\n\n");
}

void testBaron() {
	int seed = 1; // need some constant here that's deterministic (vs seeding by time)
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	// calling tests and passing by value since we want gameState unchanged
	baronTest1(G);
	baronTest2(G);
	baronTest3(G);
	baronTest6(G);
}

int main() {
	testBaron();
	return 0;
}
