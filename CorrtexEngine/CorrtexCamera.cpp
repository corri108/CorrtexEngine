#include "stdafx.h"
#include "CorrtexCamera.h"

using namespace glm;

//basic camera class

//default ctor
CorrtexCamera::CorrtexCamera() :
	CorrtexCamera(0.01f, 500.0f, 4.0f / 3.0f, 50.0f)
{

}
//ctor
CorrtexCamera::CorrtexCamera(float near, float far, float aspect, float fov)
{
	this->nearPlane = near;
	this->farPlane = far;
	this->aspectRatio = aspect;
	this->fieldOfView = fov;
}
//dtor
CorrtexCamera::~CorrtexCamera()
{

}

//returns projection matrix of the camera
mat4 CorrtexCamera::GetProjectionMatrix()
{
	return this->projection;
}
//returns view matrix of the camera
mat4 CorrtexCamera::GetViewMatrix()
{
	return this->view;
}

//updates projection matrix
void CorrtexCamera::UpdateProjectionMatrix()
{
	this->projection = glm::perspective(radians(fieldOfView), aspectRatio, nearPlane, farPlane);
	bool x = false;
}
//updates view matrix
void CorrtexCamera::UpdateViewMatrix()
{
	this->view = lookAt(cameraPosition, cameraTarget, cameraUp);
}

//move the camera with WASD, Space/Q
void CorrtexCamera::Update(float time, InputManager &manager)
{
	if (manager.GetKey("D", KeyPress::Down))
	{
		cameraPosition.x += 0.01f;
	}
	if (manager.GetKey("A", KeyPress::Down))
	{
		cameraPosition.x -= 0.01f;
	}
	if (manager.GetKey("W", KeyPress::Down))
	{
		cameraPosition.z += 0.01f;
	}
	if (manager.GetKey("S", KeyPress::Down))
	{
		cameraPosition.z -= 0.01f;
	}
	if (manager.GetKey("Space", KeyPress::Down))
	{
		cameraPosition.y += 0.01f;
	}
	if (manager.GetKey("Q", KeyPress::Down))
	{
		cameraPosition.y -= 0.01f;
	}

	this->projection = glm::perspective(radians(this->fieldOfView), this->aspectRatio, this->nearPlane, this->farPlane);
	this->view = lookAt(this->cameraPosition, this->cameraTarget, this->cameraUp);
}
