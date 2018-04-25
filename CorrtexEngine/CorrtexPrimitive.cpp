#include "stdafx.h"
#include "CorrtexPrimitive.h"
#include "GameEngine.h"

//base primitive class. see header file for more details.
CorrtexPrimitive::CorrtexPrimitive() : 
	CorrtexPrimitive(vec3(0), 3)
{
	
}

CorrtexPrimitive::CorrtexPrimitive(vec3 pos, int vCount)
{
	this->name = "CorrtexPrimitive Instance";
	this->position = pos;
	this->startingPosition = pos;
	this->vertexCount = vCount;
}

CorrtexPrimitive::~CorrtexPrimitive()
{
	delete this->vertexBufferData;
	delete this->colorBufferData;
}

void CorrtexPrimitive::SetBufferData()
{
	SetBufferData(this->vertexBufferData, this->colorBufferData);
}

void CorrtexPrimitive::SetBufferData(GLfloat *vertData, GLfloat *colorData)
{
	this->vertexBufferData = vertData;
	this->colorBufferData = colorData;

	//int i = 0;
	//int c = this->vertexCount * 3;

	//while (i < c)
	//{
	//	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	//	this->colorBufferData[i] = 0.6f;
	//	++i;
	//}
}

void CorrtexPrimitive::CreateBuffers()
{
	//generate vertex buffer first
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertexCount * sizeof(GLfloat) * 3, this->vertexBufferData, GL_STATIC_DRAW);

	//now color buffer
	glGenBuffers(1, &this->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertexCount * sizeof(GLfloat) * 3, this->colorBufferData, GL_STATIC_DRAW);

	//lets change it up with a UV buffer!
	glGenBuffers(1, &this->UVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->UVBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->UVCoordCount * 2 * sizeof(GLfloat), this->UVBufferData, GL_STATIC_DRAW);
}

void CorrtexPrimitive::Debug()
{
	printf("Name: %s, Pos: (%f, %f, %f) CB[0]: %f\n",
		name, position.x, position.y, position.z, this->colorBufferData[3]);
}

void CorrtexPrimitive::Initialize()
{
	this->SetBufferData();
	this->CreateBuffers();
}

void CorrtexPrimitive::Initialize(GLfloat *vertData, GLfloat *colorData)
{
	this->SetBufferData(vertData, colorData);
	this->CreateBuffers();
}

void CorrtexPrimitive::AddTexture(char *filePath)
{
	this->texture = GameEngine::imageLoader->LoadBMP(filePath);
	this->useTexture = true;
}

void CorrtexPrimitive::AddTexture(GLuint tex)
{
	this->texture = tex;
	this->useTexture = true;
}

void CorrtexPrimitive::Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform)
{
	//calculate model matrix
	this->CalculateModelMatrix();

	//calculate model view proj matrix
	mat4 mvp = proj * view * model;

	if (this->shader == NULL)//do what we normally do - simple, non-textured stuff
	{
		//apply shader uniforms
		mvpUniform.SetValue(mvp);

		//vertex positions
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//color positions
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 0; 3 vertices / triangle, 12 triangles total -> 12 * 3 vertices
											   //disable attributes after drawing
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

	else//how does this shader want us to draw?
	{
		this->shader->UseShader();
		//somehow deal with shader uniform 
		LinkedList<ShaderUniform*> tempList = this->shader->GetUniforms();
		int tlc = tempList.Count();

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
				su->SetValue(0.01f);
				break;
			case Texture:
				if (attribName == "texture")
				{
					su->SetValue(this->texture);
				}
				break;
			case Float3:
				if (attribName == "light.pos")
				{
					su->SetValue(GameEngine::light1->lightPosition);
				}
				if (attribName == "light.color")
				{
					su->SetValue(GameEngine::light1->lightColor);
				}
				break;
			}
		}

		if (this->shader->HasAttribute(VERTEX))
		{
			//vertex positions
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}

		if (this->shader->HasAttribute(COLOR))
		{
			//color positions
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}

		if (this->shader->HasAttribute(UV))
		{
			glEnable(GL_TEXTURE_2D);
			//UV coords
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, this->UVBuffer);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);		

			//if different texture
			if (this->useTexture)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, this->texture);
			}
		}

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 0; 3 vertices / triangle, 12 triangles total -> 12 * 3 vertices
		this->GetErrorIfExists();		   //disable attributes after drawing
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
}