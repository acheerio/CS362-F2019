#ifndef ASSERT_H
#define ASSERT_H

#include "dominion.h"

typedef enum bool {FALSE, TRUE} bool;

bool assert(char * assertion, int a, int b);
bool hasCard(int player, int card, struct gameState state);

#endif