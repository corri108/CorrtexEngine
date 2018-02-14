#pragma once
#include <glm\ext.hpp>
using namespace glm;

class JointTransform
{
public:
	JointTransform(vec3 pos, quat rot);
	~JointTransform();

	vec3 position;
	quat rotation;
	static JointTransform *Interpolate(JointTransform j1, JointTransform j2, float t);
	mat4 GetLocalTransform();
};

