#pragma once
#include "JointTransform.h"
#include <map>

using namespace glm;

//class to store keyframe data, which is used with AnimatedModel class
class Keyframe
{
public:
	Keyframe();
	Keyframe(float timeStamp, int numJoints, std::map<char *, JointTransform*> pose);
	~Keyframe();
	float timeStamp;
	int numJoints = 0;
	std::map<char *, JointTransform*> pose;
};

