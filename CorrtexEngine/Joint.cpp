#include "stdafx.h"
#include "Joint.h"

//joint class
Joint::Joint(int index, char *name, mat4 bindT)
{
	this->id = index;
	this->name = name;
	//original transform of joint in relation to parent
	this->bindTransform = bindT;
}

Joint::~Joint()
{
}

//calculates the inverse bind transform of every joint in the model (using recursion)
void Joint::CalculateInverseBind(mat4 parentBind)
{
	mat4 bindRegular = parentBind * bindTransform;
	mat4 inverse = glm::inverse(bindRegular);

	int s = this->children.size();
	for (int i = 0; i < s; ++i)
	{
		children[i]->CalculateInverseBind(inverse);
	}
}