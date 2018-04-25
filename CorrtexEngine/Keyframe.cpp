#include "stdafx.h"
#include "Keyframe.h"

//simple class to represent a keyframe.

Keyframe::Keyframe()
{

}

Keyframe::Keyframe(float timeStamp, int numJoints, std::map<char *, JointTransform*> pose)
{
	this->timeStamp = timeStamp;
	this->numJoints = numJoints;
	this->pose = pose;
}

Keyframe::~Keyframe()
{
}