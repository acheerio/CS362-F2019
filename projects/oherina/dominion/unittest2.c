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
	state.numActions = 1;
	int numActionsExpected = state.numActions + 1;
	
	// current player's hand = minion
	state.handCount[state.whoseTurn] = 1;
	int expectedHandCount = state.handCount[state.whoseTurn] - 1;
	state.hand[state.whoseTurn][0] = minion;
	int handPos = 0; // minion card in position 0
	
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
	
	printf("6) +1 Action.\n");
	assert("Actions incremented by 1", state.numActions, numActionsExpected);
	printf("\n\n");
}

void minionTest2(struct gameState state) {
	printf("Minion - currentPlayer has no cards to discard before redraw, other player has 4 cards so no discard or redraw.\n");

	state.whoseTurn = 0;
	// current player's hand = minion
	state.hand[state.whoseTurn][0] = minion;
	// next player's hand = copper, copper, copper, copper
	fillHand(state.whoseTurn + 1, copper, 4, &state);
	
	// unchanged: coins, currentPlayer discard, next player's discard & hand
	state.coins = 2;
	int coinsExpected = state.coins;
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn];
	int nextPlayerHandCountExpected = state.handCount[state.whoseTurn + 1]; // handCount set in fillHand
	state.discardCount[state.whoseTurn + 1] = 0;
	int nextPlayerDiscardCountExpected = state.discardCount[state.whoseTurn + 1];
	
	// changed: played cards + 1, current player's hand count = 4, numActions + 1
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount + 1;
	state.handCount[state.whoseTurn] = 1;
	int handCountExpected = 4;
	state.numActions = 1;
	int numActionsExpected = state.numActions + 1;
	
	int card = minion;
	int choice1 = 0; 
	int choice2 = 1; // chose to discard and redraw
	int handPos = 0; // minion card in position 0
	
	int result = minionEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);
	
	printf("2) Minion card played.\n");
	assert("Minion removed from hand.", hasCard(state.whoseTurn, minion, state), FALSE);
	assert("Played cards +1.", state.playedCardCount, playedCardCountExpected);
	assert("Minion placed at top of played cards.", state.playedCards[state.playedCardCount - 1], minion);
	
	printf("3) Current player no cards discarded.\n");
	assert("Number of cards in discard unchanged.", state.discardCount[state.whoseTurn], discardCountExpected);
	
	printf("4) Current player correct number of cards in hand.\n");
	assert("Four cards in hand.", state.handCount[state.whoseTurn], handCountExpected);
	
	printf("5) Other player no cards discarded.\n");
	assert("Number of cards in discard unchanged.", state.discardCount[state.whoseTurn + 1], nextPlayerDiscardCountExpected);
	
	printf("6) Other player correct number of cards in hand.\n");
	assert("Still same number (four) cards in hand.", state.handCount[state.whoseTurn + 1], nextPlayerHandCountExpected);
	
	printf("7) No coins gained.\n");
	assert("+0 Coins", state.coins, coinsExpected);
	
	printf("8) +1 Action.\n");
	assert("Actions incremented by 1", state.numActions, numActionsExpected);
	
	printf("\n\n");
}

