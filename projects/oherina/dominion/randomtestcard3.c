#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "cardEffect.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "randomhelper.h"

void testTribute(int random_seed) {
	int n, i;
	int NUMRUNS = 100;
	for (n = 0; n < NUMRUNS; n++) {
		printf("TRIBUTE - TRIAL %d\n", n + 1);
		/*
		 * GENERATE RANDOM GAME
		 */
		// set card in question
		int card = tribute;
		// generate random number of players, currentPlayer
		int numPlayers = myrand(2, 5);
		printf("Total players: %d\n", numPlayers);
		int currPlayer = myrand(0, numPlayers);
		int nextPlayer = (currPlayer + 1) % numPlayers;
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
		// fill current player's random hand, from 1 (tribute only) to 3 cards
		int handCount = myrand(1, 4);
		G.handCount[currPlayer] = handCount;
		printf("Current player: %d.\n", currPlayer);
		G.hand[currPlayer][0] = card;
		int startIndex = 1;
		fillHand(currPlayer, startIndex, handCount, &G);
		// fill next player's deck, discard
		int nextDeckCount = myrand(0, 3); // 0, 1, 2
		G.deckCount[nextPlayer] = nextDeckCount;
		printf("Next player's deck:");
		for (i = 0; i < nextDeckCount; i++) {
			G.deck[nextPlayer][i] = getRandomFromSupply(&G);
			printf(" %d", G.deck[nextPlayer][i]);
		}
		printf("\n");
		printf("Next player's discard:");
		int nextDiscardCount = myrand(0, 3); // 0, 1, 2
		G.discardCount[nextPlayer] = nextDiscardCount;
		for (i = 0; i < nextDiscardCount; i++) {
			G.discard[nextPlayer][i] = getRandomFromSupply(&G);
			printf(" %d", G.discard[nextPlayer][i]);
		}
		printf("\n");
		// randomize coins
		G.coins = myrand(0, INT_MAX - 4);
		// randomize actions
		G.numActions = myrand(0, INT_MAX - 4);
		// randomize 
		
		// check values
		if (DEBUG) {
			printHand(currPlayer, &G);
			printDeck(currPlayer, &G); // deck is non-empty, initialized with 3 estates and 7 copper
			printDiscard(currPlayer, &G); // discard count 0
		}

		int handPos = 0; // tribute card in position 0

		/*
		 * CALCULATE EXPECTED RESULTS
		 */
		int expectedTributeCount = getCount(G.hand[currPlayer], G.handCount[currPlayer], card) - 1;	// in deck, hand, discard
		int expectedHandCount = G.handCount[currPlayer];
		int expectedDeckCount = G.deckCount[currPlayer];
		int expectedPlayedCardCount = G.playedCardCount + 1;
		int expectedNextDeckCount = G.deckCount[nextPlayer] >= 2 ? G.deckCount[nextPlayer] - 2 : max(0, G.deckCount[nextPlayer] + G.discardCount[nextPlayer] - 2);
		int expectedNextDiscardCount = G.deckCount[nextPlayer] >= 2 ? G.discardCount[nextPlayer] + 2 : min(2, G.deckCount[nextPlayer] + G.discardCount[nextPlayer]);
		int expectedCoinCount = G.coins;
		int expectedActionCount = G.numActions;

		int tributeCards[2] = {-1, -1};
		int tributeCount = 0;
		int index = G.deckCount[nextPlayer] - 1;
		bool randomDraw = FALSE;

		// get the tribute card
		while (index >= 0 && tributeCount < 2) {
			tributeCards[tributeCount] = G.deck[nextPlayer][index];
			index--;
			tributeCount++;
		}
		if (tributeCount < 2) {
			if (G.discardCount[nextPlayer] <= (2 - tributeCount)) {
				index = G.discardCount[nextPlayer] - 1;
				while (index >= 0 && tributeCount < 2) {
					tributeCards[tributeCount] = G.discard[nextPlayer][index];
					index--;
					tributeCount++;
				}
			}
			else {
				printf("Random draw - discard pile has multiple tribute options.\n");
				printf("We can't predict the random shuffle so tests use >= not ==.\n");
				randomDraw = TRUE;
			}
		}
		// discard duplicate
		if (tributeCount == 2 && tributeCards[0] == tributeCards[1]) {
			tributeCards[1] = -1;
			tributeCount--;
		}

		// calculate the bonuses
		for (i = 0; i < tributeCount; i++) {
			int cardForTribute = tributeCards[i];
			printf("Tribute: %d\n", cardForTribute);
			// Victory, +2 Cards
			if ((cardForTribute >= estate && cardForTribute <= province) || 
				cardForTribute == gardens || cardForTribute == great_hall) {
				expectedHandCount += 2;
				expectedDeckCount -= 2;
			}
			// Treasure, +2 Coins
			if (cardForTribute >= copper && cardForTribute <= gold) {
				expectedCoinCount += 2;
			}
			// Action, +2 Actions
			if (cardForTribute >= adventurer && cardForTribute <= treasure_map &&
				cardForTribute != gardens) {
				expectedActionCount += 2;
			}
		}

		int result = tributeEffect(card, &G, handPos);

		printf("1) Function successful.\n");
		assert("Function returns >= 0 (Success).", result >= 0, TRUE);

		printf("2) Tribute card played.\n");
		assert("Tribute removed from hand.", getCount(G.hand[currPlayer], G.handCount[currPlayer], card), expectedTributeCount);
		assert("Played card count +1.", G.playedCardCount, expectedPlayedCardCount);
		assert("Tribute placed at top of played cards.", G.playedCards[G.playedCardCount - 1], card);

		printf("3) Next player revealed cards.\n");
		assert("Correct number of cards in next player's deck.", G.deckCount[nextPlayer], expectedNextDeckCount);
		assert("Correct number of cards in next player's discard.", G.discardCount[nextPlayer], expectedNextDiscardCount);

		if (DEBUG) {
			printf("Hand: %d Deck: %d Coins: %d Actions: %d\n", G.handCount[currPlayer], G.deckCount[currPlayer], G.coins, G.numActions);
		}
		printf("4) Current player gained expected bonuses for tribute.\n");
		int handCountStatement = randomDraw ? G.handCount[currPlayer] >= expectedHandCount : G.handCount[currPlayer] == expectedHandCount;
		assert("Hand count +2 per Victory card.", handCountStatement, TRUE);
		int deckCountStatement = randomDraw ? G.deckCount[currPlayer] <= expectedDeckCount : G.deckCount[currPlayer] == expectedDeckCount;
		assert("Deck count -2 per Victory card.", deckCountStatement, TRUE);
		int coinsStatement = randomDraw ? G.coins >= expectedCoinCount : G.coins == expectedCoinCount;
		assert("Coins +2 per Treasure card.", coinsStatement, TRUE);
		int actionsStatement = randomDraw ? G.numActions >= expectedActionCount : G.numActions == expectedActionCount;
		assert("Actions +2 per Action card.", actionsStatement, TRUE);

		printf("\n\n");
	}
}

int main() {
	int random_seed = 1;
	srand(random_seed);
	testTribute(random_seed);
	return 0;
}