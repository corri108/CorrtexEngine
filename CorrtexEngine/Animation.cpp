#include "stdafx.h"
#include "Animation.h"

//very simple Animation class that stores Animation data.
Animation::Animation(float length, int numFrames, Keyframe *frames)
{
	this->length = length;
	this->frames = frames;
	this->numFrames = numFrames;
}

Animation::~Animation()
{

}
