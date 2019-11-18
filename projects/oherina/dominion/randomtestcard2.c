#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "cardEffect.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "randomhelper.h"

void testMinion(int random_seed) {
	int n, i, j;
	int NUMRUNS = 100;
	for (n = 0; n < NUMRUNS; n++) {
		printf("MINION - TRIAL %d\n", n + 1);
		/*
		 * GENERATE RANDOM GAME
		 */
		// set card in question
		int card = minion;
		// generate random number of players, currentPlayer
		int numPlayers = myrand(2, 5);
		int currPlayer = myrand(0, numPlayers);
		// generate random kingdom cards
		int kCards[NUM_K_CARDS];
		selectKingdomCardsWith(random_seed, kCards, card);
		// initialize game
		struct gameState G;
		initializeGame(numPlayers, kCards, random_seed, &G); // initialize a new game
		if (DEBUG) {
			printSupply(&G);
		}
		G.whoseTurn = currPlayer;
		// random hand, from 1 (minion only) to 6 cards
		int handCount = myrand(1, 8);
		printf("Current Player %d: %d card(s).\n", currPlayer, handCount);
		G.handCount[currPlayer] = handCount;
		G.hand[currPlayer][0] = card;
		// fills hand from supply
		int startIndex = 1;
		fillHand(currPlayer, startIndex, handCount, &G);
		// fills other hands from supply
		for (i = 0; i < numPlayers; i++) {
			if (i != currPlayer) {
				int otherHandCount = myrand(0, 10);
				printf("Player %d: %d card(s).\n", i, otherHandCount);
				G.handCount[i] = otherHandCount;
				fillHand(i, 0, otherHandCount, &G);
			}
		}
		// randomize coins
		G.coins = myrand(0, INT_MAX - 2);
		// randomize actions
		G.numActions = myrand(0, 5);
		
		// check values
		if (DEBUG) {
			printHand(currPlayer, &G);
			printDeck(currPlayer, &G); // deck is non-empty, initialized with 3 estates and 7 copper
			printDiscard(currPlayer, &G); // discard count 0
		}

		int choice1 = myrand(0, 2); // > 0, chose to gain coins
		printf("choice1 (to gain coins) = %d.\n", choice1);
		int choice2 = myrand(0, 2); // > 0, chose discard/redraw
		printf("choice2 (to discard/draw) = %d.\n", choice2);
		int handPos = 0; // minion card in position 0

		/*
		 * CALCULATE EXPECTED RESULTS
		 */
		int expectedResult;
		// number of minion cards - may have added when filling hand
		int currentMinionCount =
			getCount(G.hand[currPlayer], G.handCount[currPlayer], minion) + 
			getCount(G.deck[currPlayer], G.deckCount[currPlayer], minion) +
			getCount(G.discard[currPlayer], G.discardCount[currPlayer], minion);
		int expectedMinionCount;	// in deck, hand, discard
		int expectedHandCounts[numPlayers];
		int expectedPlayedCardCount;
		int expectedDeckCounts[numPlayers];
		int expectedCoinCount;
		int expectedDiscardCounts[numPlayers];
		int expectedActionCount;

		bool curr = G.whoseTurn;
		// option 0 - no change, return failure
		if ((choice1 && choice2) || (!choice1 && !choice2)) {
			expectedResult = FALSE; // failure
			expectedMinionCount = currentMinionCount;
			expectedCoinCount = G.coins;
			expectedPlayedCardCount = G.playedCardCount;
			expectedActionCount = G.numActions;
			for (j = 0; j < numPlayers; j++) {
				// hands
				expectedHandCounts[j] = G.handCount[j];
				// deck
				expectedDeckCounts[j] = G.deckCount[j];
				// discard
				expectedDiscardCounts[j] = G.discardCount[j];
			}
		} // option 1 - gained coins
		else if (choice1) {
			expectedResult = TRUE; // success
			expectedMinionCount = currentMinionCount - 1;
			expectedCoinCount = G.coins + 2;
			expectedPlayedCardCount = G.playedCardCount + 1;
			expectedActionCount = G.numActions + 1;
			for (j = 0; j < numPlayers; j++) {
				// hands
				expectedHandCounts[j] = G.handCount[j];
				if (j == curr) { expectedHandCounts[j] -= 1; } // minion card was played
				// deck
				expectedDeckCounts[j] = G.deckCount[j];
				// discard
				expectedDiscardCounts[j] = G.discardCount[j];
			}
		} // option 2 - discard/draw cards
		else if (choice2) {
			expectedResult = TRUE; // success
			expectedMinionCount = currentMinionCount - 1;
			expectedCoinCount = G.coins;
			expectedPlayedCardCount = G.playedCardCount + 1;
			expectedActionCount = G.numActions + 1;
			for (j = 0; j < numPlayers; j++) {
				if (j == curr || G.handCount[j] > 4) {
					expectedHandCounts[j] = 4;
					expectedDeckCounts[j] = G.deckCount[j] - 4; // drew cards from deck
					expectedDiscardCounts[j] = G.discardCount[j] + G.handCount[j];
					if (j == curr) { expectedDiscardCounts[j] -= 1; } // minion card was played not discarded
				}
				else {
					// no change
					expectedHandCounts[j] = G.handCount[j];
					expectedDeckCounts[j] = G.deckCount[j];
					expectedDiscardCounts[j] = G.discardCount[j];
				}
			}
		}

		int result = minionEffect(card, choice1, choice2, &G, handPos);
		
		printf("1) Function successful if either choice1 or choice2 (not both or neither).\n");
		char *successStatement = expectedResult ? "Function returns >= 0 (Success)." : "Function returns < 0 (Failure).";
		assert(successStatement, result >= 0, expectedResult);
		
		printf("2) Minion card played only if success.\n");
		assert("Played card count correct.", G.playedCardCount, expectedPlayedCardCount);
		if (expectedResult) {
			assert("Minion placed at top of played cards.", G.playedCards[G.playedCardCount - 1], minion);
		}
		else {
			assert("Minion still in hand.", G.hand[currPlayer][0], card);
		}
		int minionCount = getCount(G.hand[currPlayer], G.handCount[currPlayer], minion) + 
			getCount(G.deck[currPlayer], G.deckCount[currPlayer], minion) +
			getCount(G.discard[currPlayer], G.discardCount[currPlayer], minion);
		assert("Minion count correct (-1 from hand + deck + discard if played).", minionCount, expectedMinionCount);

		printf("3) +1 Action only if success.\n");
		assert("Action count correct.", G.numActions, expectedActionCount);

		printf("4) +2 Coins only if success and choice1.\n");
		assert("Coin count correct", G.coins, expectedCoinCount);

		printf("5) Hands discarded and redrawn correctly (or unchanged) per success and choice.\n");
		for (j = 0; j < numPlayers; j++) {
			if (DEBUG) {
				printf("Player %d:\n", j);
				printf("Hand: %d, Deck: %d, Discard: %d\n", G.handCount[j], G.deckCount[j], G.discardCount[j]);
			}
			assert("Hand count correct.", G.handCount[j], expectedHandCounts[j]);
			assert("Deck count correct.", G.deckCount[j], expectedDeckCounts[j]);
			assert("Discard count correct.", G.discardCount[j], expectedDiscardCounts[j]);
		}

		printf("\n\n");
	}
}

int main() {
	int random_seed = 1;
	srand(random_seed);
	testMinion(random_seed);
	return 0;
}