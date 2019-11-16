#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffect.h"
#include "randomhelper.h"
#include "rngs.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>

void testBaron() {
	// non-random random seed, for initial testing
	randomSeed = 1;
	// generate random kingdom cards
	int kCards[10];
	selectKingdomCards(randomSeed, kCards);
	int i;
	for (i = 0; i < 10; i++) {
		printf("%d\n", kCards[i]);
	}
	// initialize game
	// numPlayers
	// kingdom cards (9 random, 1 is the card to play)
	// discard pile
	// hand
	// supply - # estates (since we are not testing isGameOver we will not vary others)

	/*
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	initializeGame(numPlayer, k, seed, &G); // initialize a new game

	int i;
	const NUMRUNS = 100;
	for (i = 0; i < NUMRUNS; i++) {
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
		assert("Baron placed at top of played cards.", state.playedCards[state.playedCardCount - 1], baron);
		
		printf("3) Estate card discarded.\n");
		assert("Estate card removed from hand.", hasCard(state.whoseTurn, estate, state), FALSE);
		assert("Number of cards in discard incremented.", state.discardCount[state.whoseTurn], discardCountExpected);
		assert("Estate card at top of discard pile.", state.discard[state.whoseTurn][state.discardCount[state.whoseTurn]], estate);
		
		printf("4) Four coins gained.\n");
		assert("+4 Coins", state.coins, coinsExpected);
		
		printf("5) Correct number of cards in hand.\n");
		assert("No cards in hand.", state.handCount[state.whoseTurn], expectedHandCount);
		printf("\n\n");
	}
	*/
}

int main() {
	testBaron();
	return 0;
}