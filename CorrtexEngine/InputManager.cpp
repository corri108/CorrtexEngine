#include "stdafx.h"
#include "InputManager.h"

InputManager::InputManager() :
	InputManager(NULL)
{

}

InputManager::InputManager(GLFWwindow *gamewindow)
{
	this->thisWindow = gamewindow;

	if (this->thisWindow == NULL)
	{
		printf("Error initializing game window.\n");
		return;
	}
	
	//setup input
	glfwSetInputMode(this->thisWindow, GLFW_STICKY_KEYS, GL_TRUE);
}

InputManager::~InputManager()
{

}

vec2 InputManager::GetMouseDelta()
{
	float dx = this->mouseXPosition - this->mouseXPositionPrevious;
	float dy = this->mouseYPosition - this->mouseYPositionPrevious;

	/*if(dx != 0 || dy != 0)
		printf("Mouse Position: (%f, %f)\n", dx, dy);*/

	return vec2(dx, dy);
}

void InputManager::UpdateFirst()
{
	//numerical
	if (glfwGetKey(this->thisWindow, GLFW_KEY_0))
	{
		currentKeys[0] = true;
	}
	else currentKeys[0] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_1))
	{
		currentKeys[1] = true;
	}
	else currentKeys[1] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_2))
	{
		currentKeys[2] = true;
	}
	else currentKeys[2] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_3))
	{
		currentKeys[3] = true;
	}
	else currentKeys[3] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_4))
	{
		currentKeys[4] = true;
	}
	else currentKeys[4] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_5))
	{
		currentKeys[5] = true;
	}
	else currentKeys[5] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_6))
	{
		currentKeys[6] = true;
	}
	else currentKeys[6] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_7))
	{
		currentKeys[7] = true;
	}
	else currentKeys[7] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_8))
	{
		currentKeys[8] = true;
	}
	else currentKeys[8] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_9))
	{
		currentKeys[9] = true;
	}
	else currentKeys[9] = false;

	//alphabetical
	if (glfwGetKey(this->thisWindow, GLFW_KEY_A))
	{
		currentKeys[10] = true;
	}
	else currentKeys[10] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_B))
	{
		currentKeys[11] = true;
	}
	else currentKeys[11] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_C))
	{
		currentKeys[12] = true;
	}
	else currentKeys[12] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_D))
	{
		currentKeys[13] = true;
	}
	else currentKeys[13] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_E))
	{
		currentKeys[14] = true;
	}
	else currentKeys[14] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_F))
	{
		currentKeys[15] = true;
	}
	else currentKeys[15] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_G))
	{
		currentKeys[16] = true;
	}
	else currentKeys[16] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_H))
	{
		currentKeys[17] = true;
	}
	else currentKeys[17] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_I))
	{
		currentKeys[18] = true;
	}
	else currentKeys[18] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_J))
	{
		currentKeys[19] = true;
	}
	else currentKeys[19] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_K))
	{
		currentKeys[20] = true;
	}
	else currentKeys[20] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_L))
	{
		currentKeys[21] = true;
	}
	else currentKeys[21] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_M))
	{
		currentKeys[22] = true;
	}
	else currentKeys[22] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_N))
	{
		currentKeys[23] = true;
	}
	else currentKeys[23] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_O))
	{
		currentKeys[24] = true;
	}
	else currentKeys[24] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_P))
	{
		currentKeys[25] = true;
	}
	else currentKeys[25] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_Q))
	{
		currentKeys[26] = true;
	}
	else currentKeys[26] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_R))
	{
		currentKeys[27] = true;
	}
	else currentKeys[27] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_S))
	{
		currentKeys[28] = true;
	}
	else currentKeys[28] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_T))
	{
		currentKeys[29] = true;
	}
	else currentKeys[29] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_U))
	{
		currentKeys[30] = true;
	}
	else currentKeys[30] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_V))
	{
		currentKeys[31] = true;
	}
	else currentKeys[31] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_W))
	{
		currentKeys[32] = true;
	}
	else currentKeys[32] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_X))
	{
		currentKeys[33] = true;
	}
	else currentKeys[33] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_Y))
	{
		currentKeys[34] = true;
	}
	else currentKeys[34] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_Z))
	{
		currentKeys[35] = true;
	}
	else currentKeys[35] = false;

	//OTHER
	if (glfwGetKey(this->thisWindow, GLFW_KEY_SPACE))
	{
		currentKeys[36] = true;
	}
	else currentKeys[36] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_LEFT_SHIFT))
	{
		currentKeys[37] = true;
	}
	else currentKeys[37] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_RIGHT_SHIFT))
	{
		currentKeys[38] = true;
	}
	else currentKeys[38] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_TAB))
	{
		currentKeys[39] = true;
	}
	else currentKeys[39] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_LEFT_ALT))
	{
		currentKeys[40] = true;
	}
	else currentKeys[40] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_RIGHT_ALT))
	{
		currentKeys[41] = true;
	}
	else currentKeys[41] = false;

	//ARROWS

	if (glfwGetKey(this->thisWindow, GLFW_KEY_LEFT))
	{
		currentKeys[42] = true;
	}
	else currentKeys[42] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_UP))
	{
		currentKeys[43] = true;
	}
	else currentKeys[43] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_RIGHT))
	{
		currentKeys[44] = true;
	}
	else currentKeys[44] = false;

	if (glfwGetKey(this->thisWindow, GLFW_KEY_DOWN))
	{
		currentKeys[45] = true;
	}
	else currentKeys[45] = false;

	//mouseee
	double xpos = (double)this->mouseXPosition;
	double ypos = (double)this->mouseYPosition;
	glfwGetCursorPos(this->thisWindow, &xpos, &ypos);

	this->mouseXPosition = (float)xpos;
	this->mouseYPosition = (float)ypos;
}

