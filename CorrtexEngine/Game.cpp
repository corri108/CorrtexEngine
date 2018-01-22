#include "stdafx.h"
#include "Game.h"

LinkedList<CorrtexObject*> *seperateList = new LinkedList<CorrtexObject*>();
CorrtexMesh *mesh = NULL;

Game::Game()
{

}

Game::~Game()
{

}

void B1(CorrtexObject &co)
{

}

void Game::Init()
{
	//make a weird sphere thing
	float amplitude = 0.9f;
	for (int i = 0; i < 12; ++i)
	{
		float phase = (float)i / 12.0f;
		phase *= 3.14159f * 2.0f;
		CorrtexCube * cq = new CorrtexCube(vec3(cos(phase) * amplitude, 0.0f, sin(phase) * amplitude), 0.25f);
		seperateList->Add(cq);
	}

	//make floor, ceiling
	CorrtexQuad *quad = new CorrtexQuad(vec3(0, -0.001f, 0), 1.0f);
	CorrtexQuad *quad2 = new CorrtexQuad(vec3(0, 10.001f, 0), 1.0f);

	CorrtexTetrahedron * tet = new CorrtexTetrahedron(vec3(1, 2, 0), 1.0f);
	mesh = new CorrtexMesh(vec3(-2, 0, 0), "Assets/teapot.obj");
	mesh->SetScale(0.3f);
}

void Game::Update(float time, int frame)
{
	int c = seperateList->Count();

	for (int i = 0; i < c; ++i)
	{
		seperateList->Get(i)->position = seperateList->Get(i)->startingPosition + vec3(0, sin(time), 0);
	}

	if (frame % 50 == 0)
	{
		CorrtexCube *c = new CorrtexCube(vec3(sin(time) * 4, -cos(time / 8) * 4, cos(time) * 4), 0.75f);
	}
}