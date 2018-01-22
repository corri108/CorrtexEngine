#pragma once
#include "GameEngine.h"

class Game
{
public:
	Game();
	~Game();
	static void Init();
	static void Update(float time, int frame);
};

