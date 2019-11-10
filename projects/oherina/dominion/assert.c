#include "assert.h"
#include <stdio.h>

bool assert(char * assertion, int a, int b) {
	if (a == b) {
		printf("%s PASSED!\n\n", assertion);
		return TRUE;
	}
	else {
		printf("ERROR: %s FAILED!\n\n", assertion);
		return FALSE;
	}
}

bool hasCard(int player, int card, struct gameState state) {
	bool hasCard = FALSE;
	int i;
	for (i = 0; i < state.handCount[currentPlayer]; i++) {
		if (state.hand[currentPlayer][i] == card) {
			hasCard = TRUE;
		}
	}
	return hasCard;
}
