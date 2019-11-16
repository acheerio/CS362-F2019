#ifndef RANDOMHELPER_H
#define RANDOMHELPER_H

#include "dominion.h"

#define K_CARD_MIN 7  // adventurer
#define K_CARD_MAX 26 // treasure_map
typedef enum bool {FALSE, TRUE} bool;

bool assert(char * assertion, int a, int b);
int myrand(int range_start, int range_end_exclusive);
//int getCount(int player, int card, struct gameState state);
int getCount(int arr[], int size, int card);
void selectKingdomCardsWith(int random_seed, int kCards[], int card);
// generate random hand (count, include specific card)
// generate random deck (count, player, state)
// generate random discard (count, player, state)

/* fills the player's hand with specified number of card (overwrites previous values)
void fillHand(int player, int card, int count, struct gameState *state);
bool hasCard(int player, int card, struct gameState state); */

#endif