#pragma once
#include "glfw3.h"
#include "glm/ext.hpp"

using namespace glm;

//3 different kinds of key presses
enum KeyPress
{
	Down,
	Trigger,
	Release
};

//input manager class. used to gather all kinds of input from the user, for now is just keyboard and mouse,
//but will hopefully be extended to accept XBox controllers, Playstaion controllers, and other kinds of input devices
class InputManager
{
public:
	InputManager();
	InputManager(GLFWwindow *gameWindow);
	~InputManager();

	//call this before you update anything in the game engine
	void UpdateFirst();
	//call this after everything has been updated in the game engine
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