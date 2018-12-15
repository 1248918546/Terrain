#pragma once
#include "Vector.h"
#include "Maths.h"

class PerlinNoiseGenerator{
private:
	const float ROUGHNESS = 0.43f;
	const float OCATAVES = 5;
	const float AMPLITUDE = 15;

	float smoothness;
	float maxSize;

	float edgeHeight = -1.0f;

	int seed;

private:
	float getNoise(int x, int y);
	float getSmoothNoise(int x, int y);
	float cosinInterpolate(float a, float b, float blend);
	float getInterpolateNoise(float x, float y);

	float getEdgeFactor(float x, float y); 

public:
	PerlinNoiseGenerator(int seed, float smoothness, float size, float edgeHeight);
	PerlinNoiseGenerator(float smoothness, float size, float edgeHeight);
	float getPerlinNoise(float x, float y);

};