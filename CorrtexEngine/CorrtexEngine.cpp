//Author: William Corrin III

//This is my personal project. The main goals of this engine project are to:
//1. Get familiar with OpenGL graphics, including shaders
//2. Get familiar with the GLM math library
//3. Make it easy and fast for the user of the engine to create objects
//4. Keep #3 true, while still having access to the engine so that the user can modify things if they would like.

//questions or concerns? 
//email: mailto:williamdewaynecorrin@gmail.com
//webiste: http://williamdcorriniii.wixsite.com/wdc3

//MAIN ENTRY POINT FOR ENGINE
#include "stdafx.h"
#include "Game.h"

using namespace glm;

//entry point
int main()
{
	//simple and clean - create an instance of the game engine, set the correct user function and run it!
	GameEngine tg = GameEngine();
	tg.SetUserFunc(Game::Init, Game::Update);
	tg.Run();
	return 0;
}