#ifndef _CARDEFFECT_H
#define _CARDEFFECT_H

#include "dominion.h"

int baronEffect(int card, int choice1, struct gameState *state, int handPos);

int minionEffect(int card, int choice1, int choice2, struct gameState *state, int handPos);

int ambassadorEffect(int card, int choice1, int choice2, struct gameState *state, int handPos);

int tributeEffect(int card, struct gameState *state, int handPos);

int mineEffect(int card, int choice1, int choice2, struct gameState *state, int handPos);

#endif