#include "stdafx.h"
#include "Animator.h"
#include "AnimatedModel.h"
#include "GameEngine.h"

//animator class - this class is complicated and not working yet totally correctly.


Animator::Animator(AnimatedModel *m)
{
	this->model = m;
}

Animator::~Animator()
{

}

//plays a given animation
void Animator::PlayAnimation(Animation *ani)
{
	this->animationTime = 0.0f;
	this->currentAnimation = ani;
}

//updates current animation if it exists
void Animator::UpdateAnimation()
{
	if (currentAnimation == NULL)
	{
		return;
	}

	IncreaseAnimationTime();
	curPose = CalculateCurrentPose();
	ApplyPoseToJoints(curPose, model->root, mat4(1.0f));
}

//increases the animation time 
void Animator::IncreaseAnimationTime()
{
	animationTime += GameEngine::timeStep;

	if (animationTime >= currentAnimation->length)
	{
		this->animationTime -= currentAnimation->length;
	}
}

//calculates the current pose, returning a hashmap of all the joint matrices
std::map<char*, mat4> Animator::CalculateCurrentPose()
{
	Keyframe previous;
	Keyframe next;
	GetPreviousAndNextFrames(&previous, &next);
	float lerp = CalculateProgression(previous, next);
	return InterpolatePoses(previous, next, lerp);
}

//gets called recursively for every joint in model, converting bone space to model space
void Animator::ApplyPoseToJoints(std::map<char*, mat4> pose, Joint *joint, mat4 parentTransform)
{
	mat4 local = pose[joint->name];
	mat4 current = parentTransform * local;

	int childSize = joint->children.size();
	for (int i = 0; i < childSize; ++i)
	{
		Joint*j = joint->children[i];
		ApplyPoseToJoints(pose, j, current);
	}

	current = joint->inverseBindTransform * current;
	joint->transform = current;
}

//gets the previous and the next keyframes
void  Animator::GetPreviousAndNextFrames(Keyframe *prev, Keyframe *next)
{
	Keyframe *allFrames = currentAnimation->frames;
	int s = allFrames->numJoints;

	for (int i = 0; i < s; ++i)
	{
		*next = allFrames[i];

		if (next->timeStamp > this->animationTime)
		{
			break;
		}

		*prev = *next;
	}
}

//calculates the progression between keyframe k1 and k2
float  Animator::CalculateProgression(Keyframe k1, Keyframe k2)
{
	float totalTime = k2.timeStamp - k1.timeStamp;
	float currentTime = this->animationTime - k1.timeStamp;
	return currentTime / totalTime;
}

//interpolates entire poses between the given 2 keyframes and the lerp value.
std::map<char*, mat4> Animator::InterpolatePoses(Keyframe k1, Keyframe k2, float lerp)
{
	std::map <char *, mat4 > pose;

	for (const auto &myPair : k1.pose)
	{
		char *key = myPair.first;
		JointTransform *prev = k1.pose[key];
		JointTransform *next = k2.pose[key];
		JointTransform *lerped = JointTransform::Interpolate(*prev, *next, lerp);
		pose[key] = lerped->GetLocalTransform();
	}

	return pose;
}