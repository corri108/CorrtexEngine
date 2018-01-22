#include "stdafx.h"
#include "CorrtexRandom.h"


CorrtexRandom::CorrtexRandom()
{
	srand(time(NULL));
}


CorrtexRandom::CorrtexRandom(int seed)
{
	this->seed = seed;
	srand(time(NULL));
}


CorrtexRandom::~CorrtexRandom()
{

}

///Returns a random float from 0->1 (inclusive)
float CorrtexRandom::RandomFloat()
{
	return (float)rand() / (float)RAND_MAX;
}

///Returns a random float from min->max (inclusive)
float CorrtexRandom::RandomFloat(float min, float max)
{
	float dif = max - min;
	float r = ((float)rand() / (float)RAND_MAX) * dif;
	return r + min;
}

///Returns a random integer from 0->RAND_MAX (inclusive)
int CorrtexRandom::RandomInt()
{
	return rand();
}

///Returns a random integer from 0->max (exclusive)
int CorrtexRandom::RandomInt(int max)
{
	float r = ((float)rand() / (float)RAND_MAX) * max;
	int ri = (int)r - 1;

	if (ri < 0)
		return 0;

	return ri;
}

///Returns a random integer from min->max (inclusive)
int CorrtexRandom::RandomInt(int min, int max)
{
	int dif = max - min;
	float r = ((float)rand() / (float)RAND_MAX) * dif;//0->dif
	int ri = r + min;//min->max
	return ri;
}