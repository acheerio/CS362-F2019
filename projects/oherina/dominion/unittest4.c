#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffect.h"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>

void ambassadorTest1(struct gameState state) {
	printf("Ambassador - choose to discard 1, have 2 of valid choice1\n");
	
	state.whoseTurn = 0;
	
	// current player's hand = ambassador estate estate
	state.handCount[state.whoseTurn] = 3;
	int handCountExpected = state.handCount[state.whoseTurn] - 2;
	int choice1Card = estate;
	state.hand[state.whoseTurn][0] = ambassador;
	state.hand[state.whoseTurn][1] = choice1Card;
	state.hand[state.whoseTurn][2] = choice1Card;
	int handPos = 0; // played card in position 0
	
	// play ambassador
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount + 1;
	
	// discard choice1
	int choice1CountExpected = getCount(state.whoseTurn, choice1Card, state) - 1;
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn]; // to supply not discard
	
	// other player gains choice1 (0 -> 1)
	state.handCount[state.whoseTurn + 1] = 0;
	int nextPlayerHandExpected = state.handCount[state.whoseTurn + 1] + 1;
	int nextPlayerChoice1CountExpected = 1;
	int supplyCountExpected = state.supplyCount[choice1Card];
	
	int card = ambassador;
	int choice1 = 1; // index of card to discard to supply
	int choice2 = 1; // number of cards to discard to supply
	
	int result = ambassadorEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);

	printf("2) Ambassador card played.\n");
	assert("Ambassador removed from hand.", hasCard(state.whoseTurn, card, state), FALSE);
	assert("Played cards +1.", state.playedCardCount, playedCardCountExpected);
	assert("Card placed at top of played cards.", state.playedCards[state.playedCardCount - 1], ambassador);

	printf("3) Choice1 discarded to supply.\n");
	assert("Number of cards in discard unchanged.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Card instances in hand -1.", getCount(state.whoseTurn, choice1Card, state), choice1CountExpected);

	printf("4) Choice1 gained by next player.\n");
	assert("Number of cards in supply net unchanged.", state.supplyCount[choice1Card],supplyCountExpected);
	assert("Card instances in hand +1.", getCount(state.whoseTurn + 1, choice1Card, state), nextPlayerChoice1CountExpected);
	
	printf("5) Correct number of cards in hands.\n");
	assert("Current player hand count -2.", state.handCount[state.whoseTurn], handCountExpected);
	assert("Next player hand count +1.", state.handCount[state.whoseTurn + 1], nextPlayerHandExpected);
	
	printf("\n\n");
}

void ambassadorTest2(struct gameState state) {
	printf("Ambassador - choose to discard 1 (to supply), have 1 of valid choice1\n");
	state.whoseTurn = 0;
	
	// current player's hand = ambassador village
	state.handCount[state.whoseTurn] = 4;
	int handCountExpected = state.handCount[state.whoseTurn] - 2;
	int choice1Card = curse;
	state.hand[state.whoseTurn][0] = ambassador;
	state.hand[state.whoseTurn][1] = copper;
	state.hand[state.whoseTurn][2] = copper;
	state.hand[state.whoseTurn][3] = choice1Card;
	// state.hand[state.whoseTurn][2] = choice1Card;
	int handPos = 0; // played card in position 0
	
	// play ambassador
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount + 1;
	
	// discard choice1
	int choice1CountExpected = getCount(state.whoseTurn, choice1Card, state) - 1;
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn]; // to supply not discard
	
	// other player gains choice1 (0 -> 1)
	state.handCount[state.whoseTurn + 1] = 0;
	int nextPlayerHandExpected = state.handCount[state.whoseTurn + 1] + 1;
	int nextPlayerChoice1CountExpected = 1;
	int supplyCountExpected = state.supplyCount[choice1Card];
	
	int card = ambassador;
	int choice1 = 3; // index of card to discard to supply
	int choice2 = 1; // number of cards to discard to supply
	
	int result = ambassadorEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);

	printf("2) Ambassador card played.\n");
	assert("Ambassador removed from hand.", hasCard(state.whoseTurn, card, state), FALSE);
	assert("Played cards +1.", state.playedCardCount, playedCardCountExpected);
	assert("Card placed at top of played cards.", state.playedCards[state.playedCardCount - 1], ambassador);

	printf("3) Choice1 discarded to supply.\n");
	assert("Number of cards in discard unchanged.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Card instances in hand -1.", getCount(state.whoseTurn, choice1Card, state), choice1CountExpected);

	printf("4) Choice1 gained by next player.\n");
	assert("Number of cards in supply net unchanged.", state.supplyCount[choice1Card],supplyCountExpected);
	assert("Card instances in hand +1.", getCount(state.whoseTurn + 1, choice1Card, state), nextPlayerChoice1CountExpected);
	
	printf("5) Correct number of cards in hands.\n");
	assert("Current player hand count -2.", state.handCount[state.whoseTurn], handCountExpected);
	assert("Next player hand count +1.", state.handCount[state.whoseTurn + 1], nextPlayerHandExpected);
	
	printf("\n\n");
}

