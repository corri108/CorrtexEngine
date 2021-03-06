#pragma once
#include <glew.h>
#include "LinkedList.h"
#include "BMPLoader.h"
#include "CorrtexLight.h"
#include "CorrtexWater.h"
#include "AnimatedModel.h"
#include "CorrtexFPSCamera.h"
#include "CorrtexRandom.h"
#include "ModelLoader.h"
#include "VBOIndexer.h"

//the actual game engine class. this is the heart of the program, and is in control of the main game loop,
//along with many helper functions.
class GameEngine
{
public:
	//ctor/dtor
	GameEngine();
	~GameEngine();

	//helpful user functions - make a lot of them static, so that we dont have to always keep a reference to the game to call some of the functions.
	static void LoadModel(const char *filePath, std::vector<vec3> &out_verts, std::vector<vec2> &out_uvs, std::vector<vec3> &out_norms);
	static void ComputeTangents(vector<vec3> in_verts, vector<vec2> in_uvs, vector<vec3> in_norms,
		vector<vec3> &out_tangents, vector<vec3> &out_bitangents);
	static int GetWindowWidth();
	static int GetWindowHeight();
	//buffer stuff
	static void BindFrameBuffer(GLuint frameBuffer, int w, int h);
	static void UnbindCurrentFrameBuffer();
	static GLuint GenColorTexture(int w, int h);
	static GLuint GenDepthTexture(int w, int h);
	static GLuint GenDepthBuffer(int w, int h);
	static GLuint GenFrameBuffer();

	//simple variables
	bool gameOver = false;
	static float width, height;
	static float time;
	static float timeMod;
	static float timeStep;//1/60th of sec
	int frame = 0;
	float aspectRatio = width / height;
	static bool initLoaded;
	static int lightCount;
	static bool showFPS;
	static bool wireframeOn;
	//important members - including lists, input manager, file loaders, and other neccesities
	static LinkedList<CorrtexObject*> *objectList;
	static LinkedList<CorrtexLight*> *lights;
	static CorrtexFPSCamera *camera;
	static InputManager *input;
	static ModelLoader *modelLoader;
	static BMPLoader *imageLoader;
	static CorrtexLight * light1;
	static VBOIndexer *vboIndexer;
	static CorrtexWater *waterObject;
	static vec4 clippingPlane;
	GLuint programID;
	ShaderUniform *mvpUni;
	GLFWwindow *window;

	//run + other important methods
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
	void DrawScene();
	void FBOObjectsDraw();
	void DoReflection(float waterHeight);
	void DoRefraction(float waterHeight);
	void UpdateDisplay();
	void FPSCounter();
	double fpsLastTime = 0.0;
	int fpsFrameNum = 0;
	GLFWwindow* WindowInit(int w, int h, char windowTitle[], bool fullscreen);
};

