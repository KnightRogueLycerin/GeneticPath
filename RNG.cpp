#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "RNG.h"

void rng::initalize(){
	/* initialize random seed: */
	srand(time(NULL));
}

int rng::generateNumber(int range) {
	/* from 0 to range - 1 */
	return rand() % range;
}