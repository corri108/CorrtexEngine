#pragma once
#include "glew.h"
#include "glm\ext.hpp"
#include <vector>

using namespace std;
using namespace glm;

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();
	bool LoadOBJ(const char *filePath,
		vector<vec3> &out_vertices,
		vector<vec2> &out_uvs,
		vector<vec3> &out_normals);
};

