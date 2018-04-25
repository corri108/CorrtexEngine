#include "Animation.h"
#include "Joint.h"
//using namespace glm;

#ifndef ANIMATOR_H
#define ANIMATOR_H

class AnimatedModel;

//animator class. This class is used to control the playing of animations for a given AnimatedModel.
class Animator
{
public:
	Animator(AnimatedModel *m);
	~Animator();
	AnimatedModel *model = NULL;
	Animation *currentAnimation;
	float animationTime = 0;
	void UpdateAnimation();
	void PlayAnimation(Animation *ani);
private:
	//lots of mathmatically complicated stuff going on in these methods - some of it is currently broken.
	void IncreaseAnimationTime();
	std::map<char*, mat4> CalculateCurrentPose();
	void ApplyPoseToJoints(std::map<char*, mat4> pose, Joint *joint, mat4 parentTransform);
	void GetPreviousAndNextFrames(Keyframe *prev, Keyframe *next);
	float CalculateProgression(Keyframe k1, Keyframe k2);
	std::map<char*, mat4> InterpolatePoses(Keyframe k1, Keyframe k2, float lerp);
	std::map<char*, mat4> curPose;
};

#endif //ANIMATOR_H