void InputManager::UpdateLast()
{
	for (int i = 0; i < this->keyCount; ++i)
	{
		this->previousKeys[i] = this->currentKeys[i];
	}

	//mouse

	//mouseee
	this->mouseXPositionPrevious = this->mouseXPosition;
	this->mouseYPositionPrevious = this->mouseYPosition;

	//check for gameover
}

bool InputManager::GetKey(const char* keyName, KeyPress press)
{
	int valueCheck = -1;

	if (keyName == "0")
	{
		valueCheck = 0;
	}
	else if (keyName == "1")
	{
		valueCheck = 1;
	}
	else if (keyName == "2")
	{
		valueCheck = 2;
	}
	else if (keyName == "3")
	{
		valueCheck = 3;
	}
	else if (keyName == "4")
	{
		valueCheck = 4;
	}
	else if (keyName == "5")
	{
		valueCheck = 5;
	}
	else if (keyName == "6")
	{
		valueCheck = 6;
	}
	else if (keyName == "7")
	{
		valueCheck = 7;
	}
	else if (keyName == "8")
	{
		valueCheck = 8;
	}
	else if (keyName == "9")
	{
		valueCheck = 9;
	}
	else if (keyName == "A")
	{
		valueCheck = 10;
	}
	else if (keyName == "B")
	{
		valueCheck = 11;
	}
	else if (keyName == "C")
	{
		valueCheck = 12;
	}
	else if (keyName == "D")
	{
		valueCheck = 13;
	}
	else if (keyName == "E")
	{
		valueCheck = 14;
	}
	else if (keyName == "F")
	{
		valueCheck = 15;
	}
	else if (keyName == "G")
	{
		valueCheck = 16;
	}
	else if (keyName == "H")
	{
		valueCheck = 17;
	}
	else if (keyName == "I")
	{
		valueCheck = 18;
	}
	else if (keyName == "J")
	{
		valueCheck = 19;
	}
	else if (keyName == "K")
	{
		valueCheck = 20;
	}
	else if (keyName == "L")
	{
		valueCheck = 21;
	}
	else if (keyName == "M")
	{
		valueCheck = 22;
	}
	else if (keyName == "N")
	{
		valueCheck = 23;
	}
	else if (keyName == "O")
	{
		valueCheck = 24;
	}
	else if (keyName == "P")
	{
		valueCheck = 25;
	}
	else if (keyName == "Q")
	{
		valueCheck = 26;
	}
	else if (keyName == "R")
	{
		valueCheck = 27;
	}
	else if (keyName == "S")
	{
		valueCheck = 28;
	}
	else if (keyName == "T")
	{
		valueCheck = 29;
	}
	else if (keyName == "U")
	{
		valueCheck = 30;
	}
	else if (keyName == "V")
	{
		valueCheck = 31;
	}
	else if (keyName == "W")
	{
		valueCheck = 32;
	}
	else if (keyName == "X")
	{
		valueCheck = 33;
	}
	else if (keyName == "Y")
	{
		valueCheck = 34;
	}
	else if (keyName == "Z")
	{
		valueCheck = 35;
	}

	else if (keyName == "Space")
	{
		valueCheck = 36;
	}
	else if (keyName == "Left Shift")
	{
		valueCheck = 37;
	}
	else if (keyName == "Right Shift")
	{
		valueCheck = 38;
	}

	else if (keyName == "Tab")
	{
		valueCheck = 39;
	}
	else if (keyName == "Left Alt")
	{
		valueCheck = 40;
	}
	else if (keyName == "Right Alt")
	{
		valueCheck = 41;
	}

	else if (keyName == "Left")
	{
		valueCheck = 42;
	}
	else if (keyName == "Up")
	{
		valueCheck = 43;
	}
	else if (keyName == "Right")
	{
		valueCheck = 44;
	}
	else if (keyName == "Down")
	{
		valueCheck = 45;
	}

	switch (press)
	{
	case KeyPress::Down:
		return this->currentKeys[valueCheck];
		break;
	case KeyPress::Trigger:
		return this->currentKeys[valueCheck] && !this->previousKeys[valueCheck];
		break;
	case KeyPress::Release:
		return !this->currentKeys[valueCheck] && this->previousKeys[valueCheck];
		break;
	}

	printf("Cannot find input for key with name %s.", keyName);
	return false;
}

bool InputManager::GetKey(int keyIndex, KeyPress press)
{
	switch (press)
	{
	case KeyPress::Down:
		return this->currentKeys[keyIndex];
		break;
	case KeyPress::Trigger:
		return this->currentKeys[keyIndex] && !this->previousKeys[keyIndex];
		break;
	case KeyPress::Release:
		return !this->currentKeys[keyIndex] && this->previousKeys[keyIndex];
		break;
	}

	printf("Cannot find input for key with index %d.", keyIndex);
	return false;
}