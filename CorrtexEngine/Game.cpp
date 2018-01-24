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
	//test phong shader
	CorrtexShader *phongGamma = new CorrtexShader("PhongGammaVertexShader.vertexshader", "PhongGammaFragmentShader.fragmentshader");
	phongGamma->AddAttributes(VERTEX, UV, NORMAL);
	phongGamma->AddUniforms(Matrix4x4, "MVP", Matrix4x4, "modelMatrix", Texture, "tex");
	phongGamma->AddUniforms(Float3, "light.pos", Float3, "light.color", Float1, "light.attenuation");
	phongGamma->AddUniforms(Float3, "cameraPosition", Float3, "specularColor", Float1, "shininess");
	phongGamma->AddUniform(Float1, "ambientIntensity");
	//test phong shader
	CorrtexShader *phongShader = new CorrtexShader("PhongVertexShader.vertexshader", "PhongFragmentShader.fragmentshader");
	phongShader->AddAttributes(VERTEX, UV, NORMAL);
	phongShader->AddUniforms(Matrix4x4, "MVP", Matrix4x4, "modelMatrix", Texture, "tex");
	phongShader->AddUniforms(Float3, "light.pos", Float3, "light.color", Float1, "ambientIntensity");
	phongShader->AddUniforms(Float3, "cameraPosition", Float3, "specularColor", Float1, "shininess");
	//test diffuse shader
	CorrtexShader *diffuseShader = new CorrtexShader("DiffuseVertexShader.vertexshader", "DiffuseFragmentShader.fragmentshader");
	diffuseShader->AddAttributes(VERTEX, UV, NORMAL);
	diffuseShader->AddUniforms(Matrix4x4, "MVP", Matrix4x4, "modelMatrix", Texture, "tex");
	diffuseShader->AddUniforms(Float3, "light.pos", Float3, "light.color");
	//test texture shader
	CorrtexShader *textureShader = new CorrtexShader("TexturedVertexShader.vertexshader", "TexturedFragmentShader.fragmentshader");
	textureShader->AddAttributes(VERTEX, UV);
	textureShader->AddUniforms(Matrix4x4, "MVP", Texture, "tex");
	//test red shader
	CorrtexShader *redShader = new CorrtexShader("AllRed.vertexshader", "AllRed.fragmentshader");
	redShader->AddUniform(Matrix4x4, "MVP");
	redShader->AddAttribute(VERTEX);

	//make a weird sphere thing
	float amplitude = 1.9f;
	GLuint blueTexture = GameEngine::imageLoader->LoadBMP("Assets/cubeTex1.bmp");

	for (int i = 0; i < 12; ++i)
	{
		float phase = (float)i / 12.0f;
		phase *= 3.14159f * 2.0f;
		CorrtexCube * cq = new CorrtexCube(vec3(cos(phase) * amplitude, 0.0f, sin(phase) * amplitude), 1);
		cq->AddTexture(blueTexture);
		cq->SetShader(textureShader);
		seperateList->Add(cq);
	}

	CorrtexMaterial *testMat = new CorrtexMaterial(0.1f, 0.2f, vec3(0.9f, 0.11f, 0.33f));
	CorrtexMaterial *testMat2 = new CorrtexMaterial(0.1f, 0.2f, vec3(93.0f / 255.0f, 112.0f / 255.0f, 33.0f / 255.0f));
	//test mesh
	mesh = new CorrtexMesh(vec3(-3, 1.22f, 0), "Assets/crate.obj");
	mesh->SetScale(0.5f);
	mesh->AddTexture("Assets/metalCrate.bmp");
	mesh->SetShader(phongGamma);
	mesh->SetMaterial(testMat);

	CorrtexMesh* mesh2 = new CorrtexMesh(vec3(0, 0, 0), "Assets/terrain.obj");
	mesh2->SetScale(0.5f);
	mesh2->AddTexture("Assets/grass.bmp");
	mesh2->SetShader(phongGamma);
	mesh2->SetMaterial(testMat2);
	mesh2->scale = vec3(2, 1, 2);
}

void Game::Update(float time, int frame)
{
	if (GameEngine::input->GetKey("Up", Down))
	{
		GameEngine::light1->lightPosition.y += 0.025f;
	}
	if (GameEngine::input->GetKey("Right", Down))
	{
		GameEngine::light1->lightPosition.x += 0.025f;
	}
	if (GameEngine::input->GetKey("Down", Down))
	{
		GameEngine::light1->lightPosition.y -= 0.025f;
	}
	if (GameEngine::input->GetKey("Left", Down))
	{
		GameEngine::light1->lightPosition.x -= 0.025f;
	}
}