void minionTest3(struct gameState state) {
	printf("Minion - currentPlayer has no cards to discard before redraw, other player has > 4 cards so discards and redraws.\n");
	
	state.whoseTurn = 0;
	// current player's hand = minion
	state.hand[state.whoseTurn][0] = minion;
	// next player's hand = copper, copper, copper, copper, copper
	int nextPlayerHandCount = 5;
	fillHand(state.whoseTurn + 1, copper, nextPlayerHandCount, &state);
	
	// unchanged: coins, currentPlayer discard
	state.coins = 2;
	int coinsExpected = state.coins;
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn];
	
	// changed: played cards + 1, current player's hand count = 4, numActions + 1, next player's hand and discard
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount + 1;
	state.handCount[state.whoseTurn] = 1;
	int handCountExpected = 4;
	int nextPlayerHandCountExpected = 4; // not dependent on former value as long as > 4
	state.discardCount[state.whoseTurn + 1] = 0;
	int nextPlayerDiscardCountExpected = nextPlayerHandCount; // discards whole hand
	state.numActions = 1;
	int numActionsExpected = state.numActions + 1;
	
	int card = minion;
	int choice1 = 0; 
	int choice2 = 1; // chose to discard and redraw
	int handPos = 0; // minion card in position 0
	
	int result = minionEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);
	
	printf("2) Minion card played.\n");
	assert("Minion removed from hand.", hasCard(state.whoseTurn, minion, state), FALSE);
	assert("Played cards +1.", state.playedCardCount, playedCardCountExpected);
	assert("Minion placed at top of played cards.", state.playedCards[state.playedCardCount - 1], minion);
	
	printf("3) Current player no cards discarded.\n");
	assert("Number of cards in discard unchanged.", state.discardCount[state.whoseTurn], discardCountExpected);
	
	printf("4) Current player correct number of cards in hand.\n");
	assert("Four cards in hand.", state.handCount[state.whoseTurn], handCountExpected);
	
	printf("5) Other player full hand discarded.\n");
	assert("Number of cards in discard = previous hand count.", state.discardCount[state.whoseTurn + 1], nextPlayerDiscardCountExpected);
	
	printf("6) Other player correct number of cards in hand.\n");
	assert("Four cards in hand.", state.handCount[state.whoseTurn + 1], nextPlayerHandCountExpected);
	
	printf("7) No coins gained.\n");
	assert("+0 Coins", state.coins, coinsExpected);
	
	printf("8) +1 Action.\n");
	assert("Actions incremented by 1", state.numActions, numActionsExpected);
	
	printf("\n\n");
}
void minionTest4(struct gameState state) {
	printf("Minion - currentPlayer has cards to discard before redraw, other player has 4 cards so no discard.\n");
	
	state.whoseTurn = 0;
	// current player's hand = minion, copper
	state.hand[state.whoseTurn][0] = minion;
	state.hand[state.whoseTurn][1] = copper;
	// next player's hand = copper, copper, copper, copper, copper
	int nextPlayerHandCount = 4;
	fillHand(state.whoseTurn + 1, copper, nextPlayerHandCount, &state);
	
	// unchanged: coins
	state.coins = 2;
	int coinsExpected = state.coins;
	// unchanged: next player's hand and discard
	int nextPlayerHandCountExpected = nextPlayerHandCount; // no cards drawn
	state.discardCount[state.whoseTurn + 1] = 0;
	int nextPlayerDiscardCountExpected = state.discardCount[state.whoseTurn + 1]; // no discard
	
	// changed: played cards + 1, current player's hand count = 4, current player's discard + 1
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount + 1;
	state.handCount[state.whoseTurn] = 2;
	int handCountExpected = 4;
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn] + 1;
	// changed state: numActions + 1
	state.numActions = 1;
	int numActionsExpected = state.numActions + 1;
	
	int card = minion;
	int choice1 = 0; 
	int choice2 = 1; // chose to discard and redraw
	int handPos = 0; // minion card in position 0
	
	int result = minionEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);
	
	printf("2) Minion card played.\n");
	assert("Minion removed from hand.", hasCard(state.whoseTurn, minion, state), FALSE);
	assert("Played cards +1.", state.playedCardCount, playedCardCountExpected);
	assert("Minion placed at top of played cards.", state.playedCards[state.playedCardCount - 1], minion);
	
	printf("3) Current player card discarded.\n");
	assert("Number of cards in discard +1.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Copper at top of discard pile.", state.discard[state.whoseTurn][state.discardCount[state.whoseTurn] - 1], copper);
	
	printf("4) Current player correct number of cards in hand.\n");
	assert("Four cards in hand.", state.handCount[state.whoseTurn], handCountExpected);
	
	printf("5) Other player full hand discarded.\n");
	assert("Number of cards in discard = previous hand count.", state.discardCount[state.whoseTurn + 1], nextPlayerDiscardCountExpected);
	
	printf("6) Other player correct number of cards in hand.\n");
	assert("Four cards in hand.", state.handCount[state.whoseTurn + 1], nextPlayerHandCountExpected);
	
	printf("7) No coins gained.\n");
	assert("+0 Coins", state.coins, coinsExpected);
	
	printf("8) +1 Action.\n");
	assert("Actions incremented by 1", state.numActions, numActionsExpected);
	
	printf("\n\n");
}
void minionTest5(struct gameState state) {
	printf("Minion - currentPlayer has cards to discard before redraw, other player has > 4 cards so discard.\n");
	
	state.whoseTurn = 0;
	// current player's hand = minion, copper
	state.hand[state.whoseTurn][0] = minion;
	state.hand[state.whoseTurn][1] = copper;
	// next player's hand = copper, copper, copper, copper, copper
	int nextPlayerHandCount = 5;
	fillHand(state.whoseTurn + 1, copper, nextPlayerHandCount, &state);
	
	// unchanged: coins
	state.coins = 2;
	int coinsExpected = state.coins;
	
	// changed: played cards + 1, current player's hand count = 4, current player's discard + 1
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount + 1;
	state.handCount[state.whoseTurn] = 2;
	int handCountExpected = 4;
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn] + 1;
	// changed: next player's hand and discard
	int nextPlayerHandCountExpected = 4; // not dependent on former value as long as > 4
	state.discardCount[state.whoseTurn + 1] = 0;
	int nextPlayerDiscardCountExpected = nextPlayerHandCount; // discards whole hand
	// changed state: numActions + 1
	state.numActions = 1;
	int numActionsExpected = state.numActions + 1;
	
	int card = minion;
	int choice1 = 0; 
	int choice2 = 1; // chose to discard and redraw
	int handPos = 0; // minion card in position 0
	
	int result = minionEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);
	
	printf("2) Minion card played.\n");
	assert("Minion removed from hand.", hasCard(state.whoseTurn, minion, state), FALSE);
	assert("Played cards +1.", state.playedCardCount, playedCardCountExpected);
	assert("Minion placed at top of played cards.", state.playedCards[state.playedCardCount - 1], minion);
	
	printf("3) Current player card discarded.\n");
	assert("Number of cards in discard +1.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Copper at top of discard pile.", state.discard[state.whoseTurn][state.discardCount[state.whoseTurn] - 1], copper);
	
	printf("4) Current player correct number of cards in hand.\n");
	assert("Four cards in hand.", state.handCount[state.whoseTurn], handCountExpected);
	
	printf("5) Other player full hand discarded.\n");
	assert("Number of cards in discard = previous hand count.", state.discardCount[state.whoseTurn + 1], nextPlayerDiscardCountExpected);
	
	printf("6) Other player correct number of cards in hand.\n");
	assert("Four cards in hand.", state.handCount[state.whoseTurn + 1], nextPlayerHandCountExpected);
	
	printf("7) No coins gained.\n");
	assert("+0 Coins", state.coins, coinsExpected);
	
	printf("8) +1 Action.\n");
	assert("Actions incremented by 1", state.numActions, numActionsExpected);
	
	printf("\n\n");
}
void minionTest6(struct gameState state) {
	printf("Minion - Both choice1 and choice2 > 0.\n");
}
void minionTest7(struct gameState state) {
	printf("Minion - Both choice1 and choice2 = 0.\n");
}

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
	minionTest7(G);	
}

int main() {
	testMinion();
	return 0;
}
