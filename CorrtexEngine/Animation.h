#pragma once
#include "Keyframe.h"

class Animation
{
public:
	Animation(float length, int numFrames, Keyframe *frames);
	~Animation();

	int numFrames;
	Keyframe * frames;
	float length;//in seconds
};

