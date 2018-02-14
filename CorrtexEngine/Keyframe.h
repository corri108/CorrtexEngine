#pragma once
#include "JointTransform.h"
#include <map>

using namespace glm;

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

