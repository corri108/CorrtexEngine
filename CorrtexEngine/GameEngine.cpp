#include "stdafx.h"
#include "GameEngine.h"

//static shite
LinkedList<CorrtexObject*> *GameEngine::objectList = NULL;
LinkedList<CorrtexLight*> *GameEngine::lights = NULL;
CorrtexFPSCamera *GameEngine::camera = NULL;
InputManager *GameEngine::input = NULL;
ModelLoader *GameEngine::modelLoader = NULL;
BMPLoader *GameEngine::imageLoader = NULL;
CorrtexLight *GameEngine::light1 = NULL;
CorrtexWater *GameEngine::waterObject = NULL;
VBOIndexer *GameEngine::vboIndexer = NULL;
bool GameEngine::initLoaded = false;
int GameEngine::lightCount = 0;
bool GameEngine::showFPS = true;
bool GameEngine::wireframeOn = false;
float GameEngine::width = 0;
float GameEngine::height = 0;
float GameEngine::time = 0.0f;
float GameEngine::timeStep = 0.016666666f;//1/60th of sec
float GameEngine::timeMod = 0.0f;
vec4 GameEngine::clippingPlane = vec4(0, -1, 0, 10000000000);

GameEngine::GameEngine()
{
}


GameEngine::~GameEngine()
{
}

//helper functions! (mostly static)
void GameEngine::LoadModel(const char *filePath, std::vector<vec3> &out_verts, std::vector<vec2> &out_uvs, std::vector<vec3> &out_norms)
{
	modelLoader->LoadOBJ(filePath, out_verts, out_uvs, out_norms);
}

void GameEngine::ComputeTangents(vector<vec3> in_verts, vector<vec2> in_uvs, vector<vec3> in_norms,
	vector<vec3> &out_tangents, vector<vec3> &out_bitangents)
{
	//go through each tri
	for (int i = 0; i < in_verts.size(); i += 3)
	{
		vec3 &v0 = in_verts[i];
		vec3 &v1 = in_verts[i + 1];
		vec3 &v2 = in_verts[i + 2];

		vec2 &uv0 = in_uvs[i];
		vec2 &uv1 = in_uvs[i + 1];
		vec2 &uv2 = in_uvs[i + 2];

		vec3 delta_pos1 = v1 - v0;
		vec3 delta_pos2 = v2 - v0;

		vec2 delta_uv1 = uv1 = uv0;
		vec2 delta_uv2 = uv2 - uv0;

		//compute tangents and bitangents
		float r = 1.0f / (delta_uv1.x * delta_uv2.y - delta_uv1.y * delta_uv2.x);
		vec3 tangent = (delta_pos1 * delta_uv2.y - delta_pos2 * delta_uv1.y) * r;
		vec3 bitangent = (delta_pos2 * delta_uv1.x - delta_pos1 * delta_uv2.x) * r;

		out_tangents.push_back(tangent);
		out_tangents.push_back(tangent);
		out_tangents.push_back(tangent);

		out_bitangents.push_back(bitangent);
		out_bitangents.push_back(bitangent);
		out_bitangents.push_back(bitangent);
	}
}

int GameEngine::GetWindowWidth()
{
	return (int)width;
}

int GameEngine::GetWindowHeight()
{
	return (int)height;
}

void GameEngine::BindFrameBuffer(GLuint frameBuffer, int w, int h)
{
	glBindTexture(GL_TEXTURE_2D, 0);//make sure no texture is bound
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, w, h);
}

void GameEngine::UnbindCurrentFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, width, height);
}

GLuint GameEngine::GenColorTexture(int w, int h)
{
	// The texture we're going to render to
	GLuint renderedTexture;
	glGenTextures(1, &renderedTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
		0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

	return renderedTexture;
}

GLuint GameEngine::GenDepthTexture(int w, int h)
{
	// The texture we're going to render to
	GLuint renderedTexture;
	glGenTextures(1, &renderedTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, w, h,
		0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, renderedTexture, 0);

	return renderedTexture;
}

GLuint GameEngine::GenDepthBuffer(int w, int h)
{
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	return depthBuffer;
}

GLuint GameEngine::GenFrameBuffer()
{
	GLuint frameBuffer;
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);

	return frameBuffer;
}

