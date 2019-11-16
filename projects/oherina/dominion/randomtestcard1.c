#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "cardEffect.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "randomhelper.h"

void testBaron(int random_seed) {
	int n;
	int NUMRUNS = 10;
	for (n = 0; n < NUMRUNS; n++) {

		/*
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
		*/
		
		// generate random number of players, currentPlayer
		int numPlayers = myrand(2, 5);
		int currPlayer = myrand(0, numPlayers);
		// generate random kingdom cards
		int kCards[NUM_K_CARDS];
		printf("Before selectKingdomCardsWith\n");
		selectKingdomCardsWith(random_seed, kCards, baron);
		printf("After selectKingdomCardsWith\n");
		// initialize game
		struct gameState G;
		initializeGame(numPlayers, kCards, random_seed, &G); // initialize a new game
		if (DEBUG) {
			printSupply(&G);
		}
		// random hand, from 1 (baron) to 10 cards
		int handCount = myrand(1, 11);
		G.handCount[currPlayer] = handCount;
		G.hand[currPlayer][0] = baron;
		// random estates in hand, either 0 or 1
		int estatesInHand = handCount == 1 ? 0 : myrand(0, 2);
		if (estatesInHand > 0) {
			G.hand[currPlayer][1] = estate;
		}
		// fills hand from supply
		int startIndex = 1 + estatesInHand;
		fillHand(currPlayer, startIndex, handCount, &G);
		// random estates in supply, either 0 or 1
		G.supplyCount[estate] = myrand(0, 2);
		// randomize coins
		G.coins = myrand(0, INT_MAX - 2);
		// discard count 0
		// deck is non-empty, initialized with 3 estates and 7 copper

		// check values
		// printHand(currPlayer, &G);
		// printDeck(currPlayer, &G);
		// printDiscard(currPlayer, &G);

		int card = baron;
		int choice1 = myrand(0, 2);
		int handPos = 0; // baron card in position 1
		
		int result = baronEffect(card, choice1, &state, handPos);
		/*
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
		*/
	}
}

int main() {
	int random_seed = 1;
	srand(random_seed);
	testBaron(random_seed);
	return 0;
}