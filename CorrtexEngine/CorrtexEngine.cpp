// CorrtexEngine.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "Game.h"

using namespace glm;

int main()
{
	GameEngine *tg = new GameEngine();
	tg->SetUserFunc(Game::Init, Game::Update);
	tg->Run();
	return 0;
}

