#pragma once
#include "stdafx.h"
#include "glew.h"
#include "CorrtexDebug.h"
#include "glfw3.h"
#include "CorrtexCube.h"
#include "LinkedList.h"
#include "BMPLoader.h"
#include "CorrtexFPSCamera.h"
#include "InputManager.h"
#include "CorrtexRandom.h"
#include "ModelLoader.h"
#include "CorrtexDelegate.h"
#include "ShaderUniform.h"
#include "CorrtexQuad.h"
#include <glm/ext.hpp>
#include <vector>
#include <fstream>
#include <sstream>

class CorrtexGame
{
public:
	CorrtexGame(int w, int h, char windowTitle[], bool fullscreen);
	~CorrtexGame();
	void SetStandardShader(char *vertexShaderPath, char *fragmentShaderPath);
	void SetUserFunc(CorrtexFunc init, CorrtexFuncf update);
	int Run();
	bool gameOver = false;
	bool fullscreen = false;
	int windowWidth, windowHeight;
	char * windowTitle;
	static LinkedList<CorrtexObject*> *objectList;
	InputManager *input = NULL;
	GLFWwindow *window = NULL;
	BMPLoader *bmpLoader = NULL;
	ModelLoader *modelLoader = NULL;
	CorrtexCamera * camera = NULL;
	
	//shader ID
	GLuint programID;
	//texture ID
	GLuint textureID;
	GLuint textureID2;
	float aspectRatio;
	float timeStep = 0.001f;
	float time = 0.0f;
	int frame = 0;
	CorrtexQuad *cq = NULL;


	//test vars
	int testVertexCount = 36;
	GLfloat *testVertexBufferData = new GLfloat[36 * 3]
	{
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,//one tri

		1, 0, 1,
		0, 0, 1,
		0, 0, 0,//two tri

		0, 0, 0,
		0, 1, 0,
		0, 1, 1,//three tri

		0, 1, 1,
		0, 0, 1,
		0, 0, 0,//four tri

		0, 1, 0,
		1, 1, 0,
		1, 1, 1,//5 tri

		1, 1, 1,
		0, 1, 1,
		0, 1, 0,//6 tri (half cube)

		0, 0, 0,
		1, 0, 0,
		1, 1, 0,

		1, 1, 0,
		0, 1, 0,
		0, 0, 0,

		0, 0, 1,
		1, 0, 1,
		1, 1, 1,

		1, 1, 1,
		0, 1, 1,
		0, 0, 1,

		1, 1, 1,
		1, 0, 1,
		1, 0, 0,

		1, 0, 0,
		1, 1, 0,
		1, 1, 1
	};
	GLfloat *testColorBufferData = new GLfloat[36 * 3]
	{
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,//one tri

		1, 0, 1,
		0, 0, 1,
		0, 0, 0,//two tri

		0, 0, 0,
		0, 1, 0,
		0, 1, 1,//three tri

		0, 1, 1,
		0, 0, 1,
		0, 0, 0,//four tri

		0, 1, 0,
		1, 1, 0,
		1, 1, 1,//5 tri

		1, 1, 1,
		0, 1, 1,
		0, 1, 0,//6 tri (half cube)

		0, 0, 0,
		1, 0, 0,
		1, 1, 0,

		1, 1, 0,
		0, 1, 0,
		0, 0, 0,

		0, 0, 1,
		1, 0, 1,
		1, 1, 1,

		1, 1, 1,
		0, 1, 1,
		0, 0, 1,

		1, 1, 1,
		1, 0, 1,
		1, 0, 0,

		1, 0, 0,
		1, 1, 0,
		1, 1, 1
	};
	GLuint testVertexBuffer;
	GLuint testColorBuffer;

private:
	GLFWwindow* WindowInit(int w, int h, char windowTitle[], bool fullscreen);
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void Update();
	void Draw();
	void Init();
	void ObjectListInit();
	char *currentVertexShader = "";
	char *currentFragmentShader = "";
	CorrtexFunc UserInit;
	CorrtexFuncf UserUpdate;
	ShaderUniform *mvpUniform;
};

