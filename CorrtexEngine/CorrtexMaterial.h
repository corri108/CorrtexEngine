#pragma once
#include "glew.h"
#include "glm\ext.hpp"
#include <map>
using namespace glm;

//simple struct to correlate between texture number and texture location
struct TextureHolder
{
	GLuint texture;
	int textureNum = 1;
};

//material class. this makes it easy to talk between a Mesh and its Shader. it basically 
//communicates between the two of them.
class CorrtexMaterial
{
public:
	CorrtexMaterial();
	CorrtexMaterial(float ambient, float shininess, vec3 spec);
	~CorrtexMaterial();
	void AddTexture(const char * texName, GLuint texValue);
	void AddTexture(const char *texName, GLuint texValue, int texNum);
	void UpdateTexture(const char *texName, GLuint texValue);
	GLuint GetTexture(const char * texName);
	int GetTextureNumber(const char * texName);

	//default material values
	float ambientIntensity = 0.075f;
	float shininess = 0.1f;
	vec3 specularColor = vec3(0.22f, 0.12f, 0.35f);
	vec2 uvScale = vec2(1.0f, 1.0f);
	std::map<const char *, TextureHolder> textures;
	bool useAlphaBlending = false;

private:
	int totalTexNum = 0;
};

