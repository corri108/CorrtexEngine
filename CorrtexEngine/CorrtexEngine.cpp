// CorrtexEngine.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "GameEngine.h"

using namespace glm;

bool gameOver = false;
int width, height;

LinkedList<CorrtexObject*> *objectList;
InputManager *input = NULL;

GLFWwindow * CorrtexInit(int w, int h, char windowTitle[], bool fullscreen)
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

	srand(time(NULL));

	return window;
}

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) 
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

void RaymarchMain()
{
	width = 1024;
	height = 768;
	GLFWwindow *window = CorrtexInit(width, height, "Corrtex Engine Alpha v1.0", false);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//load shaders
	GLuint programID = LoadShaders("raymarch.vertexshader", "raymarchfrag.fragmentshader");

	GLuint res_handle = glGetUniformLocation(programID, "iResolution");
	GLuint time_handle = glGetUniformLocation(programID, "iGlobalTime");

	GLuint texCoordBuffer;
	float sample_tex_coord[] = {
		0.0f, 0.0f,
		0.0f, 0.1f,
		0.1f, 0.0f,
		0.1f, 0.1f
	};

	float aspect = (float)width / (float)height;
	CorrtexCamera * camera = new CorrtexCamera(0.001f, 500.0f, aspect, 50.0f);

	glGenBuffers(1, &texCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sample_tex_coord), sample_tex_coord, GL_STATIC_DRAW);

	float s = 0.001f;
	float t = 0.0f;
	int i = 0;

	do
	{
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glUseProgram(programID);


		glUniform2f(res_handle, width, height);
		glUniform1f(time_handle, t);

		glfwSwapBuffers(window);
		glfwPollEvents();

		t += s;
		i++;

		// Check if the ESC key was pressed or the window was closed
		gameOver = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
			glfwWindowShouldClose(window) != 0;

	} while (!gameOver);
}

void MakeCubeRing()
{
	//make a weird sphere thing
	float amplitude = 0.9f;
	for (int i = 0; i < 12; ++i)
	{
		float phase = (float)i / 12.0f;
		phase *= 3.14159f * 2.0f;
		CorrtexCube * cq = new CorrtexCube(vec3(cos(phase) * amplitude, 0.0f, sin(phase) * amplitude), 0.25f);
		//bum->Add(new CorrtexCube(vec3(cos(phase) * amplitude, 0.0f, sin(phase) * amplitude), 0.25f));
	}
}

int EngineMain()
{
	float width = 1600, height = 1000;
	float time = 0.0f;
	float tstep = 0.001f;
	float aspectRatio = width / height;
	CorrtexDebug::Set(true);

	GLFWwindow *window = CorrtexInit(width, height, "Corrtex Engine Alpha v1.0", false);
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	CorrtexGame::objectList = new LinkedList<CorrtexObject*>();
	MakeCubeRing();
	//camera, input & model view projection matrix handle
	CorrtexFPSCamera *camera = new CorrtexFPSCamera(0.01f, 500.0f, aspectRatio, 50.0f);
	InputManager *input = new InputManager(window);
	ShaderUniform *mvpUni = new ShaderUniform(Matrix4x4, programID, "MVP");
	//make floor, ceiling
	CorrtexQuad *quad = new CorrtexQuad(vec3(0, -0.001f, 0), 1.0f);
	CorrtexQuad *quad2 = new CorrtexQuad(vec3(0, 10.001f, 0), 1.0f);

	int c = CorrtexGame::objectList->Count();
	for (int i = 0; i < c; ++i)
	{
		CorrtexGame::objectList->Get(i)->Initialize();
	}

	while (!gameOver)
	{
		input->UpdateFirst();

		glClearColor(0.4f, 0.6f, 0.8f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glUseProgram(programID);

		camera->Update(time, *input);

		int c = CorrtexGame::objectList->Count();
		for (int i = 0; i < c; ++i)
		{
			CorrtexGame::objectList->Get(i)->Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix(), *mvpUni);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		time += tstep;

		input->UpdateLast();

		//gameover
		gameOver = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
			glfwWindowShouldClose(window) != 0;
	}

	return 0;
}

int Run()
{
	CorrtexGame *game = new CorrtexGame(1024, 768, "Corrtex Engine Alpha v1.0", false);
	//game->SetUserFunc(Game::Init, Game::Update);
	game->SetStandardShader("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	int end = game->Run();

	return end;
}

int main()
{
	//return EngineMain();
	//return Run();
	GameEngine *tg = new GameEngine();
	tg->SetUserFunc(Game::Init, Game::Update);
	tg->Run();
	return 0;
}

