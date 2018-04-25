#pragma once
#include "glew.h"
#include "glm\ext.hpp"
#include "Animation.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <assimp\cimport.h>
#include "assimp\postprocess.h"
#include "assimp\scene.h"

using namespace std;
using namespace glm;
//class that can load a model by taking in a file path and lists of vertex attributes by reference, then modifying
//those attribute lists so that the user will have the model attributes for use after the function call.

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();
	//loads a regular model
	bool LoadOBJ(const char *filePath,
		vector<vec3> &out_vertices,
		vector<vec2> &out_uvs,
		vector<vec3> &out_normals);
	//loads a skinned model (in progress)
	bool LoadSkinned(const char *filePath,
		vector<vec3> &out_vertices,
		vector<vec2> &out_uvs,
		vector<vec3> &out_normals,
		vector<ivec3> &jointIDs,
		vector<vec3> &weights,
		int *boneCount, int *rootBoneIndex, char **rootBoneName, mat4 *rootBoneBind,
		std::vector<Animation*> &animations);
};

