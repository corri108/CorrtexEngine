#include "stdafx.h"
#include "ModelLoader.h"

using namespace glm;

ModelLoader::ModelLoader()
{

}


ModelLoader::~ModelLoader()
{

}


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


//else if (strcmp(lineHeader, "f") == 0) {
//	std::string vertex1, vertex2, vertex3;
//	unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
//	int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
//	if (matches != 9) {
//		printf("File can't be read by our simple parser : ( Try exporting with other options\n");
//		return false;
//	}
//	vertexIndices.push_back(vertexIndex[0]);
//	vertexIndices.push_back(vertexIndex[1]);
//	vertexIndices.push_back(vertexIndex[2]);
//	uvIndices.push_back(uvIndex[0]);
//	uvIndices.push_back(uvIndex[1]);
//	uvIndices.push_back(uvIndex[2]);
//	normalIndices.push_back(normalIndex[0]);
//	normalIndices.push_back(normalIndex[1]);
//	normalIndices.push_back(normalIndex[2]);