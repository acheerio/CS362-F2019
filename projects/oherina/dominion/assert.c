#include "assert.h"
#include <stdio.h>

bool assert(char * assertion, int a, int b) {
	if (a == b) {
		printf("   PASSED: %s\n", assertion);
		return TRUE;
	}
	else {
		printf("   FAILED: %s FAILED!\n\n", assertion);
		return FALSE;
	}
}

bool hasCard(int player, int card, struct gameState state) {
	bool hasCard = FALSE;
	int i;
	for (i = 0; i < state.handCount[player]; i++) {
		if (state.hand[player][i] == card) {
			hasCard = TRUE;
		}
	}
	return hasCard;
}
