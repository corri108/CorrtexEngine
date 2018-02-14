#pragma once
#include "glew.h"
#include "glm\ext.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <assimp\cimport.h>
#include "assimp\postprocess.h"
#include "assimp\scene.h"

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
	bool LoadSkinned(const char *filePath,
		vector<vec3> &out_vertices,
		vector<vec2> &out_uvs,
		vector<vec3> &out_normals,
		vector<ivec3> &jointIDs,
		vector<vec3> &weights,
		int *boneCount, int *rootBoneIndex, char **rootBoneName, mat4 *rootBoneBind);
};

