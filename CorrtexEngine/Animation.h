#pragma once
#include "Keyframe.h"

//class to store Animation data
class Animation
{
public:
	Animation(float length, int numFrames, Keyframe *frames);
	~Animation();

	int numFrames;
	Keyframe * frames;
	float length;//in seconds
};

