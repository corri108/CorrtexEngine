#include "stdafx.h"
#include "Animation.h"


Animation::Animation(float length, int numFrames, Keyframe *frames)
{
	this->length = length;
	this->frames = frames;
	this->numFrames = numFrames;
}


Animation::~Animation()
{

}
