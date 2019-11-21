#include "dominion.h"
#include "dominion_helpers.h"
#include "testhelper.h"
#include <stdlib.h>
#include <stdio.h>

void tributeTest1(struct gameState state) {
	printf("Tribute - next player has only 1 card total in deck (treasure)\n");
	
	state.whoseTurn = 0;
	// current player's hand = tribute
	state.handCount[state.whoseTurn] = 1;
	int handCountExpected = state.handCount[state.whoseTurn] - 1;
	state.hand[state.whoseTurn][0] = tribute;
	int handPos = 0; // played card in position 0
	
	// current player's deck = copper copper copper copper
	state.deckCount[state.whoseTurn] = 4;
	int deckCountExpected = state.deckCount[state.whoseTurn];
	state.deck[state.whoseTurn][0] = copper;
	state.deck[state.whoseTurn][1] = copper;
	state.deck[state.whoseTurn][2] = copper;
	state.deck[state.whoseTurn][3] = copper;
	
	// next player's discard empty, deck has 1 card
	int nextPlayer = state.whoseTurn + 1;
	state.discardCount[nextPlayer] = 0;
	state.deckCount[nextPlayer] = 1;
	int tribute1 = copper;
	state.deck[nextPlayer][state.deckCount[nextPlayer] - 1] = tribute1;
	
	// play tribute
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount + 1;
	
	// next player discards card
	int npDiscardCountExpected = state.discardCount[nextPlayer] + 1;
	
	// current player gains 2 coins
	state.coins = 1;
	int coinsExpected = state.coins + 2;
	state.numActions = 1;
	int numActionsExpected = state.numActions;
	
	int card = tribute;
	int result = tributeEffect(card, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);
	
	printf("2) Tribute card played.\n");
	assert("Tribute removed from hand.", hasCard(state.whoseTurn, card, state), FALSE);
	assert("Played cards +1.", state.playedCardCount, playedCardCountExpected);
	assert("Tribute placed at top of played cards.", state.playedCards[state.playedCardCount - 1], card);
	
	printf("3) Next player discards tribute card(s).\n");
	assert("Discard pile +1.", state.discardCount[nextPlayer], npDiscardCountExpected);
	assert("Top of discard pile is tribute.", state.discard[nextPlayer][state.discardCount[nextPlayer] - 1], tribute1);
	
	printf("4) Current player gains correct (amounts of) rewards.\n");
	assert("Coins +2.", state.coins, coinsExpected);
	assert("Actions unchanged.", state.numActions, numActionsExpected);
	assert("Hand count as expected (0 cards drawn).", state.handCount[state.whoseTurn], handCountExpected);
	
	printf("\n\n");
}

void tributeTest2(struct gameState state) {
	printf("Tribute - next player has empty deck but cards in discard\n");
	
	state.whoseTurn = 0;
	// current player's hand = tribute
	state.handCount[state.whoseTurn] = 1;
	int handCountExpected = state.handCount[state.whoseTurn] + 1;
	state.hand[state.whoseTurn][0] = tribute;
	int handPos = 0; // played card in position 0
	
	// current player's deck = copper copper copper copper
	state.deckCount[state.whoseTurn] = 4;
	int deckCountExpected = state.deckCount[state.whoseTurn] - 2;
	state.deck[state.whoseTurn][0] = copper;
	state.deck[state.whoseTurn][1] = copper;
	state.deck[state.whoseTurn][2] = copper;
	state.deck[state.whoseTurn][3] = copper;
	
	// next player's discard has cards, deck empty
	int nextPlayer = state.whoseTurn + 1;
	state.discardCount[nextPlayer] = 5;
	int tribute1 = estate;
	state.discard[nextPlayer][0] = tribute1;
	state.discard[nextPlayer][1] = tribute1;
	state.discard[nextPlayer][2] = tribute1;
	state.discard[nextPlayer][3] = tribute1;
	state.discard[nextPlayer][4] = tribute1;
	state.deckCount[nextPlayer] = 0;
	
	// play tribute
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount + 1;
	
	// next player discards cards
	int npDiscardCountExpected = 2; // other discards were shuffled
	
	// current player gains 2 cards
	state.coins = 1;
	int coinsExpected = state.coins;
	state.numActions = 1;
	int numActionsExpected = state.numActions;
	
	int card = tribute;
	int result = tributeEffect(card, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);
	
	printf("2) Tribute card played.\n");
	assert("Tribute removed from hand.", hasCard(state.whoseTurn, card, state), FALSE);
	assert("Played cards +1.", state.playedCardCount, playedCardCountExpected);
	assert("Tribute placed at top of played cards.", state.playedCards[state.playedCardCount - 1], card);
	
	printf("3) Next player discards tribute card(s).\n");
	assert("Discard pile 2.", state.discardCount[nextPlayer], npDiscardCountExpected);
	assert("Top of discard pile is tribute.", state.discard[nextPlayer][state.discardCount[nextPlayer] - 1], tribute1);
	
	printf("4) Current player gains correct (amounts of) rewards.\n");
	assert("Coins +0.", state.coins, coinsExpected);
	assert("Actions unchanged.", state.numActions, numActionsExpected);
	assert("Hand count as expected (2 cards drawn).", state.handCount[state.whoseTurn], handCountExpected);
	assert("Current player draws two cards.", state.deckCount[state.whoseTurn], deckCountExpected);
	
	printf("\n\n");
}

void testTribute() {
	int seed = 1; // need some constant here that's deterministic (vs seeding by time)
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, minion, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	// calling tests and passing by value since we want gameState unchanged
	tributeTest1(G);
	tributeTest2(G);
}

int main() {
	testTribute();
	return 0;
}