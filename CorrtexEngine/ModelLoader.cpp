#include "stdafx.h"
#include "ModelLoader.h"

using namespace glm;

//helper class to load model files

//ctor/dtor
ModelLoader::ModelLoader()
{

}
ModelLoader::~ModelLoader()
{

}

//conversion methods from assimp (animation + math library) to glm
vec2 toGLM(aiVector2D v)
{
	return vec2(v.x, v.y);
}
vec2 toGLM_tex(aiVector3D v)
{
	return vec2(v.x, v.y);
}
vec3 toGLM(aiVector3D v)
{
	return vec3(v.x, v.y, v.z);
}
mat4 toGLM(aiMatrix4x4 m)
{
	mat4 ret = mat4(1.0f);
	ret[0][0] = m.a1;
	ret[0][1] = m.a2;
	ret[0][2] = m.a3;
	ret[0][3] = m.a4;

	ret[1][0] = m.b1;
	ret[1][1] = m.b2;
	ret[1][2] = m.b3;
	ret[1][3] = m.b4;

	ret[2][0] = m.c1;
	ret[2][1] = m.c2;
	ret[2][2] = m.c3;
	ret[2][3] = m.c4;

	ret[3][0] = m.d1;
	ret[3][1] = m.d2;
	ret[3][2] = m.d3;
	ret[3][3] = m.d4;

	return ret;
}

//loads a .obj file
bool ModelLoader::LoadOBJ(const char *filePath,
	vector<vec3> &out_vertices,
	vector<vec2> &out_uvs,
	vector<vec3> &out_normals)
{
	//declare data
	unsigned int headerSize = 54;
	unsigned char header[54];
	unsigned int dataSection;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char* pixelData;

	GLuint modelID = 0;

	//open file
	FILE* file = fopen(filePath, "rb");
	if (!file)
	{
		printf("Error opening file with filepath: %s\n", filePath);
		return false;
	}

	vector<unsigned int> vertexIndices;
	vector<unsigned int> uvIndices;
	vector<unsigned int> normalIndices;

	vector<vec3> temp_vertices;
	vector<vec2> temp_uvs;
	vector<vec3> temp_normals;

	while (true)
	{
		char line[128];
		int res = fscanf(file, "%s", line);

		//end of file
		if (res == EOF)
			break;
		else//do our thang
		{
			if (strcmp(line, "v") == 0)//vertex
			{
				vec3 vertex = vec3(0);
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(line, "vt") == 0)//tex coords
			{
				vec2 uv = vec2(0);
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if (strcmp(line, "vn") == 0)//normals
			{
				vec3 normal = vec3(0);
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(line, "f") == 0)//face
			{
				unsigned int vIndex[3], uvIndex[3], nIndex[3];
				int matches = fscanf(file, "%d/%d/%d ", &vIndex[0], &uvIndex[0], &nIndex[0]);
				matches += fscanf(file, "%d/%d/%d ", &vIndex[1], &uvIndex[1], &nIndex[1]);
				matches += fscanf(file, "%d/%d/%d\n", &vIndex[2], &uvIndex[2], &nIndex[2]);

				if (matches != 9)
				{
					//we cant read this file
					printf("This .obj file cannot be read. Try exporting the model with different parameters / options.\n");
					return false;
				}

				vertexIndices.push_back(vIndex[0]);
				vertexIndices.push_back(vIndex[1]);
				vertexIndices.push_back(vIndex[2]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);

				normalIndices.push_back(nIndex[0]);
				normalIndices.push_back(nIndex[1]);
				normalIndices.push_back(nIndex[2]);
			}
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		if (i == 12)
		{
			int j = 0;
		}
		unsigned int vIndex = vertexIndices[i];
		vec3 vert = temp_vertices[vIndex - 1];
		out_vertices.push_back(vert);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		vec2 uv = temp_uvs[uvIndex - 1];
		out_uvs.push_back(uv);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int nIndex = normalIndices[i];
		vec3 normal = temp_normals[nIndex - 1];
		out_normals.push_back(normal);
	}

	return true;
}
//loads a skinned model (doesn't work yet :( )
bool ModelLoader::LoadSkinned(const char *filePath,
	vector<vec3> &out_vertices,
	vector<vec2> &out_uvs,
	vector<vec3> &out_normals,
	vector<ivec3> &jointIDs,
	vector<vec3> &weights,
	int *boneCount, int *rootBoneIndex, char **rootBoneName, mat4 *rootBoneBind,
	std::vector<Animation *> &animations)
{
	const aiScene * animatedModel = aiImportFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality);
	const char *error = aiGetErrorString();

	if (*error != '\0')
	{
		printf("error importing: %s", aiGetErrorString());
		return false;
	}

	vector<aiVertexWeight*> vertWeights;
	vector<aiBone*> bones;
	vector<int> bonesPerMesh;

	for (int i = 0; i < animatedModel->mNumMeshes; ++i)
	{
		int vertexCount = animatedModel->mMeshes[i]->mNumVertices;

		for (int v = 0; v < vertexCount; ++v)
		{
			aiVector3D vert = animatedModel->mMeshes[i]->mVertices[v];
			out_vertices.push_back(toGLM(vert));

			aiVector3D tex = animatedModel->mMeshes[i]->mTextureCoords[0][v];
			out_uvs.push_back(toGLM_tex(tex));

			aiVector3D norm = animatedModel->mMeshes[i]->mNormals[v];
			out_normals.push_back(toGLM(norm));

			//set jointIDs and weights for this index to 0
			jointIDs.push_back(ivec3(-1, -1, -1));
			weights.push_back(vec3(0, 0, 0));
		}

		int bonesThisMesh = animatedModel->mMeshes[i]->mNumBones;
		bonesPerMesh.push_back(bonesThisMesh);
		for (int b = 0; b < bonesThisMesh; ++b)
		{
			bones.push_back(animatedModel->mMeshes[i]->mBones[b]);
		}
	}

	vector<mat4> bindTransforms;

	//now for bones
	for (int b = 0; b < bones.size(); ++b)
	{
		const char* boneName = bones[b]->mName.C_Str();
		bindTransforms.push_back(toGLM(bones[b]->mOffsetMatrix));
		unsigned int numWeights = bones[b]->mNumWeights;

		for (int w = 0; w < numWeights; ++w)
		{
			unsigned int vid = bones[b]->mWeights[w].mVertexId;
			float weight = bones[b]->mWeights[w].mWeight;
			ivec3 joint = jointIDs[vid];
			
			if (joint.x == -1)//first spot open?
			{
				jointIDs[vid].x = b;
				weights[vid].x = weight;
			}
			else if (joint.y == -1)//second spot open?
			{
				jointIDs[vid].y = b;
				weights[vid].y = weight;
			}
			else if (joint.z == -1)//last chance
			{
				jointIDs[vid].z = b;
				weights[vid].z = weight;
			}
		}

		bool k = false;
	}

	*boneCount = bones.size();
	*rootBoneIndex = 0;
	*rootBoneName = (char *)bones[0]->mName.C_Str();
	*rootBoneBind = bindTransforms[0];

	int animCount = animatedModel->mNumAnimations;

	for (int i = 0; i < animCount; ++i)
	{
		float duration = (float)(animatedModel->mAnimations[i]->mDuration);
		const char * aniName = animatedModel->mAnimations[i]->mName.C_Str();
		int numChannels = animatedModel->mAnimations[i]->mNumChannels;

		for (int c = 0; c < numChannels; ++c)
		{
			//animatedModel->mAnimations[i]->mChannels[c]->
		}
	}

	printf("animation count: %d", animCount);
	return true;
}