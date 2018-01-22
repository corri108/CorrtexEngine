#pragma once
#include <iostream>
#include <ctime>

class CorrtexRandom
{
public:
	static float RandomFloat();
	static float RandomFloat(float min, float max);
	static int RandomInt();
	static int RandomInt(int max);
	static int RandomInt(int min, int max);
	CorrtexRandom();
	CorrtexRandom(int seed);
	~CorrtexRandom();
	int seed = 0;
};

