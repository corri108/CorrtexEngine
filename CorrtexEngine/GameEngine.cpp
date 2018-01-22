#include "stdafx.h"
#include "GameEngine.h"


GameEngine::GameEngine()
{
}


GameEngine::~GameEngine()
{
}

GLFWwindow* GameEngine::WindowInit(int w, int h, char windowTitle[], bool fullscreen)
{
	if (glfwInit() != GLFW_TRUE)
	{
		fprintf(stderr, "Couldn't initialize glfw\n");
		return NULL;
	}

	GLFWwindow *window = glfwCreateWindow(w, h, windowTitle, fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

void GameEngine::SetUserFunc(CorrtexFunc userInit, CorrtexFuncf userUpdate)
{
	this->UserInit = userInit;
	this->UserUpdate = userUpdate;
}

void GameEngine::Init()
{
	CorrtexDebug::Set(true);

	window = WindowInit(width, height, "Corrtex Engine Alpha v1.0", false);
	programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	CorrtexGame::objectList = new LinkedList<CorrtexObject*>();
	//camera, input & model view projection matrix handle
	camera = new CorrtexFPSCamera(0.01f, 500.0f, aspectRatio, 50.0f);
	input = new InputManager(window);
	mvpUni = new ShaderUniform(Matrix4x4, programID, "MVP");

	UserInit();

	int c = CorrtexGame::objectList->Count();
	for (int i = 0; i < c; ++i)
	{
		CorrtexGame::objectList->Get(i)->Initialize();
	}
}

void GameEngine::Update()
{
	input->UpdateFirst();
	camera->Update(time, *input);

	int c = CorrtexGame::objectList->Count();
	for (int i = 0; i < c; ++i)
	{
		CorrtexGame::objectList->Get(i)->Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix(), *mvpUni);
	}
}

void GameEngine::Draw()
{
	Update();
	UserUpdate(this->time);

	glClearColor(0.4f, 0.6f, 0.8f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glUseProgram(programID);

	//camera->Update(time, *input);

	int c = CorrtexGame::objectList->Count();
	for (int i = 0; i < c; ++i)
	{
		CorrtexGame::objectList->Get(i)->Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix(), *mvpUni);
	}

	glfwSwapBuffers(window);
	glfwPollEvents();

	time += timeStep;

	input->UpdateLast();

	//gameover
	gameOver = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
		glfwWindowShouldClose(window) != 0;

}

void GameEngine::Run()
{
	Init();

	while (!gameOver)
	{
		Update();
		Draw();
	}
}