void ambassadorTest3(struct gameState state) {
	printf("Ambassador - choose to discard 0, have 1 of valid choice1\n");
	state.whoseTurn = 0;
	
	// current player's hand = ambassador estate estate
	state.handCount[state.whoseTurn] = 3;
	int handCountExpected = state.handCount[state.whoseTurn] - 1;
	int choice1Card = estate;
	state.hand[state.whoseTurn][0] = ambassador;
	state.hand[state.whoseTurn][1] = copper;
	state.hand[state.whoseTurn][2] = choice1Card;
	int handPos = 0; // played card in position 0
	
	// play ambassador
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount + 1;
	
	// discard choice1 (0)
	int choice1CountExpected = getCount(state.whoseTurn, choice1Card, state);
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn]; // to supply not discard
	
	// other player gains choice1 (0 -> 1)
	state.handCount[state.whoseTurn + 1] = 0;
	int nextPlayerHandExpected = state.handCount[state.whoseTurn + 1] + 1;
	int nextPlayerChoice1CountExpected = 1;
	int supplyCountExpected = state.supplyCount[choice1Card] - 1;
	
	int card = ambassador;
	int choice1 = 2; // index of card to discard to supply
	int choice2 = 0; // number of cards to discard to supply
	
	int result = ambassadorEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);

	printf("2) Ambassador card played.\n");
	assert("Ambassador removed from hand.", hasCard(state.whoseTurn, card, state), FALSE);
	assert("Played cards +1.", state.playedCardCount, playedCardCountExpected);
	assert("Card placed at top of played cards.", state.playedCards[state.playedCardCount - 1], ambassador);

	printf("3) Choice1 not discarded to supply.\n");
	assert("Number of cards in discard unchanged.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Card instances in hand unchanged.", getCount(state.whoseTurn, choice1Card, state), choice1CountExpected);

	printf("4) Choice1 gained by next player.\n");
	assert("Number of cards in supply -1.", state.supplyCount[choice1Card],supplyCountExpected);
	assert("Card instances in hand +1.", getCount(state.whoseTurn + 1, choice1Card, state), nextPlayerChoice1CountExpected);
	
	printf("5) Correct number of cards in hands.\n");
	assert("Current player hand count -1.", state.handCount[state.whoseTurn], handCountExpected);
	assert("Next player hand count +1.", state.handCount[state.whoseTurn + 1], nextPlayerHandExpected);
	
	printf("\n\n");
}

