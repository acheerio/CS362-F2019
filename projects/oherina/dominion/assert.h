#ifndef ASSERT_H
#define ASSERT_H

#include "dominion.h"

typedef enum bool {FALSE, TRUE} bool;

bool assert(char * assertion, int a, int b);
bool hasCard(int player, int card, struct gameState state);
int getCount(int player, int card, struct gameState state);
// fills the player's hand with specified number of card (overwrites previous values)
void fillHand(int player, int card, int count, struct gameState *state);

#endif