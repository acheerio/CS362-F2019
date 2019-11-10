#ifndef ASSERT_H
#define ASSERT_H

typedef enum bool {FALSE, TRUE} bool;

bool assert(char * assertion, int a, int b);
bool hasCard(int player, int card, gameState state);

#endif