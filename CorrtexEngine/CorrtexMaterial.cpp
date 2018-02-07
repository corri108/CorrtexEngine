#include "stdafx.h"
#include "CorrtexMaterial.h"


CorrtexMaterial::CorrtexMaterial()
{
}

CorrtexMaterial::CorrtexMaterial(float ambient, float shininess, vec3 spec)
{
	this->ambientIntensity = ambient;
	this->shininess = shininess;
	this->specularColor = spec;
	this->textures = std::map<const char *, TextureHolder>();
}

CorrtexMaterial::~CorrtexMaterial()
{
}

void CorrtexMaterial::AddTexture(const char *texName, GLuint texValue)
{
	if (this->textures.find(texName) == this->textures.end())
	{
		//good it doesnt exist yet, lets add the texture
		totalTexNum++;

		TextureHolder th = TextureHolder();
		th.texture = texValue;
		th.textureNum = totalTexNum;
		this->textures[texName] = th;
	}
	else
	{
		printf("Error! Texture with this value has already been added to the map.\n");
	}
}

void CorrtexMaterial::AddTexture(const char *texName, GLuint texValue, int texNum)
{
	if (this->textures.find(texName) == this->textures.end())
	{
		//good it doesnt exist yet, lets add the texture
		TextureHolder th = TextureHolder();
		th.texture = texValue;
		th.textureNum = texNum;
		this->textures[texName] = th;
	}
	else
	{
		printf("Error! Texture with this value has already been added to the map.\n");
	}
}

GLuint CorrtexMaterial::GetTexture(const char * texName)
{
	//only return texture if it exists in the map
	if (textures.find(texName) != textures.end())
	{
		return textures[texName].texture;
	}

	return false;
}

int CorrtexMaterial::GetTextureNumber(const char * texName)
{
	//only return texture if it exists in the map
	if (textures.find(texName) != textures.end())
	{
		return textures[texName].textureNum;
	}

	return -1;
}