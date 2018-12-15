#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include <time.h>

class Maths {
public:
	static int randomInt(int nextInt);
	static float randomFloat(int seed);
	static float clamp(float x, float lower, float upper);
};