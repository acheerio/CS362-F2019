#include "assert.h"
#include <stdio.h>

bool assert(char * assertion, int a, int b) {
	if (a == b) {
		printf("%s PASSED!", assertion);
		return true;
	}
	else {
		printf("ERROR: %s FAILED!", assertion);
		return false;
	}
}