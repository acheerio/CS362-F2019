#ifndef RANDOMHELPER_H
#define RANDOMHELPER_H

#include "dominion.h"

typedef enum bool {FALSE, TRUE} bool;

bool assert(char * assertion, int a, int b);
int getCount(int player, int card, struct gameState state);
// generate random hand (count, include specific card)
// generate random deck (count, player, state)
// generate random discard (count, player, state)

/* fills the player's hand with specified number of card (overwrites previous values)
void fillHand(int player, int card, int count, struct gameState *state);
bool hasCard(int player, int card, struct gameState state); */

#endif