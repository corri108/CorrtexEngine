#include "stdafx.h"
#include "JointTransform.h"


JointTransform::JointTransform(vec3 pos, quat rot)
{
	this->position = pos;
	this->rotation = rot;
}


JointTransform::~JointTransform()
{
}

mat4 JointTransform::GetLocalTransform()
{
	return glm::translate(position) * mat4(rotation);
}

JointTransform *JointTransform::Interpolate(JointTransform j1, JointTransform j2, float t)
{
	vec3 pos = glm::lerp(j1.position, j2.position, t);
	quat rot = glm::slerp(j1.rotation, j2.rotation, t);
	return new JointTransform(pos, rot);
}