#include "stdafx.h"
#include "CorrtexMesh.h"
#include "GameEngine.h"

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

	if (this->shader == NULL)//no shader? just vertex buffer then.
	{
		//vertex buffer
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	}
	else
	{
		//deal with indexing
		std::vector<vec3> vert_list;
		std::vector<vec2> uv_list;
		std::vector<vec3> norm_list;
		std::vector<vec3> tan_list;
		std::vector<vec3> bitan_list;

		//ARE WE USING INDEXING??
		if (this->useIndexing)
		{
			int countBeforeIndex = vertices.size();

			if (this->shader->HasAttribute(TANGENT) &&
				this->shader->HasAttribute(BITANGENT))
			{
				GameEngine::vboIndexer->IndexVBO_TBN(vertices, uvs, normals, tangents, bitangents,
					indicies, vert_list, uv_list, norm_list, tan_list, bitan_list);
			}
			else
			{
				GameEngine::vboIndexer->IndexVBO(vertices, uvs, normals,
					indicies, vert_list, uv_list, norm_list);
			}

			int countAfterIndex = vert_list.size();

			printf("Before index: %d verts....After index: %d verts.\n", countBeforeIndex, countAfterIndex);

			//index buffer
			glGenBuffers(1, &indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned short), &indicies[0], GL_STATIC_DRAW);
		}
		else
		{
			//set the indexed_verts and all other vectors to the original vertices lists
			vert_list = vertices;
			uv_list = uvs;
			norm_list = normals;
			tan_list = tangents;
			bitan_list = bitangents;
		}

		if (this->shader->HasAttribute(VERTEX))
		{
			//vertex buffer
			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, vert_list.size() * sizeof(glm::vec3), &vert_list[0], GL_STATIC_DRAW);
		}
		if (this->shader->HasAttribute(UV))
		{
			//uv buffer
			glGenBuffers(1, &uvBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
			glBufferData(GL_ARRAY_BUFFER, uv_list.size() * sizeof(glm::vec2), &uv_list[0], GL_STATIC_DRAW);
		}
		if (this->shader->HasAttribute(NORMAL))
		{
			//normal buffer
			glGenBuffers(1, &normalBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
			glBufferData(GL_ARRAY_BUFFER, norm_list.size() * sizeof(glm::vec3), &norm_list[0], GL_STATIC_DRAW);
		}
		if (this->shader->HasAttribute(TANGENT))
		{
			glGenBuffers(1, &tangentBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
			glBufferData(GL_ARRAY_BUFFER, tan_list.size() * sizeof(glm::vec3), &tan_list[0], GL_STATIC_DRAW);
		}
		if (this->shader->HasAttribute(BITANGENT))
		{
			glGenBuffers(1, &bitangentBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
			glBufferData(GL_ARRAY_BUFFER, bitan_list.size() * sizeof(glm::vec3), &bitan_list[0], GL_STATIC_DRAW);
		}
	}

	GenSpecialBuffers();
}

void CorrtexMesh::GenSpecialBuffers()
{

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

void CorrtexMesh::ShaderInit()
{
	//compute bitangents and tangents if needed
	if (this->shader->HasAttribute(TANGENT) && this->shader->HasAttribute(BITANGENT))
	{
		GameEngine::ComputeTangents(this->vertices, this->uvs, this->normals, this->tangents, this->bitangents);
	}
}

void CorrtexMesh::SetShaderValues(mat4 mvp, mat4 view)
{
	//somehow deal with shader uniform 
	LinkedList<ShaderUniform*> tempList = this->shader->GetUniforms();
	int tlc = tempList.Count();
	const char* MATERIAL_ERROR_STRING = "CORRTEX ERROR: This object (%s) must have a material attached to it because the shader requires it.\n";

	for (int i = 0; i < tlc; ++i)
	{
		ShaderUniform* su = tempList.Get(i);
		char* attribName = su->glslName;

		if (su->valueInArray)//is this an array param?
		{
			if (su->arrayStructName == "allLights")//for lights
			{
				su->SetArrayValues();
			}
		}
		else//its just a singular one time deal.
		{
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
				else if (attribName == "viewMatrix")
				{
					su->SetValue(view);
				}
				break;
			case Matrix3x3: 
				if (attribName == "MV3x3")
				{
					su->SetValue(mat3(view * model));
				}
				break;
			case Float1:
				if (attribName == "time")
				{
					su->SetValue(GameEngine::time);
				}
				else if (attribName == "waveStrength")
				{
					su->SetValue(GameEngine::waterObject->waveStrength);
				}
				else if (attribName == "waveTime")
				{
					su->SetValue(GameEngine::waterObject->waveTime);
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
				else if (attribName == "numLights")
				{
					su->SetValuei(GameEngine::lightCount);
				}
				else if (attribName == "light.attenuation")
				{
					if (GameEngine::lightCount > 1)
					{

					}
					else
					{
						su->SetValue(GameEngine::light1->attenuation);
					}
				}
				break;
			case Texture:
				if (attribName == "texture")
				{
					su->SetValue(this->texture);
				}
				if (this->material != NULL)
				{
					GLuint texExists = material->GetTexture(attribName);
					int texNum = material->GetTextureNumber(attribName) - 1;

					if (texExists != false)
					{
						su->SetValue(texExists, texNum);
					}
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
				if (attribName == "modelPosition")
				{
					su->SetValue(this->position);
				}
				if (attribName == "lightPosition")
				{
					su->SetValue(GameEngine::light1->lightPosition);
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
				else if (attribName == "clippingPlane")
				{
					su->SetValue(GameEngine::clippingPlane);
				}
				break;
			}
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
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		if (this->material != NULL)
		{
			for (const auto &myPair : this->material->textures)
			{
				const char *name = this->name;
				const char *key = myPair.first;
				int textureNumber = this->material->GetTextureNumber(key);
				GLuint matTexture = this->material->GetTexture(key);

				//are these valid?
				if (textureNumber != -1)
				{
					switch (textureNumber)
					{
					case 1://tex
						glActiveTexture(GL_TEXTURE0);
						break;
					case 2://tex
						glActiveTexture(GL_TEXTURE1);
						break;
					case 3://tex
						glActiveTexture(GL_TEXTURE2);
						break;
					case 4://tex
						glActiveTexture(GL_TEXTURE3);
						break;
					case 5://tex
						glActiveTexture(GL_TEXTURE4);
						break;
					case 6://tex
						glActiveTexture(GL_TEXTURE5);
						break;
					case 7://tex
						glActiveTexture(GL_TEXTURE6);
						break;
					case 8://tex
						glActiveTexture(GL_TEXTURE7);
						break;
					case 9://tex
						glActiveTexture(GL_TEXTURE8);
						break;
					case 10://tex
						glActiveTexture(GL_TEXTURE9);
						break;
					case 11://tex
						glActiveTexture(GL_TEXTURE10);
						break;
					case 12://tex
						glActiveTexture(GL_TEXTURE11);
						break;
					case 13://tex
						glActiveTexture(GL_TEXTURE12);
						break;
					}

					//bind the texture
					glBindTexture(GL_TEXTURE_2D, matTexture);
				}
			}
		}
		else if (this->useTextures)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, this->texture);
		}
	}

	if (shader->HasAttribute(NORMAL))
	{
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	if (shader->HasAttribute(TANGENT))
	{
		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, this->tangentBuffer);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	if (shader->HasAttribute(BITANGENT))
	{
		glEnableVertexAttribArray(5);
		glBindBuffer(GL_ARRAY_BUFFER, this->bitangentBuffer);
		glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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
		this->SetShaderValues(mvp, view);
		this->SetShaderAttributes();

		//if we are using indexing, we will draw differently
		if (this->useIndexing)
		{
			// Index buffer drawing
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);

			// Draw the triangles !
			glDrawElements(
				GL_TRIANGLES,      // mode
				indicies.size(),    // count
				GL_UNSIGNED_SHORT,   // type
				(void*)0           // element array buffer offset
			);
		}
		else//draw regular triangle arrays
		{
			glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
		}

		//this->GetErrorIfExists();
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
		glDisableVertexAttribArray(5);
		//glDisable(GL_TEXTURE_2D);
	}
}
