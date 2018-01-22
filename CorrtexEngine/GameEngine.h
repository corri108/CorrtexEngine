#pragma once
#include "CorrtexGame.h"
#include "Game.h"

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void Run();
	void Init();
	void Update();
	void Draw();
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	GLFWwindow* WindowInit(int w, int h, char windowTitle[], bool fullscreen);
	bool gameOver = false;
	float width = 1600, height = 1000;
	float time = 0.0f;
	float timeStep = 0.001f;
	float aspectRatio = width / height;

	GLuint programID;
	CorrtexFPSCamera *camera;
	InputManager *input;
	ShaderUniform *mvpUni;
	GLFWwindow *window;
	void SetUserFunc(CorrtexFunc userInit, CorrtexFuncf userUpdate);
protected:
	CorrtexFunc UserInit;
	CorrtexFuncf UserUpdate;
};

