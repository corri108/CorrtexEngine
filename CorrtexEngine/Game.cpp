#include "stdafx.h"
#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

void B1(CorrtexObject &co)
{

}

CorrtexMesh *skysphere = NULL;
CorrtexMesh* water = NULL;
CorrtexMesh* terrain = NULL;
AnimatedModel* character = NULL;

void Game::Init()
{
	//set wireframe mode to false
	GameEngine::wireframeOn = false;

	//////////////////////////////////////////////////////////////////////////////////////////////
	//CREATE SHADERS HERE
	//////////////////////////////////////////////////////////////////////////////////////////////

	//animated model shader
	CorrtexShader *animatedShader = new CorrtexShader("AnimatedModel.vertexshader", "AnimatedModel.fragmentshader");
	animatedShader->AddAttributes(VERTEX, UV, NORMAL);
	animatedShader->AddAttributes(JOINTS, WEIGHTS);
	animatedShader->AddUniforms(Texture, "diffuse", Matrix4x4, "modelMatrix", Matrix4x4, "MVP");
	animatedShader->AddUniforms(Int1, "numJoints", Matrix4x4, "viewProjectionMatrix", Float4, "clippingPlane");
	animatedShader->AddUniforms(Float1, "ambientIntensity", Float1, "numLights", Float2, "texRatio");
	//array for bone stuff
	animatedShader->AddUniformArray(Matrix4x4, "joints", "boneTransform");
	//array for light stuff
	animatedShader->AddUniformsArray(Float4, "allLights", "pos", Float3, "allLights", "color", Float1, "allLights", "attenuation");
	animatedShader->AddUniformsArray(Float1, "allLights", "coneAngle", Float3, "allLights", "coneDirection");


	//water shader
	CorrtexShader *waterShader = new CorrtexShader("WaterVertexShader.vertexshader", "WaterFragmentShader.fragmentshader");
	waterShader->AddAttributes(VERTEX, UV, NORMAL);
	waterShader->AddUniforms(Matrix4x4, "MVP", Matrix4x4, "modelMatrix", Texture, "tex");
	waterShader->AddUniforms(Texture, "tex2", Float4, "clippingPlane", Float2, "texRatio");
	waterShader->AddUniforms(Float1, "time", Float1, "waveTime", Float1, "waveStrength");
	waterShader->AddUniforms(Texture, "dudv", Texture, "normal", Float3, "cameraPosition");
	waterShader->AddUniformsArray(Float4, "allLights", "pos", Float3, "allLights", "color", Float1, "allLights", "attenuation");
	waterShader->AddUniformsArray(Float1, "allLights", "coneAngle", Float3, "allLights", "coneDirection");
	waterShader->AddUniforms(Float1, "numLights", Float1, "shininess", Float3, "specularColor");
	waterShader->AddUniforms(Texture, "depth", Float1, "nearPlane", Float1, "farPlane");

	//multitextured terrain
	CorrtexShader *multitexturedTerrainShader = new CorrtexShader("MultitexturedTerrain.vertexshader", "MultitexturedTerrain.fragmentshader");
	multitexturedTerrainShader->AddAttributes(VERTEX, UV, NORMAL);
	multitexturedTerrainShader->AddAttributes(TANGENT, BITANGENT);
	multitexturedTerrainShader->AddUniforms(Matrix4x4, "MVP", Matrix4x4, "modelMatrix", Texture, "tex");
	multitexturedTerrainShader->AddUniformsArray(Float4, "allLights", "pos", Float3, "allLights", "color", Float1, "allLights", "attenuation");
	multitexturedTerrainShader->AddUniformsArray(Float1, "allLights", "coneAngle", Float3, "allLights", "coneDirection");
	multitexturedTerrainShader->AddUniforms(Float3, "cameraPosition", Float3, "specularColor", Float1, "shininess");
	multitexturedTerrainShader->AddUniforms(Float1, "ambientIntensity", Float2, "texRatio", Float1, "numLights");
	multitexturedTerrainShader->AddUniforms(Texture, "tex2", Texture, "tex3", Texture, "tex4");
	multitexturedTerrainShader->AddUniforms(Float3, "modelPosition", Matrix3x3, "MV3x3", Matrix4x4, "viewMatrix");
	multitexturedTerrainShader->AddUniforms(Float3, "lightPosition", Texture, "tex_normal");
	multitexturedTerrainShader->AddUniforms(Texture, "tex_normal2", Texture, "tex_normal3", Texture, "tex_normal4");
	multitexturedTerrainShader->AddUniform(Float4, "clippingPlane");

	//LOD shader
	CorrtexShader *LODshader = new CorrtexShader("DiffuseVertexShader.vertexshader", "DiffuseLODFragmentShader.fragmentshader");
	LODshader->AddAttributes(VERTEX, UV, NORMAL);
	LODshader->AddUniforms(Matrix4x4, "MVP", Matrix4x4, "modelMatrix", Texture, "tex");
	LODshader->AddUniformsArray(Float4, "allLights", "pos", Float3, "allLights", "color", Float1, "allLights", "attenuation");
	LODshader->AddUniformsArray(Float1, "allLights", "coneAngle", Float3, "allLights", "coneDirection");
	LODshader->AddUniforms(Float2, "texRatio", Float1, "ambientIntensity", Float1, "numLights");
	LODshader->AddUniforms(Float3, "cameraPosition", Float4, "clippingPlane");

	//phong shader
	CorrtexShader *phongShader = new CorrtexShader("PhongVertexShader.vertexshader", "PhongFragmentShader.fragmentshader");
	phongShader->AddAttributes(VERTEX, UV, NORMAL);
	phongShader->AddUniforms(Matrix4x4, "MVP", Matrix4x4, "modelMatrix", Texture, "tex");
	phongShader->AddUniformsArray(Float4, "allLights", "pos", Float3, "allLights", "color", Float1, "allLights", "attenuation");
	phongShader->AddUniformsArray(Float1, "allLights", "coneAngle", Float3, "allLights", "coneDirection");
	phongShader->AddUniforms(Float3, "cameraPosition", Float3, "specularColor", Float1, "shininess");
	phongShader->AddUniforms(Float1, "ambientIntensity", Float2, "texRatio", Float1, "numLights");
	phongShader->AddUniform(Float4, "clippingPlane");

	//diffuse shader
	CorrtexShader *diffuseShader = new CorrtexShader("DiffuseVertexShader.vertexshader", "DiffuseFragmentShader.fragmentshader");
	diffuseShader->AddAttributes(VERTEX, UV, NORMAL);
	diffuseShader->AddUniforms(Matrix4x4, "MVP", Matrix4x4, "modelMatrix", Texture, "tex");
	diffuseShader->AddUniformsArray(Float4, "allLights", "pos", Float3, "allLights", "color", Float1, "allLights", "attenuation");
	diffuseShader->AddUniformsArray(Float1, "allLights", "coneAngle", Float3, "allLights", "coneDirection");
	diffuseShader->AddUniforms(Float2, "texRatio", Float1, "ambientIntensity", Float1, "numLights");
	diffuseShader->AddUniform(Float4, "clippingPlane");

	//texture shader
	CorrtexShader *textureShader = new CorrtexShader("TexturedVertexShader.vertexshader", "TexturedFragmentShader.fragmentshader");
	textureShader->AddAttributes(VERTEX, UV);
	textureShader->AddUniforms(Matrix4x4, "MVP", Texture, "tex", Float2, "texRatio");

	//red shader
	CorrtexShader *redShader = new CorrtexShader("AllRed.vertexshader", "AllRed.fragmentshader");
	redShader->AddUniform(Matrix4x4, "MVP");
	redShader->AddAttribute(VERTEX);

	//////////////////////////////////////////////////////////////////////////////////////////////
	//LOAD TEXTURES HERE
	//////////////////////////////////////////////////////////////////////////////////////////////

	//blue texture
	GLuint blueTexture = GameEngine::imageLoader->LoadBMP("Assets/cubeTex1.bmp");
	//terrain textures
	GLuint grassTexture = GameEngine::imageLoader->LoadBMP("Assets/grass.bmp");
	GLuint rockTexture = GameEngine::imageLoader->LoadBMP("Assets/rock.bmp");
	GLuint waterTexture = GameEngine::imageLoader->LoadBMP("Assets/water.bmp");
	GLuint snowTexture = GameEngine::imageLoader->LoadBMP("Assets/snow.bmp");
	//terrain normals
	GLuint grassTexture_normal = GameEngine::imageLoader->LoadBMP("Assets/grass_normal.bmp");
	GLuint rockTexture_normal = GameEngine::imageLoader->LoadBMP("Assets/rock_normal.bmp");
	GLuint waterTexture_normal = GameEngine::imageLoader->LoadBMP("Assets/water_normal.bmp");
	GLuint snowTexture_normal = GameEngine::imageLoader->LoadBMP("Assets/snow_normal.bmp");
	//skysphere texture
	GLuint skysphereTex = GameEngine::imageLoader->LoadBMP("Assets/skysphere.bmp");
	//dudv water texture
	GLuint dudvTexture = GameEngine::imageLoader->LoadBMP("Assets/dudv.bmp");

	//////////////////////////////////////////////////////////////////////////////////////////////
	//CREATE MATERIALS HERE
	//////////////////////////////////////////////////////////////////////////////////////////////

	CorrtexMaterial *terrainGrassMaterial = new CorrtexMaterial(0.011f, 0.82f, vec3(100.0f / 255.0f, 100.0f / 255.0f, 100.0f / 255.0f));
	terrainGrassMaterial->uvScale = vec2(10);
	terrainGrassMaterial->AddTexture("tex", grassTexture, 1);
	terrainGrassMaterial->AddTexture("tex2", grassTexture, 2);
	terrainGrassMaterial->AddTexture("tex3", rockTexture, 3);
	terrainGrassMaterial->AddTexture("tex4", snowTexture, 4);
	terrainGrassMaterial->AddTexture("tex_normal", grassTexture_normal, 5);
	terrainGrassMaterial->AddTexture("tex_normal2", grassTexture_normal, 6);
	terrainGrassMaterial->AddTexture("tex_normal3", rockTexture_normal, 7);
	terrainGrassMaterial->AddTexture("tex_normal4", snowTexture_normal, 8);

	CorrtexMaterial *skysphereMat = new CorrtexMaterial(0.075f, 0.2f, vec3(0.9f, 0.11f, 0.33f));
	skysphereMat->AddTexture("tex", skysphereTex, 1);

	CorrtexMaterial *waterMat = new CorrtexMaterial(0.1f, 0.2f, vec3(0.1f, 0.66f, 0.82f));
	waterMat->AddTexture("tex", 0, 1);//doesnt matter what you put here because texture must be constantly updated - see GameEngine draw method
	waterMat->AddTexture("tex2", 0, 2);//doesnt matter what you put here because texture must be constantly updated - see GameEngine draw method
	waterMat->AddTexture("dudv", dudvTexture, 3);
	waterMat->AddTexture("normal", waterTexture_normal, 4);
	waterMat->AddTexture("depth", 0, 5);//doesnt matter what you put here because texture must be constantly updated - see GameEngine draw method
	waterMat->uvScale = vec2(6, 6);
	waterMat->useAlphaBlending = true;

	CorrtexMaterial *playerMaterial = new CorrtexMaterial(0.075f, 0.2f, vec3(0.9f, 0.11f, 0.33f));
	playerMaterial->AddTexture("tex", blueTexture, 1);

	//////////////////////////////////////////////////////////////////////////////////////////////
	//CREATE OBJECTS HERE
	//////////////////////////////////////////////////////////////////////////////////////////////

	//create water object
	CorrtexWater *cw = new CorrtexWater(vec3(0, 5, 0));

	skysphere = new CorrtexMesh(vec3(0, 0, 0), "Assets/skysphere.obj");
	skysphere->SetScale(25);
	skysphere->SetShader(diffuseShader);
	skysphere->SetMaterial(skysphereMat);
	skysphere->useIndexing = false;
	skysphere->name = "Skysphere";

	terrain = new CorrtexMesh(vec3(0, -50, 0), "Assets/terrain2.obj");
	terrain->SetShader(multitexturedTerrainShader);
	terrain->SetMaterial(terrainGrassMaterial);
	terrain->scale = vec3(2, 2, 2);
	terrain->useIndexing = false;
	terrain->name = "Terrain";

	water = new CorrtexMesh(vec3(0, -35, 0), "Assets/water_plane.obj");
	water->SetShader(waterShader);
	water->SetMaterial(waterMat);
	water->scale = vec3(3, 1, 3);
	water->useIndexing = false;
	//we dont want the water to be rendered to other frame buffers since it is using a render texture 
	water->renderOtherBuffers = false;
	water->name = "WaterPlane";

	character = new AnimatedModel(vec3(0, 10, 0), "Assets\\deer.dae");
	//character->SetScale(10);
	character->SetShader(animatedShader);
	character->SetMaterial(playerMaterial);
	character->useIndexing = false;
	character->name = "Player";
}
float v = 0.0005f;
float lightX = 0.0f;
int day = 1;
void Game::Update(float time, int frame)
{
	if (GameEngine::input->GetKey("Up", Down))
	{
		GameEngine::waterObject->waveSpeed += v;
	}
	if (GameEngine::input->GetKey("Right", Down))
	{
		GameEngine::waterObject->waveStrength += v;
	}
	if (GameEngine::input->GetKey("Down", Down))
	{
		GameEngine::waterObject->waveSpeed -= v;
	}
	if (GameEngine::input->GetKey("Left", Down))
	{
		GameEngine::waterObject->waveStrength -= v;
	}
	if (GameEngine::input->GetKey("Q", Down))
	{
		water->material->uvScale -= v * 10;
	}
	if (GameEngine::input->GetKey("E", Down))
	{
		water->material->uvScale += v * 10;
	}

	//day night cycle
	skysphere->yaw = 0.00025;
	GameEngine::light1->lightPosition.x = sinf(time / 100.0f) * 10;
	GameEngine::light1->lightPosition.y = cosf(time / 100.0f) * 10;

	if (GameEngine::light1->lightPosition.x >= 0.0f && lightX < 0.0f)
	{
		day++;
	}

	lightX = GameEngine::light1->lightPosition.x;

	if (GameEngine::input->GetKey("1", Trigger))
		GameEngine::wireframeOn = !GameEngine::wireframeOn;

	if (GameEngine::input->GetKey("2", Trigger)) {
	}

	if (GameEngine::input->GetKey("3", Trigger)) {
	}

	if (GameEngine::input->GetKey("4", Trigger))
		printf("strength: %f, speed: %f, uv:(%f, %f)\n", GameEngine::waterObject->waveStrength, GameEngine::waterObject->waveSpeed,
			water->material->uvScale.x, water->material->uvScale.y);
}