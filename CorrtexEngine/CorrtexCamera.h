#pragma once
#include "glm/ext.hpp"
#include "InputManager.h"

using namespace glm;

//base camera class for my Corrtex engine.
class CorrtexCamera
{
public:
	CorrtexCamera();
	CorrtexCamera(float near, float far, float aspect, float fov);
	~CorrtexCamera();
	virtual void Update(float time, InputManager &manager);
	void UpdateProjectionMatrix();
	void UpdateViewMatrix();
	mat4 GetProjectionMatrix();
	mat4 GetViewMatrix();
	vec3 cameraPosition = vec3(0, 0, 0);
	vec3 cameraTarget = vec3(0, 0, 0);
	vec3 cameraUp = vec3(0, 1, 0);
	float nearPlane = 0.0f;
	float farPlane = 0.0f;
	float aspectRatio = 0.0f;
	float fieldOfView = 0.0f;
protected:
	mat4 projection;
	mat4 view;
};

