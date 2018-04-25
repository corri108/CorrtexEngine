#include "stdafx.h"
#include "AnimatedModel.h"
#include "Animator.h"
#include "GameEngine.h"

//AnimatedModel class - not yet working all the way due to the Animator class having issues.

//constructor - includes loading the skinned model
AnimatedModel::AnimatedModel(vec3 pos, const char *filePath)
{
	int rootJointIndex;
	char *rootJointName;
	mat4 rootJointBind;

	std::vector<Animation *> animations;
	this->position = pos;
	this->startingPosition = pos;
	this->animator = new Animator(this);
	GameEngine::modelLoader->LoadSkinned(filePath, this->vertices, this->uvs, this->normals, 
		this->jointIDs, this->weights, &this->jointCount, &rootJointIndex, &rootJointName, &rootJointBind,
		animations);

	//this->jointCount = 1;
	this->root = new Joint(rootJointIndex, rootJointName, rootJointBind);
	this->root->CalculateInverseBind(mat4(1.0f));
}

//destructor - nothing here yet
AnimatedModel::~AnimatedModel()
{
	
}

//init
void AnimatedModel::Initialize()
{
	//base initialize - will add another thing herelater
	CorrtexMesh::Initialize();
}

//gets all the joint transforms for the whole model by calling the recursive AddJoints method
mat4 *AnimatedModel::GetJointTransforms()
{
	mat4 *jointMats = new mat4[this->jointCount];
	AddJoints(this->root, jointMats);
	return jointMats;
}

//adds the updating of the animator to the inherited update method from CorrtexMesh
void AnimatedModel::Update(float time)
{
	CorrtexMesh::Update(time);
	animator->UpdateAnimation();
}

//recursive function that calculates joint matrices for all joints in the model, by passing in the root joint as the first joint.
void AnimatedModel::AddJoints(Joint *head, mat4* jointMatrices)
{
	jointMatrices[head->id] = head->transform;

	int childSize = head->children.size();
	for (int i = 0; i < childSize; ++i)
	{
		AddJoints(head->children[i], jointMatrices);
	}
}

//sets the shader attributes of the extra buffers needed for this class (joint ids and weights)
void AnimatedModel::SetShaderAttributes()
{
	if (jointIDs.size() > 0)
	{
		//set all other shader attributes other than jointIDs and weights
		CorrtexMesh::SetShaderAttributes();

		//now for jointIDs and weights
		glEnableVertexAttribArray(6);
		glBindBuffer(GL_ARRAY_BUFFER, this->jointIDBuffer);
		glVertexAttribIPointer(6, 3, GL_INT, GL_FALSE, 0);// , (void*)0);

		glEnableVertexAttribArray(7);
		glBindBuffer(GL_ARRAY_BUFFER, this->weightBuffer);
		glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
}

//generates the special buffers needed for animated models (joint ids and weights)
void AnimatedModel::GenSpecialBuffers()
{
	if (jointIDs.size() > 0)
	{
		//gen buffers for jointIDs and for weights
		glGenBuffers(1, &jointIDBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, jointIDBuffer);
		glBufferData(GL_ARRAY_BUFFER, jointIDs.size() * sizeof(glm::ivec3), &jointIDs[0], GL_STATIC_DRAW);

		glGenBuffers(1, &weightBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, weightBuffer);
		glBufferData(GL_ARRAY_BUFFER, weights.size() * sizeof(glm::vec3), &weights[0], GL_STATIC_DRAW);
	}
}