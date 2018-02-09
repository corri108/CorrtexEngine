#pragma once
#include "CorrtexCamera.h"
#include "CorrtexDebug.h"

class CorrtexFPSCamera : public CorrtexCamera
{
public:
	CorrtexFPSCamera(float near, float far, float aspect, float fov);
	~CorrtexFPSCamera();
	void Update(float time, InputManager &input);
	void RotationInput(float time, InputManager &input);
	void TranslationInput(float time, InputManager &input);
	void InvertPitch();
	float yaw, pitch, roll = 0.0f;
	mat4 yawMatrix, pitchMatrix, rollMatrix;
	mat4 rotation, translation;
};

