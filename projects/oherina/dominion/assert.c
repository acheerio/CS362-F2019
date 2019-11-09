#include "assert.h"
#include <stdio.h>

bool assert(char * assertion, int a, int b) {
	if (a == b) {
		printf("%s PASSED!", assertion);
		return TRUE;
	}
	else {
		printf("ERROR: %s FAILED!", assertion);
		return FALSE;
	}
}