void ambassadorTest4(struct gameState state) {
	printf("Ambassador - choose to discard 0, no more choice1 card in supply to gain\n");
	
	state.whoseTurn = 0;
	
	// current player's hand = ambassador estate estate
	state.handCount[state.whoseTurn] = 3;
	int handCountExpected = state.handCount[state.whoseTurn] - 1;
	int choice1Card = estate;
	state.hand[state.whoseTurn][0] = ambassador;
	state.hand[state.whoseTurn][1] = choice1Card;
	state.hand[state.whoseTurn][2] = choice1Card;
	int handPos = 0; // played card in position 0
	
	// play ambassador
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount + 1;
	
	// do not discard choice1
	int choice1CountExpected = getCount(state.whoseTurn, choice1Card, state);
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn]; // to supply not discard
	
	// other player does not gain choice1
	state.supplyCount[choice1Card] = 0;
	int supplyCountExpected = state.supplyCount[choice1Card];
	state.handCount[state.whoseTurn + 1] = 0;
	int nextPlayerHandExpected = state.handCount[state.whoseTurn + 1];
	int nextPlayerChoice1CountExpected = 0;
	
	
	int card = ambassador;
	int choice1 = 2; // index of card to discard to supply
	int choice2 = 0; // number of cards to discard to supply
	
	int result = ambassadorEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function successful.\n");
	assert("Function returns >= 0 (Success)", result >= 0, TRUE);

	printf("2) Ambassador card played.\n");
	assert("Ambassador removed from hand.", hasCard(state.whoseTurn, card, state), FALSE);
	assert("Played cards +1.", state.playedCardCount, playedCardCountExpected);
	assert("Card placed at top of played cards.", state.playedCards[state.playedCardCount - 1], ambassador);

	printf("3) Choice1 not removed from hand.\n");
	assert("Number of cards in discard unchanged.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Card instances in hand unchanged.", getCount(state.whoseTurn, choice1Card, state), choice1CountExpected);

	printf("4) Choice1 not gained by next player.\n");
	assert("Number of cards in supply unchanged.", state.supplyCount[choice1Card],supplyCountExpected);
	assert("Card instances in hand unchanged.", getCount(state.whoseTurn + 1, choice1Card, state), nextPlayerChoice1CountExpected);
	
	printf("5) Correct number of cards in hands.\n");
	assert("Current player hand count -1.", state.handCount[state.whoseTurn], handCountExpected);
	assert("Next player hand count unchanged.", state.handCount[state.whoseTurn + 1], nextPlayerHandExpected);
	
	printf("\n\n");
}

void ambassadorTest5(struct gameState state) {
	printf("Ambassador - choice1 invalid, it is the ambassador card being played (error)\n");
	
	state.whoseTurn = 0;
	
	// current player's hand = ambassador copper copper
	state.handCount[state.whoseTurn] = 3;
	int handCountExpected = state.handCount[state.whoseTurn];
	int choice1Card = ambassador;
	state.hand[state.whoseTurn][0] = ambassador;
	state.hand[state.whoseTurn][1] = copper;
	state.hand[state.whoseTurn][2] = copper;
	int handPos = 0; // played card in position 0
	
	// do not play ambassador
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount;
	
	// do not discard choice1
	int choice1CountExpected = getCount(state.whoseTurn, choice1Card, state);
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn]; // to supply not discard
	
	// other player does not gain choice1
	state.handCount[state.whoseTurn + 1] = 0;
	int nextPlayerHandExpected = state.handCount[state.whoseTurn + 1];
	int nextPlayerChoice1CountExpected = getCount(state.whoseTurn + 1, choice1Card, state);
	int supplyCountExpected = state.supplyCount[choice1Card];
	
	int card = ambassador;
	int choice1 = 0; // index of card to discard to supply
	int choice2 = 1; // number of cards to discard to supply
	
	int result = ambassadorEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function throws error.\n");
	assert("Function returns < 0 (Error)", result < 0, TRUE);

	printf("2) Ambassador card not played.\n");
	assert("Ambassador still in hand.", state.hand[state.whoseTurn][0], card);
	assert("Played cards unchanged.", state.playedCardCount, playedCardCountExpected);

	printf("3) Choice1 not discarded.\n");
	assert("Number of cards in discard unchanged.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Card instance in hand unchanged.", getCount(state.whoseTurn, choice1Card, state), choice1CountExpected);

	printf("4) Choice1 not gained by next player.\n");
	assert("Number of cards in supply net unchanged.", state.supplyCount[choice1Card],supplyCountExpected);
	assert("Card instances in hand unchanged.", getCount(state.whoseTurn + 1, choice1Card, state), nextPlayerChoice1CountExpected);
	
	printf("5) Correct number of cards in hands.\n");
	assert("Current player hand count unchanged.", state.handCount[state.whoseTurn], handCountExpected);
	assert("Next player hand count unchanged.", state.handCount[state.whoseTurn + 1], nextPlayerHandExpected);
	
	printf("\n\n");
}

