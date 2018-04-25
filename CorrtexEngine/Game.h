#pragma once
#include "GameEngine.h"

//user game class - this is very simple, and what the user will see when the project is first opened up.
//essentially, the user will create objects in the Init function, and add behaviours to the objects in there as well.
//then, the user will add any nessesary code to the Update function if needed. the GameEngine class automatically knows
//to take the Init and Update functions and use them while creating the game.
class Game
{
public:
	Game();
	~Game();
	static void Init();
	static void Update(float time, int frame);
};

