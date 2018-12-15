#include "Maths.h"

int Maths::randomInt(int nextInt) {
	srand((int)time(0));
	return rand() % nextInt;
}

float Maths::randomFloat(int seed) {
	srand(seed);
	float m1 = (float)(rand() / float(RAND_MAX));
	return m1;
}

float Maths::clamp(float x, float lower, float upper) {
	return fmaxf(lower, fminf(x, upper));
}