void ambassadorTest6(struct gameState state) {
	printf("Ambassador - choice1 invalid, not a valid index in player's hand (error)\n");
	
	state.whoseTurn = 0;
	
	// current player's hand = ambassador copper
	state.handCount[state.whoseTurn] = 2;
	int handCountExpected = state.handCount[state.whoseTurn];
	int choice1Card = copper;
	state.hand[state.whoseTurn][0] = ambassador;
	state.hand[state.whoseTurn][1] = copper;
	int handPos = 0; // played card in position 0
	
	// do not play ambassador
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount;
	
	// do not discard choice1
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn]; // to supply not discard
	
	// other player does not gain choice1
	state.handCount[state.whoseTurn + 1] = 0;
	int nextPlayerHandExpected = state.handCount[state.whoseTurn + 1];
	int nextPlayerChoice1CountExpected = getCount(state.whoseTurn + 1, choice1Card, state);
	int supplyCountExpected = state.supplyCount[choice1Card];
	
	int card = ambassador;
	int choice1 = 2; // index of card to discard to supply
	int choice2 = 0; // number of cards to discard to supply
	
	int result = ambassadorEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function throws error.\n");
	assert("Function returns < 0 (Error)", result < 0, TRUE);

	printf("2) Ambassador card not played.\n");
	assert("Ambassador still in hand.", state.hand[state.whoseTurn][0], card);
	assert("Played cards unchanged.", state.playedCardCount, playedCardCountExpected);

	printf("3) Choice1 not discarded.\n");
	assert("Number of cards in discard unchanged.", state.discardCount[state.whoseTurn], discardCountExpected);

	printf("4) Choice1 not gained by next player.\n");
	assert("Number of cards in supply net unchanged.", state.supplyCount[choice1Card],supplyCountExpected);
	assert("Card instances in hand unchanged.", getCount(state.whoseTurn + 1, choice1Card, state), nextPlayerChoice1CountExpected);
	
	printf("5) Correct number of cards in hands.\n");
	assert("Current player hand count unchanged.", state.handCount[state.whoseTurn], handCountExpected);
	assert("Next player hand count unchanged.", state.handCount[state.whoseTurn + 1], nextPlayerHandExpected);
	
	printf("\n\n");
}

void ambassadorTest7(struct gameState state) {
	printf("Ambassador - choice2 invalid, > 2 (error)\n");
	
	state.whoseTurn = 0;
	
	// current player's hand = ambassador copper
	state.handCount[state.whoseTurn] = 5;
	int handCountExpected = state.handCount[state.whoseTurn];
	int choice1Card = estate;
	state.hand[state.whoseTurn][0] = ambassador;
	state.hand[state.whoseTurn][1] = choice1Card;
	state.hand[state.whoseTurn][2] = choice1Card;
	state.hand[state.whoseTurn][3] = choice1Card;
	state.hand[state.whoseTurn][4] = choice1Card;
	int handPos = 0; // played card in position 0
	
	// do not play ambassador
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount;
	
	// do not discard choice1
	int choice1CountExpected = getCount(state.whoseTurn, choice1Card, state);
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn]; // to supply not discard
	
	// other player does not gain choice1
	state.handCount[state.whoseTurn + 1] = 0;
	int nextPlayerHandExpected = state.handCount[state.whoseTurn + 1];
	int nextPlayerChoice1CountExpected = getCount(state.whoseTurn + 1, choice1Card, state);
	int supplyCountExpected = state.supplyCount[choice1Card];
	
	int card = ambassador;
	int choice1 = 1; // index of card to discard to supply
	int choice2 = 3; // number of cards to discard to supply
	
	int result = ambassadorEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function throws error.\n");
	assert("Function returns < 0 (Error)", result < 0, TRUE);

	printf("2) Ambassador card not played.\n");
	assert("Ambassador still in hand.", state.hand[state.whoseTurn][0], card);
	assert("Played cards unchanged.", state.playedCardCount, playedCardCountExpected);

	printf("3) Choice1 not discarded to supply.\n");
	assert("Number of cards in discard unchanged.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Card instance in hand unchanged.", getCount(state.whoseTurn, choice1Card, state), choice1CountExpected);

	printf("4) Choice1 not gained by next player.\n");
	assert("Number of cards in supply net unchanged.", state.supplyCount[choice1Card],supplyCountExpected);
	assert("Card instances in hand unchanged.", getCount(state.whoseTurn + 1, choice1Card, state), nextPlayerChoice1CountExpected);
	
	printf("5) Correct number of cards in hands.\n");
	assert("Current player hand count unchanged.", state.handCount[state.whoseTurn], handCountExpected);
	assert("Next player hand count unchanged.", state.handCount[state.whoseTurn + 1], nextPlayerHandExpected);
	
	printf("\n\n");
}

