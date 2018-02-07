#pragma once
#include "glew.h"
#include "glm\ext.hpp"
#include <map>
using namespace glm;

struct TextureHolder
{
	GLuint texture;
	int textureNum = 1;
};

class CorrtexMaterial
{
public:
	CorrtexMaterial();
	CorrtexMaterial(float ambient, float shininess, vec3 spec);
	~CorrtexMaterial();
	void AddTexture(const char * texName, GLuint texValue);
	void AddTexture(const char *texName, GLuint texValue, int texNum);
	GLuint GetTexture(const char * texName);
	int GetTextureNumber(const char * texName);
	float ambientIntensity = 0.075f;
	float shininess = 0.1f;
	vec3 specularColor = vec3(0.22f, 0.12f, 0.35f);
	vec2 uvScale = vec2(1.0f, 1.0f);
	std::map<const char *, TextureHolder> textures;

private:
	int totalTexNum = 0;
};

