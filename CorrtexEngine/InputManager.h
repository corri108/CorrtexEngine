#pragma once
#include "glfw3.h"
#include "glm/ext.hpp"

using namespace glm;
enum KeyPress
{
	Down,
	Trigger,
	Release
};

class InputManager
{
public:
	InputManager();
	InputManager(GLFWwindow *gameWindow);
	~InputManager();
	void UpdateFirst();
	void UpdateLast();
	vec2 GetMouseDelta();
	GLFWwindow *thisWindow = NULL;
	bool GetKey(const char* keyName, KeyPress press);
	bool GetKey(int keyIndex, KeyPress press);
	float mouseXPosition = 0.0f;
	float mouseYPosition = 0.0f;
	float mouseXPositionPrevious = 0.0f;
	float mouseYPositionPrevious = 0.0f;

private:
	int keyCount = 46;
	bool previousKeys[46] = 
	{
		false,false,false,false,false,
		false,false,false,false,false,//NUMBERS 0-9
		//a = 10
		false,false,false,false,false,false,
		false,false,false,false,false,false,
		false,false,false,false,false,false,
		false,false,false,false,false,false,
		false,false,//ALPHABET A-Z
		
		false,false,false,//spacebar = 36, L/R shift = 37/38
		false,false,false,//tab = 39, L/R alt = 40/41

		false,false,false,//left up right down (42-45)
		false

	};
	bool currentKeys[46] =
	{
		false,false,false,false,false,
		false,false,false,false,false,//NUMBERS 0-9
		//a = 10
		false,false,false,false,false,false,
		false,false,false,false,false,false,
		false,false,false,false,false,false,
		false,false,false,false,false,false,
		false,false,//ALPHABET A-Z

		false,false,false,//spacebar = 36, L/R shift = 37/38
		false,false,false,//tab = 39, L/R alt = 40/41

		false,false,false,//left up right down (42-45)
		false
	};
};