void ambassadorTest8(struct gameState state) {
	printf("Ambassador - choice2 invalid, choose to discard 2, have 1 of choice1 (error)\n");
	
	state.whoseTurn = 0;
	
	// current player's hand = ambassador copper
	state.handCount[state.whoseTurn] = 2;
	int handCountExpected = state.handCount[state.whoseTurn];
	int choice1Card = estate;
	state.hand[state.whoseTurn][0] = ambassador;
	state.hand[state.whoseTurn][1] = choice1Card;
	int handPos = 0; // played card in position 0
	
	// do not play ambassador
	state.playedCardCount = 0;
	int playedCardCountExpected = state.playedCardCount;
	
	// do not discard choice1
	int choice1CountExpected = getCount(state.whoseTurn, choice1Card, state);
	state.discardCount[state.whoseTurn] = 0;
	int discardCountExpected = state.discardCount[state.whoseTurn]; // to supply not discard
	
	// other player does not gain choice1
	state.handCount[state.whoseTurn + 1] = 0;
	int nextPlayerHandExpected = state.handCount[state.whoseTurn + 1];
	int nextPlayerChoice1CountExpected = getCount(state.whoseTurn + 1, choice1Card, state);
	int supplyCountExpected = state.supplyCount[choice1Card];
	
	int card = ambassador;
	int choice1 = 1; // index of card to discard to supply
	int choice2 = 2; // number of cards to discard to supply
	
	int result = ambassadorEffect(card, choice1, choice2, &state, handPos);
	
	printf("1) Function throws error.\n");
	assert("Function returns < 0 (Error)", result < 0, TRUE);

	printf("2) Ambassador card not played.\n");
	assert("Ambassador still in hand.", state.hand[state.whoseTurn][0], card);
	assert("Played cards unchanged.", state.playedCardCount, playedCardCountExpected);

	printf("3) Choice1 not discarded to supply.\n");
	assert("Number of cards in discard unchanged.", state.discardCount[state.whoseTurn], discardCountExpected);
	assert("Card instance in hand unchanged.", getCount(state.whoseTurn, choice1Card, state), choice1CountExpected);

	printf("4) Choice1 not gained by next player.\n");
	assert("Number of cards in supply unchanged.", state.supplyCount[choice1Card],supplyCountExpected);
	assert("Card instances in hand unchanged.", getCount(state.whoseTurn + 1, choice1Card, state), nextPlayerChoice1CountExpected);
	
	printf("5) Correct number of cards in hands.\n");
	assert("Current player hand count unchanged.", state.handCount[state.whoseTurn], handCountExpected);
	assert("Next player hand count unchanged.", state.handCount[state.whoseTurn + 1], nextPlayerHandExpected);
	
	printf("\n\n");
}

void testAmbassador() {
	int seed = 1; // need some constant here that's deterministic (vs seeding by time)
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, minion, gardens, mine, remodel, ambassador, village, baron, great_hall};
	struct gameState G;
	initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	// calling tests and passing by value since we want gameState unchanged
	ambassadorTest1(G);
	ambassadorTest2(G);
	ambassadorTest3(G);
	ambassadorTest4(G);
	ambassadorTest5(G);
	ambassadorTest6(G);
	ambassadorTest7(G);
	ambassadorTest8(G);
}

int main() {
	testAmbassador();
	return 0;
}
