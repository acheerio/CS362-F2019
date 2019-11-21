#ifndef TESTHELPER_H
#define TESTHELPER_H

#include "dominion.h"

#define K_CARD_MIN 7  // adventurer
#define K_CARD_MAX 26 // treasure_map
typedef enum bool {FALSE, TRUE} bool;

bool assert(char * assertion, int a, int b);
int min(int a, int b);
int max(int a, int b);
int myrand(int range_start, int range_end_exclusive);
bool hasCard(int player, int card, struct gameState state);
int getHandCount(int player, int card, struct gameState state);
int getCount(int arr[], int size, int card);
int countSupply(struct gameState state);
int getRandomFromSupply(struct gameState *state);
void selectKingdomCardsWith(int random_seed, int kCards[], int include);
void fillHand(int player, int card, int count, struct gameState *state);
void fillHandRandom(int currPlayer, int startIndex, int handCount, struct gameState *state);

#endif