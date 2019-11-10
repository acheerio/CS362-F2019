#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffect.h"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>

void mineTest1(struct gameState state) {
	printf("choice1 and choice2 are valid, choice2 cost < choice1 cost\n");
	
}

void mineTest2(struct gameState state) {
	printf("choice1 and choice2 are valid, choice2 cost = choice1 cost + 3 (silver -> gold)\n");
	
	state.whoseTurn = 0;
	
	// current player's hand = mine silver
	state.handCount[state.whoseTurn] = 2;
	int handCountExpected = state.handCount[state.whoseTurn] - 1;
	state.hand[state.whoseTurn][0] = minion;
	state.hand[state.whoseTurn][0] = silver;
	int handPos = 0; // played card in position 0
	int cardToTrash = silver;
	
	// play mine
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount + 1;
	
	// trash treasure
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn]; // trashed not discarded
	
	// gain treasure
	int cardToGain = gold;
	int supplyCountExpected = state.supplyCount[gold] - 1;
	
	int card = mine;
	int choice1 = 1; // index of card to trash
	int choice2 = cardToGain; // value of card to gain
	
	int result = mineEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);
	
	printf("2) Mine card played.\n");
	assert("Mine removed from hand.", hasCard(state.whoseTurn, mine, state), FALSE);
	assert("Played cards incremented.", state.playedCardCount, playedCardCountExpected);
	assert("Mine placed at top of played cards.", state.playedCards[state.playedCardCount - 1], mine);
	
	printf("3) Treasure trashed.\n");
	assert("Number of cards in discard unchanged.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Treasure no longer in hand.", hasCard(state.whoseTurn, cardToTrash, state), FALSE);
	
	printf("4) Treasure gained.\n");
	assert("Supply count -1.", state.supplyCount[cardToGain], supplyCountExpected);
	assert("Treasure in hand.", hasCard(state.whoseTurn, cardToGain, state), TRUE);
	
	printf("5) Correct number of cards in hand.\n");
	assert("Hand count -1.", state.handCount[state.whoseTurn], handCountExpected);
	
	printf("\n\n");
}

void mineTest3(struct gameState state) {
	printf("choice1 and choice2 are valid, choice2 cost = choice1 cost + 3 (copper -> silver)\n");
	
	state.whoseTurn = 0;
	
	// current player's hand = mine copper
	state.handCount[state.whoseTurn] = 2;
	int handCountExpected = state.handCount[state.whoseTurn] - 1;
	state.hand[state.whoseTurn][0] = minion;
	state.hand[state.whoseTurn][0] = copper;
	int handPos = 0; // played card in position 0
	int cardToTrash = copper;
	
	// play mine
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount + 1;
	
	// trash treasure
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn]; // trashed not discarded
	
	// gain treasure
	int cardToGain = silver;
	int supplyCountExpected = state.supplyCount[silver] - 1;
	
	int card = mine;
	int choice1 = 1; // index of card to trash
	int choice2 = cardToGain; // value of card to gain
	
	int result = mineEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);
	
	printf("2) Mine card played.\n");
	assert("Mine removed from hand.", hasCard(state.whoseTurn, mine, state), FALSE);
	assert("Played cards incremented.", state.playedCardCount, playedCardCountExpected);
	assert("Mine placed at top of played cards.", state.playedCards[state.playedCardCount - 1], mine);
	
	printf("3) Treasure trashed.\n");
	assert("Number of cards in discard unchanged.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Treasure no longer in hand.", hasCard(state.whoseTurn, cardToTrash, state), FALSE);
	
	printf("4) Treasure gained.\n");
	assert("Supply count -1.", state.supplyCount[cardToGain], supplyCountExpected);
	assert("Treasure in hand.", hasCard(state.whoseTurn, cardToGain, state), TRUE);
	
	printf("5) Correct number of cards in hand.\n");
	assert("Hand count -1.", state.handCount[state.whoseTurn], handCountExpected);
	
	printf("\n\n");
}

void mineTest4(struct gameState state) {
	printf("choice1 and choice2 are valid, choice2 is the last of its kind in supply\n");
	state.whoseTurn = 0;
}
void mineTest5(struct gameState state) {
	printf("choice1 and choice2 are valid, current player = 1\n");
	state.whoseTurn = 1;
}
void mineTest6(struct gameState state) {
	printf("choice1 is not a treasure card\n");
	state.whoseTurn = 0;
}
void mineTest7(struct gameState state) {
	printf("choice1 is not valid index in player's hand\n");
	state.whoseTurn = 0;
}
void mineTest8(struct gameState state) {
	printf("choice2 is not a treasure card\n");
	state.whoseTurn = 0;
}

void mineTest9(struct gameState state) {
	printf("choice2 is not in the supply\n");
	state.whoseTurn = 0;
}

void mineTest10(struct gameState state) {
	printf("choice2 costs too much\n");
	state.whoseTurn = 0;
}

void testMine() {
	int seed = 1; // need some constant here that's deterministic (vs seeding by time)
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, minion, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	// calling tests and passing by value since we want gameState unchanged
	mineTest1(G);
	mineTest2(G);
	mineTest3(G);
	mineTest4(G);
	mineTest5(G);
	mineTest6(G);
	mineTest7(G);
	mineTest8(G);
	mineTest9(G);
}

int main() {
	testMine();
	return 0;
}
