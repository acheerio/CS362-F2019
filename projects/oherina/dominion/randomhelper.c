#include "randomhelper.h"
#include "interface.h"
#include <stdlib.h>
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

int myrand(int range_start, int range_end_exclusive) {
	int range = range_end_exclusive - range_start;
	int num = (rand() % range) + range_start;
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

int getCount(int arr[], size_t size, int card) {
	int count = 0;
	int i;
	for (i = 0; i < size; i++) {
		if (arr[i] == card) {
			count++;
		}
	}
	return count;
}

void selectKingdomCardsWith(int random_seed, int kCards[], int card) {
	selectKingdomCards(random_seed, kCards);
	// make sure baron card in kingdom cards
	if (getCount(kCards, NUM_SELECTED_KCARDS, card) < 1) {
		int index = myrand(0, NUM_SELECTED_KCARDS);
		kCards[index] = card;
	}
}

/*
bool hasCard(int player, int card, struct gameState state) {
	int i;
	for (i = 0; i < state.handCount[player]; i++) {
		if (state.hand[player][i] == card) {
			return TRUE;
		}
	}
	return FALSE;
}

void fillHand(int player, int card, int count, struct gameState *state) {
	state->handCount[player] = count;
	int i;
	for (i = 0; i < state->handCount[player]; i++) {
		state->hand[player][i] = card;
	}
}
*/