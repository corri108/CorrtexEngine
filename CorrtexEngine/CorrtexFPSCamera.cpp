#include "stdafx.h"
#include "CorrtexFPSCamera.h"


CorrtexFPSCamera::CorrtexFPSCamera(float near, float far, float aspect, float fov) :
	CorrtexCamera(near, far, aspect, fov)
{
	this->yawMatrix = mat4(1.0f);
	this->pitchMatrix = mat4(1.0f);
	this->rollMatrix = mat4(1.0f);

	this->yaw = 0.0f;
	this->pitch = 0.0f;
	this->roll = 0.0f;

	this->cameraPosition = vec3(0, 0.75f, 0);
	this->rotation = mat4(1.0f);
	this->translation = mat4(1.0f);
}

CorrtexFPSCamera::~CorrtexFPSCamera()
{

}

void CorrtexFPSCamera::InvertPitch()
{
	pitch = -pitch;
}

void CorrtexFPSCamera::Update(float time, InputManager &input)
{
	RotationInput(time, input);
	TranslationInput(time, input);

	this->yawMatrix = mat4(1.0f);
	this->pitchMatrix = mat4(1.0f);
	this->rollMatrix = mat4(1.0f);

	this->yawMatrix = rotate(this->yawMatrix, this->yaw, vec3(0.0f, 1.0f, 0.0f));
	this->pitchMatrix = rotate(this->pitchMatrix, this->pitch, vec3(1.0f, 0.0f, 0.0f));
	this->rollMatrix = rotate(this->rollMatrix, this->roll, vec3(0.0f, 0.0f, 1.0f));

	this->rotation = this->rollMatrix * this->pitchMatrix * this->yawMatrix;
	//this->translation = glm::translate(this->translation, -this->cameraPosition);

	this->translation = mat4(1.0f);
	this->translation = glm::translate(this->translation, -this->cameraPosition);
	this->view = this->rotation * this->translation;
	this->UpdateProjectionMatrix();
}

void CorrtexFPSCamera::RotationInput(float time, InputManager &input)
{
	vec2 mouseD = input.GetMouseDelta();
	const float mouseSensitivity = 0.005f;

	this->yaw += mouseD.x * mouseSensitivity;
	this->pitch += mouseD.y * mouseSensitivity;

	float radMax = glm::radians(89.9999f);

	if (this->pitch >= radMax)
		this->pitch = radMax;
	else if (this->pitch <= -radMax)
		this->pitch = -radMax;

	if (CorrtexDebug::Get())
	{
		if (mouseD.x != 0 || mouseD.y != 0)
			printf("YAW: %f, PITCH: %f\n", yaw, pitch);
	}
}

void CorrtexFPSCamera::TranslationInput(float time, InputManager &input)
{
	float dx = 0.0f, dz = 0.0f;
	bool moved = false;
	
	if (input.GetKey("A", KeyPress::Down))
	{
		dx += -1.0f;
		moved = true;
	}
	if (input.GetKey("D", KeyPress::Down))
	{
		dx += 1.0f;
		moved = true;
	}
	if (input.GetKey("W", KeyPress::Down))
	{
		dz += 1.0f;
		moved = true;
	}
	if (input.GetKey("S", KeyPress::Down))
	{
		dz += -1.0f;
		moved = true;
	}

	const float speed = 0.05f;

	if (moved)
	{
		vec3 forward = vec3(view[0][2], view[1][2], view[2][2]);
		vec3 right = vec3(view[0][0], view[1][0], view[2][0]);

		if (CorrtexDebug::Get())
		{
			printf("forward vector: (%f, %f, %f)\n", forward.x, forward.y, forward.z);
		}

		if (input.GetKey("Left Shift", KeyPress::Down))
		{
			this->cameraPosition += (-dz * forward + dx * right) * speed * 10.0f;
		}
		else
		{
			this->cameraPosition += (-dz * forward + dx * right) * speed;
		}
	}
}