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
#include "VBOIndexer.h"
#include "Game.h"

class GameEngine
{
public:
	//ctor/dtor
	GameEngine();
	~GameEngine();

	//user functions
	static void LoadModel(const char *filePath, std::vector<vec3> &out_verts, std::vector<vec2> &out_uvs, std::vector<vec3> &out_norms);
	static void ComputeTangents(vector<vec3> in_verts, vector<vec2> in_uvs, vector<vec3> in_norms,
		vector<vec3> &out_tangents, vector<vec3> &out_bitangents);

	//simple variables
	bool gameOver = false;
	float width = 1600, height = 1000;
	float time = 0.0f;
	float timeStep = 10.0f;
	int frame = 0;
	float aspectRatio = width / height;
	static bool initLoaded;
	static int lightCount;
	static bool showFPS;
	static bool wireframeOn;
	//important members
	static LinkedList<CorrtexObject*> *objectList;
	static LinkedList<CorrtexLight*> *lights;
	static CorrtexFPSCamera *camera;
	static InputManager *input;
	static ModelLoader *modelLoader;
	static BMPLoader *imageLoader;
	static CorrtexLight * light1;
	static VBOIndexer *vboIndexer;
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
	void FPSCounter();
	double fpsLastTime = 0.0;
	int fpsFrameNum = 0;
	//very internal
	GLFWwindow* WindowInit(int w, int h, char windowTitle[], bool fullscreen);
};