//very internal functions
GLFWwindow* GameEngine::WindowInit(int w, int h, char windowTitle[], bool fullscreen)
{
	GLenum glfwErr = glfwInit();

	if (glfwErr != GLFW_TRUE)
	{
		fprintf(stderr, "Couldn't initialize glfw\n");
		return NULL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_DECORATED, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	GLFWwindow *window = glfwCreateWindow(w, h, windowTitle, fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

	glfwMakeContextCurrent(window);

	printf("Version: %s\n", glGetString(GL_VERSION));
	printf("Device: %s\n", glGetString(GL_RENDERER));

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		// Problem: glewInit failed, something is seriously wrong.
		printf("glewInit failed. %s\n", glewGetErrorString(err));
		return NULL;
	}

	return window;
}

GLuint GameEngine::LoadShaders(const char * vertex_file_path, const char * fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

//regular internal functions
void GameEngine::SetUserFunc(CorrtexFunc userInit, CorrtexFuncf userUpdate)
{
	this->UserInit = userInit;
	this->UserUpdate = userUpdate;
}

void GameEngine::FPSCounter()
{
	// Measure speed
	double currentTime = glfwGetTime();
	fpsFrameNum++;
	if (currentTime - fpsLastTime >= 1.0) { // If last prinf() was more than 1 sec ago
										 // printf and reset timer
		double msecPerFrame = 1000.0 / double(fpsFrameNum);
		//printf("%f ms/frame\n", msecPerFrame);
		double fps = (1 / msecPerFrame) * 1000.0;
		printf("FPS: %f\n", fps);
		fpsFrameNum = 0;
		fpsLastTime += 1.0;
	}
}

void GameEngine::Init()
{
	width = 1600;
	height = 900;
	aspectRatio = (float)width / (float)height;


	window = WindowInit(width, height, "Corrtex Engine Alpha v1.0", true);
	programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	objectList = new LinkedList<CorrtexObject*>();
	lights = new LinkedList<CorrtexLight*>();
	//camera, input & model view projection matrix handle
	camera = new CorrtexFPSCamera(0.01f, 2000.0f, aspectRatio, 50.0f);
	camera->cameraPosition = vec3(-230, 150, -230);
	input = new InputManager(window);
	mvpUni = new ShaderUniform(Matrix4x4, programID, "MVP");
	modelLoader = new ModelLoader();
	imageLoader = new BMPLoader();
	light1 = new CorrtexLight(vec4(0, 0, 0, 0), 0.88f * vec3(1, 1, 1));
	vboIndexer = new VBOIndexer();
	fpsLastTime = glfwGetTime();
	fpsFrameNum = 0;
	//CorrtexLight *light2 = new CorrtexLight(vec4(2, 3, 0, 1), 1 * vec3(0, 0, 1));//blue spot light
	//light2->coneAngle = 45.0f;
	//CorrtexLight *light3 = new CorrtexLight(vec4(1, 5, 2, 0), 1 * vec3(1, 1, 1));//white directional light


	UserInit();

	int c = objectList->Count();
	for (int i = 0; i < c; ++i)
	{
		objectList->Get(i)->Initialize();
	}

	initLoaded = true;
}

void GameEngine::Update()
{
	input->UpdateFirst();
	camera->Update(time, *input);

	UserUpdate(time, frame);

	int c = objectList->Count();
	for (int i = 0; i < c; ++i)
	{
		objectList->Get(i)->Update(time);
	}
}

void GameEngine::UpdateDisplay()
{
	//poll events and swap buffers
	glfwPollEvents();
	glfwSwapBuffers(window);

	//increase time
	time += timeStep;

	//deal with modTime (time that is always from 0->1)
	timeMod += timeStep;
	if (timeMod >= 1.0f)
		timeMod -= 1.0f;

	//increase frame
	frame++;

	//update input
	input->UpdateLast();

	//gameover
	gameOver = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
		glfwWindowShouldClose(window) != 0;
}

void GameEngine::DrawScene()
{
	int currentFrameBuffer;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFrameBuffer);

	this->FPSCounter();
	glClearColor(0.4f, 0.6f, 0.8f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glUseProgram(programID);

	if (this->wireframeOn)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//camera->Update(time, *input);

	//draw every object in the object list
	int c = objectList->Count();
	for (int i = 0; i < c; ++i)
	{
		//get pointer to current object
		CorrtexObject *o = objectList->Get(i);

		if (dynamic_cast<CorrtexWater*>(o) == nullptr)
		{
			if (currentFrameBuffer == 0 || o->renderOtherBuffers)
			{
				glUseProgram(programID);//set default shader for those objects without shaders
				o->Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix(), *mvpUni);
			}
		}
	}
}

void GameEngine::DoReflection(float waterHeight)
{
	///////////////////////////////////////////////////////////////////////
	//REFLECTION
	///////////////////////////////////////////////////////////////////////

	//set clipping plane
	clippingPlane = vec4(0, 1, 0, -waterHeight);

	//move camera
	float distance = 2 * (camera->cameraPosition.y - waterHeight);

	camera->cameraPosition.y -= distance;
	camera->InvertPitch();

	//bind buffer and draw scene
	waterObject->BindReflectionFrameBuffer();
	DrawScene();

	//move camera back
	camera->InvertPitch();
	camera->cameraPosition.y += distance;
}

void GameEngine::DoRefraction(float waterHeight)
{
	///////////////////////////////////////////////////////////////////////
	//REFRACTION
	///////////////////////////////////////////////////////////////////////

	//set clipping plane
	clippingPlane = vec4(0, -1, 0, waterHeight);

	//bind buffer and draw scene
	waterObject->BindRefractionFrameBuffer();
	DrawScene();
}

void GameEngine::FBOObjectsDraw()
{
	//if we have water
	int waterPos = -35;

	if (waterObject != NULL)
	{
		glEnable(GL_CLIP_DISTANCE0);

		DoReflection(waterPos );
		DoRefraction(waterPos + 1);

		//unbind the current buffer before we draw the actual scene.
		this->UnbindCurrentFrameBuffer();
		glDisable(GL_CLIP_DISTANCE0);
		clippingPlane.w = 100000000000;
	}

	//update textures onto object
	int sz = objectList->Count();
	for (int i = 0; i < sz; ++i)
	{
		if (objectList->Get(i)->name == "WaterPlane")
		{
			objectList->Get(i)->material->UpdateTexture("tex", waterObject->reflectionTexture);
			objectList->Get(i)->material->UpdateTexture("tex2", waterObject->refractionTexture);
			objectList->Get(i)->material->UpdateTexture("depth", waterObject->refractionDepthTexture);
		}
	}
}

void GameEngine::Run()
{
	Init();

	while (!gameOver)
	{
		//update func
		Update();

		//special materials needing FBO will draw here
		FBOObjectsDraw();

		//draw the scene
		DrawScene();

		//update the display(swap buffers)
		UpdateDisplay();
	}
}