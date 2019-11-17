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
	int NUMRUNS = 25;
	for (n = 0; n < NUMRUNS; n++) {
		/*
		 * GENERATE RANDOM GAME
		 */
		// generate random number of players, currentPlayer
		int numPlayers = myrand(2, 5);
		int currPlayer = myrand(0, numPlayers);
		// generate random kingdom cards
		int kCards[NUM_K_CARDS];
		selectKingdomCardsWith(random_seed, kCards, baron);
		// initialize game
		struct gameState G;
		initializeGame(numPlayers, kCards, random_seed, &G); // initialize a new game
		if (DEBUG) {
			printSupply(&G);
		}
		G.whoseTurn = currPlayer;
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
		G.coins = myrand(0, INT_MAX - 4);
		
		// check values
		if (DEBUG) {
			printHand(currPlayer, &G);
			printDeck(currPlayer, &G); // deck is non-empty, initialized with 3 estates and 7 copper
			printDiscard(currPlayer, &G); // discard count 0
		}

		int card = baron;
		int choice1 = myrand(0, 2); // > 0, chose to discard estate
		int handPos = 0; // baron card in position 1

		/*
		 * CALCULATE EXPECTED RESULTS
		 */
		// number of baron cards - may have added more random
		int expectedBaronCount = getCount(G.hand[currPlayer], G.handCount[currPlayer], baron) - 1;
		// number of estate cards - may have added more random
		int currentEstateCountHand = getCount(G.hand[currPlayer], G.handCount[currPlayer], estate);
		int expectedEstateCountHand;
		int expectedEstateCountSupply;
		int expectedHandCount;
		int expectedPlayedCardCount = G.playedCardCount + 1;	// played baron
		int expectedDeckCount = G.deckCount[currPlayer];
		int expectedCoinCount;
		int expectedDiscardCount;	
		int discarded = FALSE;
		int gained = FALSE;

		// option 1 successfully discarded estate
		if (choice1 == 1 && estatesInHand > 0) {
			discarded = TRUE;
			expectedEstateCountHand = currentEstateCountHand - 1;
			expectedEstateCountSupply = G.supplyCount[estate];	// unchanged
			expectedHandCount = G.handCount[currPlayer] - 2; // played baron, discarded estate
			expectedCoinCount = G.coins + 4;	
			// discard has additional estate (from hand)
			expectedDiscardCount = G.discardCount[currPlayer] + 1;
		}
		// option 2 did not discard, must gain if possible
		else if (G.supplyCount[estate] > 0) {
			gained = TRUE;
			expectedEstateCountHand = currentEstateCountHand + 1;
			expectedEstateCountSupply = G.supplyCount[estate] - 1;	// unchanged
			expectedHandCount = G.handCount[currPlayer] - 1; // played baron
			expectedCoinCount = G.coins;
			// discard has additional estate (gained from supply)
			expectedDiscardCount = G.discardCount[currPlayer] + 1;
		} 
		// option 3 no change
		else {
			expectedEstateCountHand = currentEstateCountHand;
			expectedEstateCountSupply = G.supplyCount[estate];
			expectedHandCount = G.handCount[currPlayer];
			expectedCoinCount = G.coins;
			// discard unchanged
			expectedDiscardCount = G.discardCount[currPlayer];
		}
		
		int result = baronEffect(card, choice1, &G, handPos);
		
		printf("BARON - TRIAL %d\n", n);
		printf("1) Function successful.\n");
		assert("Function returns >= 0 (Success)", result >= 0, 0);
		
		printf("2) Baron card played.\n");
		assert("Baron removed from hand.", getCount(G.hand[currPlayer], G.handCount[currPlayer], baron), expectedBaronCount);
		assert("Played cards incremented.", G.playedCardCount, expectedPlayedCardCount);
		assert("Baron placed at top of played cards.", G.playedCards[G.playedCardCount - 1], baron);
		
		printf("3) Correct estates in hand, deck, supply, discard.\n");
		assert("Estate card, if any, removed from hand.", getCount(G.hand[currPlayer], G.handCount[currPlayer], estate), expectedEstateCountHand);
		assert("Deck unchanged.", G.deckCount[currPlayer], expectedDeckCount);
		assert("Number of estates in supply as expected.", G.supplyCount[estate], expectedEstateCountSupply);
		assert("Number of cards in discard as expected.", G.discardCount[G.whoseTurn], expectedDiscardCount);
		if (gained || discarded) {
			assert("Estate card at top of discard pile.", G.discard[G.whoseTurn][G.discardCount[G.whoseTurn] - 1], estate);
		}

		printf("4) Correct number of coins.\n");
		char *coinStatement = discarded ? "Gained 4 coins" : "Coins unchanged";
		assert(coinStatement, G.coins, expectedCoinCount);
		
		printf("5) Correct number of cards in hand.\n");
		assert("Hand count correct.", G.handCount[G.whoseTurn], expectedHandCount);
		printf("\n\n");
	}
}

int main() {
	int random_seed = 1;
	srand(random_seed);
	testBaron(random_seed);
	return 0;
}