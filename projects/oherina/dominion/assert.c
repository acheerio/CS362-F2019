#include "assert.h"
#include <stdio.h>

bool assert(char * assertion, int a, int b) {
	if (a == b) {
		printf("   PASSED: %s\n", assertion);
		return TRUE;
	}
	else {
		printf("   FAILED: %s\n", assertion);
		return FALSE;
	}
}

bool hasCard(int player, int card, struct gameState state) {
	int i;
	for (i = 0; i < state.handCount[player]; i++) {
		if (state.hand[player][i] == card) {
			return TRUE;
		}
	}
	return FALSE;
}

int getCount(int player, int card, struct gameState state) {
	int count = 0;
	int i;
	for (i = 0; i < state.handCount[player]; i++) {
		if (state.hand[player][i] == card) {
			count++;
		}
	}
	return count;
}

void fillHand(int player, int card, int count, struct gameState *state) {
	state->handCount[player] = count;
	int i;
	for (i = 0; i < state->handCount[player]; i++) {
		state->hand[player][i] = card;
	}
}
