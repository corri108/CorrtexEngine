#include "stdafx.h"
#include "CorrtexMesh.h"


CorrtexMesh::CorrtexMesh()
{
}

CorrtexMesh::CorrtexMesh(vec3 position, char *fileLoc)
{
	this->position = position;
	GameEngine::LoadModel(fileLoc, this->vertices, this->uvs, this->normals);
}

CorrtexMesh::~CorrtexMesh()
{
}

void CorrtexMesh::Initialize()
{
	printf("Vertex size: %d, UV size: %d, Normal size: %d\n", vertices.size(), uvs.size(), normals.size());
	//vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	//uv buffer
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	//normal buffer
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}

void CorrtexMesh::AddTexture(char * textureLocation)
{
	this->texture = GameEngine::imageLoader->LoadBMP(textureLocation);
	this->useTextures = true;
}

void CorrtexMesh::AddTexture(GLuint textureLoc)
{
	this->texture = textureLoc;
	this->useTextures = true;
}

void CorrtexMesh::SetShaderValues(mat4 mvp)
{
	//somehow deal with shader uniform 
	LinkedList<ShaderUniform*> tempList = this->shader->GetUniforms();
	int tlc = tempList.Count();
	const char* MATERIAL_ERROR_STRING = "CORRTEX ERROR: This object (%s) must have a material attached to it because the shader requires it.\n";

	for (int i = 0; i < tlc; ++i)
	{
		ShaderUniform* su = tempList.Get(i);
		char* attribName = su->glslName;

		switch (su->uniformType)
		{
		case Matrix4x4:
			if (attribName == "MVP")
			{
				su->SetValue(mvp);
			}
			else if (attribName == "modelMatrix")
			{
				su->SetValue(model);
			}
			break;
		case Float1:
			if (attribName == "time")
			{
				//su->SetValue(GameEngine::time);
			}
			else if (attribName == "shininess")
			{
				if (material == NULL)
				{
					printf(MATERIAL_ERROR_STRING, this->name);
					break;
				}
				su->SetValue(material->shininess);
			}
			else if (attribName == "ambientIntensity")
			{
				if (material == NULL)
				{
					printf(MATERIAL_ERROR_STRING, this->name);
					break;
				}
				su->SetValue(material->ambientIntensity);
			}
			else if (attribName == "light.attenuation")
			{
				su->SetValue(GameEngine::light1->attenuation);
			}
			break;
		case Texture:
			if (attribName == "texture")
			{
				su->SetValue(this->texture);
			}
			break;
		case Float2:
			if (attribName == "texRatio")
			{
				if (material == NULL)
				{
					printf(MATERIAL_ERROR_STRING, this->name);
					break;
				}
				su->SetValue(material->uvScale);
			}
			break;
		case Float3:
			if (attribName == "light.color")
			{
				su->SetValue(GameEngine::light1->lightColor);
			}
			if (attribName == "cameraPosition")
			{
				su->SetValue(GameEngine::camera->cameraPosition);
			}

			//mat stuff
			if (attribName == "specularColor")
			{
				if (material == NULL)
				{
					printf(MATERIAL_ERROR_STRING, this->name);
					break;
				}
				su->SetValue(material->specularColor);
			}
			break;

		case Float4:
			if (attribName == "light.pos")
			{
				su->SetValue(GameEngine::light1->lightPosition);
			}
			break;
		}
	}
}

void CorrtexMesh::SetShaderAttributes()
{

	if (shader->HasAttribute(VERTEX))
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	//if (shader->HasAttribute(COLOR))
	//{
	//	glEnableVertexAttribArray(1);
	//	glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
	//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//}

	if (shader->HasAttribute(UV))
	{
		glEnable(GL_TEXTURE_2D);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//if different texture
		if (this->useTextures)
		{
			//glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, this->texture);
		}
	}

	if (shader->HasAttribute(NORMAL))
	{
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
}

void CorrtexMesh::Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform)
{
	//calc model matrix and pass MVP to shader
	this->CalculateModelMatrix();
	mat4 mvp = proj * view * this->model;

	if (this->shader == NULL)
	{
		mvpUniform.SetValue(mvp);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//glEnableVertexAttribArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
		glDisableVertexAttribArray(0);
	}

	else
	{
		this->shader->UseShader();
		this->SetShaderValues(mvp);
		this->SetShaderAttributes();

		glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
		this->GetErrorIfExists();
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
	}
}
