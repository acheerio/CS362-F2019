#ifndef _CARDEFFECT_H
#define _CARDEFFECT_H

int baronEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

int minionEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

int ambassadorEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

int tributeEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

int mineEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);