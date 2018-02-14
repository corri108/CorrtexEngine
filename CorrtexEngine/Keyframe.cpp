#include "stdafx.h"
#include "Keyframe.h"


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
