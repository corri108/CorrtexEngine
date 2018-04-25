#pragma once
#include <vector>
#include <glm\ext.hpp>

using namespace glm;

//class for storing Joint data - used for AnimatedModel
class Joint
{
public:
	Joint(int index, char *name, mat4 bindT);
	~Joint();
	void CalculateInverseBind(mat4 parentBind);

	//joint structure
	char *name = "";
	std::vector<Joint*> children;
	int id = 0;

	//different matrices needed
	mat4 transform;
	mat4 bindTransform;
	mat4 inverseBindTransform;
};

