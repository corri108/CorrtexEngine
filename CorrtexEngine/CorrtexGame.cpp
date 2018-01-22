#include "stdafx.h"
#include "CorrtexGame.h"

LinkedList<CorrtexObject*> *CorrtexGame::objectList = NULL;

CorrtexGame::CorrtexGame(int w, int h, char windowTitle[], bool fullscreen)
{
	this->windowWidth = w;
	this->windowHeight = h;
	this->windowTitle = windowTitle;
	this->fullscreen = fullscreen;
}

CorrtexGame::~CorrtexGame()
{
	//delete this->window;
}

void CorrtexGame::SetStandardShader(char *vertexShaderPath, char *fragmentShaderPath)
{
	this->currentVertexShader = vertexShaderPath;
	this->currentFragmentShader = fragmentShaderPath;
}

void CorrtexGame::SetUserFunc(CorrtexFunc init, CorrtexFuncf update)
{
	this->UserInit = init;
	this->UserUpdate = update;
}

GLFWwindow* CorrtexGame::WindowInit(int w, int h, char windowTitle[], bool fullscreen)
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

GLuint CorrtexGame::LoadShaders(const char * vertex_file_path, const char * fragment_file_path)
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

void CorrtexGame::Init()
{
	this->window = WindowInit(this->windowWidth, this->windowHeight, this->windowTitle, this->fullscreen);
	this->programID = LoadShaders(this->currentVertexShader, this->currentFragmentShader);
	this->camera = new CorrtexFPSCamera(0.001f, 500.0f, this->aspectRatio, 60.0f);
	this->input = new InputManager(this->window);
	this->objectList = new LinkedList<CorrtexObject*>();
	this->bmpLoader = new BMPLoader();
	this->modelLoader = new ModelLoader();

	this->mvpUniform = new ShaderUniform(Matrix4x4, this->programID, "MVP");

	//load texture
	this->textureID = bmpLoader->LoadBMP("Assets/cubeTex1.bmp");
	GLuint tex_handle = glGetUniformLocation(programID, "tex");
	glUniform1i(tex_handle, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void CorrtexGame::ObjectListInit()
{
	this->cq = new CorrtexQuad();

	int c = objectList->Count();
	for (int i = 0; i < c; ++i)
	{
		objectList->Get(i)->Initialize();
	}
}

void CorrtexGame::Update()
{
	//first update the input before anything else
	input->UpdateFirst();

	this->camera->Update(this->time, *input);

	int c = objectList->Count();
	for (int j = 0; j < c; ++j)
	{
		objectList->Get(j)->Update(this->time);
	}

	time += timeStep;
	frame++;

	//check for gameover
	gameOver = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
		glfwWindowShouldClose(window) != 0;
}

void CorrtexGame::Draw()
{
	glClearColor(0.4f, 0.6f, 0.8f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glUseProgram(this->programID);

	mat4 proj = camera->GetProjectionMatrix();
	mat4 view = camera->GetViewMatrix();

	int c = objectList->Count();
	for (int i = 0; i < c; ++i)
	{
		objectList->Get(i)->Draw(view, proj, *mvpUniform);
	}

	glfwSwapBuffers(window);
	glfwPollEvents();

	//last of all end the update for input
	input->UpdateLast();
}

int CorrtexGame::Run()
{
	this->Init();
	this->UserInit();
	this->ObjectListInit();

	while (!this->gameOver)
	{
		this->Update();
		this->UserUpdate(this->time);
		this->Draw();
	}

	return 0;
}