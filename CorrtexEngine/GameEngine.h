#pragma once
#include "stdafx.h"
#include "glew.h"
#include "CorrtexDebug.h"
#include "glfw3.h"
#include "CorrtexCube.h"
#include "LinkedList.h"
#include "CorrtexLight.h"
#include "BMPLoader.h"
#include "CorrtexFPSCamera.h"
#include "InputManager.h"
#include "CorrtexRandom.h"
#include "ModelLoader.h"
#include "CorrtexDelegate.h"
#include "CorrtexShader.h"
#include "CorrtexQuad.h"
#include "CorrtexTetrahedron.h"
#include "CorrtexMesh.h"
#include <glm/ext.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include "Game.h"

class GameEngine
{
public:
	//ctor/dtor
	GameEngine();
	~GameEngine();

	//user functions
	static void LoadModel(const char *filePath, std::vector<vec3> &out_verts, std::vector<vec2> &out_uvs, std::vector<vec3> &out_norms);

	//simple variables
	bool gameOver = false;
	float width = 1600, height = 1000;
	float time = 0.0f;
	float timeStep = 10.0f;
	int frame = 0;
	float aspectRatio = width / height;
	static bool initLoaded;
	//important members
	static LinkedList<CorrtexObject*> *objectList;
	static CorrtexFPSCamera *camera;
	static InputManager *input;
	static ModelLoader *modelLoader;
	static BMPLoader *imageLoader;
	static CorrtexLight * light1;
	GLuint programID;
	ShaderUniform *mvpUni;
	GLFWwindow *window;

	//public internal
	void Run();
	void SetUserFunc(CorrtexFunc userInit, CorrtexFuncf userUpdate);
	static GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
protected:
	//delegates for function pointers
	CorrtexFunc UserInit;
	CorrtexFuncf UserUpdate;

	/////////////////////////////////////////////////////////////////////////////////
	//internal
	void Init();
	void Update();
	void Draw();
	//very internal
	GLFWwindow* WindowInit(int w, int h, char windowTitle[], bool fullscreen);
};

